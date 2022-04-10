#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Information
{
    char* carrier;
    int value;
    char* valueUom;
    char* name;
    char* author;
};

void remove_enter(struct Information* info, int* amount)
{
    for(int j = 0; j < *amount; j++)
    {
        for(int i = 0; i < 30; i++)
        {
            if(info[j].carrier[i] == '\n')
            {
                for(int k = i; k < 30; k++)
                {
                    info[j].carrier[k] = info[j].carrier[k+1];
                }
            }
        }
    }
                   
    for(int j = 0; j < *amount; j++)
    {
        for(int i = 0; i < 30; i++)
        {
            if(info[j].author[i] == '\n')
            {
                for(int k = i; i < 30; i++)
                {
                    info[j].author[k] = info[j].author[k+1];
                }
            }
        }
    }
    
    for(int j = 0; j < *amount; j++)
    {
        for(int i = 0; i < 30; i++)
        {
            if(info[j].valueUom[i] == '\n')
            {
                for(int k = i; i < 30; i++)
                {
                    info[j].valueUom[k] = info[j].valueUom[k+1];
                }
            }
        }
    }
    
    for(int j = 0; j < *amount; j++)
    {
        for(int i = 0; i < 30; i++)
        {
            if(info[j].name[i] == '\n')
            {
                for(int k = i; i < 30; i++)
                {
                    info[j].name[k] = info[j].name[k+1];
                }
            }
        }
    }
    
}




void print_line()
{
    for(int i = 0; i < 57; i++)
    {
        printf("-");
    }
    printf("\n");
}




int want_to_continue()
{
    int choice;
    
    printf("Do you want to enter? (1 - yes; 2 - no)");
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






void add(struct Information* info, int* amount)
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
    
    
    info = (struct Information*)realloc(info,(*amount + number_to_add)*sizeof(struct Information));
    
    for (int i = *amount; i < *amount + number_to_add; ++i)
    {
        info[i].carrier = (char*)calloc(1,30);
        if (info[i].carrier == NULL)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                free(info[i].carrier);
            }
            printf("Memory is not allocated");
        }
    }
    
    for (int i = *amount; i < *amount + number_to_add; ++i)
    {
        info[i].valueUom = (char*)calloc(1,30);
        if (info[i].valueUom == NULL)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                free(info[i].valueUom);
            }
            printf("Memory is not allocated");
        }
    }
    
    for (int i = *amount; i < *amount + number_to_add; ++i)
    {
        info[i].name = (char*)calloc(1, 30);
        if (info[i].name == NULL)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                free(info[i].name);
            }
            printf("Memory is not allocated");
        }
    }
    
    for (int i = *amount; i < *amount + number_to_add; ++i)
    {
        info[i].author = (char*)calloc(1, 30);
        if (info[i].author == NULL)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                free(info[i].author);
            }
            printf("Memory is not allocated");
        }
    }
    
    int tmp;
    
    for (int i = *amount; i < *amount + number_to_add; i++)
    {
        //printf("i = %d", i);
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
            
            printf("Enter type of Carrier: \n");
            rewind(stdin);
            fgets(info[i].carrier, 30, stdin);
            
            printf("Enter volume of Carrier %d\n", i+1);
            flag = 0;
            do
            {
                rewind (stdin);
                if (flag > 0)
                    printf ("Input correct value");
                flag++;
            } while(!(scanf("%d", &info[i].value)) || info[i].value < 0);

            flag = 0;
            printf("Enter measure unit\n kb - kilobytes\n mb - megabytes\n gb - gigabytes \n");
            while (strcmp(info[i].valueUom,"kb\n") != 0 && strcmp(info[i].valueUom,"mb\n") != 0 && strcmp(info[i].valueUom,"gb\n") != 0)
            {
                rewind(stdin);
                if (flag > 0)
                    printf("Input correct option: \n");
                    flag++;
                fgets(info[i].valueUom, 30, stdin);
            }

            printf("Enter Name of carrier %d\n", i+1);
            rewind(stdin);
            fgets(info[i].name, 30, stdin);
            
            printf("Enter author of %d carrier: \n",i+1);
            rewind(stdin);
            fgets(info[i].author, 30, stdin);
            
            fact_added++;
            tmp = 0;
        }
    }
    
    info = (struct Information*)realloc(info,(*amount + fact_added)*sizeof(struct Information));
    *amount = *amount + fact_added;
    
    remove_enter(info, amount);

}





