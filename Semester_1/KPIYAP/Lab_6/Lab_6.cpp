#include <stdio.h>
#include <locale.h>
#include <malloc.h>

int main() {
    setlocale(LC_ALL, "Russian");

    int** a;
    int i, j, n, p, c;

    printf("\nВведит количество строк и столбцов массива: ");

    scanf_s("%d", &n);

    a = (int**)malloc(n * sizeof(int*));

    for (i = 0; i < n; i++) {
        a[i] = (int*)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            printf("Введите значение матрицы A[%d][%d]: ", i, j);
            scanf_s("%d", &a[i][j]);
        }
    }

    printf("\nИсходная матрица: \n\n");
    for (i = 0; i < n; i++) {
        printf("\n");
        for (j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
    }


    for (p = 0; p < n - 1; p++) {
        for (j = n - 2; j >= p; j--) {
            if (a[j][j] > a[j+1][j + 1]) {
                c = a[j][j];
                a[j][j] = a[j+1][j + 1];
                a[j+1][j + 1] = c;
            }
        }
    }

    printf("\n");


    printf("\nИтоговая матрица (Значения главной оси отсортированы по возрастанию): \n");
    for (i = 0; i < n; i++) {
        printf("\n");
        for (j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    printf("\n");
    return 0;
}