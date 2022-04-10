#include "functions.h"
#include <cstring>

using namespace std;

void myUnexpected(){
    cout<<"my_unexpected handler"<< endl;
    throw LinkedList();
}

void  myTerm(){
    cout<<"Terminate() exception";
    exit(1);
}


int inputValidation()
{
    char number[10];
    std::cin >> number;
    int length = strlen(number);
    int i = 0;
    bool isTrue = true;
    while(isTrue)
    {
        while (i < length)
        {
            if (number[i] < '0' || number[i] > '9')
            {
                isTrue = true;
                std::cout << "Incorrect value" << std::endl;
                std::cout << "Try again: " << std::endl;
                std::cin >> number;
                length = strlen(number);
                i = 0;
                break;

            }
            i++;
            isTrue = false;
        }
    }
    int value = atoi(number);
    isTrue = true;
    return value;
}


int menu()
{
    bool isTrue = true;
    int choice;
    cout << "1 - Add item" << endl;
    cout << "2 - Display a list" << endl;
    cout << "3 - Delete item" << endl;
    cout << "4 - Sort the list" << endl;
    cout << "6 - Delete duplicates" << endl;
    cout << "0 - Exit" << endl;
    while(isTrue)
    {
        choice = inputValidation();
        if (choice > 6 || choice < 0)
        {
            cout << "Incorrect choice. Try again" << endl;
        }
        else
        {
            isTrue = false;
        }
    }
    return choice;
}
