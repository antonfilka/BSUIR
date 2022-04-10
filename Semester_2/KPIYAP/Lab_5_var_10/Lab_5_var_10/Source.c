#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int menu() {
    int n;
    printf("1. Add element\n");
    printf("2. Show elements\n");
    printf("3. Delete elements\n");
    printf("4. Find elements\n");
    printf("5. Write to file\n");
    printf("6. Read from file\n");
    printf("7. Close program\n");
    printf("\nEnter the number : ");
    while (!scanf("%d", &n) || n <= 0 || n > 7) {
        printf("We don't have this number in the menu, try again : ");
        rewind(stdin);
    }
    return n;
}
void deleteEnter(struct Animals** n)
{
    for (int i = 0; i < 20; i++) {
        if (((*n)->animalName[i]) == '\n') {
            (*n)->animalName[i] = '\0';
            break;
        }
    }
    if ((*n)->flag == 1) {
        for (int i = 0; i < 30; i++) {
            if ((*n)->info.arrivalDate[i] == '\n') {
                (*n)->info.arrivalDate[i] = '\0';
                break;
            }
        }
    }
}
void push(struct Animals** head, struct Animals** tale)
{
    int isContinue;
    struct Animals* n;
    do
    {
        if (!(n = (struct Animals*)calloc(1, sizeof(struct Animals))))
        {
            puts("Not enough memory");
            return;
        }
        printf("Enter id : ");
        while (!scanf("%d", &(n)->id)) {
            printf("Wrong value, try again : ");
            rewind(stdin);
        }
        printf("Enter animal name : ");
        rewind(stdin);
        fgets((n)->animalName, 20, stdin);
        rewind(stdin);
        printf("Enter number of animals : ");
        while (!scanf("%d", &(n)->number) || (n)->number <= 0) {
            printf("Wrong value, try again : ");
            rewind(stdin);
        }
        printf("What you want to add ?\n");
        printf("1. Date of arrival\n");
        printf("2. Average length of life\n");
        printf("\nEnter the choice : ");
        while (!scanf("%d", &(n)->flag) || (n)->flag < 1 || (n)->flag > 2) {
            printf("Wrong value, try again : ");
            rewind(stdin);
        }
        if ((n)->flag == 1) {
            printf("Enter Date of arrival : ");
            rewind(stdin);
            fgets((n)->info.arrivalDate, 30, stdin);
            rewind(stdin);
        }
        else {
            printf("Enter Average length of life : ");
            while (!scanf("%f", &(n)->info.averageLife) || (n)->info.averageLife < 0 ) {
                printf("Wrong value, try again : ");
                rewind(stdin);
            }
        }
        deleteEnter(&n);
        if (!*head)
            *tale = *head = n;
        else {
            (*tale)->adress = n;
            *tale = n;
        }
        printf("Do you want to continue adding ?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("\nEnter the number : ");
        while (!scanf("%d", &isContinue) || isContinue < 1 || isContinue > 2) {
            rewind(stdin);
        }
    } while (isContinue == 1);
}
void show(struct Animals* s)
{
    if (!s) {
        puts("Stack is empty");
        return;
    }
    tableHat();
    do {
        tabulation(s);
        s = s->adress;
    } while (s);
    printf("|");
    for (int i = 0; i < 80; i++) {
        printf("=");
    }
    printf("|\n");
    int stop;
    printf("If you want to continue, press 0 : ");
    while (!(scanf("%d", &stop)) || stop != 0) {
        printf("\nWrong value, try again : ");
        rewind(stdin);
    }
}
void line() {
    for (int i = 0; i < 80; i++)
        printf("_");
}
void tableHat() {
    printf(" ");
    line();
    printf("\n|%40s%-40s|\n", "A N I M A L S", "");
    printf("|"); line();
    printf("|\n"); printf("|   %-4s|", "#");
    printf("        Name        |");
    printf("  num  |"); printf("     arrival date    |");
    printf("    Av len of life   |\n|=======|");
    for (int i = 0; i < 20; i++)
        printf("=");
    printf("|=======|"); printf("=============================|");
    printf("=============|\n");
}
void tabulation(struct Animals* s) {
    int temp;
    printf("|");
    temp = (7 - convertInteger(s->id));
    if (temp % 2 == 1) {
        for (int j = 0; j < temp / 2 + 1; j++)
            printf(" ");
        printf("%d", s->id);
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        printf("|");
    }
    else {
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        printf("%d", s->id);
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        printf("|");
    }
    temp = (20 - convertChar(s->animalName));
    if (temp % 2 == 1) {
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        for (int j = 0; j < convertChar(s->animalName); j++) {
            printf("%c", s->animalName[j]);
        }
        for (int j = 0; j < temp / 2 + 1; j++)
            printf(" ");
        printf("|");
    }
    else {
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        for (int j = 0; j < convertChar(s->animalName); j++) {
            printf("%c", s->animalName[j]);
        }
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        printf("|");
    }
    temp = (10 - convertFloat(s->number) - 4);
    if (temp % 2 == 1) {
        for (int j = 0; j < temp / 2 + 1; j++)
            printf(" ");
        printf("%.2d", s->number);
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        printf("|");
    }
    else {
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        printf("%.2d", s->number);
        for (int j = 0; j < temp / 2; j++)
            printf(" ");
        printf("|");
    }
    if (s->flag == 1) {
        temp = (29 - convertChar(s->info.arrivalDate));
        if (temp % 2 == 1) {
            for (int j = 0; j < temp / 2; j++)
                printf(" ");
            for (int j = 0; j < convertChar(s->info.arrivalDate); j++) {
                printf("%c", s->info.arrivalDate[j]);
            }
            for (int j = 0; j < temp / 2 + 1; j++)
                printf(" ");
            printf("|");
        }
        else {
            for (int j = 0; j < temp / 2; j++)
                printf(" ");
            for (int j = 0; j < convertChar(s->info.arrivalDate); j++) {
                printf("%c", s->info.arrivalDate[j]);
            }
            for (int j = 0; j < temp / 2; j++)
                printf(" ");
            printf("|");
        }
        printf("    "); printf("---");
        printf("   |\n");
    }
    else {
        for (int j = 0; j < 13; j++)
            printf(" ");
        printf("---");
        for (int j = 0; j < 13; j++)
            printf(" ");
        printf("|");
        temp = (10 - convertFloat(s->info.averageLife) - 3);
        if (temp % 2 == 1) {
            for (int j = 0; j < temp / 2 + 1; j++)
                printf(" ");
            printf("%.3f", s->info.averageLife);
            for (int j = 0; j < temp / 2; j++)
                printf(" ");
            printf("|\n");
        }
        else {
            for (int j = 0; j < temp / 2; j++)
                printf(" ");
            printf("%.3f", s->info.averageLife);
            for (int j = 0; j < temp / 2; j++)
                printf(" ");
            printf("|\n");
        }
    }
    printf("|");
    for (int i = 0; i < 80; i++) {
        printf("=");
    }
    printf("|\n");
}
int convertInteger(int idElement) {
    int n = 1;
    while (idElement >= 10) {
        idElement = idElement / 10;
        n++;
    }
    return n;
}
int convertFloat(float idElement) {
    int n = 1;
    while (idElement >= 10) {
        idElement = idElement / 10;
        n++;
    }
    return n;
}
int convertChar(char stringElement[30]) {
    int n = 0;
    while (stringElement[n] != '\0' && stringElement[n] != '\n') {
        n++;
    }
    return n;
}


void del(struct Animals** head, struct Animals** tale) {
    if (!head) {
        printf("Stack is empty...\n");
        return;
    }
    int choice = 0;
    printf("Enter id of note you want to delete : ");
    while (!scanf("%d", &choice) || (choice < 0)) {
        printf("Wrong value. Try again.\n");
        rewind(stdin);
    }
    struct Animals* tempElement, *previousTempElement;
    if (*tale == *head && choice == (*head) -> id) {
        free(*tale);
        
        *tale = *head;
        return;
    }
    if ((*head)->id == choice) {
        tempElement = *head;
        *head = (*head)->adress;
        free(tempElement);
        return;
    }
    else {
        if ((*head)->adress == NULL) {
            printf("Nothing was found...\n\n");
            return;
        }
        previousTempElement = *head;
        tempElement = (*head)->adress;
    }
    while ((tempElement)->id != choice) {
        if ((tempElement)->adress == NULL) {
            printf("Nothing was found...\n\n");
            return;
        }
        previousTempElement = tempElement;
        tempElement = (tempElement)->adress;
    }
    if (*tale == tempElement) {
        *tale = previousTempElement;
        (*tale)->adress = NULL;
        free(tempElement);
        return;
    }
    else {
        (previousTempElement)->adress = (tempElement)->adress;
        free(tempElement);
    }
}
void paricletSearch(struct Animals* s) {
    if (!s) {
        printf("Stack is empty...\n");
        return;
    }
    printf("Search for...\n");
    printf("1. Animal id\n");
    printf("2. Animal name\n");
    printf("3. Number\n");
    printf("4. Date of arrival\n");
    printf("5. Average length of life\n");
    printf("6. Go back to the menu\n");
    printf("\nEnter the number : ");
    int choice;
    while (!scanf("%d", &choice) || choice < 1 || choice > 6) {
        printf("We don't have this number in the menu, try again : ");
        rewind(stdin);
    }
    switch (choice) {
    case 1:
        printf("Enter particle id of the element. Use * to fill the emptiness between symbols : ");
        convertToChar(s, 1);
        break;
    case 2:
        printf("Enter particle animal name. Use * to fill the emptiness between symbols  : ");
        convertToChar(s, 2);
        break;
    case 3:
        printf("Enter particle number of animals. Use * to fill the emptiness between symbols : ");
        convertToChar(s, 3);
        break;
    case 6:
        return;
    }
}
void convertToChar(struct Animals* s, int choice)
{
    char tempString[30], tempString1[30];
    rewind(stdin);
    fgets(tempString, 30, stdin);
    rewind(stdin);
    for (int i = 0; i < 30; i++) {
        if (tempString[i] == '\n') {
            tempString[i] = '\0';
            break;
        }
    }
    int isFirst = 0;
    do
    {
        switch (choice)
        {
        case 1:
            sprintf(tempString1, "%d", s->id);
            break;
        case 2:
            for (int i = 0; i < 30; i++)
                tempString1[i] = s->animalName[i];
            break;
        case 3:
                sprintf(tempString1, "%d", s->number);
            break;
        case 4:
            for (int i = 0; i < 30; i++)
                tempString1[i] = s->info.arrivalDate[i];
            break;
        case 5:
            sprintf(tempString1, "%f", s->info.averageLife);
            break;
        }
        int charFound = 0, charWrote = 0, startPoint = 0;
        char tempChar;
        for (int i = 0; i < strlen(tempString); i++) {
            if ((tempString[i] != '*') && (tempString[i] != '\0')) {
                tempChar = tempString[i];
                charWrote++;
                for (int j = startPoint; j < strlen(tempString1); j++) {
                    if (tempString1[j] == tempChar) {
                        charFound++;
                        startPoint = j;
                        break;
                    }
                }
            }
        }
        if ((charFound == charWrote) && (charWrote != 0)) {
            if (isFirst == 0) {
                tableHat();
                isFirst++;
            }
            tabulation(s);
            printf("|");
            for (int i = 0; i < 80; i++) {
                printf("=");
            }
            printf("|\n");
        }
        charFound = 0;
        charWrote = 0;
        s = s->adress;
    } while (s);
}
void writeToTextFile(struct Animals* s)
{
    FILE* file;
    file = fopen("/Users/antonfilka/Xcode/Anton_labs_2/Lab_5_var_10/Lab_5_var_10/Animals TXT.txt", "w+");
    int isFirst = 0;
    do {
        if (isFirst == 0)
            isFirst++;
        else fprintf(file, "\n");
        fprintf(file, "%d\n%s\n%d\n%d\n", s->flag, s->animalName, s->id, s->number);
        if (s->flag == 1) {
            fprintf(file, "%s", s->info.arrivalDate);
        }
        else {
            fprintf(file, "%f", s->info.averageLife);
        }
        s = s->adress;
    } while (s);
    fclose(file);
}
void writeToBinFile(struct Animals* s)
{
    FILE* file;
    file = fopen("/Users/antonfilka/Xcode/Anton_labs_2/Lab_5_var_10/Lab_5_var_10/Animals BIN.bin", "w+");
    do
    {
        fwrite(&(s->flag), sizeof(int), 1, file);
        fwrite(s->animalName, strlen(s->animalName), 1, file);
        fwrite(&(s->id), sizeof(int), 1, file);
        fwrite(&(s->number), sizeof(float), 1, file);
        if (s->flag == 1) {
            fwrite(s->info.arrivalDate, strlen(s->info.arrivalDate), 1, file);
        }
        else {
            fwrite(&(s->info.averageLife), sizeof(float), 1, file);
        }
        s = s->adress;
    } while (s);
    fclose(file);
    printf("Successfully written to the file!!!\n");
}
void writeToFile(struct Animals* s) {
    int n;
    printf("In which file you want to write information ?\n");
    printf("1. Animals TXT.txt\n");
    printf("2. Animals BIN.bin");
    while (!(scanf("%d", &n)) || n < 1 || n > 2) {
        printf("Wrong value, try again : ");
        rewind(stdin);
    }
    switch (n) {
    case 1: writeToTextFile(s); break;
    case 2: writeToBinFile(s); break;
    }
}
void reading(struct Animals** head, struct Animals** tale) {
    printf("Choose type of file:\n1)Text file(.txt)\n2)Binary file(.bin)\n");
    int choice;
    while (!scanf("%d", &choice) || (choice < 1) || (choice > 2)) {
        printf("Wrong value. Try again.\n");
        rewind(stdin);
    }
    switch (choice) {
    case 1:
        readFromTextFile(head, tale);
        break;
    case 2:
        readFromBinFile(head, tale);
        break;
    }
}
void readFromTextFile(struct Animals** head, struct Animals** tale) {
    FILE* file = fopen("/Users/antonfilka/Xcode/Anton_labs_2/Lab_5_var_10/Lab_5_var_10/Animals TXT.txt", "r");
    int counter = 0;
    
    do {
        if (counter == 0) {
            if (!(*tale = (struct Animals*)calloc(1, sizeof(struct Animals)))) {
                printf("Not enough memory!\n");
                return;
            }
            *head = *tale;
            counter++;
        }
        else {
            if (!((*tale)->adress = (struct Animals*)calloc(1, sizeof(struct Animals)))) {
                printf("Not enough memory!\n");
                return;
            }
            *tale = (*tale)->adress;
        }
        fscanf(file, "%d", &(*tale)->flag);
        fseek(file, 1, SEEK_CUR);
        fgets((*tale)->animalName, 20, file);
        //(*tale)->vacancyName[strlen((*tale)->vacancyName) - 1] = '\0';
        fscanf(file, "%d", &(*tale)->id);
        fscanf(file, "%d", &(*tale)->number);
        if ((*tale)->flag == 1) {
            fseek(file, 1, SEEK_CUR);
            fgets((*tale)->info.arrivalDate, 30, file);
            //(*tale)->info.additionalRequire[strlen((*tale)->info.additionalRequire) - 1] = '\0';
        }
        else {
            fscanf(file, "%f", &(*tale)->info.averageLife);
        }
        deleteEnter(tale);
        //char checkEnter;
        if (feof(file)) break;
    } while (1);
    fclose(file);
    printf("Info from file is successfully read!\n");
}
void readFromBinFile(struct Animals** head, struct Animals** tale) {
    FILE* file = fopen("/Users/antonfilka/Xcode/Anton_labs_2/Lab_5_var_10/Lab_5_var_10/Animals BIN.bin", "rb");
    int counter = 0;
    struct Animals* temp = NULL;
    do
    {
        fpos_t check;
        if (feof(file)) break;
        if (counter == 0) {
            if (!(*tale = (struct Animals*)calloc(1, sizeof(struct Animals)))) {
                printf("Not enough memory!\n");
                return;
            }
            *head = *tale;
            counter++;
        }
        else {
            if (!((*tale)->adress = (struct Animals*)calloc(1, sizeof(struct Animals)))) {
                printf("Not enough memory!\n");
                return;
            }
            temp = *tale;
            *tale = (*tale)->adress;
        }
        fread(&(*tale)->flag, sizeof(int), 1, file);
        fgetpos(file, &check);
        fgets((*tale)->animalName, 20, file);
        (*tale)->animalName[strlen((*tale)->animalName) - 1] = '\0';
        fseek(file, check + strlen((*tale)->animalName), SEEK_SET);
        fread(&(*tale)->id, sizeof(int), 1, file);
        fread(&(*tale)->number, sizeof(int), 1, file);
        if ((*tale)->flag == 1) {
            fgetpos(file, &check);
            fgets((*tale)->info.arrivalDate, 30, file);
            (*tale)->info.arrivalDate[strlen((*tale)->info.arrivalDate) - 1] = '\0';
            fseek(file, check + strlen((*tale)->info.arrivalDate), SEEK_SET);
        }
        else {
            fread(&(*tale)->info.averageLife, sizeof(float), 1, file);
        }
        if (feof(file)) break;
    } while (1);
    struct Animals * deleteElement;
    deleteElement = *tale;
    *tale = temp;
    free(deleteElement);
    (*tale)->adress = NULL;
    fclose(file);
    printf("Info from file is successfully read!\n");
}
void freshStack(struct Animals** head, struct Animals ** tale) {
    while (*head != NULL)
    {
        struct Animals* temp;
        temp = *head;
        *head = (*head)->adress;
        free(temp);
    }
}


