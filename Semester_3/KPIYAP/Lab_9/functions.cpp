#include "functions.h"
#include "City.h"
#include <iostream>
#include <cstring>

int intInputValidation()
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
                std::cout << "Try again >>>" << std::endl;
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

double doubleInputValidation()
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
                if(number[i] != '.')
                {
                    isTrue = true;
                    std::cout << "Incorrect value" << std::endl;
                    std::cout << "Try again >>>" << std::endl;
                    std::cin >> number;
                    length = strlen(number);
                    i = 0;
                    break;
                }
            }
            i++;
            isTrue = false;
        }
    }
    double value = atof(number);

    return value;
}

int menu()
{
    std::cout << "  (11) to enter data" << std::endl;
    std::cout << "  (1) to save file as binary" << std::endl;
    std::cout << "  (2) to load file as binary" << std::endl;
    std::cout << "  (3) to save file as text" << std::endl;
    std::cout << "  (4) to load file as text" << std::endl;
    std::cout << "  (5) to output file in reverse order" << std::endl;
    std::cout << "  (6) to search by the option" << std::endl;
//    std::cout << "  (7) to delete by the cityName" << std::endl;
//    std::cout << "  (8) to sort information by the option" << std::endl;
//    std::cout << "  (9) to range search" << std::endl;
    std::cout << "  (7) to delete duplicates" << std::endl;
    std::cout << std::endl;
    std::cout << "      0 to exit" << std::endl;
    std::cout << std::endl;
    int choice;
    std::cout << "Your choice is: "<< std::endl;
    choice = intInputValidation();
    while(choice < 0 || choice > 11)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    return choice;
}

int menuForOutputInReverseOrder()
{
    int choice;
    std::cout << "  (1) to output Text file in reverse order" << std::endl;
    std::cout << "  (2) to output Binary file in reverse order" << std::endl;
    std::cout << "Your choice is: "<< std::endl;
    choice = intInputValidation();
    while(choice < 0 || choice > 2)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    return choice;
}

void outputInReverseOrder(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName)
{
    City *dish = new City();
    switch(menuForOutputInReverseOrder())
    {
        case 1:
        {
            dish->loadTextFileInReverseOrder(file, textFileName);
            break;
        }
        case 2:
        {
            dish->loadBinaryFileInReverseOrder(file, binaryFileName);
            break;
        }
    }
}

void menuForSearchByTheOption(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName, int seekChoice)
{
    std::string key;
    City *dish = new City();
    int choice;

    std::cout << "  (1) to search by cityName" <<std::endl;
    std::cout << "  (2) to search by country" <<std::endl;
    std::cout << "  (3) to search by numberOfPeople" <<std::endl;
    std::cout << "Your choice is: " << std::endl;
    choice = intInputValidation();
    while (choice < 1 || choice > 3)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    switch(seekChoice)
    {
        case 1:
        {
            std::cout << "Enter a key to search by: " << std::endl;
            std::cin >> key;
            dish->searchInBinaryFile(file, binaryFileName, key, choice);
            break;
        }
        case 2:
        {
            std::cout << "Enter a key to search by: " << std::endl;
            std::cin >> key;
            dish->searchInTextFile(file, textFileName, key, choice);
            break;
        }
        case 0:
        {
            break;
        }
    }

}

int menuForDelete()
{
    std::cout << "  (1) to delete from text file" << std::endl;
    std::cout << "  (2) to delete from binary file" << std::endl;
    std::cout << "      0 to exit" << std::endl;
    std::cout << "Your choice is: " << std::endl;
    int choice = intInputValidation();
    while (choice < 0 || choice > 2)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    return choice;
}

int menuForSort()
{
    std::cout << "  (1) to sort text file" << std::endl;
    std::cout << "  (2) to sort binary file" << std::endl;
    std::cout << "      0 to exit" << std::endl;
    std::cout << "Your choice is: " << std::endl;
    int choice = intInputValidation();
    while (choice < 0 || choice > 2)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    return choice;
}

int menuForChooseOption()
{
    int choice;
    std::cout << "  (1) to sort by cityName" <<std::endl;
    std::cout << "  (2) to sort by country" <<std::endl;
    std::cout << "  (3) to sort by numberOfPeople" <<std::endl;
    std::cout << "Your choice is: " << std::endl;
    choice = intInputValidation();
    while (choice < 1 || choice > 3)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    return choice;
}

int menuForSearch()
{
    std::cout << "  (1) to search in text file" << std::endl;
    std::cout << "  (2) to search in binary file" << std::endl;
    std::cout << "      0 to exit" << std::endl;
    std::cout << " Your choice is: " << std::endl;
    int choice = intInputValidation();
    while (choice < 0 || choice > 2)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    return choice;
}

int menuForDuplicates()
{
    std::cout << "  (1) to delete from text file" << std::endl;
    std::cout << "  (2) to delete from binary file" << std::endl;
    std::cout << "      0 to exit" << std::endl;
    std::cout << "Your choice: " << std::endl;
    int choice = intInputValidation();
    while (choice < 0 || choice > 2)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    return choice;
}

int menuForChooseOptionDuplicates()
{
    int choice;
    std::cout << "  (1) to delete by cityName" <<std::endl;
    std::cout << "  (2) to delete by country" <<std::endl;
    std::cout << "  (3) to delete by numberOfPeople" <<std::endl;
    std::cout << "Your choice: " << std::endl;
    choice = intInputValidation();
    while (choice < 1 || choice > 3)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    return choice;
}