
#include "City.h"
#include "functions.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstring>
#include <string.h>


City :: City() {

}

void City ::getInformation()
{
    std::cout << "Enter cityName: " << std::endl;
    std::cin >> cityName;
    std::cout << "Enter country: " << std::endl;
    std::cin >> country;
    std::cout << "Enter numberOfPeople: " << std::endl;
    std::cin >> numberOfPeople;

}

void City ::outputInformation() {
    std::cout << "City cityName is: ";
    std::cout << "\t" << cityName << std::endl;
    std::cout << "Country is: ";
    std::cout << "\t" << country << std::endl;
    std::cout << "Number of people is: ";
    std::cout << "\t" << numberOfPeople << std::endl;
    std::cout << std::endl;
}

void City::loadTextFile(std::ifstream &file)
{
    if (!file.is_open()) {
        throw (std::runtime_error("File is not open"));
    }
    file >> *this;
}

std::ostream &operator<< (std::ostream &out, const City &city)
{
    out << city.cityName << std::endl;
    out << city.country << std::endl;
    out << city.numberOfPeople << std::endl;
    return out;
}

std::istream &operator>> (std::istream &in, City &city)
{
    in >> city.cityName;
    in >> city.country;
    in >> city.numberOfPeople;
    return in;
}


int City::diskCount(const std::string &fileName)
{
    std::ifstream infile;
    infile.open(fileName, std::ios::binary);
    infile.seekg(0, std::ios::end);
    int numberOfDishes;
    int endPosition = infile.tellg();
    numberOfDishes = endPosition/sizeof(City);
    return numberOfDishes;
}

void City::readBinaryFile(std::ifstream& file) {
    if (!file.is_open()) {
        throw (std::runtime_error("File is not open"));
    }
    try {

        size_t nameSize;
        file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        char* temp = new char[nameSize + 1];
        file.read(temp, static_cast<std::streamsize>(nameSize));
        temp[nameSize] = '\0';
        cityName = temp;

        delete[] temp;

        size_t countrySize;
        file.read(reinterpret_cast<char*>(&countrySize), sizeof(countrySize));

        temp = new char[countrySize + 1];
        file.read(temp, static_cast<std::streamsize>(countrySize));
        temp[countrySize] = '\0';
        country = temp;

        delete[] temp;

        size_t numberOfPeopleSize;
        file.read(reinterpret_cast<char*>(&numberOfPeopleSize), sizeof(numberOfPeopleSize));

        temp = new char[numberOfPeopleSize + 1];
        file.read(temp, static_cast<std::streamsize>(numberOfPeopleSize));
        temp[numberOfPeopleSize] = '\0';
        numberOfPeople = temp;

        delete[] temp;
    }
    catch (std::ifstream::failure& ex) {
        throw std::runtime_error("Invalid read data type");
    }
}

void City::saveTxtInBin(std::ofstream &file, const std::string &fileName)
{

    file.open(fileName,  std::ios::binary | std::ios::app );
    if (!file.is_open()) {
        throw (std::runtime_error("File is not open"));
    }


    try {
        std::size_t nameSize = cityName.size();
        file.write(reinterpret_cast<char *>(&nameSize), sizeof(nameSize));
        file.write(cityName.c_str(), static_cast<std::streamsize>(nameSize));

        std::size_t kitchenSize = country.size();
        file.write(reinterpret_cast<char * >(&kitchenSize), sizeof(kitchenSize));
        file.write(country.c_str(), static_cast<std::streamsize>(kitchenSize));

        std::size_t priceSize = numberOfPeople.size();
        file.write(reinterpret_cast<char * >(&priceSize), sizeof(priceSize));
        file.write(numberOfPeople.c_str(), static_cast<std::streamsize>(priceSize));


    } catch (std::ofstream::failure &ex) {
        throw std::runtime_error("Invalid write data type");
    }
    file.close();
}



void City :: loadTxtInBin(std::ifstream &file, const std::string &fileName)
{
    int dishesNumber = diskCount(fileName);

    if (!file.is_open()) {
        file.open(fileName, std:: ios::binary | std::ios::in);
    }

    City temp;

    int counter{};
    while (true) {
        temp.readBinaryFile(file);
        if (file.eof()) {
            break;
        }
        counter++;
        std::cout << "\t\t\tNumber is >>> " << counter << std::endl;
        temp.outputInformation();
    }
    file.close();
}

