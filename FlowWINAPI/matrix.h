#ifndef LAB8_MATRIX_H
#define LAB8_MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <typeinfo>
#include <exception>
#include <windows.h>
#include <chrono>
#include <mutex>
using namespace std;

static mutex mtx;

template <class TYPE>
class Matrix
{
    size_t lines, cols;
    vector<vector<TYPE>> data;

public:
    Matrix();
    Matrix(size_t, size_t);
    Matrix(size_t, size_t, TYPE);
    Matrix(initializer_list<pair<pair<size_t, size_t>, TYPE>>);
    Matrix(const Matrix<TYPE> &);
    Matrix(Matrix<TYPE> &&);
    ~Matrix();

    size_t get_lines();
    size_t get_cols();
    vector<vector<TYPE>> get_data();

    static Matrix<TYPE> zeroMatrix(size_t);
    static Matrix<TYPE> oneMatrix(size_t);

    void writeTo(ostream &) const;
    void takeDataFrom(istream &);

    bool isSquare() const;
    double det() const;
    Matrix<TYPE> trans() const;
    Matrix<TYPE> minor(size_t, size_t) const;

    template <typename T>
    friend ostream &operator<<(ostream &, const Matrix<T> &);
    template <typename T>
    friend istream &operator>>(istream &, Matrix<T> &);

    friend DWORD for_plus(LPVOID param);
    Matrix<TYPE> operator+(Matrix<TYPE> &);
    friend DWORD for_minus(LPVOID param);
    Matrix<TYPE> operator-(Matrix<TYPE> &);
    friend DWORD for_multiply(LPVOID param);
    Matrix<TYPE> operator*(Matrix<TYPE> &);
    friend DWORD for_multiply_with_value(LPVOID param);
    Matrix<TYPE> operator*(TYPE);
    friend DWORD for_oBratka(LPVOID param);
    Matrix<TYPE> operator~() const;
    Matrix<TYPE> &operator=(const Matrix<TYPE> &);
    Matrix<TYPE> &operator=(Matrix<TYPE> &&);
    bool operator==(Matrix<TYPE> &);
    bool operator==(TYPE);
    bool operator<=(Matrix<TYPE> &);
    bool operator>=(Matrix<TYPE> &);
    bool operator<(Matrix<TYPE> &);
    bool operator>(Matrix<TYPE> &);
};

template <typename T>
struct help
{
    Matrix<T> mat1;
    Matrix<T> mat2;
    vector<vector<T>> tmp;
    T value;
    size_t i;
    size_t j;
};
#endif
