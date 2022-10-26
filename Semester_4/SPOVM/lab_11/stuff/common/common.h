
#pragma once
#define SERVER "SERVER"
#define USERS	"USERS"

#define SINGLE_USER "SINGLE_USER"
#define ALL_USER  "ALL_USER"


#define LOGIN "LOGIN"
#define REGISTER "REGISTER"



#define ALREADY_REG "ALREADY_REG"
#define REG_SUCCEED "REG_SUCCEED"
#define ALREADY_LOGGED "ALREADY_LOGGED"






struct message
{
	char sender[32];
	char receiver[32];
	char cmd[32];
	char data[0];
};

struct Login
{
	char username[16];
	char password[32];
};


struct Register
{
	char username[16];
	char password[32];
};



struct LoginRsp
{
	int32_t errcode;
	char errinfo[100];
};


struct RegisterRsp
{
	int32_t errcode;
	char errinfo[100];
	char username[16];
};


struct SingleUser
{
	char from[32];
	char to[32];
	char message[100];
};


struct SingleUserRsp
{
	int32_t errcode;
	char errinfo[100];
};


struct AllUser
{
	char from[32];
	char message[100];
};

struct AllUserRsp
{
	int32_t errcode;
	char errinfo[100];
};

#define BUF_SIZE 1024