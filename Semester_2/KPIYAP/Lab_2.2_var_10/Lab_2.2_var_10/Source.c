#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
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
};

int menu()
{
    int choice;
    printf("Choose an operation:\n");
    printf("1. Add notes\n");
    printf("2. Show animals\n");
    printf("3. Change animals\n");
    printf("4. Search animals\n");
    printf("5. Sort animals\n");
    printf("6. Delete animals\n");
    printf("7. Exit\n");
    choice = correct_input(7);
    return choice;
}

struct Animals* add(struct Animals* animal, int arraySize, int newArraySize)
{
    if (arraySize - newArraySize == 0)
        animal = (struct Animals*)calloc(arraySize, sizeof(struct Animals));
    else
        animal = (struct Animals*)realloc(animal, arraySize * sizeof(struct Animals));
    for (int i = arraySize - newArraySize; i < arraySize; i++)
    {
        printf("Number of animal: %d\n", i + 1);
        
        printf("Enter type: ");
        rewind(stdin);
        fgets(animal[i].type, 20, stdin);
        rewind(stdin);
        animal[i].type[strlen(animal[i].type) - 1] = '\0';
        
        printf("Enter number: ");
        animal[i].number = input_int();
        
        printf("1 - to enter arrival date : \n");
        printf("2 - to enter length of life :\n");
        animal[i].flag = correct_input(2);
        if (animal[i].flag == 1)
        {
            printf("Enter arrival date: ");
            rewind(stdin);
            fgets(animal[i].info.date, 15, stdin);
            rewind(stdin);
            animal[i].info.date[strlen(animal[i].info.date) - 1] = '\0';
        }
        else
        {
            printf("Enter length of life: ");
            animal[i].info.life = input_float();
        }
    }
    return animal;
}


void show(struct Animals* animal, int arraySize) {
    top();
    for (int i = 0; i < arraySize; i++) {
        print_all(animal, i);
        line();
    }
}


void top() {
    char title[] = "A N I M A L S";
    line();
    printf("|%-28s%-43s|\n", " ", title);
    line();
    printf("|\t%-2s\t|\t%-s\t|\t%-4s\t|\t%-s\t|\t%-s\t|\n", "#", "Type", "Number", "Arriving date", "Length of life");
    line();
}



void line()
{
    for (int i = 0; i < 73; i++)
    {
        printf("%c", '-');
    }
    printf("\n");
}



void print_all(struct Animals* animal, int i) {
    if (animal[i].flag == 1)
        printf("|\t%-2d\t|\t%-7s\t|\t%-7d\t|\t%-13s\t|\t%-4s\t\t\t|\n", i + 1,
               animal[i].type, animal[i].number, animal[i].info.date, "-");
    else printf("|\t%-2d\t|\t%-7s\t|\t%-7d\t|\t%-13s\t|\t%-.2f\t\t\t|\n", i + 1,
                animal[i].type, animal[i].number, "-", animal[i].info.life);
    line();
}



void change(struct Animals* animal, int arraySize)
{
    printf("Choose an operation:\n");
    printf("1. Edit the entire note\n");
    printf("2. Edit part of note\n");
    printf("3. Exit\n");
    int choice = correct_input(3);
    switch (choice)
    {
        case 1:
            change_one_animal(animal, arraySize);
            break;
        case 2:
            partial_change(animal, arraySize);
            break;
        case 3:
            break;
    }
}



void change_one_animal(struct Animals* animal, int arraySize)
{
    printf("Enter animal number\n");
    int animal_number = correct_input(arraySize);
    animal_number--;
    printf("Enter new animal type\n");
    rewind(stdin);
    fgets(animal[animal_number].type,20, stdin);
    rewind(stdin);
    animal[animal_number].type[strlen(animal[animal_number].type) - 1] = '\0';
    printf("Enter new number of animals\n");
    animal[animal_number].number = input_int();
    
    
    if (animal[animal_number].flag == 1)
    {
        printf("Choose the option\n");
        printf("1. Change date of arrival\n");
        printf("2. Change the field with the date of arrival to the legth of life\n");
        int choice = correct_input(2);
        switch (choice)
        {
            case 1:
                printf("Enter a new arrival date\n");
                rewind(stdin);
                fgets(animal[animal_number].info.date, 20, stdin);
                rewind(stdin);
                animal[animal_number].info.date[strlen(animal[animal_number].info.date) - 1] = '\0';
                return;
            case 2:
                printf("Enter the length of life\n");
                animal[animal_number].info.life = input_float();
                animal[animal_number].flag = 2;
                return;
        }
    }
    if (animal[animal_number].flag == 2)
    {
        printf("Choose the option\n");
        printf("1. Change the the length of life\n");
        printf("2. Change the length of life to arrival date\n");
        int choice = correct_input(2);
        switch (choice)
        {
            case 1:
                printf("Enter the length of life\n");
                animal[animal_number].info.life = input_float();
                return;
            case 2:
                printf("Enter new arrival date\n");
                rewind(stdin);
                fgets(animal[animal_number].info.date, 20, stdin);
                rewind(stdin);
                animal[animal_number].info.date[strlen(animal[animal_number].info.date) - 1] = '\0';
                animal[animal_number].flag = 1;
                return;
        }
    }
}


