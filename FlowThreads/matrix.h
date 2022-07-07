#ifndef LAB8_MATRIX_H
#define LAB8_MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <typeinfo>
#include <thread>
#include <mutex>
#include <chrono>
#include <exception>
#include <windows.h>
using namespace std;

static mutex mtx;

template<class TYPE>
class Matrix{
    size_t lines, cols;
    vector<vector<TYPE>> data;
public:
    using data_type = vector<vector<TYPE>>;

    Matrix();
    Matrix(size_t, size_t);
    Matrix(size_t, size_t, TYPE);
    Matrix(initializer_list<pair<pair<size_t, size_t>, TYPE>>);
    Matrix(const Matrix<TYPE>&);
    Matrix(Matrix<TYPE>&&);
    ~Matrix();

    static Matrix<TYPE> zeroMatrix(size_t);
    static Matrix<TYPE> oneMatrix(size_t);

    void writeTo(ostream&) const;
    void takeDataFrom(istream&);

    bool isSquare() const;
    double det() const;
    Matrix<TYPE> trans() const;
    Matrix<TYPE> minor(size_t, size_t) const;

    template<typename T>
    friend ostream& operator <<(ostream&, const Matrix<T>&);
    template<typename T>
    friend istream& operator >>(istream&, Matrix<T>&);

    Matrix<TYPE> operator +(Matrix<TYPE>&);
    Matrix<TYPE> operator -(Matrix<TYPE>&);
    Matrix<TYPE> operator *(Matrix<TYPE>&);
    Matrix<TYPE> operator *(TYPE);
    Matrix<TYPE> operator ~() const;
    Matrix<TYPE>& operator =(const Matrix<TYPE>&);
    Matrix<TYPE>& operator =(Matrix<TYPE>&&);
    bool operator ==(Matrix<TYPE>&);
    bool operator ==(TYPE);
    bool operator <=(Matrix<TYPE>&);
    bool operator >=(Matrix<TYPE>&);
    bool operator <(Matrix<TYPE>&);
    bool operator >(Matrix<TYPE>&);
};
#endif
