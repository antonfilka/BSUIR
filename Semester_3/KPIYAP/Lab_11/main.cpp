#include <iostream>
#include "Locomotive.h"
#include "RailwayCarriage.h"
#include "namespace.h"
#include "functions.h"


// сортиовка по любому +
// вывод по диапозону мощности +
// удаление по направлению поезда +


int main()
{
    int size = 3;
    railway::Train* trainArray = new railway::Train [size];
    bool isQuite = false;
    while (!isQuite) {
        switch (menu()) {
            case 1: {
                for (int i = 0; i < size; i++) {
                    std::cout << "\t\t\t[" << i << "]" << std::endl;
                    trainArray[i].inputInformationTrain();
                }
                std::cout << std::endl;
                break;
            }
            case 2: {
                for (int i = 0; i < size; i++) {
                    std::cout << "\t\t\t[" << i << "]" << std::endl;
                    trainArray[i].outputInformationTrain();
                    std::cout << std::endl;
                }
                std::cout << std::endl;
                break;
            }
            case 3: {
                size = deleteDuplicates(trainArray, size);
                break;
            }
            case 4:
            {
                std::cout << "Enter low border to search: " << std::endl;
                int lowBorder = inputValidation();
                std::cout << "Enter high border to search: " << std::endl;
                int highBorder = inputValidation();
                findInRange(trainArray, size, lowBorder, highBorder);
                break;
            }
            case 5:
            {
                std::cout << "Enter destination to delete: " << std::endl;
                std::string destName;
                std::cin >> destName;
                deleteByDestination(trainArray, size, destName);
                break;
            }
            case 6:
            {
                switch (sortMenu()) {
                    case 1:
                        sortByPower(trainArray, size);
                        break;
                    case 2:
                        sortByDirection(trainArray, size);
                        break;
                    case 3:
                        sortByType(trainArray, size);
                        break;
                    default:
                        break;
                }
                break;
            }
            case 0: {
                isQuite = true;
                break;
            }
        }
    }

    return 0;
}