void partial_change(struct Animals* animal, int arraySize)
{
    printf("Enter animal number :\n");
    int animal_number = correct_input(arraySize);
    animal_number--;
    printf("Select an operation : \n");
    printf("1. Change animal name\n");
    printf("2. Change number\n");
    printf("3. Change arrival date\n");
    printf("4. Change the length of life\n");
    int choice = correct_input(4);
    switch (choice)
    {
        case 1:
            printf("Enter new animal type\n");
            rewind(stdin);
            fgets(animal[animal_number].type, 20, stdin);
            rewind(stdin);
            animal[animal_number].type[strlen(animal[animal_number].type) - 1] = '\0';

            break;
        case 2:
            printf("Enter new number\n");
            animal[animal_number].number = input_int();
            break;
        case 3:
            if (animal[animal_number].flag == 1)
            {
                printf("Enter new arrival date\n");
                rewind(stdin);
                fgets(animal[animal_number].info.date,20,stdin);
                rewind(stdin);
                animal[animal_number].info.date[strlen(animal[animal_number].info.date) - 1] = '\0';

            }
            if (animal[animal_number].flag == 2)
            {
                printf("If you change this field,"
                       "you will no longer be able to store information about the length of life\n");
                printf("Do you want to make changes?\n");
                printf("1. No\n");
                printf("2. Yes\n");
                int editChoice = correct_input(2);
                switch (editChoice)
                {
                    case 1:
                        break;
                    case 2:
                        printf("Enter the arrival date\n");
                        rewind(stdin);
                        gets(animal[animal_number].info.date);
                        animal[animal_number].flag = 1;
                }
            }
            break;
        case 4:
            if (animal[animal_number].flag == 2)
            {
                printf("Enter the length of life\n");
                animal[animal_number].info.life = input_float();
            }
            if (animal[animal_number].flag == 1)
            {
                printf("If you change this field,"
                       "you will no longer be able to store information about the date of arrival\n");
                printf("Do you want to make changes?\n");
                printf("1. No\n");
                printf("2. Yes\n");
                int editChoice = correct_input(2);
                switch (editChoice)
                {
                    case 1:
                        break;
                    case 2:
                        printf("Enter the length of life\n");
                        animal[animal_number].info.life = input_float();
                        animal[animal_number].flag = 2;
                }
            }
            break;
    }
}


void search(struct Animals* animal, int arraySize)
{
    printf("Choose an operation:\n");
    printf("1. By the given parameter\n");
    printf("2. Part search\n");
    int choice = correct_input(2);
    switch (choice)
    {
        case 1:
            search_by_parameter(animal, arraySize);
            break;
        case 2:
            search_part(animal, arraySize);
            break;
    }
}
void search_by_parameter(struct Animals* animal, int arraySize)
{
    printf("Choose an operation :\n");
    printf("1. Type\n");
    printf("2. Number\n");
    printf("3. Arrival date\n");
    printf("4. Length of life\n");
    printf("5. Exit\n");
    int choice = correct_input(5);
    switch (choice)
    {
        case 1:
            printf("Enter animal type: ");
            rewind(stdin);
            char name[20];
            fgets(name, 20, stdin);
            rewind(stdin);
            name[strlen(name) - 1] = '\0';
            top();
            for (int i = 0; i < arraySize; ++i)
            {
                if (strcmp(name, animal[i].type) == 0)
                {
                    print_all(animal, i);
                }
            }
            rewind(stdin);
            break;
        case 2:
            printf("Enter the number\n");
            float number = input_float();
            top();
            for (int i = 0; i < arraySize; ++i)
            {
                if (number == animal[i].number)
                {
                    print_all(animal, i);
                }
            }
            break;
        case 3:
            printf("Enter arrival date\n");
            rewind(stdin);
            char arrival_date[20];
            fgets(arrival_date,20, stdin);
            rewind(stdin);
            arrival_date[strlen(arrival_date) - 1] = '\0';
            top();
            for (int i = 0; i < arraySize; ++i)
            {
                if (strcmp(arrival_date, animal[i].info.date) == 0)
                {
                    print_all(animal, i);
                }
            }
            rewind(stdin);
            break;
        case 4:
            printf("Enter the length of life\n");
            int length_of_life = input_int();
            top();
            for (int i = 0; i < arraySize; ++i)
            {
                if (length_of_life == animal[i].info.life)
                {
                    print_all(animal, i);
                }
            }
            break;
        
        case 5:
            break;
    }
}


