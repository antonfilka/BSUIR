#include "Ring.h"
#include <iostream>
using namespace std;

template <class T>
void Ring<T> ::pushback(const T& value)
{
    RingNode<T>* newlink = new RingNode<T>;
    newlink->word = value;
    if (isEmpty())
    {
        first = newlink;
        first->next = first;
        first->prev = first;
        last = first;
    }
    else
    {
        newlink->next = first;
        newlink->prev = last;
        last->next = newlink;
        first->prev = newlink;
        last = newlink;
    }
}

template <class T>
void Ring<T> ::showList()
{
    RingNode<T>* temp = first;
    if (!isEmpty())
    {
        temp->word.hat();
        do
        {
            cout << temp->word << endl;
            temp = temp->next;
        } while (temp != last->next);
    }
    else
        cout << "������ ����!" << endl;
}

template <class T>
void Ring<T> ::popfront()
{
    if (howmany_links() == 0)
    {
        cout << "������ ����!" << endl;
        return;
    }
    else if (howmany_links() == 1)
    {
        first = nullptr;
        last = nullptr;
    }
    else
    {
        RingNode<T>* forDel = first;
        last->next = forDel->next;
        first = forDel->next;
        first->prev = last;
        delete forDel;
    }
}

template <class T>
T Ring<T> ::popback()
{
    T toDelete;

    if (first == nullptr)
    {
        cout << "������ ����!" << endl;
        return toDelete;
    }
    else if (howmany_links() == 1)
    {
        toDelete = first->word;
        first = nullptr;
        last = nullptr;
    }
    else
    {
        RingNode<T>* forDel = last;
        first->prev = forDel->prev;
        last = forDel->prev;
        last->next = first;
        toDelete = forDel->word;
        delete forDel;
    }

    return toDelete;
}

template <class T>
void Ring<T>::popAny(const int index)
{
    if (first == nullptr)
    {
        cout << "������ ����!" << endl;
        return;
    }
    else if (howmany_links() == 1)
    {
        first = nullptr;
        last = nullptr;
    }
    else if (index == 0)
    {
        popfront();
    }
    else if (index == howmany_links())
    {
        popback();
    }
    else
    {
        RingNode<T>* previous = first;
        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->next;
        }

        RingNode<T>* forDel = previous->next;
        previous->next = forDel->next;
        forDel->prev = previous;

        for (int i = index; i < howmany_links(); i++)
        {
            previous = previous->next;
            last = previous;
        }

        delete forDel;
    }
}

template <class T>
void Ring<T> ::sortlist()
{
    RingNode<T>* temp = new RingNode<T>;
    RingNode<T>* temp1 = first;
    RingNode<T>* temp3 = new RingNode<T>;

    for (int i = 0; i < howmany_links() - 1; i++)
    {
        RingNode<T>* temp2 = temp1->prev;

        for (int j = i; j < howmany_links() - 1; j++)
        {
            if (temp1->word.getName() > temp2->word.getName())
            {
                temp->word = temp2->word;
                temp2->word = temp1->word;
                temp1->word = temp->word;
            }
            temp2 = temp2->prev;
        }
        cout << temp1->word << " ";
        temp1 = temp1->prev;
        temp3->word = temp1->word;
    }
    if (!isEmpty())
        cout << temp3->word;

    delete temp3;
    delete temp;
}

template <class T>
void Ring<T> ::clear()
{
    if (first == nullptr)
    {
        return;
    }

    while (last != nullptr)
    {
        popfront();
    }

    first = nullptr;
    last = nullptr;
}

template <class T>
int Ring<T> ::howmany_links()
{
    if (!isEmpty())
    {
        RingNode<T>* temp = first;
        int i = 0;
        do
        {
            temp = temp->next;
            i++;
        } while (temp != first);

        return i;
    }
    else
        return 0;
}

template <class T>
bool Ring<T>::isEmpty()
{
    if (first == nullptr)
        return true;
    else
        return false;
}

template <class T>
void Ring<T>::findByValue()
{
    T object;
    int count = 0;
    T* arr = new T[howmany_links()];
    RingNode<T>* temp = first;

    cout << "������� ��������� ������." << endl;
    system("pause");
    object.changeInf();

    for (int i = 0; i < howmany_links(); i++)
    {
        if (object == temp->word)
        {
            arr[count] = temp->word;
            count++;
        }

        temp = temp->next;
    }

    if (count != 0)
    {
        object.hat();
        for (int i = 0; i < count; i++)
        {
            cout << arr[i] << endl;
        }
    }
    else
    {
        cout << "��������� � �������� ���������� � ������ �� �������!" << endl;
    }

    delete[] arr;
    system("pause");
}

template <class T>
void Ring<T>::editElement()
{
    int choice;
    RingNode<T>* temp = first;

    showList();

    do
    {
        cout << "������� ����� ��������, � �������� ������ �������� ������: ";
        cin >> choice;
    } while (choice < 1 || choice > howmany_links());

    for (int i = 1; i < choice; i++)
    {
        temp = temp->next;
    }

    temp->word.changeInf();
}