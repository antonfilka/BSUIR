#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include "Source.cpp"

int main()
{
    int amount = 0;
    struct Information* info = (struct Information*)calloc(1,sizeof(struct Information));
    while(1)
    {
        int exit = menu(info, &amount);
        if (exit == 7)
        {
            free(info);
            return 0;
        }
    }
}
