#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

void* print(void* n);

pthread_mutex_t mutex;
char *str = "thread ->  ";


int main(){
    pthread_t tid[1000];
    int num = 0;
    pthread_mutex_init(&mutex, NULL);

    char c;
    int n = 0;
    while(true){
        fflush(stdin);
        switch(getc(stdin)){
            case '+':
                pthread_create(&tid[num], NULL, print, (void *) num);
                num++;
                break;
            case '-':
                pthread_cancel(tid[num-1]);
                num--;
                break;
            case 'q':
                for(int i = 0; i < num; i++) pthread_cancel(tid[i]);
                return 0;
        }
    }    
    pthread_mutex_destroy(&mutex);
    return 0;
}

void* print(void* n){
    while(1){
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        sleep(0.3);
        pthread_mutex_lock(&mutex); 

        for(int i = 0; i < 11; i++){
            putc(str[i], stdout);   
            usleep(90000);
            fflush(stdout);
        }

        printf("%d", (int*) n);
        putchar('\n');

        pthread_mutex_unlock(&mutex);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
    }
    
    pthread_exit(0);
}