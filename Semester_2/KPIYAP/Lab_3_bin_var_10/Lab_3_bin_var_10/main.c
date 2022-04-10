#include <stdio.h>
#include <string.h>

//1. С клавиатуры заполнить файл целыми числами. +
//2. Найти и напечатать номер элемента, произведение которого с предыдущим элементом минимально. +
//3. Попарно поменять элементы местами. Если их количество нечетное, последний элемент оставить на месте. +

int main()
{
    
    FILE *f;
    int input_number, output_number, i1, i2, counter = 0, number_id = 0, min_value = 0;
    fpos_t pos1 = 1, pos2 = 0;
    char file_path[60] = "/Users/antonfilka/Xcode/Lab_3_bin_var_10/", file_name[30];
    printf("Enter the file name: ");
    rewind(stdin);
    fgets(file_name, 30, stdin);
    file_name[strlen(file_name) - 1] = '\0';
    strcat(file_name, ".bin");
    strcat(file_path, file_name);
    if (!(f = fopen(file_path, "w+b")))
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
        //printf("%d*%d = %d  ", i1 ,i2, i1*i2);
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
    return 0;
}