void City::saveTxt(std::ofstream &file, const std::string &fileName)
{
    file.open(fileName, std::ios::app);
    try
    {
        if (!file)
            throw CannotOpenFile();
    }
    catch (City ::CannotOpenFile)
    {
        std::cout << "Cannot open" << std::endl;
    }
    file << (*this);
    file.close();
}



void City::loadTxt(std::ifstream &file, const std::string &fileName)
{
    file.open(fileName, std::ios::out);
    try
    {
        if (!file)
        {
            throw CannotOpenFile();
        }
    }
    catch (City :: CannotOpenFile)
    {
        std::cout << "Cannot open" << std::endl;
    }
    int counter = 0;
    City* dish = new City();
    while (true)
    {
        dish->loadTextFile(file);
        if (file.eof())
            break;
        counter++;
        std::cout << "\t\t\tNumber is >>> " << counter << std:: endl;
        dish->outputInformation();
    }

    file.close();
}

void City::loadTextFileInReverseOrder(std::ifstream &file, const std::string &fileName)
{
    if (!file.is_open())
    {

        file.open(fileName, std::ios::out);
    }
    int numberOfDishes = 0;
    City* dish = new City();
    bool isQuite = false;
    while (!isQuite)
    {
        dish->loadTextFile(file);
        if (file.eof())
        {
            break;
        }
        numberOfDishes++;
    }

    file.clear();
    file.seekg(std::ios::beg);
    int k = 0;
    while (numberOfDishes != 0)
    {
        for (int i = 0; i < numberOfDishes; i++)
        {
            dish->loadTextFile(file);
        }
        k++;
        std::cout << "\t\t\tNumber is >>> " << k  <<std :: endl;
        dish->outputInformation();
        file.seekg(std::ios::beg);
        numberOfDishes--;
    }

}


void City:: loadBinaryFileInReverseOrder(std::ifstream &file, const std::string &fileName)
{
    bool isQuite = false;
    City temp;
    int numberOfDishes = 0;
    file.open(fileName, std::ios::in);
    while (!isQuite)
    {
        temp.readBinaryFile(file);
        if (file.eof())
        {
            isQuite = true;
            break;
        }
        numberOfDishes++;
    }
    file.clear();
    file.seekg(std::ios::beg);
    int number = 0;
    isQuite = false;
    while (!isQuite)
    {
        if (numberOfDishes == 0)
        {
            isQuite = true;
            break;
        }
        for (int i = 0; i < numberOfDishes; i++) {
            temp.readBinaryFile(file);
        }
        numberOfDishes--;
        number++;
        std::cout << "\t\t\tNumber is >>> " << number  << std::endl;
        temp.outputInformation();
        file.seekg(std::ios::beg);
    }
    file.close();
}


void City :: searchByTheOption(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName)
{
    int choice;
    bool isQuite = false;
    std::cout << "1 to search in Binary file" << std::endl;
    std::cout << "2 to search in Text file" << std::endl;
    std::cout << "0 to exit" << std::endl;
    std::cout << "Your choice is >>" << std::endl;
    choice = intInputValidation();
    while (choice < 0 || choice > 2)
    {
        std::cout << "Incorrect value. Please try again" << std::endl;
        choice = intInputValidation();
    }
    while (!isQuite)
    {
        switch (choice)
        {
            case 1:
            {
                menuForSearchByTheOption(file, textFileName, binaryFileName, choice);
                isQuite = true;
                break;
            }
            case 2:
            {
                menuForSearchByTheOption(file, textFileName, textFileName, choice);
                isQuite = true;
                break;
            }
            case 0:
            {
                isQuite = true;
                break;
            }
        }
    }
}

