struct Tree
{
    char word[30];
    char translation[30];
    struct Tree* left;
    struct Tree* right;
};

int menu(void);
void add(struct Tree**);
void showMenu(struct Tree*);
void recShow(struct Tree*);
void show(struct Tree*);
void clean(struct Tree**);
struct Tree* delMenu(struct Tree*);
struct Tree* delItem(struct Tree*, char*);
