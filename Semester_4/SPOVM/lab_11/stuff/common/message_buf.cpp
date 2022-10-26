#include "message_buf.h"



// inline void add_msg(const char* p, size_t len) {
// 	msgchain_push(&head, p, len);
// }
// inline uint32_t get_header(int header_size) {
// 	return msgchain_getheader(&head, header_size);
// }
// inline uint32_t get_msg(char* pbuffer, int len) {
// 	return msgchain_getmsg(&head, pbuffer, len);
// }

message_buf::message_buf()
{
	msgchain_init(&head);
}

message_buf::~message_buf()
{
	msgchain_reset(&head);
}

void message_buf::add_msg(const char* p, size_t len)
{
	msgchain_push(&head, p, len);
}

uint32_t message_buf::get_header(int header_size)
{
	return msgchain_getheader(&head, header_size);
}

uint32_t message_buf::get_msg(char* pbuffer, int len)
{
	return msgchain_getmsg(&head, pbuffer, len);
}

void message_buf::msgchain_init(message_chain* head) {
	memset(head, 0, sizeof(message_chain));
	head->next = head->prev = head;
	head->total_len = 0;
}

void message_buf::msgchain_reset(message_chain* head) {
	message_chain* current = head->next;
	while (current != head)
	{
		if (current->data != nullptr)
			delete current->data;
		message_chain* temp = current;
		current = current->next;
		delete temp;
	}
	msgchain_init(head);
}

void message_buf::msgchain_push(message_chain* head, const char* p, size_t len) {
	message_chain* m = new message_chain;
	char* b = new char[len];
	memcpy(b, p, len);
	m->data = b;
	m->len = len;
	m->offset = 0;
	message_chain* tail = head->prev;
	m->prev = tail;
	m->next = tail->next;

	tail->next = m;
	head->prev = m;
	head->total_len += len;
}


message_chain* message_buf::msgchain_delete(message_chain* head, message_chain* chain) {
	message_chain* prev = chain->prev;
	chain->prev->next = chain->next;
	chain->next->prev = chain->prev;

	delete chain->data;
	delete chain;
	return prev;
}


uint32_t message_buf::msgchain_getmsg(message_chain* head, char* pbuffer, int len) {
	int obatained = 0;
	if (head->total_len < len)
		return obatained;
	message_chain* current = head->next;
	for (;;)
	{
		int size = current->len - current->offset;
		if (len < size) {
			memcpy(pbuffer + obatained, current->data + current->offset, len);
			current->offset += len;
			obatained += len;
			head->total_len -= len;
			break;
		}
		else if (len == size) {
			memcpy(pbuffer + obatained, current->data + current->offset, len);
			current = msgchain_delete(head, current);
			obatained += len;
			head->total_len -= len;
			break;
		}
		else {
			memcpy(pbuffer + obatained, current->data + current->offset, size);
			current = msgchain_delete(head, current);
			obatained += size;
			head->total_len -= size;
		}
		current = current->next;
		len -= obatained;
	}
	return obatained;
}


int message_buf::msgchain_getheader(message_chain* head, int header_size) {
	uint32_t msglen = 0;
	msgchain_getmsg(head, (char*)& msglen, header_size);
	return msglen;
}
