#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


static const int FIELDS_SEGMENT_SIZE = 1038;
static const char * SYNCHRON_MESSAGE = "SYN";
static const char * ACK_MESSAGE = "ACK";

//Header ether frame with sourse and dest MAC-addr//
typedef struct header{

    unsigned char dest_addr  [6];
    unsigned char source_addr[6];

} header;


typedef union frame {

    struct {

        unsigned char start_flag;
        struct header frame_header;
        unsigned char data[1024];
        unsigned char fcs[4];
        unsigned char end_flag;

    } data_fields;

    unsigned char buffer[1042];

} frame;

typedef struct token_ring_marker {

    int own_marker;


} token_ring_market;

typedef struct full_frame {

    union frame frame_header;
    struct token_ring_marker marker;

} full_frame;



struct termios * interface_init(const char * const interface_file_path);

int set_output_interface_speed(speed_t interface_speed, struct termios * interface_config);

int set_input_interface_speed(speed_t interface_speed, struct termios * interface_config);

speed_t get_baud_speed(int speed);

int configure_interface(struct termios * interface, int interface_fd);

int frame_sending(union frame * m_frame, unsigned char start_stop_flag, char * sending_data, int data_size);

int str_size(char * str);

int frame_disassebling(union frame * m_frame, char ss_flag);

void get_binary_symbol_code(unsigned char symbol, char * buffer, int buffer_size);

void reverse_array(unsigned char * array, int size);

void fill_hamming_buffer(unsigned char * hamming_buffer, int size_h, unsigned char * data_buffer, int size_d);

void fill_control_bits(unsigned char * buffer, int b_size);

bool connect(int socket_fd);

bool accept_connect(int socket_fd);

void tcp_data_sending(int socket_fd, char * message);

void tcp_data_recieving(int socket_fd);

int get_str_len(char * str);