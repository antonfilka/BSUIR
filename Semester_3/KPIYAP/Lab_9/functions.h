#ifndef LABWORK9_FUNCTIONS_H
#define LABWORK9_FUNCTIONS_H

#endif //LABWORK9_FUNCTIONS_H

#include <iostream>

int intInputValidation();
double doubleInputValidation();
int menu();
void outputInReverseOrder(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName);
int menuForOutputInReverseOrder();
void menuForSearchByTheOption(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName,
                              int seekChoice);
int menuForDelete();
int menuForSort();
int menuForChooseOption();
int menuForSearch();
int menuForDuplicates();
int menuForChooseOptionDuplicates();