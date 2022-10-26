// server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <fstream>
#include <assert.h>
#include <vector>
#include "../common/message_buf.h"
#include "../common/common.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct Client
{
	string clientID;
	sockaddr_in clientAddr;
	int addrLen;
};

vector<Client> clients;

int getClientIndex(string usr) {
	vector<Client>::iterator iter = clients.begin();
	for (iter; iter != clients.end(); iter ++)
	{
		if (!iter->clientID.compare(usr))
			return iter - clients.begin();
	}
	return -1;
}


namespace Gernarator {
	char* messageGernarate(string sender, string receiver, string cmd, const char *msgdata, size_t msglen, uint32_t* plen) {
		uint32_t len = sizeof(message) + msglen + sizeof(uint32_t);
		char* buf = new char[len];
		memset(buf, 0, len);
		//len
		memcpy(buf, &len, sizeof(uint32_t));
		//message header
		message* mes = (message *)((char *)buf + sizeof(uint32_t));
		memcpy_s(mes->sender, sizeof(mes->sender), sender.c_str(), sender.length());
		memcpy_s(mes->receiver, sizeof(mes->receiver), receiver.c_str(), receiver.length());
		memcpy_s(mes->cmd, sizeof(mes->cmd), cmd.c_str(), cmd.length());
		//message data
		memcpy(mes->data, msgdata, msglen);
		*plen = len;
		return buf;
	}

	char* addMessageHeader(const char* msgdata, size_t msglen, uint32_t* plen) {
		uint32_t len = msglen + sizeof(uint32_t);
		char* buf = new char[len];
		memset(buf, 0, len);
		//len
		memcpy(buf, &len, sizeof(uint32_t));
		//message data
		memcpy(buf + sizeof(uint32_t), msgdata, msglen);
		*plen = len;
		return buf;
	}
}



void addUserList(const char* name, const char* pwd) {
	ofstream osf;
	osf.open("userList.txt", ios::app);
	osf << name << "," << pwd << endl;
	osf.close();
}

bool userInList(const char* name) {
	ifstream ifs;
	ifs.open("userList.txt");
	string ss;
	while (getline(ifs, ss))
	{
		int pos = ss.find(",");
		string clientID = ss.substr(0, pos);
		string cliendPWD = ss.substr(pos + 1, ss.length() - 1);
		if (0 == clientID.compare(name)) {
			ifs.close();
			return true;
		}
	}
	ifs.close();
	return false;
}


int ServerToSingleMessage(string to, string fromusr, const SOCKET fd, sockaddr_in* clientAddr, int addrLen, const char* mes, int len) {
	int clientIndex = getClientIndex(to);
	if (clientIndex == -1) {
		//错误找不到用户,返回一个错误信息
		SingleUserRsp rsp;
		rsp.errcode = -1;
		strcpy_s(rsp.errinfo, ("没有此用户:" + to).c_str());
		uint32_t errlen = 0;
		char* errmes = Gernarator::messageGernarate("SERVER", fromusr, SINGLE_USER, (const char*)&rsp, sizeof(rsp), &errlen);
		sendto(fd, (const char*)errmes, errlen, 0, (const sockaddr*)clientAddr, addrLen);
		delete errmes;
		return 0;
	}

	//把消息转发给目标用户

	uint32_t newlen = 0;
	char* newmes = Gernarator::messageGernarate(USERS, fromusr, SINGLE_USER, (const char*)mes, len, &newlen);
	Client& c = clients[clientIndex];
	int r = sendto(fd, (const char*)newmes, newlen, 0, (const sockaddr*)& c.clientAddr, c.addrLen);
	delete newmes;
	return 0;
}


int ServerToAllMessage(string from, const SOCKET fd, const char* mes, int len) {
	vector<Client>::iterator iter = clients.begin();
	for (iter; iter != clients.end(); iter++){
		//把消息转发给目标用户
		cout << "发送全体消息到:" << iter->clientID << endl;
		uint32_t newlen = 0;
		char* newmes = Gernarator::messageGernarate(USERS, from, ALL_USER, (const char*)mes, len, &newlen);
		int r = sendto(fd, (const char*)newmes, newlen, 0, (const sockaddr*)&iter->clientAddr, iter->addrLen);
		delete newmes;
	}
	return 0;
}

