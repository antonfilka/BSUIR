#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MSGSZ     128
typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;

int term_flg = 1;

void term_handl(int sig) {
	term_flg = 0;
}

union semun arg;


int main() {
	signal(SIGTERM, term_handl);

	int semid;
	semid = semget(10, 3, 0666);

	int res_counter = 0;
	int msqid;
    message_buf  rbuf;

    if ((msqid = msgget(10, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }
  	struct timespec tw = {5,0};
    struct timespec tr;

	struct sembuf sops[3];

	while(term_flg) {	
		nanosleep(&tw, &tr);
		sops[0].sem_num = 2;
		sops[0].sem_op = -1;

		sops[1].sem_num = 0;
		sops[1].sem_op = -1;

		semop(semid, sops, 2);

		if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) >= 0) {
			sops[0].sem_num = 4;
			sops[0].sem_op = 1;
			semop(semid, sops, 1);

			res_counter = semctl(semid, 4, GETVAL);
			printf("\n\nPID: %d\n", getpid());
			printf("consumer %d   %s\n", res_counter, rbuf.mtext);
		}

		sops[0].sem_num = 0;
		sops[0].sem_op = 1;

		sops[1].sem_num = 1;
		sops[1].sem_op = 1;

		semop(semid, sops, 2);

	}

    exit(0);
}
