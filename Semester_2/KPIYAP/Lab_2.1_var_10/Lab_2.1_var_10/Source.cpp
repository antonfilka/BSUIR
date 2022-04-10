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
    char* type;
    union Info info;
};


void remove_enter(struct Animals* animal, int* amount)
{
    for(int j = 0; j < *amount; j++)
    {
        for(int i = 0; i < 30; i++)
        {
            if(animal[j].type[i] == '\n')
            {
                for(int k = i; k < 30; k++)
                {
                    animal[j].type[k] = animal[j].type[k+1];
                }
            }
        }
    }
                   
    for(int j = 0; j < *amount; j++)
    {
        for(int i = 0; i < 15; i++)
        {
            if(animal[j].info.date[i] == '\n')
            {
                for(int k = i; i < 15; i++)
                {
                    animal[j].info.date[k] = animal[j].info.date[k+1];
                }
            }
        }
    }
}


void print_line()
{
    for(int i = 0; i < 67; i++)
    {
        printf("-");
    }
    printf("\n");
}

int option_menu(int* option)
{
    printf("\nChoose the option t work with:\n1 - Work with arraving date\n2 - Work with average length of live\n3 - Exit\n");
    while(!scanf("%d", &*option) || (*option < 1) || (*option > 3))
    {
        printf("Input correct option number\n");
        rewind(stdin);
    }
    return *option;
}


int want_to_continue()
{
    int choice;
    
    printf("\nDo you want to enter? (1 - yes; 2 - no)   ");
    while(!scanf("%d", &choice) || (choice < 1) || (choice > 2))
    {
        printf("Input correct option number\n");
        rewind(stdin);
    }
    if (choice == 1)
        return 1;
    else
        return 5;
}



//void add(struct Animals* animal, int* amount, int* option)
//{
//    int number_to_add, fact_added = 0;
//    printf("Enter amount of notes to add: ");
//
//    int flag = 0;
//    do
//    {
//        rewind (stdin);
//        if (flag > 0)
//            printf ("Input correct value");
//        flag++;
//    } while(!(scanf("%d", &number_to_add)) || number_to_add < 1);
//
//
//    if(*amount != 0)
//        animal = (struct Animals*)realloc(animal,(*amount + number_to_add)*sizeof(struct Animals));
//    else
//        animal = (struct Animals*)calloc((*amount + number_to_add),sizeof(struct Animals));
//
//    for (int i = *amount; i < *amount + number_to_add; ++i)
//    {
//        animal[i].type = (char*)calloc(1,30);
//        if (animal[i].type == NULL)
//        {
//            for (int j = i - 1; j >= 0; --j)
//            {
//                free(animal[i].type);
//            }
//            printf("Memory is not allocated");
//        }
//    }
//
//    int tmp;
//
//    for (int i = *amount; i < *amount + number_to_add; i++)
//    {
//        tmp = want_to_continue();
//        if (tmp != 1)
//            break;
//        while(tmp)
//        {
//            if (tmp != 1)
//            {
//                tmp = 0;
//                break;
//            }
//
//            int flag = 0;
//
//            printf("Enter type of animal: \n");
//            rewind(stdin);
//            fgets(animal[i].type, 30, stdin);
//
//            printf("Enter number of animals: \n");
//            flag = 0;
//            do
//            {
//                rewind (stdin);
//                if (flag > 0)
//                    printf ("Input correct value");
//                flag++;
//            } while(!(scanf("%d", &animal[i].number)) || animal[i].number < 0);
//
//            if(*option == 1)
//            {
//                printf("Enter date of arrival: \n");
//                rewind(stdin);
//                fgets(animal[i].info.date, 30, stdin);
//            }
//            else
//            {
//                printf("Enter average length of life: \n");
//                flag = 0;
//                do
//                {
//                    rewind (stdin);
//                    if (flag > 0)
//                        printf ("Input correct value");
//                    flag++;
//                } while(!(scanf("%f", &animal[i].info.life)) || animal[i].info.life < 0);
//            }
//
//            fact_added++;
//            tmp = 0;
//        }
//    }
//
//    animal = (struct Animals*)realloc(animal,(*amount + fact_added)*sizeof(struct Animals));
//    *amount = *amount + fact_added;
//
//    remove_enter(animal, amount);
//
//}

struct Animals* add(struct Animals* animal, int* amount, int* option)
{
    int number_to_add, fact_added = 0;
    printf("Enter amount of notes to add: ");
    
    int flag = 0;
    do
    {
        rewind (stdin);
        if (flag > 0)
            printf ("Input correct value");
        flag++;
    } while(!(scanf("%d", &number_to_add)) || number_to_add < 1);
    
    
    if(*amount != 0)
        animal = (struct Animals*)realloc(animal,(*amount + number_to_add)*sizeof(struct Animals));
    else
        animal = (struct Animals*)calloc((*amount + number_to_add),sizeof(struct Animals));
    