void show_all (struct Information* info, int* amount)
{
    if(*amount == 0)
    {
        printf("\nThere is no any notes. You can add some..(option 1)");
        return;
    }
    
    char carriers[] = " C A R R I E R S ";
    
    print_line();
    printf("|\t\t\t\t\t %-35s|\n", carriers);
    print_line();
    printf("|\t%-10s|\t%-10s|\t%-5s|\t%-8s|\t%-8s|\n", "Type", "Value", "Uom", "Name", "Author");
    print_line(); print_line();

    for(int i = 0; i < *amount; i++)
    {
        printf("|\t%-10s|\t%-10d|\t%-5s|\t%-8s|\t%-8s|\n", info[i].carrier, info[i].value, info[i].valueUom, info[i].name, info[i].author);
        print_line();
    }
    
}



void delete_particular(struct Information* info, int* amount, int to_del)
{
    for(int i = to_del; i < *amount; i++)
    {
        info[i] = info[i+1];
    }
    *amount = *amount - 1;
    info = (struct Information*)realloc(info, *amount*sizeof(struct Information));
    printf("\nNote %d was deleted!\n\n", to_del);
}


void delete_by_option (struct Information* info, int* amount)
{
    printf("Select option to search:\n1 - By carrier\n2 - By value\n3 - By name\n4 - Author\n5 - Exit\n\nEnter your choice: ");
    int choice, value_to_delete;
    char str[20];
    while (!scanf("%d", &choice) || (choice < 1) || (choice > 5))
    {
        printf("This option doesn't exist\n");
        rewind(stdin);
    }
    printf("\n");
    
    switch (choice)
    {
        case 1:
            printf("Enter Carrier: ");
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
                if(strlen(info[i].carrier) == strlen(str))
                {
                    for(int j = 0; j < strlen(str); j++)
                    {
                        if(info[i].carrier[j] != str[j])
                            break;
                        else
                            temp++;
                        if(temp == strlen(str))
                        {
                            delete_particular(info, amount, i);
                            break;
                        }
                    }
                }
            }
            
            printf("\n%s was deleted.\n\n", str);
            break;
            
        case 2:
            printf("Enter value to delete nonte");
            while (!scanf("%d", &value_to_delete) || (choice < 1))
            {
                printf("Try again\n");
                rewind(stdin);
            }
            printf("\n");
            
            for(int i = 0; i < *amount; i++)
            {
                if(info[i].value == value_to_delete)
                    delete_particular(info, amount, i);
            }
            
            break;
            
        case 3:
            printf("Enter Name: ");
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
                if(strlen(info[i].name) == strlen(str))
                {
                    for(int j = 0; j < strlen(str); j++)
                    {
                        if(info[i].name[j] != str[j])
                            break;
                        else
                            temp++;
                        if(temp == strlen(str))
                        {
                            delete_particular(info, amount, i);
                            break;
                        }
                    }
                }
            }
            
            printf("\n%s was deleted.\n\n", str);
            break;
        
        case 4:
            printf("Enter Author: ");
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
                if(strlen(info[i].author) == strlen(str))
                {
                    for(int j = 0; j < strlen(str); j++)
                    {
                        if(info[i].author[j] != str[j])
                            break;
                        else
                            temp++;
                        if(temp == strlen(str))
                        {
                            delete_particular(info, amount, i);
                            break;
                        }
                    }
                }
            }
            
            printf("\n%s was deleted.\n\n", str);
            break;
            
        case 5:
            return;
            break;
        default:
            break;
    }
    
}

