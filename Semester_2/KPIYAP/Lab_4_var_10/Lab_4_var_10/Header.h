#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union Info
{
    char date[15];
    float life;
};

struct Animals
{
    int number;
    char type[20];
    union Info info;
    int flag;
    struct Animals* following;
};

int menu(void);
int correct_input(int);
int input_int(void);
float input_float(void);
void print_line(void);
void no_enter(struct Animals*);
void adding_notes(struct Animals**);
void show_one_note(struct Animals*);
void show_all_notes(struct Animals*);
void delete_note(struct Animals**);
void create_file(struct Animals*);
void create_bin(struct Animals*);
void create_txt(struct Animals*);
void reverse (struct Animals**);
void read_file(struct Animals**);
void read_txt(struct Animals**);
void read_bin(struct Animals**);
void clear_all(struct Animals**);
void search(struct Animals*);