    for (int i = *amount; i < *amount + number_to_add; ++i)
    {
        animal[i].type = (char*)calloc(1,30);
        if (animal[i].type == NULL)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                free(animal[i].type);
            }
            printf("Memory is not allocated");
        }
    }
    
    int tmp;
    
    for (int i = *amount; i < *amount + number_to_add; i++)
    {
        tmp = want_to_continue();
        if (tmp != 1)
            break;
        while(tmp)
        {
            if (tmp != 1)
            {
                tmp = 0;
                break;
            }
            
            int flag = 0;
            
            printf("Enter type of animal: \n");
            rewind(stdin);
            fgets(animal[i].type, 30, stdin);
            
            printf("Enter number of animals: \n");
            flag = 0;
            do
            {
                rewind (stdin);
                if (flag > 0)
                    printf ("Input correct value");
                flag++;
            } while(!(scanf("%d", &animal[i].number)) || animal[i].number < 0);

            if(*option == 1)
            {
                printf("Enter date of arrival: \n");
                rewind(stdin);
                fgets(animal[i].info.date, 30, stdin);
            }
            else
            {
                printf("Enter average length of life: \n");
                flag = 0;
                do
                {
                    rewind (stdin);
                    if (flag > 0)
                        printf ("Input correct value");
                    flag++;
                } while(!(scanf("%f", &animal[i].info.life)) || animal[i].info.life < 0);
            }
            
            fact_added++;
            tmp = 0;
        }
    }
    
    animal = (struct Animals*)realloc(animal,(*amount + fact_added)*sizeof(struct Animals));
    *amount = *amount + fact_added;
    
    remove_enter(animal, amount);
    return animal;
}


struct Animals* show_all (struct Animals* animal, int* amount, int* option)
{
    if(*amount == 0)
    {
        printf("\nThere is no any notes. You can add some..(option 1)");
        return 0;
    }
    
    char animals[] = " A N I M A L S ";
    
    print_line();
    printf("|\t\t\t\t\t %-45s|\n", animals);
    print_line();
    printf("|\t%-10s|\t%-10s|\t%-18s|\t%-18s|\n", "Type", "Number", "Arriving date", "Average life");
    print_line(); print_line();

    for(int i = 0; i < *amount; i++)
    {
        if(*option == 1)
            printf("|\t%-10s|\t%-10d|\t%-18s|\t%-18s|\n", animal[i].type, animal[i].number, animal[i].info.date, "-");
        else
            printf("|\t%-10s|\t%-10d|\t%-18s|\t%-18.2f|\n", animal[i].type, animal[i].number, "-", animal[i].info.life);
        print_line();
    }
    return animal;
}

void print_particular(struct Animals* animal, int* amount, int* option, int i)
{
    print_line();
    if(*option == 1)
        printf("|\t%-10s|\t%-10d|\t%-18s|\t%-18s|\n", animal[i].type, animal[i].number, animal[i].info.date, "-");
    else
        printf("|\t%-10s|\t%-10d|\t%-18s|\t%-18f|\n", animal[i].type, animal[i].number, "-", animal[i].info.life);
    print_line();
}

void search(struct Animals* animal, int* amount, int* option)
{
    
    printf("1 - Search by Type\n2 - Search by Number\n3 - Exit");
    printf("\nEnter the option to search by: ");
    int choice, temp_value;
    char str[20];
    while(!scanf("%d", &choice) || (choice < 1) || (choice > 3))
    {
        printf("Input correct option number\n");
        rewind(stdin);
    }
    
    switch (choice)
    {
        case 1:
            printf("Enter Type: ");
            rewind(stdin);
            fgets(str, 20, stdin);
            
            for(int i = 0; i < 20; i++)
            {
                if(str[i] == '\n')
                {
                    for(int k = i; k < 20; k++)
                    {
                        str[k] = str[k+1];
                    }
                }
            }
            
            for(int i = 0; i < *amount; i++)
            {
                int temp = 0;
                if(strlen(animal[i].type) == strlen(str))
                {
                    for(int j = 0; j < strlen(str); j++)
                    {
                        if(animal[i].type[j] != str[j])
                            break;
                        else
                            temp++;
                    }
                }
                
                if(temp == strlen(str))
                {
                    print_particular(animal, amount, option, i);
                }
                
            }
            break;
            
        case 2:
            printf("Enter Number: ");
            while(!scanf("%d", &temp_value))
            {
                printf("Input right number\n");
                rewind(stdin);
            }
            
            for(int i = 0; i < *amount; i++)
            {
                if(temp_value == animal[i].number)
                    print_particular(animal, amount, option, i);
            }
            
            break;
            
        case 3:
            return;
            break;
        
        default:
            break;
    }
    
}

