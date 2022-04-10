#include "Header.h"

int menu()
{
    int menu_choice;
    printf("\nChoose option:\n1 - Add new notes\n2 - Show notes\n3 - Delete notes\n4 - Find particular note\n5 - Create files\n6 - Read the file\n7 - Exit\n\nEnter your choice: ");
    menu_choice = correct_input(7);
    return menu_choice;
}

void adding_notes(struct Animals** animal)
{
    struct Animals* tmp = *animal;
    do
    {
        if (!(*animal = (struct Animals*)calloc(1, sizeof(struct Animals))))
        {
            puts("\nMemory wasn'tvallocated..\n\n");
            return;
        }
        printf("\nEnter animal type: ");
        rewind(stdin);
        fgets((*animal)->type, 20, stdin);
        printf("\nEnter number of animals: ");
        (*animal)->number = input_int();
        printf("\nChoose \n1 to enter Date of arrival or choose \n2 to enter Average length of life: ");
        (*animal)->flag = correct_input(2);
        if ((*animal)->flag == 1)
        {
            printf("\nEnter date of arrival: ");
            rewind(stdin);
            fgets((*animal)->info.date, 15, stdin);
        }
        if ((*animal)->flag == 2)
        {
            printf("\nEnter average length of life: ");
            (*animal)->info.life = input_float();
        }
        no_enter(*animal);
        (*animal)->following = tmp;
        tmp = *animal;
        rewind(stdin);
        printf("\nIf you want to add more notes press 1: ");
        rewind(stdin);
    } while (getchar() == '1');
}

void no_enter(struct Animals* animal)
{
        animal->type[strlen(animal->type) - 1] = '\0';
        if (animal->flag == 1) animal->info.date[strlen(animal->info.date) - 1] = '\0';
        animal = animal->following;
}

int correct_input(int k)
{
    int n; rewind(stdin);
    while (!scanf("%d", &n) || n <= 0 || n > k)
    {
        rewind(stdin); printf("\nTry again\n");
    }
    return n;
}

int input_int()
{
    int n; rewind(stdin);
    while (!scanf("%d", &n) || n <= 0)
    {
        rewind(stdin); printf("Try again\n");
    }
    return n;
}

float input_float()
{
    float n; rewind(stdin);
    while (!scanf("%f", &n) || n <= 0)
    {
        rewind(stdin); printf("Try again\n");
    }
    return n;
}

void show_one_note(struct Animals* animal)
{
    char table[] = "A N I M A L S";
    print_line();
    printf("|\t\t\t\t\t %-51s|\n", table);
    print_line();
    printf("|\t%-5s|\t%-15s|\t%-8s|\t%-13s|\t%-12s|\n", "N", "Type", "Number", "Len of life", "Arrival date");
    print_line();
    int counter = 1;
    if (animal->flag == 1)
    {
        printf("|\t%-5d|\t%-15s|\t%-8d|\t%-13s|\t%-12s|\n",
            counter, animal->type,
            animal->number, "-",
            animal->info.date);
        print_line();
    }
    else
    {
        printf("|\t%-5d|\t%-15s|\t%-8d|\t%-12.2f|\t%-12s|\n",
            counter, animal->type,
               animal->number, animal->info.life,
            "-");
        print_line();
    }
    animal = animal->following;
    counter++;
}

void show_all_notes(struct Animals* animal)
{
    char table[] = "A N I M A L S";
    print_line();
    printf("|\t\t\t\t\t %-51s|\n", table);
    print_line();
    printf("|\t%-5s|\t%-15s|\t%-8s|\t%-13s|\t%-12s|\n", "N", "Type", "Number", "Len of life", "Arrival date");
    print_line();
    int counter = 1;
    do
    {
        if (animal->flag == 1)
        {
            printf("|\t%-5d|\t%-15s|\t%-8d|\t%-13s|\t%-12s|\n", counter, animal->type, animal->number, "-", animal->info.date);
            print_line();
        }
        else
        {
            printf("|\t%-5d|\t%-15s|\t%-8d|\t%-13.2f|\t%-12s|\n", counter, animal->type, animal->number, animal->info.life, "-");
            print_line();
        }
        animal = animal->following;
        counter++;
    }while(animal);
}

void print_line()
{
    for (int i = 0; i < 73; i++)
    {
        printf("%c", '-');
    }
    printf("\n");
}

