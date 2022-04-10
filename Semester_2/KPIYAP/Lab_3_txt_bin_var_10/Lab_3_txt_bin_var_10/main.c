 #include "Header.h"
#include "Source.c"


int functiontxt(char* path)
{
    FILE *f;
    fpos_t n1 = 0, n2 = 0, n3 = 0;
    long i;
    int dl = 0, counter = 0;
    char s, s_buf, st[500];
    strcat(path, ".txt");
    if (!(f = fopen(path, "w+")))
    {
        puts("File cannot be created..");
        return 0;
    }
    printf("\nEnter words: ");
    rewind(stdin);
    fprintf(f, "%s", fgets(st, 500, stdin));
    rewind(f);
    printf("\nSource file  : \n");
    while ((s = getc(f)) != EOF)
          printf("%c", s);
    rewind(f);
    
    while (1)
    {
        while (!feof(f))
        {
            fgetpos(f, &n1);
            fscanf(f, "%c", &s);
            if (s != ' ') break;
        }
        if (feof(f)) break;
        while (!feof(f) && (s != ' ') && (s != '\n'))
        {
            fgetpos(f, &n2);
            fscanf(f, "%c", &s);
        }
        if (n2-n1>dl)
        {
            dl = (int)n2-(int)n1;
            n3 = n1;
        }
        counter++;
    }
    i = dl;
    rewind(f);
    printf("\n\nThe number of worsds is %d", counter);
    printf("\nThe longest word to reverse : ");
    fsetpos(f, &n3);
    while (!feof(f) && i)               // цикл вывода на экран найденного слова
    {
        fscanf(f, "%c", &s);
        printf("%c", s);
        i--;
    }
    printf("\n");
    i = dl;
    n1 = n3; n2 = n1 + dl - 1;
    while(n1 < n2)
    {
        fsetpos(f, &n1);
        fscanf(f, "%c", &s_buf);
        fsetpos(f, &n2);
        fscanf(f, "%c", &s);
        fsetpos(f, &n1);
        fprintf(f, "%c", s);
        fsetpos(f, &n2);
        fprintf(f, "%c", s_buf);
        n1++; n2--;
    }
    rewind(f);
    printf("\nEdited file : \n");
    while ((s = getc(f)) != EOF)
    {
        if (s == '\r') s = '\n';
        printf("%c", s);
    }
    printf("\n\n");
    fclose(f);
    path[strlen(path) - 4] = '\0';
    return 1;
}

int functionbin(char* path)
{
    FILE *f;
    int input_number, output_number, i1, i2, counter = 0, number_id = 0, min_value = 0;
    fpos_t pos1 = 1, pos2 = 0;
    strcat(path, ".bin");
    if (!(f = fopen(path, "w+b")))
    {
        puts("File cannot be created..");
        return 0;
    }
    printf("\nEnter numbers: (999 to exit)\n");
    rewind(f);
    while(1)
    {
        rewind(stdin);
        scanf("%d", &input_number);
        if(input_number == 999) break;
        fwrite(&input_number, sizeof(int), 1, f);
        counter++;
    }
    printf("\n\nSource file: ");
    rewind(f);
    do
    {
        fread(&output_number, sizeof(int), 1, f);
        if(feof(f))  break;
        printf("%3d ", output_number);
    }while (1);
    printf("\n");
    rewind(f);
    for(int i = 0; i < counter-1; i++)                 //вычисдение минимального произведения и id
    {
        if(feof(f)) break;
        fseek(f, -sizeof(int), SEEK_CUR);
        fgetpos(f, &pos1);
        fread(&i1, sizeof(int), 1, f);
        fgetpos(f, &pos2);
        fread(&i2, sizeof(int), 1, f);
        printf("%d*%d = %d  ", i1 ,i2, i1*i2);
        if(i == 0)
        {
            min_value = i1*i2;
            number_id = 2;
        }
        if(i1*i2 < min_value)
        {
            min_value = i1*i2;
            number_id = i+2;
        }
    }
    if(counter % 2 != 0)
        counter--;
    rewind(f);
    for(int i = 0; i < counter/2; i++)                 //меняет местами попарно
    {
        fgetpos(f, &pos1);
        fread(&i1, sizeof(int), 1, f);
        fgetpos(f, &pos2);
        fread(&i2, sizeof(int), 1, f);
        fseek(f, -2*sizeof(int), SEEK_CUR);
        fwrite(&i2, sizeof(int), 1, f);
        fgetpos(f, &pos1);
        fwrite(&i1, sizeof(int), 1, f);
    }
    printf("\nMin number id = %d\n", number_id);
    printf("\nEdited file: ");
    rewind(f);
    do
    {
        fread(&output_number, sizeof(int), 1, f);
        if(feof(f))  break;
        printf("%3d ", output_number);
    }while (1);
    fclose(f);
    printf("\n");
    path[strlen(path) - 4] = '\0';
    return 1;
}


int main()
{
    char file_path[60] = "/Users/antonfilka/Xcode/Lab_3_txt_bin_var_10/", file_name[30];
    printf("Enter the file name: ");
    rewind(stdin);
    fgets(file_name, 30, stdin);
    file_name[strlen(file_name) - 1] = '\0';
    strcat(file_path, file_name);
    int choice;
    while(1)
    {
        printf("\n\nChoose the option to work with:\n1. Create .txt file\n2. Create .bin file\n3. Exit\n");
        while (!scanf("%d", &choice) || choice > 3 || choice < 1)
        {
            printf("\nInput correct option number.\n");
        }
        switch (choice)
        {
            case 1:
                functiontxt(file_path);
                break;
            case 2:
                functionbin(file_path);
                break;
            case 3:
                return 0;
            default:
                break;
        }
    }
    return 0;
}
