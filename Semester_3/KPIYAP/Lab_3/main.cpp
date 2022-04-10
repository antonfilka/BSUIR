#include <iostream>
using namespace std;

class Complex{

private:
    double real;
    double imag;

public:
    Complex(){
        real = imag = 0;
    }

    Complex(double real, double imag){
        this->real = real;
        this->imag = imag;
    }

    Complex (const Complex& other){
        this->real = other.real;
        this->imag = other.imag;
    }

    Complex operator + (const Complex & other) const{
        return {this->real + other.real, this->imag + other.imag};
    }

    Complex operator - (const Complex & other) const{
        return {this->real - other.real, this->imag - other.imag};
    }

    Complex operator * (const Complex & other) const{
        return {this->real * other.real, this->imag * other.imag};
    }

    Complex operator / (const Complex & other) const{
        return {this->real / other.real, this->imag / other.imag};
    }

    Complex operator ++ (int){
        return {real++, imag++};
    }
    Complex operator -- (int){
        return {real--, imag--};
    }

    Complex& operator ++ (){
        real++; imag++;
        return *this;
    }
    Complex& operator -- (){
        real--; imag--;
        return *this;
    }

    double getReal() const {
        return real;
    }
    void setReal(double reall) {
        Complex::real = reall;
    }

    double getImag() const {
        return imag;
    }
    void setImag(double imagin) {
        Complex::imag = imagin;
    }

    friend class ComplexMatrix;
    friend ostream &operator << (ostream &out, const Complex &a);
    ~Complex() = default;
};
ostream &operator << (ostream &out, const Complex &a){
    out << "Real: " << a.real << " Imag: " << a.imag << endl;
    return out;
}

class ComplexMatrix{

private:
    Complex matrix[10][10];
    int size;
public:

    ComplexMatrix(){
        size = 9;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                matrix[i][j].real = 0;
                matrix[i][j].imag = 0;
            }
        }
    }

    explicit ComplexMatrix(int size){
        this->size = size-1;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                cout<<"[" << i+1 << "]["<< j+1 << "]real:";   cin>>matrix[i][j].real;
                cout<<"[" << i+1 << "]["<< j+1 << "]imag:";   cin>>matrix[i][j].imag;
                cout << endl;
            }

        }
    }

    ComplexMatrix(int size, int flag){
        this->size = size-1;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                matrix[i][j].real = 0;
                matrix[i][j].imag = 0;
                cout << endl;
            }

        }
    }

    ComplexMatrix operator + (const ComplexMatrix &other){
        ComplexMatrix temp;

        for(int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                temp[i][j] = this->matrix[i][j] + other.matrix[i][j];
            }
        }
        return temp;
    }

    ComplexMatrix operator - (const ComplexMatrix &other){
        ComplexMatrix temp;

        for(int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                temp[i][j] = this->matrix[i][j] - other.matrix[i][j];
            }
        }
        return temp;
    }

    ComplexMatrix operator / (const ComplexMatrix &other){
        ComplexMatrix temp;

        for(int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                temp[i][j] = this->matrix[i][j] / other.matrix[i][j];
            }
        }
        return temp;
    }

    ComplexMatrix operator * (const ComplexMatrix &other){
        ComplexMatrix temp;

        for(int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                temp[i][j] = this->matrix[i][j] * other.matrix[i][j];
            }
        }
        return temp;
    }

    ComplexMatrix operator ++ (int) const{
        ComplexMatrix temp;

        for(int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                temp[i][j]++;
            }
        }
        return temp;
    }

    ComplexMatrix operator -- (int) const{
        ComplexMatrix temp;

        for(int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                temp[i][j]--;
            }
        }
        return temp;
    }


    Complex* operator [](const int index)
    {
        return matrix[index];
    }

    void PrintMatrix(int sizeToPrint){
        for( int i = 0; i <= sizeToPrint-1; i++){
            cout << endl;
            for(int j = 0; j <= sizeToPrint-1; j++){
                cout<<"[" << i+1 << "]["<< j+1 << "] = " << matrix[i][j].real << " + " << matrix[i][j].imag << "*I ";
            }
        }
    }
};


void menuChoice(){
    cout << endl << endl << "1. Choose operation to do with matrix" << endl << "2. Show source matrix" << endl << "3. exit" << endl;
}
void optionToDo(){
    cout << endl << "Operations with matrix: "
    << endl << "1. +"
    << endl << "2. -"
    << endl << "3. *"
    << endl << "4. ++(postfix) /for complex number"
    << endl << "5. --(postfix) /for complex number"
    << endl << "6. operator <<"
    << endl << "7. (c = ++a - b--)"
    << endl << endl;
}

int main(){

    int size;
    cout << "Enter the size of matrix: ";
    cin >> size;
    cout << "Input of matrix 1" << endl;
    ComplexMatrix matrix1(size);

    cout << "Matrix 1:" << endl << endl;
    matrix1.PrintMatrix(size);

    cout << endl << endl << "Input of matrix 2" << endl;
    ComplexMatrix matrix2(size);

    cout << endl << endl << "Matrix 2:" << endl << endl;
    matrix2.PrintMatrix(size);
    Complex complexShow(5, 4);
    ComplexMatrix resultMatrixSum(size, 1);
    ComplexMatrix resultMatrixExtract(size, 1);
    ComplexMatrix resultMatrixMul(size, 1);
    ComplexMatrix resultMatrixIncrDecr(size, 1);
    int menuchoice = 0;

    do{
        menuChoice();
        cin >> menuchoice;
        Complex a(2, 2), b(1, 1), c, number(10, 2);;
        switch (menuchoice) {
            case 1:
                optionToDo();
                int optiontodo; cin >> optiontodo;

                switch (optiontodo) {
                    case 1:
                        resultMatrixSum = matrix1 + matrix2;
                        cout << endl << "Result matrix:" << endl << endl;
                        resultMatrixSum.PrintMatrix(size);
                        break;

                    case 2:
                        resultMatrixExtract = matrix1 - matrix2;
                        cout << endl << "Result matrix:" << endl << endl;
                        resultMatrixExtract.PrintMatrix(size);
                        break;

                    case 3:
                        resultMatrixMul = matrix1 * matrix2;
                        cout << endl << "Result matrix:" << endl << endl;
                        resultMatrixMul.PrintMatrix(size);
                        break;

                    case 4:
                        cout << "ComplexNumber: " << complexShow << endl;
                        cout << "ComplexNumber++" << endl;
                        complexShow++;
                        cout << "ComplexNumber: " << complexShow << endl;
                        break;


                    case 5:
                        cout << "ComplexNumber: " << complexShow << endl;
                        cout << "ComplexNumber--" << endl;
                        complexShow--;
                        cout << "ComplexNumber: " << complexShow << endl;
                        break;


                    case 6:
                        cout << "Example of overloading << :" << endl;
                        cout << number << endl;
                        break;

                    case 7:
                        cout << "Example of (c = ++a - b--)" << endl;
                        cout << "a= " << a << "b= " << b << endl;
                        c = ++a - b--;
                        cout << "c = ++a - b--" << endl;
                        cout << "c= " << c;
                        cout << endl << "b= " << b;
                        cout << endl << "a= " << a;
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                cout << "Matrix 1:" << endl << endl;
                matrix1.PrintMatrix(size);
                cout << endl << endl << "Matrix 2:" << endl << endl;
                matrix2.PrintMatrix(size);
                break;
            default:
                break;
        }
    }while(menuchoice != 3);
    return 0;
}
