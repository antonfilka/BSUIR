#include <iostream>
#include <stdlib.h>
using namespace std;

//Трехмерный массив с элементами типа int. ++
//размерность с клавиатуры, рандомное заполнение ++
//ф транспонирвания всех матриц массива ++
//создание нового массива матриц на основе трех выбирая максимальное значение по индексу ++


class threeDemensionalArray{
private:
    int defaultSize = 2, defaultValue = 0;
    int sizeX, sizeY, sizeZ;
    int ***array;

public:

    threeDemensionalArray(){

        this->sizeX = this->sizeY =  this->sizeZ = defaultSize;

        cout << "Enter X size of array: ";
        cin >> this->sizeX;
        cout << endl << "Enter Y size of array: ";
        cin >> this->sizeY;
        cout << endl << "Enter Z size of array: ";
        cin >> this->sizeZ;

        array = new int **[defaultSize];
        for (int x = 0; x < defaultSize; x++){
            array[x] = new int *[defaultSize];
            for (int y = 0; y < defaultSize; y++){
                array[x][y] = new int[defaultSize];
                for (int z = 0; z < defaultSize; z++){
                    array[x][y][z] = defaultValue;
                }
            }
        }
    }
    explicit threeDemensionalArray(int sizeX){
        this->sizeX = this->sizeY =  this->sizeZ = sizeX;
        array = new int **[sizeX];
        for (int x = 0; x < sizeX; x++){
            array[x] = new int *[sizeY];
            for (int y = 0; y < sizeY; y++){
                array[x][y] = new int[sizeZ];
                for (int z = 0; z < sizeZ; z++){
                    array[x][y][z] = defaultValue;
                }
            }
        }
    }
    explicit threeDemensionalArray(int sizeX, int sizeY, int sizeZ){
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->sizeZ = sizeZ;
        array = new int **[sizeX];
        for (int x = 0; x < sizeX; x++){
            array[x] = new int *[sizeY];
            for (int y = 0; y < sizeY; y++){
                array[x][y] = new int[sizeZ];
                for (int z = 0; z < sizeZ; z++){
                    array[x][y][z] = defaultValue;
                }
            }
        }
    }
    threeDemensionalArray(const threeDemensionalArray& a){
        this->sizeX = a.sizeX;
        this->sizeY = a.sizeY;
        this->sizeZ = a.sizeZ;
        this->defaultSize = a.defaultSize;
        this->defaultValue = a.defaultValue;

        array = new int **[sizeX];
        for (int x = 0; x < sizeX; x++){
            array[x] = new int *[sizeY];
            for (int y = 0; y < sizeY; y++){
                array[x][y] = new int[sizeZ];
                for (int z = 0; z < sizeZ; z++){
                    array[x][y][z] = a.array[x][y][z];
                }
            }
        }
    }

    int getDefaultValue() const {
        return defaultValue;
    }
    void setDefaultValue(int defaultValue) {
        threeDemensionalArray::defaultValue = defaultValue;
    }
    int getDefaultSize() const {
        return defaultSize;
    }
    void setDefaultSize(int defaultSize) {
        threeDemensionalArray::defaultSize = defaultSize;
    }
    int getSizeX() const {
        return sizeX;
    }
    void setSizeX(int sizeX) {
        threeDemensionalArray::sizeX = sizeX;
    }
    int getSizeY() const {
        return sizeY;
    }
    void setSizeY(int sizeY) {
        threeDemensionalArray::sizeY = sizeY;
    }
    int getSizeZ() const {
        return sizeZ;
    }
    void setSizeZ(int sizeZ) {
        threeDemensionalArray::sizeZ = sizeZ;
    }
    int ***getArray() const {
        return array;
    }
    void setArray(int ***array) {
        threeDemensionalArray::array = array;
    }

