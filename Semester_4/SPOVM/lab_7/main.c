#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <sys/sem.h>

pid_t create_child(int child_number, const char* child_path) {
	pid_t new_pid;
	new_pid = fork();
	char* c_arg[2] = {0};	
	char* child_name = (char*)calloc(4, 1);
	c_arg[0] = child_name;

	switch (new_pid) {
		case -1:
			perror("create_child(): fork");
			return -1;
		case 0:
			if (child_number > 50) {
				fprintf(stderr, "create_child(): child_number > 50\n");
				return -1;
			}

			sprintf(child_name, "C_%d", child_number);

			if (execv(child_path, c_arg) == -1) {
				fprintf(stderr, "execve error\n");
				return -1;
			}
			break;
		default:
			break;
	}
	return new_pid;
}

#define CONSUMER_PATH "./consumer"
#define PRODUCER_PATH "./producer"

int c_amount = 0;
int p_amount = 0;
pid_t consumers[50] = {0};
pid_t producers[50] = {0};

int create_producer() {
	producers[p_amount] = create_child(p_amount, PRODUCER_PATH);
	
	if (producers[p_amount] == -1)
		return 1;

	printf("Producer %d: created\n", p_amount);
	p_amount++;
	return 0;
}

int create_consumer() {
	consumers[c_amount] = create_child(c_amount, CONSUMER_PATH);
	
	if (consumers[c_amount] == -1)
		return 1;

	printf("Consumer %d: created\n", c_amount);
	c_amount++;
	return 0;
}

int term_producer() {
	if (p_amount == 0) {
		printf("Producer's amount: 0\n");
		return 0;
	}

	p_amount--;
	kill(producers[p_amount], SIGTERM);
	producers[p_amount] = (pid_t)0;
	printf("Producer %d: deleted\n", p_amount);
	return 0;
}
int term_consumer() {
	if (c_amount == 0) {
		printf("Consumer's amount: 0\n");
		return 0;
	}

	c_amount--;
	kill(consumers[c_amount], SIGTERM);
	consumers[c_amount] = (pid_t)0;
	printf("Consumer %d: deleted\n", c_amount);
	return 0;
}

int term_all() {
	for (int i = 0; i < p_amount; i++)
		kill(producers[i], SIGTERM);

	for (int i = 0; i < c_amount; i++)
		kill(consumers[i], SIGTERM);
		
	c_amount = 0;
	p_amount = 0;
	return 0;
}

union semun arg;

int main() {
	int msgid;
    key_t key=10;
	msgid = msgget(key, IPC_CREAT); 

	int semid;
	semid = semget(key, 5, IPC_CREAT);

	arg.val = 1;
	semctl(semid, 0, SETVAL, arg);  // для контроля поочередного доступа 
	arg.val = 10;
	semctl(semid, 1, SETVAL, arg);  // для контроля переполнения буффера сообщений
	arg.val = 0;
	semctl(semid, 2, SETVAL, arg);     // для контроля наличия сообщений в буффере
	arg.val = 0;
	semctl(semid, 3, SETVAL, arg);    // для id продьюсера
	arg.val = 0;
	semctl(semid, 4, SETVAL, arg);    // для id консьюмера

	char c;	
	do {
		putchar('>');
		c = getchar();
		getchar();
		switch(c) {
			case 'p': 
				if (create_producer())
					c = 0;
				break;
			case 'c': 
				if (create_consumer())
					c = 0;
				break;
			case 'r': 
				term_consumer();
				break;
			case 'd': 
				term_producer();
				break;
			default:
				c = 0;
				break;
		}
	} while(c);
	
	term_all();
	printf("\nTerminated\n");
	return 0;
}
