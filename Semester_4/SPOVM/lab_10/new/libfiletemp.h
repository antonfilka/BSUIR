#include <aio.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <pthread.h>


#define BUFFER_SIZE 1024


bool next_read = true, next_write = false;
struct aiocb *list;
int n = 3, s;
char *buffer, **files;


void end_read(int sig){
    
    next_write = true;

}

void end_write(int sig){
    
    next_read = true;

}

void read_file(){
    for(int i = 0; i < 3; i++) {

        while(!next_read) { }

        next_read = false;
    
        buffer = malloc(BUFFER_SIZE);

        list = malloc(sizeof(struct aiocb));
        
        list -> aio_fildes  = open(files[i], O_RDONLY);
        list -> aio_buf     = (void*)buffer;
        list -> aio_nbytes  = BUFFER_SIZE;
        list -> aio_reqprio = 0;
        list -> aio_offset  = 0;
        list -> aio_sigevent.sigev_notify = SIGEV_SIGNAL;
        list -> aio_sigevent.sigev_signo  = SIGUSR1;
        
        aio_read(list);

    }

}

void* write_file(void *arg){
    int num = n, write_bytes = 0;
    struct aiocb *write_struct;
    int offset = 0;

    while(num > 0) {

        while(!next_write);

        next_write = false;

        write_struct = malloc(sizeof(struct aiocb));
        write_bytes  = 0;
        write_struct -> aio_fildes  = open("out.txt", O_WRONLY | O_CREAT);
        write_struct -> aio_reqprio = 0;
        write_struct -> aio_offset  = 0;
        write_struct -> aio_sigevent.sigev_notify = SIGEV_SIGNAL;
        write_struct -> aio_sigevent.sigev_signo  = SIGUSR2;

        for(int i = 0; i < BUFFER_SIZE; i++) if(buffer[i] != '\0') write_bytes++;
        
        write_struct -> aio_buf    = (void*)buffer;
        write_struct -> aio_nbytes = write_bytes;
        write_struct -> aio_offset = offset;
        
        aio_write(write_struct);
        offset += write_bytes;
        num--;
    }
    
    return NULL;
}

void init(){

    struct sigaction sa;

    files    = malloc(3 * sizeof(char*));
    files[0] = malloc(2*sizeof(char));
    files[1] = malloc(2*sizeof(char));
    files[2] = malloc(2*sizeof(char));
    strcpy(files[0], "1");
    strcpy(files[1], "2");
    strcpy(files[2], "3");

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = end_read;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = end_write;
    sigaction(SIGUSR2, &sa, NULL);
    
}
