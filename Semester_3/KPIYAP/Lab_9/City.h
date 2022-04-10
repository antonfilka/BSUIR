#ifndef LABWORK9_DISH_H
#define LABWORK9_DISH_H


#include <iostream>
#include <fstream>
#include <ostream>

class City {
private:
    std::string cityName{};
    std::string country{};
    std::string numberOfPeople{};


public:
    class Empty {};
    class CannotOpenFile{};
    City();
    void getInformation();
    void outputInformation();

    int diskCountBinary(const std::string &fileName);
    int diskCount(const std::string &fileName);

    void saveTxtInBin(std::ofstream &file, const std::string &fileName);
    void loadTxtInBin(std::ifstream &file, const std::string &fileName);
    void saveTxt(std::ofstream &file, const std::string &fileName);
    void loadTxt(std::ifstream &file, const std::string &fileName);
    void loadTextFile(std::ifstream &file);

    void loadTextFileInReverseOrder(std::ifstream &file, const std::string &fileName);
    void loadBinaryFileInReverseOrder(std::ifstream &file, const std::string &fileName);
    void readBinaryFile(std::ifstream& file);

    friend std::ostream &operator<< (std::ostream &out, const City &dish);
    friend std::istream &operator>> (std::istream &in, City &dish);

    void searchInBinaryFile(std::ifstream &file, const std::string &binaryFileName, std::string key,  int choice);
    void searchByTheOption(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName);
    void searchInTextFile(std::ifstream &file, const std::string &textFileName, std::string key, int choice);
    void deleteObjectInFile(std::ifstream &file, const std::string &binaryFileName, const std::string &textFileName);


    void sortFile(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName);
    void sortTextFile(std::ifstream &file, const std::string &textFileName);
    void sortBinaryFile(std::ifstream &file, const std::string &binaryFileName);
    void rangeSearch(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName);
    void deleteDuplicates(std::ifstream &file, const std::string &binaryFileName, const std::string &textFileName);
};


#endif //LABWORK9_DISH_H