void deleting(struct Information* info, int* amount)
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
            free (info);
            *amount = 0;
            printf("All notes are deleted");
            break;
            
        case 2:
            printf("Enter the number of carrier you want to delete: ");
            while(!(scanf("%d", &to_delete)) || to_delete < 1 || to_delete > *amount)
            {
                printf("Incorrect number. Try again.");
                rewind(stdin);
            }
            to_delete--;
            delete_particular(info, amount, to_delete);
            break;
            
        case 3:
            delete_by_option(info, amount);
            break;
            
        case 4:
            return;
            break;
            
        default:
            break;
    }
    
}

void change(struct Information* info, int* amount)
{
    printf("Enter number of Carrier which option to change: ");
    int note_to_change, choice;
    while(!scanf("%d", &note_to_change) || (note_to_change < 1) || (note_to_change > *amount))
    {
        printf("Input correct number\n");
        rewind(stdin);
    }
    note_to_change--;
    printf("\nChoose the option to change:\n1 - Change carrier\n2 - Change value\n3 - Change name\n4 - Change author\n5 - Exit\n");
    while(!scanf("%d", &choice) || (choice < 1) || (choice > 5))
    {
        printf("Input correct option number\n");
        rewind(stdin);
    }
    
    switch (choice)
    {
        case 1:
            printf("Enter new Carrie:  ");
            rewind(stdin);
            fgets(info[note_to_change].carrier, 20, stdin);
            break;
            
        case 2:
            printf("Enter new Value: ");
            rewind(stdin);
            while(!scanf("%d", &info[note_to_change].value))
            {
                printf("Input right number\n");
                rewind(stdin);
            }
            break;
            
        case 3:
            printf("Enter new Name: ");
            rewind(stdin);
            fgets(info[note_to_change].name, 20, stdin);
            break;
            
        case 4:
            printf("Enter new Author: ");
            rewind(stdin);
            fgets(info[note_to_change].author, 20, stdin);
            break;
            
        case 5:
            return;
            break;
            
        default:
            break;
    }
    remove_enter(info, amount);
}


void print_particular(struct Information* info, int* amount, int to_print)
{
    print_line();
    printf("|\t%-10s|\t%-10d|\t%-5s|\t%-8s|\t%-8s|\n", info[to_print].carrier, info[to_print].value, info[to_print].valueUom, info[to_print].name, info[to_print].author);
    print_line();
}

void search(struct Information* info, int* amount)
{
    
    printf("1 - Search by Carrier\n2 - Search by Value\n3 - Search by Name\n4 - Search by Author\n5 - Exit");
    printf("\nEnter the option to search by: ");
    int choice, temp_value;
    char str[20];
    while(!scanf("%d", &choice) || (choice < 1) || (choice > 5))
    {
        printf("Input correct option number\n");
        rewind(stdin);
    }
    
    switch (choice)
    {
        case 1:
            printf("Enter Carrier: ");
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
                if(strlen(info[i].carrier) == strlen(str))
                {
                    for(int j = 0; j < strlen(str); j++)
                    {
                        if(info[i].carrier[j] != str[j])
                            break;
                        else
                            temp++;
                    }
                }
                
                if(temp == strlen(str))
                {
                    print_particular(info, amount, i);
                }
                
            }
            break;
            
        case 2:
            printf("Enter Value: ");
            while(!scanf("%d", &temp_value))
            {
                printf("Input right number\n");
                rewind(stdin);
            }
            
            for(int i = 0; i < *amount; i++)
            {
                if(temp_value == info[i].value)
                    print_particular(info, amount, i);
            }
            
            break;
            
        case 3:
            printf("Enter Name: ");
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
                if(strlen(info[i].name) == strlen(str))
                {
                    for(int j = 0; j < strlen(str); j++)
                    {
                        if(info[i].name[j] != str[j])
                            break;
                        else
                            temp++;
                    }
                }
                
                if(temp == strlen(str))
                {
                    print_particular(info, amount, i);
                }
                
            }
            
            break;
            
        case 4:
            printf("Enter Author: ");
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
                if(strlen(info[i].author) == strlen(str))
                {
                    for(int j = 0; j < strlen(str); j++)
                    {
                        if(info[i].author[j] != str[j])
                            break;
                        else
                            temp++;
                    }
                }
                
                if(temp == strlen(str))
                {
                    print_particular(info, amount, i);
                }
                
            }
            
            break;
            
        case 5:
            return;
            break;
        
        default:
            break;
    }
    
}

