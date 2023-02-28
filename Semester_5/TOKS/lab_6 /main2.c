#include "com_port_api.h"


int main(int argc, char ** argv) {

    struct termios * com2 = malloc(sizeof(struct termios));
    int com2_fd           = open("/dev/ttys004", O_RDWR);

    tcgetattr(com2_fd, com2);
    cfsetispeed(com2, B50);
    cfsetospeed(com2, B50);

    int ret_value = configure_interface(com2, com2_fd);
    if(ret_value == -1) {

        printf("error configure_interface() func\n");
        return 1;

    } ////////////////////////////////////////////////////
    

    
    accept_connect(com2_fd);
    tcp_data_recieving(com2_fd);


}