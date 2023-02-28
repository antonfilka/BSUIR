#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h>


#define FIRST_MATRIX_ROWS 100
#define FIRST_MATRIX_COLUMNS 150
#define SECOND_MATRIX_ROWS 150
#define SECOND_MATRIX_COLUMNS 250
#define INNER_MATRIX_SIZE 12

using namespace std;
using namespace chrono;

using InnerMatrix = vector<vector<float>>;
using MainMatrix = vector<vector<InnerMatrix>>;

InnerMatrix FillInnerMatrix ();
MainMatrix FillMainMatrix (MainMatrix matrix);
void sumMatrix(InnerMatrix &matrix1, const InnerMatrix &matrix2);
InnerMatrix multiplyInnerMatrixAutomaticVectorization(InnerMatrix &matrix1, InnerMatrix &matrix2);
MainMatrix multiplyMatrixAutomaticVectorization(MainMatrix &matrix1, MainMatrix &matrix2);
InnerMatrix multiplyInnerMatrixNoVectorization(InnerMatrix &matrix1, InnerMatrix &matrix2);
MainMatrix multiplyMatrixNoVectorization(MainMatrix &matrix1, MainMatrix &matrix2);
InnerMatrix multiplyInnerMatrixHandleVectorization(InnerMatrix &matrix1, const InnerMatrix &matrix2);
MainMatrix multiplyMainMatrixHandleVectorization(MainMatrix &matrix1, MainMatrix &matrix2);

int main() {

    MainMatrix firstMatrix(FIRST_MATRIX_ROWS, {FIRST_MATRIX_COLUMNS, {INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE)}});
    MainMatrix secondMatrix(SECOND_MATRIX_ROWS, {SECOND_MATRIX_COLUMNS, {INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE)}});

    firstMatrix = FillMainMatrix(firstMatrix);
    secondMatrix = FillMainMatrix(secondMatrix);

    auto start = steady_clock::now();
    auto matrixResultAutomaticVectorization = multiplyMatrixAutomaticVectorization(firstMatrix, secondMatrix);
    auto time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    cout << "Automatic vectorization: " << time << " ms" << endl;

    start = steady_clock::now();
    auto matrixResultNoVectorization = multiplyMatrixNoVectorization(firstMatrix, secondMatrix);
    time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    cout << "No vectorization: " << time << " ms" << endl;

    start = steady_clock::now();
    auto matrixResultHandleVectorization = multiplyMainMatrixHandleVectorization(firstMatrix, secondMatrix);
    time = duration_cast<milliseconds>(steady_clock::now() - start).count();
    cout << "Intrinsics: " << time << " ms" << endl;


   for (int i =0;i<FIRST_MATRIX_ROWS; i++){
       for (int j = 0;j < SECOND_MATRIX_COLUMNS;j++){
           for (int k = 0; k < INNER_MATRIX_SIZE;k++){
               for (int l = 0; l < INNER_MATRIX_SIZE;l++){
                   if (matrixResultAutomaticVectorization[i][j][k][l] != matrixResultNoVectorization[i][j][k][l] ||
                       matrixResultAutomaticVectorization[i][j][k][l] != matrixResultHandleVectorization[i][j][k][l] ) {
                       cout << "NOT EQUAL" << endl
                       << "Automatic vectorization : " << matrixResultAutomaticVectorization[i][j][k][l] <<endl
                       << "No vectorization : " << matrixResultNoVectorization[i][j][k][l] << endl
                       << "Handle vectorization : " << matrixResultHandleVectorization[i][j][k][l] << endl
                       << i << endl << j << endl << k << endl << l << endl;
                       return 0;
                   }
               }
           }
       }
   }
   cout << "All matrices are equal" << endl;
    return 0;
}

InnerMatrix FillInnerMatrix () {
    InnerMatrix matrix(INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE));
    for (int i = 0; i < INNER_MATRIX_SIZE; i++) {
        for (int j = 0; j < INNER_MATRIX_SIZE; j++) {
            matrix[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }
    }

    return matrix;
}

MainMatrix FillMainMatrix (MainMatrix matrix) {
    for (auto &i : matrix){
        for (auto &j:i){
            j = FillInnerMatrix();
        }
    }
    return matrix;
}


