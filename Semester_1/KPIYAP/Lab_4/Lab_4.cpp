#include <stdio.h>
#include <locale.h>
#include <malloc.h>

int main(){

    setlocale(LC_ALL, "Russian");
    int *a, *b;
    int i, n, num = 0, sum = 0;
    
    printf("������� ������ ��������: ");  //���� ������� ��������
    while((scanf_s("%d", &n) == 0) || ((n > 0) == 0)) {
        printf("\n������� ����� ��� ���: ");
        rewind(stdin);
    }

 
    a = (int*)malloc(n * sizeof(int));  //��������� ������ ��� ������� � � �
    b = (int*)malloc(n * sizeof(int));

    for (i = 1; i <= n; i++)
    {
        printf("������� a%d = ", i); //���������� ��������
        while (scanf_s("%d", &a[i]) == 0) {
            printf("\n������� ����� ��� ���: ");
            rewind(stdin);
        }      
    }
    printf("\n");
    for (i = 1; i <= n; i++)
    {
        printf("������� b%d = ", i);
        while (scanf_s("%d", &b[i]) == 0) {
            printf("\n������� ����� ��� ���: ");
            rewind(stdin);
        }
    }
    printf("\n������ �: ");  //����������� ��������
    for (i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n������ �: ");
    for (i = 1; i <= n; i++) {
        printf("%d ", b[i]);
    }
    printf("\n\n");  
    for (i = 1; i <= n; i++) {    //���� � ����������� � �����������
        if (a[i] * b[i] > 10) {
            printf("%0d � %0d (i = %0d)\n", a[i], b[i], i);
            num++;
            sum += (a[i] * b[i]);
        }
    }

    printf("\n����� ���: %0d\n����� ������������: %0d\n", num, sum);
    free(a); free(b);
    return (0);
}