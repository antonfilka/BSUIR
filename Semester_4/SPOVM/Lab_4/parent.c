#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

pid_t *child_pids;
int number_of_child_pids;

void myAlarm();

int main(){
    system("clear");
    child_pids = NULL;
    number_of_child_pids = 0;

    pid_t tmp;
    char parametr, number_of_child = '\0';
    
    signal(SIGALRM, myAlarm);
    signal(SIGUSR1, SIG_IGN);
    signal(SIGUSR2, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    while(1){
        fflush(stdin);
        scanf("%c", &parametr);

        switch(parametr){
            case '+':
                printf("creating new procces...\n");
                tmp = fork();
                if(tmp){
                    number_of_child_pids++;
                    child_pids = realloc(child_pids, number_of_child_pids * sizeof(pid_t));
                    child_pids[number_of_child_pids-1] = tmp;
                    printf("successful creation, pid: %d\n", tmp);
                }
                else if(tmp == -1) printf("error of creation!\n");
                else execv("child", NULL);
                break;
            case '-':
                printf("killing procces %d...\n", child_pids[number_of_child_pids-1]);
                kill(child_pids[number_of_child_pids-1], SIGTERM);
                number_of_child_pids--;
                child_pids = realloc(child_pids, number_of_child_pids * sizeof(pid_t));
                printf("killing successful\n");
                printf("number of children: %d\n", number_of_child_pids);
                break;
            case 'k':
                printf("killing all children\n");
                while (number_of_child_pids)
                {
                    printf("killing procces %d...\n", child_pids[number_of_child_pids-1]);
                    kill(child_pids[number_of_child_pids-1], SIGTERM);
                    number_of_child_pids--;
                }
                free(child_pids);
                break;
            case 's':
                printf("number of child: ");
                fflush(stdin);
                number_of_child = getc(stdin);
                system("clear");

                if(number_of_child != '\n') kill(child_pids[(number_of_child-'0')], SIGUSR1);
                else for(int i = 0; i < number_of_child_pids; i++) kill(child_pids[i], SIGUSR1);
                
                break;
            case 'g':
                alarm(0);
                printf("number of child: ");
                fflush(stdin);
                number_of_child = getc(stdin);
                system("clear");
                
                if(number_of_child != '\n'){
                    printf("%d", number_of_child-'0');
                    kill(child_pids[(number_of_child-'0')], SIGUSR2);
                } 
                else for(int i = 0; i < number_of_child_pids; i++) kill(child_pids[i], SIGUSR2);

                break;
            case 'p':
                do{
                    printf("number of child: ");
                    fflush(stdin);
                    number_of_child = getc(stdin);
                    system("clear");
                }while(number_of_child == '\n');
                
                
                kill(child_pids[(number_of_child-'0')], SIGINT);
                for(int i = 0; i < number_of_child_pids; i++) kill(child_pids[i], SIGUSR1);
                alarm(5);
                break;
            case 'q':
                printf("killing all children\n");
                while (number_of_child_pids)
                {
                    printf("killing procces %d...\n", child_pids[number_of_child_pids-1]);
                    kill(child_pids[number_of_child_pids-1], SIGTERM);
                    number_of_child_pids--;
                }
                free(child_pids);
                return 0;
                break;
        }
    }
    return 0;
}

void myAlarm(){
    for(int i = 0; i < number_of_child_pids; i++) kill(child_pids[i], SIGUSR2);
}