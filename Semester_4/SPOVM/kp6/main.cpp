#include <conio.h>
#include <dos.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#define SIZE 10
float array[SIZE];

void inputArray();
void outputArray();
void asmAlgorithm();

int main() {
	inputArray();
	printf("Input array: \n");
	outputArray();

	asmAlgorithm();

	printf("\nResult array: \n");
	outputArray();

	return 0;
}

void inputArray() {
	int res;
	printf("Input 10 elements: \n");

	for (int i = 0; i < SIZE; ++i) {
		do {
			res = scanf("%f", &array[i]);
			while (getchar() != '\n');
			if (res != 1) printf("Invalid input\n");
		} while (res != 1);
	}
}

void outputArray() {
	for (int i = 0; i < SIZE; ++i) {
		printf("%.3f ", array[i]);
	}
}


void asmAlgorithm() {


	__asm {          	
		finit
		xor cx, cx
		lea bx, array
		mov cx, SIZE
	}
	calculate_loop:
	__asm {
		fld dword ptr[bx]
		db 0d9h, 0feh
		fstp dword ptr[bx]
		add bx, 4
		loop calculate_loop
		fwait
	}
}