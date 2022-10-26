#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MSGSZ 128

typedef struct msgbuf {
	long mtype;
	char mtext[MSGSZ];
} message_buf;

int term_flg = 1;

void term_handler(int sig) {
	term_flg = 0;
}

union semun arg;

void rand_str(char* str) {

	int size = rand()%50 + 2;

	int i = 0;
	for (i = 0; i < size; i++) {
		str[i] = (char)(rand()%26 + 97);
	}

	str[i+1] = '\0';

}

int main() {
	srand(time(NULL));

	signal(SIGTERM, term_handler);
	int sent_counter = 0;
	
	int semid;
	semid = semget(10, 3, 0666);

	int msqid;
    message_buf sbuf;
    size_t buf_length;

    if ((msqid = msgget(10, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

	struct timespec tw = {5,0};
    struct timespec tr = {3,0};
	

	struct sembuf sops[3];

	
	while (term_flg) {
		nanosleep(&tw, &tr);

		sbuf.mtype = 1;
		rand_str(sbuf.mtext);
		buf_length = strlen(sbuf.mtext) + 1 ;
		
	
		sops[0].sem_num = 1;
		sops[0].sem_op = -1;
		
		sops[1].sem_num = 0;
		sops[1].sem_op = -1;

		
		semop(semid, sops, 2);
		
		if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) == 0) {
			sops[0].sem_num = 3;
			sops[0].sem_op = 1;
			semop(semid, sops, 1);

			sent_counter = semctl(semid, 3, GETVAL);

			printf("\n\nPID: %d\n", getpid());
			printf ("producer %d   %s\n", sent_counter, sbuf.mtext);
		}
			
   
		sops[0].sem_num = 0;
		sops[0].sem_op = 1;
		
		sops[1].sem_num = 2;
		sops[1].sem_op = 1;

		semop(semid, sops, 2);
   
	}

	msgctl(msqid, IPC_RMID, &sbuf);
      
    exit(0);
}
