#ifndef LABWORK8_LINKEDLIST_H
#define LABWORK8_LINKEDLIST_H

#include <iostream>


struct link
{
    int info;
    link* next;
};

class LinkedList
{
private:
    link* first;

public:
    class Empty { };
    class NoSuitable { };
    LinkedList()
    {
        first = NULL;
    }
    void addItem(int number);
    void display();
    void deleteItem(int number, int length);
    bool searchByOption(int number);
    int listLength();
    void sortAscending();
    void sortDescending();
    void moveToAnotherPlace();
    int deleteDublicates();

};


#endif