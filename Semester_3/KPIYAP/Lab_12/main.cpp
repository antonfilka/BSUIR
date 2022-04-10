#include "BracketsCheck.h"
using namespace std;

int main()
{
    std::string source_file = "/Users/antonfilka/CLionProjects/Labs_3/Lab_12/Brackets.txt";
    std::string result_file = "/Users/antonfilka/CLionProjects/Labs_3/Lab_12/Result.txt";

    BracketsCheck test(source_file, result_file);

    try {
        test.loadFromTxt();
        test.check();
        test.saveInTxt();
    }
    catch (UserException &exception) {
        std::cout << exception.what() << std::endl << "End of the program!" << std::endl;
    }

    return 0;
}