void search_part(struct Animals* animal, int arraySize)
{
    printf("Select option to search:\n");
    printf("1. Type\n");
    printf("2. Number\n");
    printf("3. Arrival date\n");
    printf("4. Length of life\n");
    printf("5. Exit\n");
    int choice;
    choice = correct_input(5);
    printf("\n");
    switch (choice)
    {
        case 1:
            printf("Enter type: ");
            break;
        case 2:
            printf("Enter Number: ");
            break;
        case 3:
            printf("Enter arrival date: ");
            break;
        case 4:
            printf("Enter length of life: ");
            break;
        case 5:
            break;
    }
    char temp;
    int flag = 0, flag1 = 0;
    rewind(stdin);
    char string1[20], string2[20];
    fgets(string1, 20, stdin);
    rewind(stdin);
    for (int l = 0; l < arraySize; l++)
    {
        switch (choice)
        {
            case 1:
                for (int i = 0; i < 20; i++)
                    string2[i] = animal[l].type[i];
                break;
            case 2:
                sprintf(string2, "%d", animal[l].number);
                break;
            case 3:
                if (animal[l].flag != 1)
                    continue;
                for (int i = 0; i < 20; i++)
                    string2[i] = animal[l].info.date[i];
                break;
            case 4:
                if (animal[l].flag == 1)
                    continue;
                sprintf(string2, "%f", animal[l].info.life);
                break;
        }
        
        int j = 0, i = 0, j1 = 0;
        for ( ; i < strlen(string1); i++)
        {
            while ((string1[i] != '*') && (string1[i] != '\n') && (string1[i] != '\0'))
            {
                temp = string1[i];
                flag1++;
                for (j = j1; j < strlen(string2); j++)
                {
                    if (string2[j] == temp)
                    {
                        flag++;
                        j1 = j;
                        j = (int)strlen(string2);
                    }
                }
                break;
            }
        }
        
        if ((flag == flag1) && (flag1 != 0))
        {
            top();
            print_all(animal, l);
        }
        flag = 0;
        flag1 = 0;
    }
}
struct Animals* del(struct Animals* animal, int* arraySize)
{
    printf("1. Delete by number\n");
    printf("2. Delete by parameter\n");
    printf("3. Exit\n");
    int choice = correct_input(3);
    switch (choice)
    {
        case 1:
            printf("Choose animal to delete:\n");
            int choice_case = input_int();
            animal = delete_animal(animal, arraySize, choice_case);
            break;
        case 2:
            printf("Choose an operation:\n");
            printf("1. Type\n");
            printf("2. Number\n");
            printf("3. Arrival date\n");
            printf("4. Length of life\n");
            choice = correct_input(4);
            switch (choice)
            {
                case 1:
                    printf("Enter animal type: ");
                    rewind(stdin);
                    char type[20];
                    fgets(type, 20, stdin);
                    for (int i = 0; i < *arraySize; ++i)
                    {
                        if (strcmp(type, animal[i].type) == 0)
                        {
                            animal = delete_animal(animal, arraySize, i);
                        }
                    }
                    rewind(stdin);
                    break;
                case 2:
                    printf("Enter the number\n");
                    float number = input_int();
                    for (int i = 0; i < *arraySize; ++i)
                    {
                        if (number == animal[i].number)
                        {
                            animal = delete_animal(animal, arraySize, i);
                        }
                    }
                    break;
                case 3:
                    printf("Enter arrival date\n");
                    rewind(stdin);
                    char arrival_date[20];
                    gets(arrival_date);
                    for (int i = 0; i < *arraySize; ++i)
                    {
                        if (strcmp(arrival_date, animal[i].info.date) == 0)
                        {
                            animal = delete_animal(animal, arraySize, i);
                        }
                    }
                    rewind(stdin);
                    break;
                case 4:
                    printf("Enter the length of life\n");
                    int length_of_life = input_int();
                    for (int i = 0; i < *arraySize; ++i)
                    {
                        if (length_of_life == animal[i].info.life)
                        {
                            animal = delete_animal(animal, arraySize, i);
                        }
                    }
                    break;
            }
            break;
        case 3:
            break;
    }
    return animal;
}


struct Animals* delete_animal(struct Animals* animal, int* arraySize, int num)
{
    printf("Animal '%s' was successfully deleted.\n", animal[num-1].type);
    for (int i = num - 1; i < *arraySize; i++)
    {
        animal[i] = animal[i + 1];
    }
    *arraySize = *arraySize - 1;
    animal = (struct Animals*)realloc(animal, *arraySize * sizeof(struct Animals));
    return animal;
}