    void outputArray(){
        for (int x = 0; x < sizeX; x++){
           cout << endl;
            for (int y = 0; y < sizeY; y++){
                cout << endl;
                for (int z = 0; z < sizeZ; z++){
                    if (array[x][y][z] < 10 )
                        cout << "  a[" << x << "][" << y << "][" << z << "]: " << array[x][y][z] << "  ";
                    else
                        cout << "  a[" << x << "][" << y << "][" << z << "]: " << array[x][y][z] << " ";

                }
            }
        }
    }
    void outputFirst3Array(){
        for (int x = 0; x < 3; x++){
            cout << endl;
            for (int y = 0; y < sizeY; y++){
                cout << endl;
                for (int z = 0; z < sizeZ; z++){
                    if (array[x][y][z] < 10 )
                        cout << "  a[" << x << "][" << y << "][" << z << "]: " << array[x][y][z] << "  ";
                    else
                        cout << "  a[" << x << "][" << y << "][" << z << "]: " << array[x][y][z] << " ";

                }
            }
        }
    }
    void outputOnly4Array(){
        for (int y = 0; y < sizeY; y++){
            cout << endl;
            for (int z = 0; z < sizeZ; z++){
                if (array[3][y][z] < 10 )
                    cout << "  a[3][" << y << "][" << z << "]: " << array[3][y][z] << "  ";
                else
                    cout << "  a[3][" << y << "][" << z << "]: " << array[3][y][z] << " ";

            }
        }
    }
    void setArrayValue(int defaultValue){
        this->defaultValue = defaultValue;
        for (int x = 0; x < sizeX; x++){
            for (int y = 0; y < sizeY; y++){
                for (int z = 0; z < sizeZ; z++){
                    array[x][y][z] = defaultValue;
                }
            }
        }
    }
    void setArrayRandomValue(){
        for (int x = 0; x < sizeX; x++){
            for (int y = 0; y < sizeY; y++){
                for (int z = 0; z < sizeZ; z++){
                    array[x][y][z] = getRandomNumber(0, 400);
                }
            }
        }
    }
    void setArrayByValue(int numberOfArray, int Value){
        for(int y = 0; y < sizeY; y++){
            for (int z = 0; z < sizeZ; z++){
                array[numberOfArray][y][z] = Value;
            }
        }
    }
    int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }
    void transpose3DMatrix (){
        int temp;
        for (int i = 0; i < sizeX; i++){
            for(int j = 0; j < sizeY; ++j){
                for(int k = j; k < sizeZ; ++k){
                    temp = array[i][j][k];
                    array[i][j][k] = array[i][k][j];
                    array[i][k][j] = temp;
                }
            }
        }
    }
    void createByCompare(){
        int temp = 0, x = 0;
        for (int y = 0; y < sizeY; y++){
            for (int z = 0; z < sizeZ; z++){
                for (x = 0; x < 3; x++){
                    if (array[x][y][z] > temp)
                        temp = array[x][y][z];
                }
                array[3][y][z] = temp;
                temp = 0;
            }
        }
    }

    void* operator new(size_t size){
        return ::operator new(size);
    }
    void operator delete(void* ptr){
        ::operator delete(ptr);
    }
    void* operator new[](size_t size){
        return ::operator new[](size);
    }
    void operator delete[](void* ptr){
        ::operator delete[](ptr);
    }

    ~threeDemensionalArray(){
        for (int x = 0; x < sizeX; x++){
            for (int y = 0; y < sizeY; y++){
                delete[] array[x][y];
            }
        }
        for (int x = 0; x < sizeX; x++){
            delete[] array[x];
        }
        delete[] array;
    }
};


int main() {

    /*
    threeDemensionalArray *a = new threeDemensionalArray(2, 3, 2);
    a->setArrayValue(3);
    threeDemensionalArray *b = new threeDemensionalArray(*a);

    cout << "ARRAY 'A': ";
    a->outputArray();
    cout << endl << endl << "ARRAY 'B' IS MADE AS A COPY OF ARRAY 'A': " ;
    b->outputArray();
    a->setArrayValue(5);
    //b->setArrayValue(6);
    cout << endl << endl << "ARRAY 'A' VALUE IS CHANGED TO '5': ";
    a->outputArray();
    cout << endl << endl << "ARRAY B: " ;
    b->outputArray();
    delete a, b;
    cout << endl << endl;


    int numberOfArrays;

    cout << " -- -- -- -- -- -- " << endl << "Enter number of 3d arrays: ";
    cin >> numberOfArrays;

    threeDemensionalArray *arr = new threeDemensionalArray[numberOfArrays]();

    for (int i = 0; i < numberOfArrays; i++){
        arr[i].setArrayValue(i);
        cout << endl << endl << "ARRAY '" << i << "' ->" << endl;
        arr[i].outputArray();
    }

    delete[] arr;
    */

    int sizeX = 1, sizeY = 1, sizeZ = 1;
    cout << "Enter X size of array: ";
    cin >> sizeX;
    cout << endl << "Enter Y size of array: ";
    cin >> sizeY;
    cout << endl << "Enter Z size of array: ";
    cin >> sizeZ;

    threeDemensionalArray arr1(sizeX, sizeY, sizeZ);
    arr1.setArrayRandomValue();
    cout << "Output of array: ";

    arr1.outputArray();

    cout << endl << "Now every matrix of this array is gonna be transpositioned " << endl ;
    arr1.transpose3DMatrix();
    cout << "Output of transpositioned array: ";
    arr1.outputArray();
    cout << endl << "Set measures of 3 matrix to be compared: " << endl;

    cout << endl << "Enter Y size of array: ";
    cin >> sizeY;
    cout << endl << "Enter Z size of array: ";
    cin >> sizeZ;
    threeDemensionalArray *arr2 = new threeDemensionalArray(4, sizeY, sizeZ);
    arr2->setArrayRandomValue();
    cout << endl << "Source matrix to be compared: " << endl;
    arr2->outputFirst3Array();
    cout << endl << " - - - - - - " << endl;
    arr2->setArrayByValue(3, 0);

   arr2->createByCompare();

    arr2->outputOnly4Array();

    return 0;
}
