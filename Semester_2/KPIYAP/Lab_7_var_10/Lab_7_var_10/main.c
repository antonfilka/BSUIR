#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
    struct Tree* root = NULL;
    while (1)
    {
        switch (menu())
        {
        case 1:
            add(&root);
            break;
        case 2:
            showMenu(root);
            break;
        case 3:
            delMenu(root);
            break;
        case 4:
            system("CLS");
            clean(&root);
            return 0;
        }
    }
}
