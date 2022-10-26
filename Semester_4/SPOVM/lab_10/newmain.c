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

#define NUM_OF_FILES 5


struct aiocb aioStructForWrite[NUM_OF_FILES];
struct aiocb aioStructForRead[NUM_OF_FILES];


int main() {




return 0;

}