void City :: searchInBinaryFile(std::ifstream &file, const std::string &binaryFileName, std::string key,  int choice)
{
    City *dish = new City();
    switch(choice)
    {
        case 1:
        {
            file.open( binaryFileName, std::ios::binary | std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "Cannot open" << std::endl;
            }
            while (true)
            {
                dish->readBinaryFile(file);
                if (file.eof())
                {
                    break;
                }
                if (dish->cityName == key)
                {
                    std::cout << "Suitable item" << std::endl;
                    dish->outputInformation();
                }
            }
            file.close();
            break;
        }
        case 2:
        {
            file.open( binaryFileName, std::ios::binary | std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "Cannot open" << std::endl;
            }
            while (true)
            {
                dish->readBinaryFile(file);
                if (file.eof())
                {
                    break;
                }
                if (dish->country == key)
                {
                    std::cout << "Suitable item" << std::endl;
                    dish->outputInformation();
                }
            }
            file.close();
            break;
        }
        case 3:
        {
            file.open( binaryFileName, std::ios::binary | std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "Cannot open" << std::endl;
            }
            while (true)
            {
                dish->readBinaryFile(file);
                if (file.eof())
                {
                    break;
                }
                if (dish->numberOfPeople == key)
                {
                    std::cout << "\t\t Suitable item" << std::endl;
                    dish->outputInformation();
                }
            }
            file.close();
            break;
        }
        case 0:
        {
            break;
        }

    }
}