int ProcessClientCMD(message* p_msg, const SOCKET fd, sockaddr_in* clientAddr, int addrLen) {
	string scmd = p_msg->cmd;
	if (!scmd.compare(REGISTER)) {
		string user, pwd;
		Register* reg = (Register*)p_msg->data;
		user = reg->username;
		pwd = reg->password;
		RegisterRsp regrsp;
		if (userInList(user.c_str())) {
			cout << "用户:" << user << "已存在." << endl;
			regrsp.errcode = -1;
			strcpy_s(regrsp.errinfo, sizeof(regrsp.errinfo), "注册失败,用户已存在.");
		}
		else {
			addUserList(user.c_str(), pwd.c_str());
			cout << "用户:" << user << "注册成功." << endl;
			regrsp.errcode = 0;
			strcpy_s(regrsp.errinfo, sizeof(regrsp.errinfo), "注册成功.");
		}

		
		strcpy_s(regrsp.username, sizeof(regrsp.username), reg->username);
		uint32_t len = 0;
		char *mes = Gernarator::messageGernarate("SERVER", user, REGISTER, (const char *)&regrsp, sizeof(regrsp), &len);
		sendto(fd, (const char*)mes, len, 0, (const sockaddr*)clientAddr, addrLen);
		delete mes;

	}
	else if (!scmd.compare(LOGIN)) {
		cout << "LOGIN:" << endl;
		Login* login = (Login*)p_msg->data;
		string user = login->username;
		string pwd = login->password;


		LoginRsp loginrsp;
		loginrsp.errcode = 0;
		strcpy_s(loginrsp.errinfo, sizeof(loginrsp.errinfo), "登录成功.");
		uint32_t len = 0;
		char* mes = Gernarator::messageGernarate("SERVER", user, LOGIN, (const char*)& loginrsp, sizeof(loginrsp), &len);
		sendto(fd, (const char*)mes, len, 0, (const sockaddr*)clientAddr, addrLen);
		delete mes;

		//保存每个登录的用户的信息
		cout << "用户:" << user << " 已加入." << endl;
		Client c;
		memcpy(&c.clientAddr, clientAddr, addrLen);
		c.addrLen = addrLen;
		c.clientID = user;
		clients.push_back(c);
	}
	else {

	}

	return 0;
}

int ProcessToUsersMessage(message* p_msg, const SOCKET fd, sockaddr_in* clientAddr, int addrLen) {
	string scmd = p_msg->cmd;
	if (!scmd.compare(SINGLE_USER)) {
		SingleUser* touser = (SingleUser*)p_msg->data;
		string to = touser->to;
		ServerToSingleMessage(to, USERS, fd, clientAddr, addrLen, (const char*)p_msg->data, sizeof(SingleUser));
	}
	else if (!scmd.compare(ALL_USER)) {
		ServerToAllMessage(USERS, fd, (const char*)p_msg->data, sizeof(AllUser));
	}
	else {

	}
	return 0;
}

void ServerReceiver(const SOCKET fd) {
	sockaddr_in clientAddr;
	int			addrLen = sizeof(clientAddr);

	message_buf recvbuf;
	int hsize = 0;

	while (true) {

		//UDP 直接从客户端接收数据
		char buf[BUF_SIZE] = { 0 };
		int irec = recvfrom(fd, buf, BUF_SIZE, 0, (sockaddr*)&clientAddr, &addrLen);
		if (irec == SOCKET_ERROR) {
			cout << "recvform failed wich code:" << WSAGetLastError() << endl;
			break;
		}

		if (irec == 0)
			continue;

		recvbuf.add_msg(buf, irec);

		if (hsize == 0) {
			hsize = recvbuf.get_header(4);
			if (hsize == 0)
				continue;
		}
		int datalen = hsize - 4;
		char* readbuf = new char[datalen];
		int len = recvbuf.get_msg(readbuf, datalen);
		if (len == 0) {
			continue;
		}


		message* p_msg = (message*)readbuf;

		string receiver = p_msg->receiver;
		if (!receiver.compare(SERVER)) {
			ProcessClientCMD(p_msg, fd, &clientAddr, addrLen);
		}else if (!receiver.compare(USERS)){
			ProcessToUsersMessage(p_msg, fd, &clientAddr, addrLen);
		}
		else {
			cout << "unknow recevier:" << p_msg->receiver << endl;
		}
		hsize = 0;
	}
}

int main()
{
	WSADATA wsa;
	int r = WSAStartup(MAKEWORD(2,2), &wsa);


	SOCKET fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));

	inet_pton(AF_INET, "0.0.0.0", &sin.sin_addr);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);

	r = ::bind(fd, (sockaddr*)&sin, sizeof(sin));
	if (SOCKET_ERROR == r) {
		cout << "bind failed with code:" << WSAGetLastError() << endl;
		return 0;
	}

	ServerReceiver(fd);
	closesocket(fd);
	WSACleanup();
}

