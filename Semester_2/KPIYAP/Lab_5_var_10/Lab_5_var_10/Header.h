struct Animals {
    int id;
    char animalName[20];
    int number;
    int flag;
    union extraInfo {
        char arrivalDate[30];
        float averageLife;
    }info;
    struct Animals* adress;
};

int menu(void);
void push(struct Animals** head, struct Animals** tale);
void line(void);
void tableHat(void);
void tabulation(struct Animals* s);
int convertInteger(int idElement);
int convertFloat(float idElement);
int convertChar(char stringElement[30]);
void show(struct Animals* s);
void del(struct Animals** head, struct Animals** tale);
void paricletSearch(struct Animals* s);
void convertToChar(struct Animals* s, int choice);
void writeToFile(struct Animals* s);
void writeToBinFile(struct Animals* s);
void writeToTextFile(struct Animals* s);
void reading(struct Animals** head, struct Animals** tale);
void readFromTextFile(struct Animals** head, struct Animals** tale);
void readFromBinFile(struct Animals** head, struct Animals ** tale);
void freshStack(struct Animals** head, struct Animals ** tale);