void City::searchInTextFile(std::ifstream &file, const std::string &textFileName, std::string key, int choice)
{
    City *dish = new City();
    switch(choice)
    {
        case 1:
        {
            file.open(textFileName, std::ios::binary | std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "Cannot open" << std::endl;
            }
            while (true)
            {
                dish->loadTextFile(file);
                if (file.eof())
                {
                    break;
                }
                if (dish->cityName == key)
                {
                    std::cout << "\t\t Suitable item" << std::endl;
                    dish->outputInformation();
                }
            }
            file.close();
            break;
        }
        case 2:
        {
            file.open(textFileName, std::ios::binary | std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "Cannot open" << std::endl;
            }
            while (true)
            {
                dish->loadTextFile(file);
                if (file.eof())
                {
                    break;
                }
                if (dish->country == key)
                {
                    std::cout << "\t\t Suitable item" << std::endl;
                    dish->outputInformation();
                }
            }
            file.close();
            break;
        }
        case 3:
        {
            file.open(textFileName, std::ios::binary | std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            while (true)
            {
                dish->loadTextFile(file);
                if (file.eof())
                {
                    break;
                }
                if (dish->numberOfPeople == key)
                {
                    std::cout << "Suitable item" << std::endl;
                    dish->outputInformation();
                }
            }
            file.close();
            break;
        }
        case 0:
        {
            break;
        }

    }
}

void City::deleteObjectInFile(std::ifstream &file, const std::string &binaryFileName, const std::string &textFileName)
{
    City* dish = new City();
    switch(menuForDelete())
    {
        case 1:
        {
            file.open(textFileName, std::ios::in | std::ios::out);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            int numberOfDishes = 0;
            bool isQuite = false;
            while (!isQuite)
            {
                dish->loadTextFile(file);
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                numberOfDishes++;
            }

            City* dishArr = new City [numberOfDishes];
//            file.clear();
//            file.seekg(std::ios::beg);
            file.close();
            file.open(textFileName, std::ios::in | std::ios::out);
            isQuite = false;
            int i = 0;
            while (i != numberOfDishes)
            {
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                dishArr[i].loadTextFile(file);
                i++;


            }
            std::cout << "Enter a key cityName to delete >>> " << std::endl;
            std::string key;
            std::cin >> key;
            file.clear();
            file.seekg(std::ios::beg);
            isQuite = false;
            int counter = 0;
            while (!isQuite)
            {
                dish->loadTextFile(file);
                counter++;
                if (dish->cityName == key)
                {
                    std::cout << "\t\t Suitable item is: " << std::endl;
                    dish->outputInformation();
                    isQuite = true;
                    break;
                }
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
            }
            for (i = counter-1; i < numberOfDishes - 1; i++)
            {
                dishArr[i] = dishArr[i + 1];
            }
            file.close();
            file.open(textFileName, std::ios::out| std::ios::trunc);
            file.close();
            numberOfDishes--;
            std::ofstream input;
            for (i =  0; i < numberOfDishes; i++)
            {
                dishArr[i].saveTxt(input, textFileName);
            }
            break;
        }
        case 2:
        {
            City* dish = new City();
            file.open(binaryFileName, std::ios::binary|std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            int numberOfDishes = 0;
            bool isQuite = false;
            while (!isQuite)
            {
                dish->readBinaryFile(file);
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                numberOfDishes++;
            }
            file.close();
            City* dishArr = new City [numberOfDishes];

            file.open(binaryFileName, std::ios::binary | std::ios::in);
            isQuite = false;
            int i = 0;
            while (i != numberOfDishes)
            {
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                dishArr[i].readBinaryFile(file);
                i++;
            }
            std::cout << "Enter a key cityName to delete >>> " << std::endl;
            std::string key;
            std::cin >> key;
            file.close();
            file.open(binaryFileName, std::ios::binary | std::ios::in);
            isQuite = false;
            int counter = 0;
            while (!isQuite)
            {
                dish->readBinaryFile(file);
                counter++;
                if (dish->cityName == key)
                {
                    std::cout << "\t\t Suitable item is: " << std::endl;
                    dish->outputInformation();
                    isQuite = true;
                    break;
                }
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
            }
            for (i = counter-1; i < numberOfDishes - 1; i++)
            {
                dishArr[i] = dishArr[i + 1];
            }
            file.close();
            file.open(binaryFileName, std::ios::binary| std::ios::out| std::ios::trunc);
            file.close();
            numberOfDishes--;
            std::ofstream input;
            for (i =  0; i < numberOfDishes; i++)
            {
                dishArr[i].saveTxtInBin(input, binaryFileName);
            }
            break;
        }
    }
}


void City::sortFile(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName)
{
    switch(menuForSort())
    {
        case 1:
        {
            City* dish = new City();
            dish->sortTextFile(file, textFileName);
            break;
        }
        case 2:
        {
            City* dish = new City();
            dish->sortBinaryFile(file, binaryFileName);
            break;
        }
        case 0:
        {
            break;
        }
    }
}

void City::sortTextFile(std::ifstream &file, const std::string &textFileName)
{
    switch(menuForChooseOption())
    {
        case 1:
        {
            City* dish = new City();
            file.open(textFileName, std::ios::in | std::ios::out);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            int numberOfDishes = 0;
            bool isQuite = false;
            while (!isQuite)
            {
                dish->loadTextFile(file);
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                numberOfDishes++;
            }

            City* dishArr = new City [numberOfDishes];
            file.close();
            file.open(textFileName, std::ios::in | std::ios::out);
            isQuite = false;
            int i = 0;
            while (i != numberOfDishes)
            {
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                dishArr[i].loadTextFile(file);
                i++;
            }
            file.close();
            for (i = 0; i < numberOfDishes; i++)
            {
                for (int j = i + 1; j < numberOfDishes; j++)
                {
                    if (strcmp(dishArr[i].cityName.c_str(), dishArr[j].cityName.c_str()) > 0)
                    {
                        City temp = dishArr[i];
                        dishArr[i] = dishArr[j];
                        dishArr[j] = temp;
                    }
                }
            }
            file.open(textFileName, std::ios::out| std::ios::trunc);
            file.close();
            std::ofstream input;
            for (i =  0; i < numberOfDishes; i++)
            {
                dishArr[i].saveTxt(input, textFileName);
            }
            break;
        }
        case 2:
        {
            City* dish = new City();
            file.open(textFileName, std::ios::in | std::ios::out);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            int numberOfDishes = 0;
            bool isQuite = false;
            while (!isQuite)
            {
                dish->loadTextFile(file);
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                numberOfDishes++;
            }

            City* dishArr = new City [numberOfDishes];
            file.close();
            file.open(textFileName, std::ios::in | std::ios::out);
            isQuite = false;
            int i = 0;
            while (i != numberOfDishes)
            {
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                dishArr[i].loadTextFile(file);
                i++;
            }
            file.close();
            for (i = 0; i < numberOfDishes; i++)
            {
                for (int j = i + 1; j < numberOfDishes; j++)
                {
                    if (strcmp(dishArr[i].country.c_str(), dishArr[j].country.c_str()) > 0)
                    {
                        City temp = dishArr[i];
                        dishArr[i] = dishArr[j];
                        dishArr[j] = temp;
                    }
                }
            }
            file.open(textFileName, std::ios::out| std::ios::trunc);
            file.close();
            std::ofstream input;
            for (i =  0; i < numberOfDishes; i++)
            {
                dishArr[i].saveTxt(input, textFileName);
            }
            break;
        }
        case 3:
        {
            City* dish = new City();
            file.open(textFileName, std::ios::in | std::ios::out);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            int numberOfDishes = 0;
            bool isQuite = false;
            while (!isQuite)
            {
                dish->loadTextFile(file);
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                numberOfDishes++;
            }

            City* dishArr = new City [numberOfDishes];
            file.close();
            file.open(textFileName, std::ios::in | std::ios::out);
            isQuite = false;
            int i = 0;
            while (i != numberOfDishes)
            {
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                dishArr[i].loadTextFile(file);
                i++;
            }
            file.close();
            for (i = 0; i < numberOfDishes; i++)
            {
                for (int j = i + 1; j < numberOfDishes; j++)
                {
                    if (strcmp(dishArr[i].numberOfPeople.c_str(), dishArr[j].numberOfPeople.c_str()) > 0)
                    {
                        City temp = dishArr[i];
                        dishArr[i] = dishArr[j];
                        dishArr[j] = temp;
                    }
                }
            }
            file.open(textFileName, std::ios::out| std::ios::trunc);
            file.close();
            std::ofstream input;
            for (i =  0; i < numberOfDishes; i++)
            {
                dishArr[i].saveTxt(input, textFileName);
            }
            break;
        }
        default:
            break;
    }
}
void City::sortBinaryFile(std::ifstream &file, const std::string &binaryFileName)
{
    switch(menuForChooseOption())
    {
        case 1:
        {
            City* dish = new City();
            file.open(binaryFileName, std::ios::binary|std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            int numberOfDishes = 0;
            bool isQuite = false;
            while (!isQuite)
            {
                dish->readBinaryFile(file);
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                numberOfDishes++;
            }
            file.close();
            City* dishArr = new City [numberOfDishes];
            file.open(binaryFileName, std::ios::binary | std::ios::in);
            isQuite = false;
            int i = 0;
            while (i != numberOfDishes)
            {
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                dishArr[i].readBinaryFile(file);
                i++;
            }
            file.close();
            for (i = 0; i < numberOfDishes; i++)
            {
                for (int j = i + 1; j < numberOfDishes; j++)
                {
                    if (strcmp(dishArr[i].cityName.c_str(), dishArr[j].cityName.c_str()) > 0)
                    {
                        City temp = dishArr[i];
                        dishArr[i] = dishArr[j];
                        dishArr[j] = temp;
                    }
                }
            }
            file.open(binaryFileName, std::ios::binary| std::ios::out| std::ios::trunc);
            file.close();
            std::ofstream input;
            for (i =  0; i < numberOfDishes; i++)
            {
                dishArr[i].saveTxtInBin(input, binaryFileName);
            }

            break;
        }
        case 2:
        {
            City* dish = new City();
            file.open(binaryFileName, std::ios::binary|std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            int numberOfDishes = 0;
            bool isQuite = false;
            while (!isQuite)
            {
                dish->readBinaryFile(file);
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                numberOfDishes++;
            }
            file.close();
            City* dishArr = new City [numberOfDishes];
            file.open(binaryFileName, std::ios::binary | std::ios::in);
            isQuite = false;
            int i = 0;
            while (i != numberOfDishes)
            {
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                dishArr[i].readBinaryFile(file);
                i++;
            }
            file.close();
            for (i = 0; i < numberOfDishes; i++)
            {
                for (int j = i + 1; j < numberOfDishes; j++)
                {
                    if (strcmp(dishArr[i].country.c_str(), dishArr[j].country.c_str()) > 0)
                    {
                        City temp = dishArr[i];
                        dishArr[i] = dishArr[j];
                        dishArr[j] = temp;
                    }
                }
            }
            file.open(binaryFileName, std::ios::binary| std::ios::out| std::ios::trunc);
            file.close();
            std::ofstream input;
            for (i =  0; i < numberOfDishes; i++)
            {
                dishArr[i].saveTxtInBin(input, binaryFileName);
            }

            break;
        }
        case 3:
        {
            City* dish = new City();
            file.open(binaryFileName, std::ios::binary|std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "\t\t Cannot open" << std::endl;
            }
            int numberOfDishes = 0;
            bool isQuite = false;
            while (!isQuite)
            {
                dish->readBinaryFile(file);
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                numberOfDishes++;
            }
            file.close();
            City* dishArr = new City [numberOfDishes];
            file.open(binaryFileName, std::ios::binary | std::ios::in);
            isQuite = false;
            int i = 0;
            while (i != numberOfDishes)
            {
                if (file.eof())
                {
                    isQuite = true;
                    break;
                }
                dishArr[i].readBinaryFile(file);
                i++;
            }
            file.close();
            for (i = 0; i < numberOfDishes; i++)
            {
                for (int j = i + 1; j < numberOfDishes; j++)
                {
                    if (strcmp(dishArr[i].numberOfPeople.c_str(), dishArr[j].numberOfPeople.c_str()) > 0)
                    {
                        City temp = dishArr[i];
                        dishArr[i] = dishArr[j];
                        dishArr[j] = temp;
                    }
                }
            }
            file.open(binaryFileName, std::ios::binary| std::ios::out| std::ios::trunc);
            file.close();
            std::ofstream input;
            for (i =  0; i < numberOfDishes; i++)
            {
                dishArr[i].saveTxtInBin(input, binaryFileName);
            }

            break;
        }
        default:
            break;

    }
}

void City::rangeSearch(std::ifstream &file, const std::string &textFileName, const std::string &binaryFileName)
{
    switch(menuForSearch())
    {
        case 1:
        {
            City* dish = new City();
            char left, right;
            std::cout << "Enter left value of range >>>" << std::endl;
            std::cin >> left;
            std::cout << "Enter right value of range >>>" << std::endl;
            std::cin >> right;
            while (left > right)
            {
                std::cout << "Incorrect value. Left should be less than right. Please try again" << std::endl;
                std::cout << "Enter left value of range >>>" << std::endl;
                std::cin >> left;
                std::cout << "Enter right value of range >>>" << std::endl;
                std::cin >> right;
            }
            file.open(textFileName,  std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "Cannot open" << std::endl;
            }
            while (true)
            {
                dish->loadTextFile(file);
                if (file.eof())
                {
                    break;
                }
                if (dish->cityName[0] >= left && dish->cityName[0] <= right)
                {
                    std::cout << "\t\t Suitable item" << std::endl;
                    dish->outputInformation();
                }
            }
            file.close();
            break;
        }
        case 2:
        {
            City* dish = new City();
            char left, right;
            std::cout << "Enter left value of range >>>" << std::endl;
            std::cin >> left;
            std::cout << "Enter right value of range >>>" << std::endl;
            std::cin >> right;
            while (left > right)
            {
                std::cout << "Incorrect value. Left should be less than right. Please try again" << std::endl;
                std::cout << "Enter left value of range >>>" << std::endl;
                std::cin >> left;
                std::cout << "Enter right value of range >>>" << std::endl;
                std::cin >> right;
            }
            file.open(binaryFileName, std::ios::binary | std::ios::in);
            try
            {
                if (!file)
                    throw CannotOpenFile();
            }
            catch (City ::CannotOpenFile)
            {
                std::cout << "Cannot open" << std::endl;
            }
            while (true)
            {
                dish->readBinaryFile(file);
                if (file.eof())
                {
                    break;
                }
                if (dish->cityName[0] >= left && dish->cityName[0] <= right)
                {
                    std::cout << "\t\t Suitable item" << std::endl;
                    dish->outputInformation();
                }
            }
            file.close();
            break;
        }
    }
}
void City :: deleteDuplicates(std::ifstream &file, const std::string &binaryFileName, const std::string &textFileName)
{

    switch(menuForDuplicates())
    {
        case 1:
        {
            switch(menuForChooseOptionDuplicates())
            {
                case 1:
                {
                    City* dish = new City();
                    file.open(textFileName, std::ios::in | std::ios::out);
                    try
                    {
                        if (!file)
                            throw CannotOpenFile();
                    }
                    catch (City ::CannotOpenFile)
                    {
                        std::cout << "\t\t Cannot open" << std::endl;
                    }
                    int numberOfDishes = 0;
                    bool isQuite = false;
                    while (!isQuite)
                    {
                        dish->loadTextFile(file);
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        numberOfDishes++;
                    }

                    City* dishArr = new City [numberOfDishes];
                    file.close();
                    file.open(textFileName, std::ios::in | std::ios::out);
                    isQuite = false;
                    int i = 0;
                    while (i != numberOfDishes)
                    {
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        dishArr[i].loadTextFile(file);
                        i++;
                    }
                    file.close();
                    isQuite = false;
                    int counter = 0;
                    for (i = 0; i < numberOfDishes; i++)
                    {
                        for (int j = i + 1; j < numberOfDishes; j++)
                        {
                            if (dishArr[i].cityName == dishArr[j].cityName)
                            {
                                for (int k = j; k < numberOfDishes-1; k++)
                                {
                                    dishArr[k] = dishArr[k + 1];
                                }
                                numberOfDishes--;
                            }
                        }
                    }
                    file.open(textFileName, std::ios::out| std::ios::trunc);
                    file.close();

                    std::ofstream input;
                    for (i =  0; i < numberOfDishes; i++)
                    {
                        dishArr[i].saveTxt(input, textFileName);
                    }
                    break;
                }
                case 2:
                {
                    City* dish = new City();
                    file.open(textFileName, std::ios::in | std::ios::out);
                    try
                    {
                        if (!file)
                            throw CannotOpenFile();
                    }
                    catch (City ::CannotOpenFile)
                    {
                        std::cout << "\t\t Cannot open" << std::endl;
                    }
                    int numberOfDishes = 0;
                    bool isQuite = false;
                    while (!isQuite)
                    {
                        dish->loadTextFile(file);
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        numberOfDishes++;
                    }

                    City* dishArr = new City [numberOfDishes];
                    file.close();
                    file.open(textFileName, std::ios::in | std::ios::out);
                    isQuite = false;
                    int i = 0;
                    while (i != numberOfDishes)
                    {
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        dishArr[i].loadTextFile(file);
                        i++;
                    }
                    file.close();
                    isQuite = false;
                    int counter = 0;
                    for (i = 0; i < numberOfDishes; i++)
                    {
                        for (int j = i + 1; j < numberOfDishes; j++)
                        {
                            if (dishArr[i].country == dishArr[j].country)
                            {
                                for (int k = j; k < numberOfDishes-1; k++)
                                {
                                    dishArr[k] = dishArr[k + 1];
                                }
                                numberOfDishes--;
                            }
                        }
                    }
                    file.open(textFileName, std::ios::out| std::ios::trunc);
                    file.close();

                    std::ofstream input;
                    for (i =  0; i < numberOfDishes; i++)
                    {
                        dishArr[i].saveTxt(input, textFileName);
                    }
                    break;
                }
                case 3:
                {
                    City* dish = new City();
                    file.open(textFileName, std::ios::in | std::ios::out);
                    try
                    {
                        if (!file)
                            throw CannotOpenFile();
                    }
                    catch (City ::CannotOpenFile)
                    {
                        std::cout << "\t\t Cannot open" << std::endl;
                    }
                    int numberOfDishes = 0;
                    bool isQuite = false;
                    while (!isQuite)
                    {
                        dish->loadTextFile(file);
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        numberOfDishes++;
                    }

                    City* dishArr = new City [numberOfDishes];
                    file.close();
                    file.open(textFileName, std::ios::in | std::ios::out);
                    isQuite = false;
                    int i = 0;
                    while (i != numberOfDishes)
                    {
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        dishArr[i].loadTextFile(file);
                        i++;
                    }
                    file.close();
                    isQuite = false;
                    int counter = 0;
                    for (i = 0; i < numberOfDishes; i++)
                    {
                        for (int j = i + 1; j < numberOfDishes; j++)
                        {
                            if (dishArr[i].numberOfPeople == dishArr[j].numberOfPeople)
                            {
                                for (int k = j; k < numberOfDishes-1; k++)
                                {
                                    dishArr[k] = dishArr[k + 1];
                                }
                                numberOfDishes--;
                            }
                        }
                    }
                    file.open(textFileName, std::ios::out| std::ios::trunc);
                    file.close();

                    std::ofstream input;
                    for (i =  0; i < numberOfDishes; i++)
                    {
                        dishArr[i].saveTxt(input, textFileName);
                    }
                    break;
                }
            }
            break;
        }
        case 2:
        {
            switch(menuForChooseOptionDuplicates())
            {
                case 1:
                {
                    City* dish = new City();
                    file.open(binaryFileName, std::ios::binary|std::ios::in | std::ios::out);
                    try
                    {
                        if (!file)
                            throw CannotOpenFile();
                    }
                    catch (City ::CannotOpenFile)
                    {
                        std::cout << "\t\t Cannot open" << std::endl;
                    }
                    int numberOfDishes = 0;
                    bool isQuite = false;
                    while (!isQuite)
                    {
                        dish->readBinaryFile(file);
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        numberOfDishes++;
                    }

                    City* dishArr = new City [numberOfDishes];
                    file.close();
                    file.open(binaryFileName, std::ios::binary|std::ios::in | std::ios::out);
                    isQuite = false;
                    int i = 0;
                    while (i != numberOfDishes)
                    {
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        dishArr[i].readBinaryFile(file);
                        i++;
                    }
                    file.close();
                    isQuite = false;
                    int counter = 0;
                    for (i = 0; i < numberOfDishes; i++)
                    {
                        for (int j = i + 1; j < numberOfDishes; j++)
                        {
                            if (dishArr[i].cityName == dishArr[j].cityName)
                            {
                                for (int k = j; k < numberOfDishes-1; k++)
                                {
                                    dishArr[k] = dishArr[k + 1];
                                }
                                numberOfDishes--;
                            }
                        }
                    }
                    file.open(binaryFileName, std::ios::binary|std::ios::out| std::ios::trunc);
                    file.close();

                    std::ofstream input;
                    for (i =  0; i < numberOfDishes; i++)
                    {
                        dishArr[i].saveTxtInBin(input, binaryFileName);
                    }
                    break;
                }
                case 2:
                {
                    City* dish = new City();
                    file.open(binaryFileName, std::ios::binary|std::ios::in | std::ios::out);
                    try
                    {
                        if (!file)
                            throw CannotOpenFile();
                    }
                    catch (City ::CannotOpenFile)
                    {
                        std::cout << "\t\t Cannot open" << std::endl;
                    }
                    int numberOfDishes = 0;
                    bool isQuite = false;
                    while (!isQuite)
                    {
                        dish->readBinaryFile(file);
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        numberOfDishes++;
                    }

                    City* dishArr = new City [numberOfDishes];
                    file.close();
                    file.open(binaryFileName, std::ios::binary|std::ios::in | std::ios::out);
                    isQuite = false;
                    int i = 0;
                    while (i != numberOfDishes)
                    {
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        dishArr[i].readBinaryFile(file);
                        i++;
                    }
                    file.close();
                    isQuite = false;
                    int counter = 0;
                    for (i = 0; i < numberOfDishes; i++)
                    {
                        for (int j = i + 1; j < numberOfDishes; j++)
                        {
                            if (dishArr[i].country == dishArr[j].country)
                            {
                                for (int k = j; k < numberOfDishes-1; k++)
                                {
                                    dishArr[k] = dishArr[k + 1];
                                }
                                numberOfDishes--;
                            }
                        }
                    }
                    file.open(binaryFileName, std::ios::binary|std::ios::out| std::ios::trunc);
                    file.close();

                    std::ofstream input;
                    for (i =  0; i < numberOfDishes; i++)
                    {
                        dishArr[i].saveTxtInBin(input, binaryFileName);
                    }
                    break;
                }
                case 3:
                {
                    City* dish = new City();
                    file.open(binaryFileName, std::ios::binary|std::ios::in | std::ios::out);
                    try
                    {
                        if (!file)
                            throw CannotOpenFile();
                    }
                    catch (City ::CannotOpenFile)
                    {
                        std::cout << "\t\t Cannot open" << std::endl;
                    }
                    int numberOfDishes = 0;
                    bool isQuite = false;
                    while (!isQuite)
                    {
                        dish->readBinaryFile(file);
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        numberOfDishes++;
                    }

                    City* dishArr = new City [numberOfDishes];
                    file.close();
                    file.open(binaryFileName, std::ios::binary|std::ios::in | std::ios::out);
                    isQuite = false;
                    int i = 0;
                    while (i != numberOfDishes)
                    {
                        if (file.eof())
                        {
                            isQuite = true;
                            break;
                        }
                        dishArr[i].readBinaryFile(file);
                        i++;
                    }
                    file.close();
                    isQuite = false;
                    int counter = 0;
                    for (i = 0; i < numberOfDishes; i++)
                    {
                        for (int j = i + 1; j < numberOfDishes; j++)
                        {
                            if (dishArr[i].numberOfPeople == dishArr[j].numberOfPeople)
                            {
                                for (int k = j; k < numberOfDishes-1; k++)
                                {
                                    dishArr[k] = dishArr[k + 1];
                                }
                                numberOfDishes--;
                            }
                        }
                    }
                    file.open(binaryFileName, std::ios::binary|std::ios::out| std::ios::trunc);
                    file.close();

                    std::ofstream input;
                    for (i =  0; i < numberOfDishes; i++)
                    {
                        dishArr[i].saveTxtInBin(input, binaryFileName);
                    }
                    break;
                }
            }
            break;
        }
        default:
            break;
    }
}

