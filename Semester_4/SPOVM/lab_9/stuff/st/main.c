#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct user{
    char name[20];
    char message[100];
};

static int fd = 0;
struct user chat; 

void *writeMessage(void * arg);
bool isNewMessage(struct user * user1, struct user * user2);

static pthread_mutex_t mutexWrite;

int main() {
    system("clear");

    pthread_t thread;
    struct user empty_user = {""};

    fd = open("./chat.txt", O_RDWR);  
    if (fd < 0) {
        perror("File opened error..");
        exit(EXIT_FAILURE);
    }

    printf("Enter name: ");
    gets(chat.name);

    ftruncate (fd, sizeof(struct user)); 
    void * shared_memory = NULL;
    shared_memory = mmap(0, sizeof(struct user), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); //
    pthread_create(&thread, NULL, writeMessage, shared_memory); 
    struct user temp_user_r;
    while(true) {
        memcpy(&temp_user_r, shared_memory, sizeof(struct user)); 
        if(isNewMessage((struct user *)&chat, (struct user *)&temp_user_r) == true) continue;
        while(!strcmp(temp_user_r.message, "")){
            memcpy(&temp_user_r, shared_memory, sizeof(struct user));
        }
        printf("\n%s: %s\n", temp_user_r.name, temp_user_r.message);  
        memcpy(shared_memory, &empty_user, sizeof(struct user));
    }
}

void *writeMessage(void * arg) {
    while(true) {
     pthread_mutex_lock(&mutexWrite);
     fflush(stdin);
     gets(chat.message);
     memcpy(arg, &chat, sizeof(struct user));
     pthread_mutex_unlock(&mutexWrite);
    }
}

bool isNewMessage(struct user * user1, struct user * user2) {
    if(!strcmp(user2 -> name, "")) return true;
    if(strcmp(user1 -> name, user2 -> name)) return false;
    return true;
}
