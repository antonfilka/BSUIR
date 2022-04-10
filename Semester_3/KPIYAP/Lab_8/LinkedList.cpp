#include "LinkedList.h"
#include "functions.h"
#include <exception>
#include <algorithm>

using namespace std;

void LinkedList :: addItem(int number){
    link* newItem = new link();
    newItem->info = number;
    newItem->next = first;
    first = newItem;
}
void LinkedList :: display()
{
    link* current = first;
    if (current == NULL)
    {
        throw Empty();
    }
    while (current)
    {
        cout << "Item value:  " << current->info << endl;
        current = current->next;
    }

    cout << "\n";
}

void LinkedList ::deleteItem(int number, int length)
{
    link* current = first;
    link* previous = current;
    if (current == NULL)
    {
        throw Empty();
    }
    int counter = 0;
    while (current->info != number)
    {
        previous = current;
        current = current->next;
        counter++;
        if (counter == length && current == NULL)
        {
            throw NoSuitable();
        }
    }

    if (counter == length )
    {
        if (current->next == NULL)
        {
            delete current;
            previous->next = NULL;
            return;
        }
        else
        {
            throw NoSuitable();
        }
    }
    if (current == first)
    {
        first = first->next;
        delete current;
        return;
    }
    previous->next = current->next;
    delete current;
    return;
}

bool LinkedList ::searchByOption(int number)
{
    bool isTrue = false;
    link* current = first;
    int counter = 0;
    while(current)
    {
        if(current->info == number)
        {

            counter++;
            isTrue = true;
        }
        current = current->next;
    }
    if (counter == 0)
    {
        throw NoSuitable();
    }
    return isTrue;
}


int LinkedList :: listLength()
{
    link* current = first;
    int length = 0;
    while (current != NULL)
    {
        current = current->next;
        length++;
    }
    return length;
}

void LinkedList ::sortAscending() {
    link* current = first;
    link* nextItem;
    int temp;
    link* tempNext;
    bool unsorted = true;
    while (unsorted)
    {
        unsorted = false;
        current = first;
        while (current->next != NULL)
        {
            nextItem = current->next;
            if(current->info > nextItem->info)
            {
                temp = current->info;
                current->info = nextItem->info;
                nextItem->info = temp;
                unsorted = true;
            }
            current = current->next;
        }
    }
}
void LinkedList ::sortDescending() {
    link* current = first;
    link* nextItem;
    int temp;
    link* tempNext;
    bool unsorted = true;
    while (unsorted)
    {
        unsorted = false;
        current = first;
        while (current->next != NULL)
        {
            nextItem = current->next;
            if(current->info < nextItem->info)
            {
                temp = current->info;
                current->info = nextItem->info;
                nextItem->info = temp;
                unsorted = true;
            }
            current = current->next;
        }
    }
}



void LinkedList ::moveToAnotherPlace() {
    link *current = first;
    link *rootFirst = first;
    link *selected;
    link *previous;
    int length = listLength();
    int chosenPosition;
    int counter = 0;
    cout << "Enter the value of item you want to move" << std::endl;
    int chosenItem = inputValidation();
    searchByOption(chosenItem);
    cout << "Positions : " << endl;
    for (int i = 0; i < length; i++) {
        cout << "\t[" << i << "]" << endl;
    }
    cout << "Choose a counter: " << endl;
    chosenPosition = inputValidation();
    while (chosenPosition < 0 || chosenPosition > (length - 1)) {
        cout << "Incorrect value. Please try again" << endl;
        chosenPosition = inputValidation();
    }
    if (chosenPosition == 0) {
        while (current->info != chosenItem) {
            previous = current;
            current = current->next;
            selected = current;
        }
        previous->next = current->next;
        current = first;
        first = selected;
        selected->next = current;
        return;


    }
    while (current->info != chosenItem) {
        previous = current;
        current = current->next;
        selected = current;

    }
    previous->next = current->next;
    current = first;
    while (counter != chosenPosition) {
        previous = current;
        current = current->next;
        counter++;
    }
    previous->next = selected;
    selected->next = current;
}

int LinkedList ::deleteDublicates()
{
    bool isFirst = true;
    int iterator = 0;

    link* current = first;
    link* nextItem = current->next;
    while(current->next != NULL)
    {
        while(nextItem->next !=NULL)
        {
            if(current->info == nextItem->info)
            {
                deleteItem(current->info, listLength());
                isFirst = false;
                iterator = iterator + 1;
                current = first;
                nextItem = current->next;
            }
            nextItem = nextItem ->next;
        }

        current = current ->next;
        nextItem = current->next;
    }
    if(isFirst)
        return 0;
    else
        return iterator;
}