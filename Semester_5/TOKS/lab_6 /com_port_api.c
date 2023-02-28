#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "com_port_api.h"




struct termios * interface_init(const char * const interface_file_path) {

    int interface_fd = open(interface_file_path, O_RDWR);
    
    struct termios * interface_settings = malloc(sizeof(struct termios));

    tcgetattr(interface_fd, interface_settings);

    close(interface_fd);

    return interface_settings;

}

int configure_interface(struct termios * interface, int interface_fd) {

        interface -> c_cflag = (interface -> c_cflag & ~CSIZE) | CS8; 
        
        interface -> c_iflag &= ~IGNBRK;         
        interface -> c_lflag = 0;                             
        interface -> c_oflag = 0;                
        interface -> c_cc[VMIN]  = 0;            
        interface -> c_cc[VTIME] = 5;            
        interface -> c_iflag &= ~(IXON | IXOFF | IXANY); 
        interface -> c_cflag |= (CLOCAL | CREAD);                                        
        interface -> c_cflag &= ~(PARENB | PARODD);
        interface -> c_cflag &= ~CSTOPB;
        interface -> c_cflag &= ~CRTSCTS;


        if (tcsetattr (interface_fd, TCSANOW, interface) != 0) {
    
                return -1;

        }
        return 1;

}


int set_output_interface_speed(speed_t interface_speed, struct termios * interface_config) {

    if(cfsetospeed(interface_config, B110) != 0) {

        perror("set_output_interface_speed(): cfsetospeed ERROR");
        return -1; 

    }

    if(tcsetattr(1, TCSANOW, interface_config) != 0) {

        perror("set_output_interface_speed(): tcsetattr ERROR");
        return -1; 

    }

    return 1;
}

int set_input_interface_speed(speed_t interface_speed, struct termios * interface_config) {

    if(cfsetispeed(interface_config, B110) != 0) {

        perror("set_input_interface_speed(): cfsetispeed ERROR");
        return -1; 

    }

    if(tcsetattr(1, TCSANOW, interface_config) != 0) {

        perror("set_input_interface_speed(): tcsetattr ERROR");
        return -1; 

    }
    return 1;
}


speed_t get_baud_speed(int speed) {

    switch (speed) {

        case 0:
            return B0;

        case 50:
            return B50;

        case 75:
            return B75;

        case 110:
            return B110;

        case 134:
            return B134;

        case 150:
            return B150;

        case 200:
            return B200;
        
        case 300:
            return B300;
        
        case 600:
            return B600;
        
        case 1200:
            return B1200;
        
        case 1800:
            return B1800;
        
        case 2400:
            return B2400;
        
        case 4800:
            return B4800;
        
        case 9600:
            return B9600;
        
        case 19200:
            return B19200;
        
        case 38400:
            return B38400;
        
        case 57600:
            return B57600;
        
        case 1152000:
            return B115200;
        
        case 230400:
            return B230400;
    
        default:
            return B0;
    }
}


int frame_sending(union frame * m_frame, unsigned char start_stop_flag, char * sending_data, int data_size) {

    (m_frame -> data_fields).start_flag = start_stop_flag;
    (m_frame -> data_fields).end_flag   = start_stop_flag;
    unsigned char escape_symbol = (char)27;

    int actuall_position = 0;
    for(int data_index = 0; data_index < data_size; data_index++) {

        if(sending_data[data_index] == start_stop_flag) {

            (m_frame -> data_fields).data[actuall_position] = escape_symbol;
            (m_frame -> data_fields).data[actuall_position] = start_stop_flag;
            actuall_position += 2;

        } else if(sending_data[data_index] == escape_symbol) {

            (m_frame -> data_fields).data[actuall_position] = escape_symbol;
            (m_frame -> data_fields).data[actuall_position] = escape_symbol;
            actuall_position += 2;

        } else {

            (m_frame -> data_fields).data[actuall_position] = sending_data[data_index];
            actuall_position ++;

        }
    }
    return 1;
}

