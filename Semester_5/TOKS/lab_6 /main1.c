#include "com_port_api.h"
#include <string.h>
#include <stdbool.h>

int main(int argc, char ** argv) {

    struct termios * com1 = malloc(sizeof(struct termios));
    int com1_fd           = open("/dev/ttys003", O_RDWR);

    tcgetattr(com1_fd, com1);
    cfsetispeed(com1, B50);
    cfsetospeed(com1, B50);

    int ret_value = configure_interface(com1, com1_fd);
    if(ret_value == -1) {

        printf("error configure_interface() func\n");
        return 1;

    } ////////////////////////////////////////////////////

    unsigned char buffer[1024] = { 0 };
    printf("Enter a message for send: \n");
    fgets(buffer, 1024, stdin);
    
    connect(com1_fd);
    tcp_data_sending(com1_fd, buffer);


}