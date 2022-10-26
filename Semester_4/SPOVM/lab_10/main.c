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
#include <signal.h>

// 1 - first partial read from file ; 2 - second partial read from file ; 3 - third partial read from file
// taking parts are about 1mb of size 

// also 3 structures for writing 

// algorithm: 

//? TRACK OF TIME :  --- 1 ---           --- 2 ---               --- 3 ---

//? TRACK OF TIME :  (1r #1)             (1w #1)                 (1w + offset #4)
//? TRACK OF TIME :  (2r + offset #2)    (2w + offset #2)        (2w + offset #5)
//? TRACK OF TIME :  (3r + offset #3)    (3w + offset #3)        (3w + offset #6)

//? TRACK OF TIME :                      (1r + offset #4)        (1r + offset #7)
//? TRACK OF TIME :                      (2r + offset #5)        (2r + offset #8)
//? TRACK OF TIME :                      (3r + offset #6)        (3r + offset #9)

// in the beggining count total size of all given files to calcute breakpoints for readers and writers
// when first reader ends reading, first free writer begins to write
// there should be a buffer of currently unActive writers to take action to write

// writers going through that breakpoints 

// reading and writing should work silmontaunisly!

// After the reader ends to read it immidiately deligates read data to writer. 
// Write immidiately begins to ewrite corresponding to given offset parameter. 


#define FILES_COUNT 2
#define NUMBER_OF_RW_THREADS 3
#define DEFAULT_READING_SIZE  // 1mb

char *files_array[]  = {"1.txt", "2.txt"};
char *res_file = "res.txt";

int fd[FILES_COUNT ];
char buf[FILES_COUNT ][BUFSIZ];

pthread_t thread_read, thread_write;

struct aiocb aioReaders[NUMBER_OF_RW_THREADS];
struct aiocb aioWriters[NUMBER_OF_RW_THREADS];


void read_struct_init(int count){
    aioReaders[count].aio_nbytes = BUFSIZ;
    aioReaders[count].aio_fildes = fd[count];
    aioReaders[count].aio_offset = 0;
    aioReaders[count].aio_buf = buf[count];
};

void write_struct_init(int count){
    aioWriters[count].aio_nbytes = strlen(buf[count]);
    aioWriters[count].aio_fildes = open(res_file, O_CREAT | O_WRONLY | O_APPEND);
    aioWriters[count].aio_buf = buf[count];
}

// bool end = false;
// bool wrtExit = false;
// bool nextWrite = false, nextRead = true;
// int count = 0;
// int offset = 0;


// void startWrite(int signal){
//     nextWrite = true;
//     (void)signal;
//     printf("read %d \n", count);
    
// }
// void endWrite(int signal){
//     nextRead = true;
//     (void)signal;
//     printf("write %d \n", count);    
// }

// void readF() {
//     while(count < COUNT){
//         while(nextRead == false){
//         nextRead = false;
//         read_struct_init(count);
//         raio_struct_array->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
//         raio_struct_array->aio_sigevent.sigev_signo = SIGUSR1;
//         if(aio_read(&raio_struct_array[count]) == -1){
//             perror("\nAio read error\n");
//             exit(EXIT_FAILURE);
//         }
//         };
        
        
//     }
//     wrtExit = true;
// }

// void writeF() {
//     while(wrtExit == false){
//         while(!nextWrite){
//         nextWrite = false;
//         write_struct_init(count);
//         waio_struct_array->aio_offset = offset;
//         offset += strlen(buf);
//         waio_struct_array->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
//         waio_struct_array->aio_sigevent.sigev_signo = SIGUSR2;

//         if(aio_write(&waio_struct_array)== -1){
//             perror("\nAio write error\n");
//             exit(EXIT_FAILURE);
//         }
//         count++;
//         };
       
        
//     }
// }

int main() {
    signal(SIGUSR1, startWrite);
    signal(SIGUSR2, endWrite);


    int dataSizeRead = 0;
    int totalDataSize = 0;

    int numberOfRWThreads = 3;

    // enter number of reading/writing threads 

    // creating a buffer for temoparary read data multiplied by the number of reading/writing threads 

    // open root dir and count number of files there 
    // get array with all files names 
    // crate an array with offset breakpoints for readers and writers 

    // create a buffer to indecate temporary unactive readers or writers 

    // create a loop starting given number of reading/writing threads 

    // readers starting reading by given offset breakpoints in each thread separatly

    // after any reader becomes unactive it is placed in a buffer as a free reader 
    // if there any unActive writers they receve a job to write 

    // if some readers are unActive it gets the next job (receving new offset param)


    // function useGetNewDataToRead

    // add a clue, to check if it is the end of file, the number of size to read from file that is passing 
    //to reader (in case if fileSize > DEFAULT_READING_SIZE * n), cause the number of bites for reading is gonna be less than an average reding size 

    // making a stream of data taken from files separated with breakpoints 
    // this function receves a signal to give the next portion of data for reader/writer 
    // as a retur value it gives a file descriptor, offset value and number of bites to read 
    // it also checks, if the file was completely read, it closes it 

    // after the portion of data was given to reader, temp var dataSizeRead increases at the given value 
    

    while(dataSizeRead < totalDataSize){
        for (int i = 0; i < numberOfRWThreads; i++ ){
            // walk through array of existing readers and if there is an emty one it receves a job 
            // also marking in a temp var, which size of data has been read 
             for (int j = 0; i < numberOfRWThreads; i++ ){
            // getting the first unActive writer to give him a job 
            }
        }
        

    }
    

    // for (int i = 0; i < COUNT; i++) {
    //     fd[i] = open(files_array[i], O_RDONLY);
    //     if (fd[i] == -1) {
    //         perror("Error while opening file");
    //         exit(1);
    //     }
    //     memset(&aio_struct_array[i], 0, sizeof(struct aiocb));
    //     memset(buf[i], 0, BUFSIZ);
    // }

    // pthread_create(&thread_read, NULL, readF, NULL);
    // pthread_join(thread_read, NULL);
    // pthread_create(&thread_write, NULL, writeF, NULL);
    // pthread_join(thread_write, NULL);

    // for (int i = 0; i < COUNT; i++) {
    //     close(raio_struct_array[i].aio_fildes);
    //     close(waio_struct_array[i].aio_fildes);
    // }

    // closing opened files 


    return 0;
}