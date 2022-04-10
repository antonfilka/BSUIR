#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

int main() {
    struct Animals* head = NULL,* tale = NULL;
    while (1) {
        switch (menu()) {
        case 1: push(&head, &tale); break;
        case 2: show(head); break;
        case 3: del(&head, &tale); break;
        case 4: paricletSearch(head); break;
        case 5: writeToFile(head); break;
        case 6: reading(&head, &tale); break;
        case 7: freshStack(&head, &tale); return 0;
        }
    }
}


