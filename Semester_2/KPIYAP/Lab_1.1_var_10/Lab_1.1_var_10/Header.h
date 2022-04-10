
#ifndef Header_h
#define Header_h

struct Information;
void remove_enter(struct Information*, int*);
void add(struct Information*, int*);
void show_all(struct Information*, int*);
void delete_particular(struct Information*, int*, int);
void delete_by_option (struct Information*, int*);
void deleting(struct Information*, int*);
void change(struct Information*, int*);
void print_particular(struct Information*, int*, int);
void search(struct Information*, int*);
void sort_min_max(struct Information*, int*);
void sort_max_min(struct Information*, int*);
void sort(struct Information*, int*);
int menu(struct Information* info, int* );


#endif 