void sort_min_max(struct Information* info, int* amount)
{
    struct Information temp;
    int temp_comp_1, temp_comp_2;
    for(int i = 0; i < *amount; i++)
        for(int j = 0; j < *amount - 1; j++)
        {
            
            if (!strcmp(info[j].valueUom, "mb"))
                temp_comp_1 = info[j].value*1000;
            else if (!strcmp(info[j].valueUom, "gb"))
                temp_comp_1 = info[j].value*1000000;
            else
                temp_comp_1 = info[j].value;
            

            if (!strcmp(info[j+1].valueUom, "mb"))
                temp_comp_2 = info[j+1].value*1000;
            else if (!strcmp(info[j+1].valueUom, "gb"))
                temp_comp_2 = info[j+1].value*1000000;
            else
                temp_comp_2 = info[j+1].value;
            
            
            if(temp_comp_1 > temp_comp_2)
            {
                temp = info[j+1];
                info[j+1] = info[j];
                info[j] = temp;
            }
        }
}

void sort_max_min(struct Information* info, int* amount)
{
    struct Information temp;
    int temp_comp_1, temp_comp_2;
    for(int i = 0; i < *amount; i++)
        for(int j = 0; j < *amount - 1; j++)
        {
            
            if (!strcmp(info[j].valueUom, "mb"))
                temp_comp_1 = info[j].value*1000;
            else if (!strcmp(info[j].valueUom, "gb"))
                temp_comp_1 = info[j].value*1000000;
            else
                temp_comp_1 = info[j].value;
            

            if (!strcmp(info[j+1].valueUom, "mb"))
                temp_comp_2 = info[j+1].value*1000;
            else if (!strcmp(info[j+1].valueUom, "gb"))
                temp_comp_2 = info[j+1].value*1000000;
            else
                temp_comp_2 = info[j+1].value;
            
            
            if(temp_comp_1 < temp_comp_2)
            {
                temp = info[j+1];
                info[j+1] = info[j];
                info[j] = temp;
            }
        }
}




void sort(struct Information* info, int* amount)
{
    printf("\nChoose option to sort by..\n1 - Sort Value from min to max\n2 - Sort Value from max to min\n3 - Exit\nChoose option: ");
    int choice;
    while(!scanf("%d", &choice) || (choice < 1) || (choice > 3))
    {
        printf("Input correct option number\n");
        rewind(stdin);
    }
    
    
    switch (choice)
    {
        case 1:
            sort_min_max(info, amount);
            break;
            
        case 2:
            sort_max_min(info, amount);
            break;
            
        case 3:
            return;
            break;
        default:
            break;
    }
    
}


int menu (struct Information* info, int* amount)
{
    int choice;
    printf("\n\nChoose the operation:\n \n1 - Add Carrier\n2 - Show existing carriers\n3 - Change carrier\n4 - Search by the option\n5 - Sort carriers\n6 - Delete carrier\n7 - Exit\nYour choice: ");
    while(!scanf("%d", &choice) || (choice < 1) || (choice > 7))
    {
        printf("Input correct option number\n");
        rewind(stdin);
    }
    switch(choice)
    {
        case 1:
            add(info, amount);
            break;
        case 2:
            show_all(info, amount);
            break;
        case 3:
            change(info, amount);
            break;
        case 4:
            search(info, amount);
            break;
        case 5:
            sort(info, amount);
            break;
        case 6:
            deleting(info, amount);
            break;
        case 7:
            break;
    }
    return choice;
}



