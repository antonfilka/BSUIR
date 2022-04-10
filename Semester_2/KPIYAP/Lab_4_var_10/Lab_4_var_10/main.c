#include "Header.h"

int main()
{
    struct Animals* animal = NULL;
    while (1)
    {
        switch (menu())
        {
        case 1:
                adding_notes(&animal);
                break;
        case 2:
                reverse(&animal);
                show_all_notes(animal);
                break;
        case 3:
                delete_note(&animal);
                break;
        case 4:
                search(animal);
                break;
        case 5:
                create_file(animal);
                break;
        case 6:
                read_file(&animal);
                break;
        case 7:
                clear_all(&animal);
                return 0;
        default:
                printf("There's no such option");
        }
    }
}