int frame_disassebling(union frame * m_frame, char ss_flag) {

    unsigned char escape_symbol = (char)27;

    for(int index = 0; index < 1024; index++) {

        if(((m_frame -> data_fields).data[index] == escape_symbol) && ((m_frame -> data_fields).data[index + 1] == ss_flag)) {

            printf("%c", (m_frame -> data_fields).data[index + 1]);

            index++;


        } else if(((m_frame -> data_fields).data[index] == escape_symbol) && ((m_frame -> data_fields).data[index + 1] == escape_symbol)) {

            printf("%c", (m_frame -> data_fields).data[index + 1]);

            index++;

        } else {

            printf("%c", (m_frame -> data_fields).data[index]);

        }

    }

}


int str_size(char * str) {

    int string_index = 0;

    while(str[string_index] != '\0') {

        string_index++;

    }
    return string_index;

}

void get_binary_symbol_code(unsigned char symbol, char * buffer, int buffer_size) {

    int i_symbol = (int)symbol;

    int index = 0;

    while(1) {

        buffer[index] = i_symbol % 2;

        i_symbol -= (i_symbol % 2);
        i_symbol /= 2;
        index++;

        if(i_symbol == 0) break;

    }
}

void reverse_array(unsigned char * array, int size) {

    for(int index = 0; index < size / 2; index++) {

        unsigned char temp_symbol = array[index];
        array[index] = array[size - index - 1];
        array[size - index - 1] = temp_symbol;

    }

}

void fill_hamming_buffer(unsigned char * hamming_buffer, int size_h, unsigned char * data_buffer, int size_d) {

    int index_data_buffer = 0;

    for(int index = 0; index < size_h; index++) {

        if(index == 0 || index == 1 || index == 3 || index == 7) {

            hamming_buffer[index] = 0;

        } else {

            hamming_buffer[index] = data_buffer[index_data_buffer];
            index_data_buffer++;

        }
    }
}

void fill_control_bits(unsigned char * buffer, int b_size) {

    for(int bit_number = 1; bit_number < 5; bit_number++) {

        int bit_result = 0;

        if(bit_number == 1) {

            int zero_values = 0;
            int ind_a[] = {0, 2, 4, 6, 8, 10};

            for(int index = 0; index < sizeof(ind_a) / sizeof(int); index++) {

                if(buffer[ind_a[index]] == 1) zero_values++;

            }

            if(zero_values % 2 == 0) {

                buffer[0] = 0;

            } else buffer[0] = 1;

        } else if(bit_number == 2) {

            int zero_values = 0;
            int ind_a[] = {1, 2, 5, 6, 9, 10};

            for(int index = 0; index < sizeof(ind_a) / sizeof(int); index++) {

                if(buffer[ind_a[index]] == 1) zero_values++;

            }

            if(zero_values % 2 == 0) {

                buffer[1] = 0;

            } else buffer[1] = 1;


        } else if(bit_number == 3) {

            int zero_values = 0;
            int ind_a[] = {3, 4, 5, 6, 11};

            for(int index = 0; index < sizeof(ind_a) / sizeof(int); index++) {

                if(buffer[ind_a[index]] == 1) zero_values++;

            }

            if(zero_values % 2 == 0) {

                buffer[3] = 0;

            } else buffer[3] = 1;


        } else if(bit_number == 4) {

            int ind_a[] = {7, 8, 9, 10, 11};
            int zero_values = 0;

            for(int index = 0; index < sizeof(ind_a) / sizeof(int); index++) {

                if(buffer[ind_a[index]] == 1) zero_values++;

            }

            if(zero_values % 2 == 0) {

                buffer[7] = 0;

            } else buffer[7] = 1;
        }
    }
}

