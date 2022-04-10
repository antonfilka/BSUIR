#include <stdio.h>
#include <malloc.h>


int main()
{
	int n, c, i, j, co1 = 0, co2 = 0;
	char* arr;
	printf("Enter the string length n: ");

	while ((scanf_s("%d", &n) == 0))
	{
		printf("Enter the right number: ");
		rewind(stdin);
	}
	rewind(stdin);

	if (!(arr = (char*)calloc(n + 1, sizeof(char))))
	{
		printf("Wrong..."); return 0;
	}

	printf("\nEnter the string, number of characters equals n = %d : ", n);

	fgets(arr, n + 1, stdin);
	printf("\nSource string: %s\n", arr);


	for (i = 0; i < n + 1; i++)
	{
		if (arr[i] == '#')
			co1++;
	}
	printf("Number of # equals %d\n", co1);

	for (i = 0; i<n+1 ; i++)
	{
		if (arr[i] != '#' && arr[i] != 0 && arr[i] != '\n')
		{
			co2++;
		}
			
	}
	printf("Number of characters equals %d\n\n", co2);


	if (co1 > co2)
	{
		printf("The number of # is more then the number of other characters..\n");
		return 0;
	}

	c = n + 1;

	for (i = 0; i < n + 1; i++)
	{
		if (arr[i] == '#')
		{
			c = c - 2;
			for (j = i; j < c; j++)
			{
				arr[j - 1] = arr[j + 1];
				i = i - 2;
			}
		}
	}

	printf("\nFinal string is: %s\n", arr);
	free(arr);
	return 0;
}