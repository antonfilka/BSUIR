#include <stdio.h>
#include <locale.h>
#include <malloc.h>

int main(){

    setlocale(LC_ALL, "Russian");
    int *a, *b;
    int i, n, num = 0, sum = 0;
    
    printf("Введите размер массивов: ");  //Ввод размера массивов
    while((scanf_s("%d", &n) == 0) || ((n > 0) == 0)) {
        printf("\nВведите число ещё раз: ");
        rewind(stdin);
    }

 
    a = (int*)malloc(n * sizeof(int));  //Выделение памяти под массивы А и В
    b = (int*)malloc(n * sizeof(int));

    for (i = 1; i <= n; i++)
    {
        printf("Введите a%d = ", i); //Заполнение массивов
        while (scanf_s("%d", &a[i]) == 0) {
            printf("\nВведите число ещё раз: ");
            rewind(stdin);
        }      
    }
    printf("\n");
    for (i = 1; i <= n; i++)
    {
        printf("Введите b%d = ", i);
        while (scanf_s("%d", &b[i]) == 0) {
            printf("\nВведите число ещё раз: ");
            rewind(stdin);
        }
    }
    printf("\nМассив А: ");  //Отображение массивов
    for (i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    printf("\nМассив В: ");
    for (i = 1; i <= n; i++) {
        printf("%d ", b[i]);
    }
    printf("\n\n");  
    for (i = 1; i <= n; i++) {    //Цикл с сортировкой и рассчетамми
        if (a[i] * b[i] > 10) {
            printf("%0d и %0d (i = %0d)\n", a[i], b[i], i);
            num++;
            sum += (a[i] * b[i]);
        }
    }

    printf("\nЧисло пар: %0d\nСумма произведений: %0d\n", num, sum);
    free(a); free(b);
    return (0);
}