#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>

typedef struct {
    char msg_text[128];
    size_t msg_size;
    int index;
} msg_t;

typedef struct {
    int counter; 
    int size;
} count_t;

msg_t *map;
count_t *count;
pthread_mutex_t mutex;
pthread_cond_t condition;

void *messageListener(void *args) {
    int temp_index = 0;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (map->index != temp_index) {

            printf("Message: %s\n", map->msg_text);
            temp_index = map->index;
            count->counter++;
        }
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condition);
    }
}

int main() {
    key_t key;
    int shmid;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);

    int fd = open("./shared.uu", O_RDWR);
    map = mmap(NULL, sizeof(msg_t), PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if(map == MAP_FAILED) perror("mmap failed");
    map->index = 0;
    close(fd);

    FILE *fp = fopen("count.txt", "w");

    fclose(fp);
    if ((key = ftok("count.txt", 'W')) == -1) exit(1);

    if ((shmid = shmget(key, IPC_CREAT)) == -1) exit(1);

    if ((count = shmat(shmid, NULL, 0)) == (void *)-1) exit(1);


    pthread_t listener;
    pthread_create(&listener, NULL, messageListener, NULL);

    pthread_mutex_lock(&mutex);
    count->size++;
    pthread_mutex_unlock(&mutex);

    char text[128];
    while (1) {

        fgets(text, 128, stdin);

        if (text[0] == 'q' && text[1] == '\n') {
            pthread_mutex_destroy(&mutex);
            pthread_cond_destroy(&condition);
            count->size--;
            exit(EXIT_SUCCESS);
        }

        pthread_mutex_lock(&mutex);
        if (count->counter < count->size)  pthread_cond_wait(&condition, &mutex);
        strcpy(map->msg_text, text);
        map->index++;
        count->counter=0;
        pthread_mutex_unlock(&mutex);
    }
}