void sort(struct Animals* animal, int arraySize)
{
    printf("How to sort:\n");
    printf("1. Ascending order\n");
    printf("2. Descending order\n");
    printf("3. Exit\n");
    int choice=correct_input(3);
    printf("\n");
    switch (choice)
    {
        case 1:
            min_sort(animal, arraySize);
            break;
        case 2:
            max_sort(animal, arraySize);
            break;
        case 3:
            break;
    }
}


void min_sort(struct Animals* animal, int arraySize)
{
    struct Animals temp;
    int choice;
    top();
    for (int i = 0; i < arraySize; i++)
        print_all(animal, i);
    printf("1. Type\n");
    printf("2. Number\n");
    printf("3. Arrival date\n");
    printf("4. Length of life\n");
    printf("5. Exit\n");
    choice = correct_input(5);
    switch (choice)
    {
        case 1:
            for (int i = 0; i < arraySize; i++)
            {
                for (int j = 0; j < arraySize - 1; j++)
                {
                    if (strcmp(animal[j].type, animal[j + 1].type) > 0)
                    {
                        temp = animal[j];
                        animal[j] = animal[j + 1];
                        animal[j + 1] = temp;
                        break;
                    }
                }
            }
            break;
            
        case 2:
            for (int i = 0; i < arraySize; i++)
            {
                for (int j = 0; j < arraySize - 1; j++)
                {
                    if (animal[j].number > animal[j + 1].number)
                    {
                        temp = animal[j];
                        animal[j] = animal[j + 1];
                        animal[j + 1] = temp;
                    }
                }
            }
            break;
            
        case 3:
            for (int i = 0; i < arraySize; i++)
            {
                for (int j = 0; j < arraySize - 1; j++)
                {
                    if (animal[j].flag != 1)
                        continue;
                    if (strcmp(animal[j].info.date, animal[j + 1].info.date) > 0)
                    {
                        temp = animal[j];
                        animal[j] = animal[j + 1];
                        animal[j + 1] = temp;
                        break;
                    }
                }
            }
            
        case 4:
            for (int i = 0; i < arraySize; i++)
            {
                for (int j = 0; j < arraySize - 1; j++)
                {
                    if (animal[j].flag == 1)
                        continue;
                    if (animal[j].info.life > animal[j + 1].info.life)
                    {
                        temp = animal[j];
                        animal[j] = animal[j + 1];
                        animal[j + 1] = temp;
                    }
                }
            }
            break;
        case 5:
            return;
    }
}


void max_sort(struct Animals* animal, int arraySize)
{
    struct Animals temp;
    int choice;
    top();
    for (int i = 0; i < arraySize; i++)
        print_all(animal, i);
    printf("1. Type\n");
    printf("2. Number\n");
    printf("3. Arrival datee\n");
    printf("4. Length of life\n");
    printf("5. Exit\n");
    choice = correct_input(5);
    switch (choice)
    {
        case 1:
            for (int i = 0; i < arraySize; i++)
            {
                for (int j = 0; j < arraySize - 1; j++)
                {
                    if (strcmp(animal[j].type, animal[j + 1].type) < 0)
                    {
                        temp = animal[j];
                        animal[j] = animal[j + 1];
                        animal[j + 1] = temp;
                        break;
                    }
                }
            }
            break;
        case 2:
            for (int i = 0; i < arraySize; i++)
            {
                for (int j = 0; j < arraySize - 1; j++)
                {
                    if (animal[j].number < animal[j + 1].number)
                    {
                        temp = animal[j];
                        animal[j] = animal[j + 1];
                        animal[j + 1] = temp;
                    }
                }
            }
            break;
        case 3:
            for (int i = 0; i < arraySize; i++)
            {
                for (int j = 0; j < arraySize - 1; j++)
                {
                    if (animal[j].flag != 1)
                        continue;
                    if (strcmp(animal[j].info.date, animal[j + 1].info.date) < 0)
                    {
                        temp = animal[j];
                        animal[j] = animal[j + 1];
                        animal[j + 1] = temp;
                        break;
                    }
                }
            }
        case 4:
            for (int i = 0; i < arraySize; i++)
            {
                for (int j = 0; j < arraySize - 1; j++)
                {
                    if (animal[j].flag == 1)
                        continue;
                    if (animal[j].info.life < animal[j + 1].info.life)
                    {
                        temp = animal[j];
                        animal[j] = animal[j + 1];
                        animal[j + 1] = temp;
                    }
                }
            }
            break;
        case 5:
            return;
    }
}


int input_int()
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}


float input_float()
{
    float n;
    while (scanf("%f", &n) != 1 || n <= 0)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}


int correct_input(int k)
{
    int n;
    while (scanf("%d", &n) != 1 || n <= 0 || n > k)
    {
        rewind(stdin);
        printf("Try again\n");
    }
    return n;
}