void delete_note(struct Animals** animal)
{
    int delete_choice = 0;
    show_all_notes(*animal);
    printf("Choose note you want to delete 0 - exit: ");
    delete_choice = input_int();
    if (delete_choice == 0) return;
    delete_choice--;
    struct Animals* tmp1, *tmp2, *tmp3;
    if (delete_choice != 0)
    {
        tmp3 = *animal;
        for (int i = 0; i < delete_choice - 1; i++)  *animal = (*animal)->following;
        tmp1 = *animal;
        *animal = (*animal)->following;
        tmp2 = *animal;
        tmp1->following = tmp2->following;
        *animal = tmp3;
    }
    else
    {
        tmp2 = *animal;
        *animal = (*animal)->following;
    }
    free(tmp2);
}

void create_file(struct Animals* animal)
{
    printf("Which file to create:\n1 - Text file\n2 - Binary file\n3 - Exit\n");
    int create_choice;
    create_choice = correct_input(3);
    switch (create_choice)
    {
    case 1:
        create_txt(animal);
        break;
    case 2:
        create_bin(animal);
        break;
    case 3:
        break;
    }
}

void create_txt(struct Animals* animal)
{
    FILE* f = fopen("/Users/antonfilka/Xcode/Anton_labs_2/Lab_4_var_10/Lab_4_var_10/Animals.txt", "w");
    do
    {
        if (animal->flag == 1)
        {
            fprintf(f, "%d %d %s %s\n", animal->flag, animal->number, animal->info.date, animal->type);
        }
        if (animal->flag == 2)
        {
            fprintf(f, "%d %d %.2f %s\n", animal->flag, animal->number, animal->info.life, animal->type);
        }
        animal = animal->following;
    } while (animal);
    fclose(f);
    printf("Txt file was created\n");
}


void create_bin(struct Animals* animal)
{
    FILE* f = fopen("/Users/antonfilka/Xcode/Anton_labs_2/Lab_4_var_10/Lab_4_var_10/Animals.bin", "wb");
    do
    {
        if (animal->flag == 1)
        {
            fwrite(animal->type, 20, 1, f);
            fwrite(&(animal->flag), sizeof(int), 1, f);
            fwrite(&(animal->number), sizeof(int), 1, f);
            fwrite(animal->info.date, strlen(animal->info.date), 1, f);
        }
        if (animal->flag == 2)
        {
            fwrite(animal->type, 20, 1, f);
            fwrite(&(animal->flag), sizeof(int), 1, f);
            fwrite(&(animal->number), sizeof(int), 1, f);
            fwrite(&(animal->info.life), sizeof(int),1 , f);
            
        }
        animal = animal->following;
    } while (animal);
    fclose(f);
    printf("Bin file was created\n");
}

void reverse (struct Animals** animal)
{
    struct Animals* temp = *animal;
    struct Animals* temp2 = *animal;
    while (temp)
    {
        if (temp->following == NULL)
            *animal = temp;
        temp = temp->following;
    }
    struct Animals* temp3 = *animal;
    while (1)
    {
        temp = temp2;
        while (1)
        {
            if (temp->following == temp3)
            {
                temp3->following = temp;
                temp3 = temp3->following;
                break;
            }
            temp = temp->following;
        }
        if (temp3 == temp2)
        {
            temp3->following = NULL;
            break;
        }
    }
}

void read_file(struct Animals** animal)
{
    printf("Choose type of file:\n1 - Text file\n2 - Binary file\n3 - Exit\n");
    int choice;
    choice = correct_input(3);
    switch (choice)
    {
    case 1:
        read_txt(animal);
        break;
    case 2:
        read_bin(animal);
        break;
    case 3:
        break;
    }
}

void read_txt(struct Animals** animal)
{
    FILE* f = fopen("/Users/antonfilka/Xcode/Anton_labs_2/Lab_4_var_10/Lab_4_var_10/Animals.txt", "r");
    struct Animals* temp = *animal;
    do
    {
        if (feof(f)) break;
        if (!(*animal = (struct Animals*)calloc(1, sizeof(struct Animals))))
        {
            printf("memory wasn't allocated\n");
            return;
        }
        fscanf(f, "%d", &(*animal)->flag);
        fseek(f, 1, SEEK_CUR);
        fscanf(f, "%d", &(*animal)->number);
        fseek(f, 1, SEEK_CUR);
        if ((*animal)->flag == 1)
            fgets((*animal)->info.date, 12, f);
        else
        {
            fscanf(f, "%f", &(*animal)->info.life);
            fseek(f, 1, SEEK_CUR);
        }
        fgets((*animal)->type, 20, f);
        no_enter(*animal);
        (*animal)->following = temp;
        if (feof(f)) break;
        temp = *animal;
    } while (1);
    *animal = (*animal)->following;
    fclose(f);
    printf("\nRead from txt completed\n");
}

