#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>

#include "City.h"
#include "functions.h"


//сначала вводим потом тип файла
//удаление дубликатов
//поиск

int main()
{
    std::ofstream input;
    std::ifstream output;
    bool isMenuExit = false;
    //std::string fileNameTxtInBin = "/Users/antonfilka/CLionProjects/Labs_3/Lab_9/txtInBin.txt";
    std::string fileNameBinBin = "/Users/antonfilka/CLionProjects/Labs_3/Lab_9/BinBin.bin";
    std::string fileNameTxtTxt = "/Users/antonfilka/CLionProjects/Labs_3/Lab_9/TxtText.txt";

    input.open(fileNameBinBin, std::ios::trunc);
    input.close();

    input.open(fileNameTxtTxt, std::ios::trunc);
    input.close();

    City* city = new City();
    while (!isMenuExit)
    {
        switch (menu())
        {
            case 11:
            {
                city->getInformation();
            }
            case 1:
            {
                int choice;
                bool isQuite = false;
                city->saveTxtInBin(input, fileNameBinBin);
                while (!isQuite)
                {
                    std::cout << "Do you want to continue?" << std::endl;
                    std::cout << "1 to continue \n0 to exit " << std::endl;
                    std::cout << "Choice is >>> " << std::endl;
                    choice = intInputValidation();
                    if (choice == 0)
                    {
                        isQuite = true;
                    }
                    else
                    {
                        city->getInformation();
                        city->saveTxtInBin(input, fileNameBinBin);
                    }
                }
                break;
            }
            case 2: {
                city->loadTxtInBin(output, fileNameBinBin);
                break;
            }
            case 3: {
                int choice;
                bool isQuite = false;
                city->saveTxt(input, fileNameTxtTxt);
                while (!isQuite) {
                    std::cout << "Do you want to continue?" << std::endl;
                    std::cout << "1 to continue \n0 to exit " << std::endl;
                    std::cout << "Choice is >>> " << std::endl;
                    choice = intInputValidation();
                    if (choice == 0) {
                        isQuite = true;
                    } else {
                        city->getInformation();
                        city->saveTxt(input, fileNameTxtTxt);
                    }
                }
                break;
            }
            case 4:
            {
                city->loadTxt(output, fileNameTxtTxt);
                break;
            }
            case 5:
            {
                outputInReverseOrder(output, fileNameTxtTxt, fileNameBinBin);
                break;
            }
            case 6:
            {
                city->searchByTheOption(output, fileNameTxtTxt, fileNameBinBin);
                break;
            }
//            case 7:
//            {
//                city->deleteObjectInFile(output, fileNameBinBin, fileNameTxtTxt);
//                break;
//            }
//            case 8:
//            {
//                city->sortFile(output, fileNameTxtTxt, fileNameBinBin);
//                break;
//            }
//            case 9:
//            {
//                city->rangeSearch(output, fileNameTxtTxt, fileNameBinBin);
//                break;
//            }
            case 7:
            {
                city ->deleteDuplicates(output, fileNameBinBin, fileNameTxtTxt);
                break;
            }
            case 0:
            {
                isMenuExit = true;
                break;
            }

        }
    }



    return 0;
}