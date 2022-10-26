#include <stdio.h>
#include <pthread.h>
#include <aio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>

#define FL_COUNT 2

char *files_array[]  = {"1.txt", "2.txt"};
char *res_file = "res.txt";

int fd[COUNT];
char buf[COUNT][BUFSIZ];

pthread_t threads[COUNT];

struct aiocb raio_struct_array[COUNT];
struct aiocb waio_struct_array[COUNT];

void check_read(int i) {
    int temp_fd = raio_struct_array[i].aio_fildes;
    while (true) {
        printf("Reading %d\n", i);
        while (aio_error(&raio_struct_array[i]) == EINPROGRESS) {
            
        }
        if (aio_return(&raio_struct_array[i]) == -1) {
            exit(1);
        } else {
            printf("read %d\n", i);
            fdatasync(temp_fd);
            close(temp_fd);
            return;
        }
    }
}

void check_write(int i) {
    int temp_fd = waio_struct_array[i].aio_fildes;
    while (true) {
        printf("Writing %d\n", i);
        while (aio_error(&waio_struct_array[i]) == EINPROGRESS) {
            
        }
        if (aio_return(&waio_struct_array[0]) == -1) {
            exit(1);
        } else {
            printf(" %d Written\n", i);
            fdatasync(temp_fd);
            close(temp_fd);
            return;

        }
    }
}

void * read_func(void *arg) {
    int i = *(int *)arg;
    if (aio_read(&raio_struct_array[i]) == -1) {
        perror("Reading error");
        exit(1);
    }
    check_read(i);
}


void * write_func(void *arg) {
    int i = *(int *)arg;
    if (aio_write(&waio_struct_array[i]) == -1) {
        perror("Write error!");
        exit(1);
    }
    check_write(i);
}

void read_struct_init(int count){
    raio_struct_array[count].aio_nbytes = BUFSIZ;
    raio_struct_array[count].aio_fildes = fd[count];
    raio_struct_array[count].aio_offset = 0;
    raio_struct_array[count].aio_buf = buf[count];
};

void write_struct_init(int count, size_t offset){
    waio_struct_array[count].aio_nbytes = strlen(buf[count]);
    waio_struct_array[count].aio_fildes = open(res_file, O_CREAT | O_WRONLY | O_APPEND);
    waio_struct_array[count].aio_offset = (long)offset;
    waio_struct_array[count].aio_buf = buf[count];
}

int main() {
    size_t offset = 0;

    for (int i = 0; i < COUNT; i++) {
        fd[i] = open(files_array[i], O_RDONLY);
        if (fd[i] == -1) {
            perror("Error opening file");
            exit(1);
        }
        memset(&raio_struct_array[i], 0, sizeof(struct aiocb));
        memset(buf[i], 0, BUFSIZ);
    }

    for (int i = 0; i < COUNT; i++) {

        read_struct_init(i);
        pthread_create(&threads[i], NULL, read_func, &i);
        pthread_join(threads[i], NULL);

        write_struct_init(i, offset);
        pthread_create(&threads[i], NULL, write_func, &i);
        pthread_join(threads[i], NULL);

        offset += strlen(buf[i]);
    }

    for (int i = 0; i < COUNT; i++) {
        close(raio_struct_array[i].aio_fildes);
        close(waio_struct_array[i].aio_fildes);
    }
    return 0;
}