void delete_particular(struct Animals* animal, int* amount, int to_del)
{
    for(int i = to_del; i < *amount; i++)
    {
        animal[i] = animal[i+1];
    }
    *amount = *amount - 1;
    animal = (struct Animals*)realloc(animal, *amount*sizeof(struct Animals));
    printf("\nNote %d was deleted!\n\n", to_del);
}



void delete_by_option (struct Animals* animal, int* amount)
{
    printf("Select option to search:\n1 - By type\n2 - By number\n3 - Exit\n\nEnter your choice: ");
    int choice, value_to_delete;
    char str[20];
    while (!scanf("%d", &choice) || (choice < 1) || (choice > 4))
    {
        printf("This option doesn't exist\n");
        rewind(stdin);
    }
    printf("\n");
    
    switch (choice)
    {
        case 1:
            printf("Enter type: ");
            rewind(stdin);
            fgets(str, 20, stdin);
            
            for(int i = 0; i < 20; i++)
            {
                if(str[i] == '\n')
                {
                    for(int k = i; k < 20; k++)
                    {
                        str[k] = str[k+1];
                    }
                }
            }
            
            for(int i = 0; i < *amount; i++)
            {
                int temp = 0;
                if(strlen(animal[i].type) == strlen(str))
                {
                    for(int j = 0; j < strlen(str); j++)
                    {
                        if(animal[i].type[j] != str[j])
                            break;
                        else
                            temp++;
                        if(temp == strlen(str))
                        {
                            delete_particular(animal, amount, i);
                            break;
                        }
                    }
                }
            }
            
            printf("\n%s was deleted.\n\n", str);
            break;
            
        case 2:
            printf("Enter number to delete note");
            while (!scanf("%d", &value_to_delete) || (choice < 1))
            {
                printf("Try again\n");
                rewind(stdin);
            }
            printf("\n");
            
            for(int i = 0; i < *amount; i++)
            {
                if(animal[i].number == value_to_delete)
                    delete_particular(animal, amount, i);
            }
            break;
        
        case 3:
            return;
            break;
            
        default:
            break;
    }
}


void deleting(struct Animals* animal, int* amount)
{
    int choice;
    printf("\nChoose the option to delete:\n1 - Delete all\n2 - Delete by number of note\n3 - Deleting by option\n4 - Exit\n");
    while (!scanf("%d", &choice) || (choice < 1) || (choice > 4))
    {
        printf("This option doesn't exist\n");
        rewind(stdin);
    }
    printf("\n");
    int to_delete;
    switch (choice)
    {
        case 1:
            free (animal);
            *amount = 0;
            printf("All notes are deleted");
            break;
            
        case 2:
            printf("Enter the number of notte you want to delete: ");
            while(!(scanf("%d", &to_delete)) || to_delete < 1 || to_delete > *amount)
            {
                printf("Incorrect number. Try again.");
                rewind(stdin);
            }
            to_delete--;
            delete_particular(animal, amount, to_delete);
            break;
            
        case 3:
            delete_by_option(animal, amount);
            break;
            
        case 4:
            return;
            break;
            
        default:
            break;
    }
    
}

struct Animals* menu (struct Animals* animal, int* amount, int* option, int* choice)
{
    printf("\n\nChoose the operation:\n \n1 - Add new notes\n2 - Show existing notes\n3 - Search for notes\n4 - Delete notes\n5 - Exit\nYour choice: ");
    while(!scanf("%d", choice) || (*choice < 1) || (*choice > 5))
    {
        printf("Input correct option number\n");
        rewind(stdin);
    }
    switch(*choice)
    {
        case 1:
            animal = add(animal, amount, option);
            break;
        case 2:
            animal = show_all(animal, amount, option);
            break;
        case 3:
            search(animal, amount, option);
            break;
        case 4:
            deleting(animal, amount);
            break;
        case 5:
            break;
    }
    return animal;
}

int start()
{
    int amount = 0, option = 0, exit_2 = 0;
    struct Animals* animal = NULL;
    while(1)
    {
        int exit_1 = option_menu(&option);
        if (exit_1 == 3)
        {
            free(animal);
            return 1;
        }
        while (1)
        {
            animal = menu(animal, &amount, &option, &exit_2);
            
            if(exit_2 == 5)
            {
                break;
            }
        }
        
    }
}

//int start()   
//{
//    int amount = 0, option = 0;
//    struct Animals* animal = (struct Animals*)calloc(1, sizeof(struct Animals));
//    while(1)
//    {
//        int exit_1 = option_menu(&option);
//        while (1)
//        {
//            int exit_2 = menu(animal, &amount, &option);
//            if(exit_2 == 5)
//            {
//                break;
//            }
//        }
//        if (exit_1 == 5)
//        {
//            free(animal);
//            return 1;
//        }
//    }
//}