void read_bin(struct Animals** animal)
{
    FILE* f = fopen("/Users/antonfilka/Xcode/Anton_labs_2/Lab_4_var_10/Lab_4_var_10/Animals.bin", "rb");
    struct Animals* temp = *animal;
    fpos_t end, pos;
    fseek(f, 0, SEEK_END);
    fgetpos(f, &end);
    rewind(f);
    do
    {
        if (!(*animal = (struct Animals*)calloc(1, sizeof(struct Animals))))
        {
            printf("memory wasn't allocated\n");
            return;
        }
        fgets((*animal)->type, 20, f);
        fseek(f, 1, SEEK_CUR);
        fread(&(*animal)->flag, sizeof(int), 1, f);
        fread(&(*animal)->number, sizeof(int), 1, f);
        if ((*animal)->flag == 1)
        {
            fgets((*animal)->info.date, 11, f);
        }
        else
        {
            fread(&(*animal)->info.life, sizeof(int), 1, f);
        }
        fgetpos(f, &pos);
        (*animal)->following = temp;
        temp = *animal;
        if (pos == end) break;
    } while (1);
    fclose(f);
    printf("\nRead from bin completed\n");
}

void clear_all(struct Animals** animal)
{
    while (*animal != NULL)
    {
        struct Animals* temp;
        temp = *animal;
        *animal = (*animal)->following;
        free(temp);
    }
}

void search(struct Animals* animal)
{
    printf("Select option to search:\n");
    printf("1 - Type\n");
    printf("2 - number \n");
    printf("3 - Arrival date\n");
    printf("4 - Length of life\n");
    printf("5 - Exit\n");
    int choice, intToSearch = 0, flag = 0;
    float floatToSearch = 0;
    char str[20];
    choice = correct_input(5);
    switch (choice)
    {
    case 1:
        printf("Enter type: ");
        rewind(stdin);
        fgets(str, 20, stdin);
        str[strlen(str) - 1] = '\0';
        do
        {
            int temp = 0;
            if (strlen(animal->type) == strlen(str))
            {
                for (int j = 0; j < strlen(str); j++)
                {
                    if (animal->type[j] != str[j])
                        break;
                    else
                        temp++;
                    if (temp == strlen(str))
                        show_one_note(animal);
                    flag = 1;
                }
            }
            animal = animal->following;
        }while (animal);
        break;
    case 2:
        printf("Enter number: ");
            intToSearch = input_int();
        do
        {
            if (animal->number == intToSearch)
            {
                show_one_note(animal);
                flag = 1;
                break;
            }
            animal = animal->following;
        } while (animal);
        break;
    case 3:
        printf("Enter arrival date: ");
        rewind(stdin);
        fgets(str, 15, stdin);
        rewind(stdin);
        str[strlen(str) - 1] = '\0';
        do
        {
            if (animal->flag != 1)
            {
                animal = animal->following;
                continue;
            }
            int temp = 0;
            if (strlen(animal->info.date) == strlen(str))
            {
                for (int j = 0; j < strlen(str); j++)
                {
                    if (animal->info.date[j] != str[j])
                        break;
                    else
                        temp++;
                    if (temp == strlen(str))
                        show_one_note(animal);
                    flag = 1;
                }
            }
            animal = animal->following;
        } while (animal);
        break;
    case 4:
        printf("Enter length of life: ");
        floatToSearch = input_float();
        do
        {
            if (animal->flag != 2)
            {
                animal = animal->following;
                continue;
            }
            if (animal->info.life == floatToSearch)
            {
                show_one_note(animal);
                flag = 1;
                break;
            }
            animal = animal->following;
        } while (animal);
        break;
    case 5:
        return;
        break;
    }
    if (flag == 0) printf("Nothing found...Try again.\n");
}




