#include <iostream>
#include <cstring>
#include "functions.h"
using namespace std;

template <typename T>
void findSuitableItem(T array[], T key , T value,  int size)
{
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == key)
        {
            cout << "Item found: " << array[i] <<"   Index of item found: " << i << endl;
            array[i] = value;
            k++;
        }
    }
    if (k == 0)
    {
        cout << "There are no suitable items in integer array" << std::endl;
        return;
    }
    cout << "Result: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << ' ';
    }
    cout <<'\n';
}
template <typename T>


void removeDuplicates(T array[], T key, T value, int size){
    int k = 0;
    for (int i = 0; i <size; i++)
    {
        if (array[i] == key)
        {
            if (k == 0)
            {
                array[i] = value;
                k++;
            }
            else
            {
                if(i != size - 1)
                {
                    for (int j = i; j < size - 1; j++)
                    {
                        array[j] = array[j + 1];
                    }
                    size--;
                    i--;
                }
                else
                {
                    size--;
                }
            }
        }

    }
    if (k == 0)
    {
        cout << "There are no suitable items in array" << endl;
        return;
    }
    cout << "Result: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << ' ';
    }

}

template <>
void findSuitableItem(char array[], char key, char letter, int size)
{
    int k = 0;
    for (int i = 0; i < size; i++)
    {
        if(array[i] == key)
        {
            cout << "Matching item: " << array[i] <<"\n Index is: " << i << endl;
            array[i] = letter;
            k++;
        }
    }
    if (k == 0)
    {
        cout << "There are no suitable items in char sentence" << endl;
        return;
    }

    cout << "Result: " <<  endl;
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i];
    }
    std::cout << std:: endl;
}

template <>
void removeDuplicates(char array[], char key, char letter, int size)
{
    int k = 0;
    for (int i = 0; i <size; i++)
    {
        if (array[i] == key)
        {
            if (k == 0)
            {
                array[i] = letter;
                k++;
            }
            else
            {
                if (i != size - 1)
                {
                    for (int j = i; j < size - 1; j++)
                    {
                        array[j] = array[j + 1];
                    }
                    size--;
                    array[size] = '\0';
                    i--;
                } else
                {
                    size--;
                    array[size] = '\0';
                }
            }
        }

    }
    if (k == 0)
    {
        cout << "There are no matching items in integer array" << endl;
        return;
    }
    cout << "Result: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << array[i];
    }
    cout << endl;
}

int main()
{
    int array[9]
            {3, 7, 2, 9, 3, 7, 1, 7, 2};
    cout << endl << endl << endl << " = = = = = = = = " << endl << "Array: " << endl;
    for(int i = 0; i<9; i++){
        cout << array[i] << " ";
    }

    cout << endl << "Enter integer key: " << endl;
    int key;
    key = inputValidation();
    char keyLetter;

    int size = sizeof(array) / sizeof(key);
    findSuitableItem(array, key, 4, size);

    cout << "Enter an integer key: " <<endl;
    key = inputValidation();
    removeDuplicates(array, key, 10, size);
    cout << '\n';


    char charArray[30];
    inputSentence(charArray);
    int length = strlen(charArray);
    cout << "Enter char key:" << endl;
    cin >> keyLetter;
    findSuitableItem(charArray, keyLetter, '~', length );
    cout << endl;
    cout << "Enter char key: " << endl;
    cin >> keyLetter;
    removeDuplicates(charArray, keyLetter, '|', length);


    switch(menu())
    {
        case 1:
        {
            char integerArray[40];
            char alphabetArray[40];
            char marksArray[40];
            char sentence[80];
//            inputSentence(sentence);
//            cout << sentence << endl;
            splitStringsWithOption(sentence, integerArray, alphabetArray, marksArray);
            //cout <<"Integer array: " << integerArray << endl;
            /*cout <<"Alphabet array: " << alphabetArray << endl;
            cout <<"Marks array: " << marksArray << endl;   */
            break;
        }
        case 0:
        {
            break;
        }
    }
    return 0;
}