#include<stdlib.h>
#include<stdio.h>
#include "Header.h"

int main()
{
    int arraySize = 0, newArraySize = 0;
    struct Animals* animal = NULL;
    while (1)
    {
        switch (menu())
        {
            case 1:
                printf("Number of notes you want to add: \n");
                newArraySize = input_int();
                arraySize += newArraySize;
                animal = add(animal, arraySize, newArraySize);
                break;
            case 2:
                show(animal, arraySize);
                break;
            case 3:
                change(animal, arraySize);
                break;
            case 4:
                search(animal, arraySize);
                break;
            case 5:
                sort(animal, arraySize);
                break;
            case 6:
                animal = del(animal, &arraySize);
                break;
            case 7:
                free(animal);
                return 0;
            default:
                printf("Error. Incorrect value!\n");
        }
    }
}

