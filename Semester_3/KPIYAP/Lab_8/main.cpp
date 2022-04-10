#include <iostream>
#include "functions.h"
#include "LinkedList.h"
#include <exception>
using namespace std;


int main()
{
    int numberOfDupl = 0;
    LinkedList* list = new LinkedList();
    set_unexpected(myUnexpected);
    bool isQuite = false;
    bool isContinue = false;
    int choice;
    while (!isQuite) {
        switch(menu()) {

            case 1: {
                list->addItem(1);
                list->addItem(3);
                list->addItem(3);
                list->addItem(3);
                list->addItem(3);
                list->addItem(99);
                break;
            }

            case 2: {
                try {
                    list->display();
                }
                catch(LinkedList :: Empty) {
                    cout << "Empty, add new positions !" << std::endl;
                }
                break;
            }

            case 3: {
                cout << "Enter number to delete >>" << endl;
                int number = inputValidation();
                int length = list->listLength();
                try {
                    list->deleteItem(number, length);
                } catch(LinkedList :: NoSuitable) {
                    cout << "There is no such number !" << endl;
                } catch (LinkedList :: Empty) {
                    cout << "Your list is empty !" << endl; }
                break;
            }

            case 4: {
                cout << "1 - Sort ascending" << endl;
                cout << "2 - Sort descending" << endl;
                choice = inputValidation();
                while (choice > 2 || choice < 1){
                    cout << "Incorrect value. Please try again" << endl;
                    choice = inputValidation();
                }
                if (choice == 1)
                {
                    list->sortAscending();
                } else if (choice == 2)
                {
                    list->sortDescending();
                }
                break;
            }

            case 5:{
                set_terminate(myTerm);
                try {
                    list->moveToAnotherPlace();
                } catch (LinkedList ::NoSuitable){
                    cout << "There is no such number" << endl;
                }
                break;
            }

            case 6:{
                set_unexpected(myUnexpected);
                try {
                    numberOfDupl = list->deleteDublicates();
                    if (numberOfDupl == 0)
                        cout << endl << "NO dublicates found" << endl << endl;
                    else
                        cout << endl << " - - - - - - " << endl << numberOfDupl << " duplicates found" << endl << " - - - - - - " << endl <<  endl;
                    numberOfDupl = 0;
                }catch (LinkedList :: Empty) {
                    cout << "Your list is empty" << endl; }
                break;
            }

            case 0:{
                isQuite = true;
                break;
            }

        }
    }
}


// добавить сортировку по возрастанию и убыванию
// удаление дубликатов и вывод количества найденых дубликатов
// удаление выбранного элемента