bool connect(int socket_fd) {

    union frame * s_frame = malloc(sizeof(union frame));
    memcpy((s_frame -> data_fields).data, SYNCHRON_MESSAGE, sizeof(SYNCHRON_MESSAGE));
    write(socket_fd, s_frame, sizeof(union frame));

    sleep(2);
    while(true) {
        int read_bytes_size = read(socket_fd, s_frame, sizeof(union frame));
        if(read_bytes_size > 0) break;
    }
    printf("%s message\n", (s_frame -> data_fields).data);

    sleep(2);
    memcpy((s_frame -> data_fields).data, ACK_MESSAGE, sizeof(ACK_MESSAGE));
    write(socket_fd, s_frame, sizeof(union frame));
    printf("Successful connection establishment\n");

    free(s_frame);
}

bool accept_connect(int socket_fd) {

    union frame * s_frame = malloc(sizeof(union frame));

    //Waiting for SYN first message
    while(true) {
        int read_bytes_size = read(socket_fd, s_frame, sizeof(union frame));
        if(read_bytes_size > 0) break;
    }
    printf("%s message\n", (s_frame -> data_fields).data);
    sleep(2);

    //Request on the first SYN message
    write(socket_fd, s_frame, sizeof(union frame));

    //Last ACK message
    while(true) {
        int read_bytes_size = read(socket_fd, s_frame, sizeof(union frame));
        if(read_bytes_size > 0) break;
    }
    printf("%s message\n", (s_frame -> data_fields).data);
    printf("Successful connection establishment\n");

    free(s_frame); 
}

int get_str_len(char * str) {
    int len = 0;

    while(str[len] != 0x0) {
        len++;
    }
    return len;
}

void tcp_data_sending(int socket_fd, char * message) {

    int message_len       = get_str_len(message);
    int window_size       = 4;
    int segments_size     = message_len / window_size;
    int last_segment_size = message_len % window_size;
    int actuall_segment   = 0;

    union frame * s_frame = malloc(sizeof(union frame));
    memcpy((s_frame -> data_fields).data, message, message_len);

    while(true) {

        if(actuall_segment != segments_size) {

            for(int i = 0; i < window_size; i++) {
                write(socket_fd, s_frame, sizeof(union frame));
            }

            actuall_segment += 1;
            union frame temp_buffer = {0};
            
            while(true) {

                int read_bytes = read(socket_fd, &temp_buffer, sizeof(union frame));

                if(read_bytes > 0) {
                    printf("%s\n", temp_buffer.data_fields.data);
                    break;
                }
            }

        } else {

            (s_frame -> data_fields).start_flag = 'E';
            write(socket_fd, s_frame, sizeof(union frame));
            break;

        }
    }

}

void tcp_data_recieving(int socket_fd) {

    unsigned char message[1024] = {0};
    union frame * s_frame = malloc(sizeof(union frame));
    int window_size = 4;
    int actuall_mes = 0;
    bool is_save_message = false;

    while(true) {
        int data_bytes_size = read(socket_fd, s_frame, sizeof(union frame));

        if(data_bytes_size > 0) {

            printf("Data package %d recieving\n", actuall_mes);
            actuall_mes += 1;

            if(is_save_message == false) {
                memcpy(message, (s_frame -> data_fields).data, 1024);
                is_save_message = true;
            }

            if(actuall_mes == window_size || (s_frame -> data_fields).start_flag == 'E') {

                if(actuall_mes == window_size) {

                    union frame temp_frame = {0};
                    memcpy(temp_frame.data_fields.data, "ACK OK recieving", sizeof("ACK OK recieving"));
                    write(socket_fd, &temp_frame, sizeof(union frame));
                    actuall_mes = 0;

                    if((s_frame -> data_fields).start_flag == 'E') return;

                } else {

                    union frame temp_frame = {0};
                    memcpy(temp_frame.data_fields.data, "ACK OK recieving", sizeof("ACK OK recieving"));
                    write(socket_fd, &temp_frame, sizeof(union frame));
                    break;

                }
            }
        }
    }
    printf("Message: %s\n", (s_frame -> data_fields).data);
    free(s_frame);
}