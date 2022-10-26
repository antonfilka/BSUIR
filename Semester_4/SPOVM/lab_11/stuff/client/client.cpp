// client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include "../common/message_buf.h"
#include "../common/common.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

namespace Gernarator {
	char* messageGernarate(string sender, string receiver, string cmd, const char* msgdata, size_t msglen, uint32_t* plen) {
		uint32_t len = sizeof(message) + msglen + sizeof(uint32_t);
		char* buf = new char[len];
		memset(buf, 0, len);
		//len
		memcpy(buf, &len, sizeof(uint32_t));
		//message header
		message* mes = (message*)((char*)buf + sizeof(uint32_t));
		memcpy_s(mes->sender, sizeof(mes->sender), sender.c_str(), sender.length());
		memcpy_s(mes->receiver, sizeof(mes->receiver), receiver.c_str(), receiver.length());
		memcpy_s(mes->cmd, sizeof(mes->cmd), cmd.c_str(), cmd.length());
		//message data
		memcpy(mes->data, msgdata, msglen);
		*plen = len;
		return buf;
	}
}



int ProcessServerCMD(message* p_msg, const SOCKET fd, sockaddr_in* serverAddr, int addrLen) {
	string cmd = p_msg->cmd;
	if (!cmd.compare(REGISTER)) {
		RegisterRsp* rsp = (RegisterRsp*)p_msg->data;
		cout << "注册结果:" << rsp->errcode << ":" << rsp->errinfo << endl;
	}
	else if (!cmd.compare(LOGIN)) {
		LoginRsp* rsp = (LoginRsp*)p_msg->data;
		cout << "登录结果:" << rsp->errcode << ":" << rsp->errinfo << endl;
	}
	else {

	}
	return 0;
}


int ProcessUsersCMD(message* p_msg, const SOCKET fd, sockaddr_in* serverAddr, int addrLen) {
	string cmd = p_msg->cmd;
	if (!cmd.compare(SINGLE_USER)) {
		SingleUser* msg = (SingleUser*)p_msg->data;
		cout << "来自:" << msg->from << " 的消息:" << msg->message << endl;
	}
	else if (!cmd.compare(ALL_USER)) {
		AllUser* msg = (AllUser*)p_msg->data;
		cout << "来自:" << msg->from << " 的全体消息:" << msg->message << endl;
	}
	else {

	}
	return 0;
}

int main()
{
	WSADATA wsa;
	int r = WSAStartup(MAKEWORD(2, 2), &wsa);


	SOCKET fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	int addLen = sizeof(sin);

	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);

	cout << "1.Login\n2.Register\n3.Exit.\n" << endl;
	string usr, pwd;
	string command;
	cin >> command;

	if (!command.compare("1")) {
		//登录
		cout << "请输入用户名:" << endl;
		cin >> usr;
		cout << "请输入密码:" << endl;
		cin >> pwd;

		Login login;
		strcpy_s(login.username, usr.c_str());
		strcpy_s(login.password, pwd.c_str());
		uint32_t len = 0;
		char* mes = Gernarator::messageGernarate(login.username, SERVER, LOGIN, (const char*)& login, sizeof(Login), &len);
		sendto(fd, mes, len, 0, (sockaddr*)& sin, sizeof(sin));
		delete mes;
	}
	else if (!command.compare("2")) {
		
		cout << "请输入用户名:" << endl;
		cin >> usr;
		cout << "请输入密码:" << endl;
		cin >> pwd;
		Register reg;
		strcpy_s(reg.username, usr.c_str());
		strcpy_s(reg.password, pwd.c_str());

		uint32_t len = 0;
		char* mes = Gernarator::messageGernarate(usr, SERVER, REGISTER, (const char *)&reg, sizeof(reg), &len);
		sendto(fd, mes, len, 0, (sockaddr*)& sin, sizeof(sin));
		delete mes;

	}
	else if (!command.compare("3")) {

	}
	else {
		cout << "unknow command! program exit." << endl;
		return 0;
	}
	message_buf recvbuf;
	int hsize = 0;
	while (true)
	{
		char buf[BUF_SIZE] = { 0 };
		int irec = recvfrom(fd, buf, BUF_SIZE, 0, (sockaddr*)&sin, &addLen);
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

		string sender = p_msg->sender;
		if (!sender.compare(SERVER)) {
			ProcessServerCMD(p_msg, fd, &sin, addLen);
		}
		else if (!sender.compare(USERS)) {
			ProcessUsersCMD(p_msg, fd, &sin, addLen);
		}
		else {
			cout << "unknow sender:" << p_msg->receiver << endl;
		}


		//等待命令
		cout << "1.发给单个用户\t2.发给所有人\t3.什么也不做.\t" << endl;
		string command;
		cin >> command;
		if (!command.compare("1")) {
			cout << "输入用户名和消息:" << endl;
			string towho, tomessage;
			cin >> towho;
			cin >> tomessage;
			SingleUser tusr;
			strcpy_s(tusr.from, usr.c_str());
			strcpy_s(tusr.to, towho.c_str());
			strcpy_s(tusr.message, tomessage.c_str());
			uint32_t len = 0;
			char* mes = Gernarator::messageGernarate(usr, USERS, SINGLE_USER, (const char*)&tusr, sizeof(tusr), &len);
			sendto(fd, mes, len, 0, (sockaddr*)& sin, sizeof(sin));
			delete mes;
		}
		else if (!command.compare("2")) {
			cout << "输入消息:" << endl;
			string tomessage;
			cin >> tomessage;
			AllUser ausr;
			strcpy_s(ausr.from, usr.c_str());
			strcpy_s(ausr.message, tomessage.c_str());
			uint32_t len = 0;
			char* mes = Gernarator::messageGernarate(usr, USERS, ALL_USER, (const char*)& ausr, sizeof(ausr), &len);
			sendto(fd, mes, len, 0, (sockaddr*)& sin, sizeof(sin));
			delete mes;
		}
		else if (!command.compare("3")) {
		}
		else {

		}
		delete readbuf;
		hsize = 0;
	}
	
}

