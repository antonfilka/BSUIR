#include "libfiletemp.h"

int main(){

    pthread_t pid;
    pthread_create(&pid, NULL, write_file, NULL);    
    init();
    read_file();
    pthread_join(pid, NULL);
    
    return 0;
}

