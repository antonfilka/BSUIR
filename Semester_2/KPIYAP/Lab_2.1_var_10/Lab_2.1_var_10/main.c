#include "Header.h"
#include "Source.cpp"


int main()
{
    while (1)
    {
        int exit = start();
        if(exit == 1)
        {
            return 0;
        }
    }
    return 0;
}