void sumMatrix(InnerMatrix &matrix1, const InnerMatrix &matrix2) {
    for (int i = 0; i < INNER_MATRIX_SIZE; i++)
        for (int j = 0; j < INNER_MATRIX_SIZE; j++)
            matrix1[i][j] += matrix2[i][j];
}


[[gnu::target("sse,avx")]]
InnerMatrix multiplyInnerMatrixAutomaticVectorization(InnerMatrix &matrix1, InnerMatrix &matrix2){
    InnerMatrix result(INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE));
    for (int i = 0; i < INNER_MATRIX_SIZE; i++) {
        for (int j = 0; j < INNER_MATRIX_SIZE; j++) {
            for (int k = 0; k < INNER_MATRIX_SIZE; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

[[gnu::target("sse,avx")]]
MainMatrix multiplyMatrixAutomaticVectorization(MainMatrix &matrix1, MainMatrix &matrix2) {

    MainMatrix result(FIRST_MATRIX_ROWS, {SECOND_MATRIX_COLUMNS, {INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE)}});

    InnerMatrix temp(INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE));
    for (int i = 0; i < FIRST_MATRIX_ROWS; i++) {
        for (int j = 0; j < SECOND_MATRIX_COLUMNS; j++) {
            for (int k = 0; k < FIRST_MATRIX_COLUMNS; k++) {
                temp = multiplyInnerMatrixAutomaticVectorization(matrix1[i][k], matrix2[k][j]);
                sumMatrix(result[i][j], temp);
            }
        }
    }
    return result;
}

[[gnu::target("no-sse")]]
InnerMatrix multiplyInnerMatrixNoVectorization(InnerMatrix &matrix1, InnerMatrix &matrix2){
    InnerMatrix result(INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE));
    for (int i = 0; i < INNER_MATRIX_SIZE; i++) {
        for (int j = 0; j < INNER_MATRIX_SIZE; j++) {
            for (int k = 0; k < INNER_MATRIX_SIZE; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

[[gnu::target("no-sse")]]
MainMatrix multiplyMatrixNoVectorization(MainMatrix &matrix1, MainMatrix &matrix2) {

    MainMatrix result(FIRST_MATRIX_ROWS, {SECOND_MATRIX_COLUMNS, {INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE)}});

    InnerMatrix temp(INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE));
    for (int i = 0; i < FIRST_MATRIX_ROWS; i++) {
        for (int j = 0; j < SECOND_MATRIX_COLUMNS; j++) {
            for (int k = 0; k < FIRST_MATRIX_COLUMNS; k++) {
                temp  = multiplyInnerMatrixNoVectorization(matrix1[i][k], matrix2[k][j]);
                sumMatrix(result[i][j], temp);
            }
        }
    }
    return result;
}

InnerMatrix multiplyInnerMatrixHandleVectorization(InnerMatrix &matrix1, const InnerMatrix &matrix2){

    InnerMatrix result(INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE));
    for (int i = 0; i < INNER_MATRIX_SIZE; i++) {
        for (int j = 0; j < INNER_MATRIX_SIZE; j+=4) {

            auto sum = _mm_setzero_ps();
            for (int k = 0; k < INNER_MATRIX_SIZE; k++) {

                auto vec_matrix1 = _mm_set1_ps(matrix1[i][k]);
                auto vec_matrix2 = _mm_loadu_ps(&matrix2[k][j]);
                auto prod = _mm_mul_ps(vec_matrix1, vec_matrix2);
                sum = _mm_add_ps(sum, prod);

            }
            _mm_storeu_ps(&result[i][j], sum);

        }
    }
    return result;
}


MainMatrix multiplyMainMatrixHandleVectorization(MainMatrix &matrix1, MainMatrix &matrix2) {
    MainMatrix result(FIRST_MATRIX_ROWS,
                       {SECOND_MATRIX_COLUMNS, {INNER_MATRIX_SIZE, vector<float>(INNER_MATRIX_SIZE)}});
    for (int i = 0; i < FIRST_MATRIX_ROWS; i++) {
        for (int j = 0; j < SECOND_MATRIX_COLUMNS; j++) {
            for (int k = 0; k < FIRST_MATRIX_COLUMNS; k++) {
                auto multiplication = multiplyInnerMatrixHandleVectorization(matrix1[i][k], matrix2[k][j]);
                sumMatrix(result[i][j], multiplication);
            }
        }
    }
    return result;
}
