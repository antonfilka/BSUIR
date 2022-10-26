#pragma once
#include <stdint.h>
#include <memory>
struct message_chain
{
	char* data;
	int len;
	int offset;
	message_chain* prev;
	message_chain* next;
	//所有数据大小，只有head节点才有
	size_t total_len;
};
class message_buf
{
public:
	message_buf();
	~message_buf();

public:
	void add_msg(const char* p, size_t len);
	uint32_t get_header(int header_size);
	uint32_t get_msg(char* pbuffer, int len);
private:
	void msgchain_init(message_chain* head);
	void msgchain_reset(message_chain* head);
	void msgchain_push(message_chain* head, const char* p, size_t len);
	message_chain* msgchain_delete(message_chain* head, message_chain* chain);
	uint32_t msgchain_getmsg(message_chain* head, char* pbuffer, int len);
	int msgchain_getheader(message_chain* head, int header_size);
private:
	message_chain head;
};

