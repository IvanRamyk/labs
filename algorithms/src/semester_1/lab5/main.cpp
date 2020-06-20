#include <iostream>
#include <vector>
#include <chrono>

using std::cout;
using std::cin;
using std::vector;
using std::string;


struct Matrix{
    int ** values;
    int rows;
    int columns;
    Matrix() {};
    Matrix(int _rows, int _columns){
        rows = _rows;
        columns = _columns;
        values = new int* [rows];
        for (int i = 0; i < rows; ++i)
            values[i] = new int[columns];
    }
    void read(){
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                cin >> values[i][j];
    }
    void null(){
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                values[i][j] = 0;
    }
    void print(){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j)
                cout << values[i][j] << " ";
            cout << "\n";
        }
    }
    void random(){
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                values[i][j] = rand() % 10;
    }
    ~Matrix(){

    }
};

bool operator ==(Matrix A, Matrix B){
    if (A.rows != B.rows || A.columns != B.columns)
        return false;
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < A.columns; ++j)
            if (A.values[i][j] != B.values[i][j])
                return false;
    return true;
}

Matrix operator +(Matrix A, Matrix B){
    Matrix res = Matrix(A.rows, A.columns);
    for (int i = 0; i < res.rows; ++i)
        for (int j = 0; j < res.columns; ++j)
            res.values[i][j] = A.values[i][j] + B.values[i][j];
    return res;
}

Matrix operator -(Matrix A, Matrix B){
    Matrix res = Matrix(A.rows, A.columns);
    for (int i = 0; i < res.rows; ++i)
        for (int j = 0; j < res.columns; ++j)
            res.values[i][j] = A.values[i][j] - B.values[i][j];
    return res;
}

Matrix mulSlow(Matrix A, Matrix B){
    Matrix res = Matrix(A.rows, B.columns);
    res.null();
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < B.columns; ++j)
            for (int k = 0; k < A.columns; ++k)
                res.values[i][j] += A.values[i][k] * B.values[k][j];
    return res;
}

Matrix combine(Matrix A11, Matrix A12, Matrix A21, Matrix A22){
    Matrix A = Matrix(A11.columns * 2, A22.rows * 2);
    for (int i = 0; i < A11.rows; ++i)
        for (int j = 0; j < A11.columns; ++j){
            A.values[i][j] = A11.values[i][j];
            A.values[i][A11.rows + j] = A12.values[i][j];
            A.values[A11.rows + i][j] = A21.values[i][j];
            A.values[A11.rows + i][A11.columns + j] = A22.values[i][j];
        }
    return A;
}

void split(Matrix A, Matrix &A11, Matrix &A12, Matrix &A21, Matrix &A22){
    A11 = Matrix(A.rows / 2, A.columns / 2);
    A12 = Matrix(A.rows / 2, A.columns / 2);
    A21 = Matrix(A.rows / 2, A.columns / 2);
    A22 = Matrix(A.rows / 2, A.columns / 2);
    for (int i = 0; i < A11.rows; ++i)
        for (int j = 0; j < A11.columns; ++j){
            A11.values[i][j] = A.values[i][j];
            A12.values[i][j] = A.values[i][A11.columns + j];
            A21.values[i][j] = A.values[A11.rows + i][j];
            A22.values[i][j] = A.values[A11.rows + i][A11.columns + j];
        }
}

Matrix mulFast(Matrix A, Matrix B){
    if (A.rows <= 64){
        return mulSlow(A, B);
    }
    Matrix A11, A12, A22, A21;
    Matrix B11, B12, B22, B21;
    split(A, A11, A12, A21, A22);
    split(B, B11, B12, B21, B22);
    Matrix P1 = mulFast((A11 + A22), (B11 + B22));
    Matrix P2 = mulFast((A21 + A22), (B11));
    Matrix P3 = mulFast(A11, (B12 - B22));
    Matrix P4 = mulFast(A22, (B21 - B11));
    Matrix P5 = mulFast((A11 + A12), B22);
    Matrix P6 = mulFast((A21 - A11), (B11 + B12));
    Matrix P7 = mulFast((A12 - A22), (B21 + B22));
    Matrix C11 = P1 + P4 - P5 + P7;
    Matrix C12 = P3 + P5;
    Matrix C21 = P2 + P4;
    Matrix C22 = P1 - P2 + P3 + P6;
    return combine(C11, C12, C21, C22);
}



int main() {
    srand(time(0));
    int size;
    cin >> size;
    Matrix A = Matrix(size, size);
    A.random();
    Matrix B = Matrix(size, size);
    B.random();
    int first_timer = clock();
    Matrix C1 = mulFast(A, B);
    int second_timer = clock();
    cout <<  "for fast " << (second_timer - first_timer) / double(CLOCKS_PER_SEC) << "\n";
    second_timer = clock();
    Matrix C2 = mulSlow(A, B);
    first_timer = clock();
    cout <<  "for slow " << -(second_timer - first_timer) / double(CLOCKS_PER_SEC) << "\n";
    //C1.print();
    if(C1 ==  C2)
        cout << "OK\n";
    return 0;
}