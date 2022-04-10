
#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <stdlib.h>
union Info;
struct Animals;
void remove_enter(struct Animals*, int*);
void print_line(void);
int option_menu(int*);
int want_to_continue(void);
struct Animals* add(struct Animals*, int*, int*);
struct Animals* show_all (struct Animals*, int*, int*);
void print_particular(struct Animals*, int*, int*, int);
void search(struct Animals*, int*, int*);
void delete_particular(struct Animals*, int*, int);
void delete_by_option (struct Animals*, int*);
struct Animals* menu (struct Animals*, int*, int*, int*);
int start(void);


#endif
