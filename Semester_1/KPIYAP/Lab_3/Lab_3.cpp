#include <stdio.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Russian");

	int i, num_pl=0, num_mn=0, num_null=0, sum_pol=0, sum_otr=0, sum_null=0, n, a;

	printf("������� ����������� ����� n: ");
	while ((scanf_s("%d", &n) == 0)||((n > 0)==0)) {
		printf("������� ����� ��� ���: ");
		rewind(stdin);
	}

	for (i = 1; i <= n; i++) {
		printf("������� ����� ����� a%d: ", i);
		
		while (scanf_s("%d", &a) == 0) {
			printf("������� ����� ��� ���: ");
			rewind(stdin);
		}

		if (a == 0) {
			num_null++;
		}
		else if (a > 0) {
			num_pl++;
			sum_pol += a;
		}
		else if (a < 0) {
			num_mn++;
			sum_otr += a;
		}
	}

	printf("\n���������� �������������: %0d\n���������� �������������: %0d\n���������� ������ ����: %0d\n����� �������������: %0d\n����� �������������: %0d\n", kolvo_pol, kolvo_otr, kolvo_null, summ_pol, summ_otr);
	return 0;
}
