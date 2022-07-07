#include "matrix.h"
#define LIMIT 100

template <typename T>
Matrix<T>::Matrix() : lines(0), cols(0), data() {}

template <typename T>
Matrix<T>::Matrix(size_t lines, size_t cols) : lines(lines), cols(cols)
{
    data.resize(lines);
}

template <typename T>
Matrix<T>::Matrix(size_t lines, size_t cols, T value) : lines(lines), cols(cols)
{
    data.resize(lines);
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == j)
            {
                data[i].push_back(value);
            }
            else
            {
                data[i].push_back(0);
            }
        }
    }
}

template <typename T>
Matrix<T>::Matrix(initializer_list<pair<pair<size_t, size_t>, T>> list)
{
    size_t cnt = 0;
    lines = 0;
    cols = 0;
    for (auto x : list)
    {
        if (cnt % 3 == 0 && lines <= x.first.first)
        {
            lines = x.first.first + 1;
        }
        else if (cnt % 3 == 1 && cols <= x.first.second)
        {
            cols = x.first.second + 1;
        }
        cnt++;
    }
    data.resize(lines);
    for (size_t i = 0; i < lines; i++)
    {
        data[i].resize(cols);
    }
    for (auto x : list)
    {
        data[x.first.first][x.first.second] = x.second;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &other)
{
    lines = other.lines;
    cols = other.cols;
    data = other.data;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&other)
{
    lines = other.lines;
    cols = other.cols;
    data = other.data;
    other.lines = 0;
    other.cols = 0;
    other.data.clear();
}

template <typename T>
Matrix<T>::~Matrix()
{
    data.clear();
}

template <typename T>
size_t Matrix<T>::get_lines() { return lines; }
template <typename T>
size_t Matrix<T>::get_cols() { return cols; }
template <typename T>
vector<vector<T>> Matrix<T>::get_data() { return data; }

template <typename T>
Matrix<T> Matrix<T>::zeroMatrix(size_t dim)
{
    if (typeid(T) != typeid(string) && typeid(T) != typeid(char))
    {
        Matrix<T> mat(dim, dim, 0);
        return mat;
    }
    else
    {
        try
        {
            throw logic_error("!!!Попытка создания нулевой матрицы типа string/char!!!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        Matrix<T> mat(dim, dim);
        return mat;
    }
}

template <typename T>
Matrix<T> Matrix<T>::oneMatrix(size_t dim)
{
    if (typeid(T) != typeid(string) && typeid(T) != typeid(char))
    {
        Matrix<T> mat(dim, dim, 0);
        return mat;
    }
    else
    {
        try
        {
            throw logic_error("Попытка создания еденичной матрицы типа string/char!!!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        Matrix<T> mat(dim, dim);
        return mat;
    }
}

template <typename T>
void Matrix<T>::writeTo(ostream &out) const
{
    if (out)
    {
        out << *this;
    }
    else
    {
        try
        {
            throw logic_error("Файл для записи не открывается!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
    }
}

template <typename T>
void Matrix<T>::takeDataFrom(istream &in)
{
    if (in)
    {
        in >> *this;
    }
    else
    {
        try
        {
            throw logic_error("Файл для чтения не открывается!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
    }
}

template <typename T>
bool Matrix<T>::isSquare() const
{
    if (cols != lines)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <typename T>
double Matrix<T>::det() const
{
    if (isSquare() && typeid(*this) != typeid(Matrix<string>))
    {
        size_t dim = lines;
        if (dim == 1)
        {
            return data[0][0];
        }
        if (dim == 2)
        {
            return (data[0][0] * data[1][1] - data[0][1] * data[1][0]);
        }
        else
        {
            Matrix<T> tmp(dim - 1, dim - 1, 0);
            double det = 0;
            int k1, k2;
            for (size_t i = 0; i < dim; i++)
            {
                k1 = 0;
                for (size_t j = 1; j < dim; j++)
                {
                    k2 = 0;
                    for (size_t k = 0; k < dim; k++)
                    {
                        if (k != i)
                        {
                            tmp.data[k1][k2] = data[j][k];
                            k2++;
                        }
                    }
                    k1++;
                }
                det += pow(-1, i + 2) * data[0][i] * tmp.det();
            }
            return det;
        }
    }
    else
    {
        try
        {
            throw logic_error("Det передает привет!Ошибка размера либо типа матрицы!!!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        return 0;
    }
}

template <typename T>
Matrix<T> Matrix<T>::trans() const
{
    Matrix<T> mat(cols, lines);
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < lines; j++)
        {
            mat.data[i].push_back(data[j][i]);
        }
    }
    return mat;
}

template <typename T>
Matrix<T> Matrix<T>::minor(size_t x, size_t y) const
{
    if (isSquare())
    {
        size_t dim = lines;
        size_t k1, k2;
        Matrix<T> tmp(dim - 1, dim - 1);
        k1 = 0;
        for (size_t i = 0; i < dim; i++)
        {
            k2 = 0;
            for (size_t j = 0; j < dim; j++)
            {
                if ((i != x) && (j != y))
                {
                    tmp.data[k1].push_back(data[i][j]);
                    k2++;
                    if (k2 % (dim - 1) == 0)
                    {
                        k1++;
                    }
                }
            }
        }
        return tmp;
    }
    else
    {
        try
        {
            throw logic_error("Невозможно найти минор прямоугольной матрицы!!!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        return *this;
    }
}

template <typename T>
ostream &operator<<(ostream &out, const Matrix<T> &mat)
{
    mtx.lock();
    if (!(mat.data.empty()))
    {
        for (int i = 0; i < mat.lines; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                out << mat.data[i][j] << "\t";
            }
            out << endl;
        }
        out << endl;
        mtx.unlock();
        return out;
    }
    else
    {
        try
        {
            throw logic_error("Хехехе, вывод матрицы без данных, серьезно?)");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        return out;
    }
}

template <typename T>
istream &operator>>(istream &in, Matrix<T> &mat)
{
    mtx.lock();
    if (mat.lines + mat.cols == 0)
    {
        in >> mat.lines >> mat.cols;
    }
    mat.data.resize(mat.lines);
    T value;
    for (size_t i = 0; i < mat.lines; i++)
    {
        for (size_t j = 0; j < mat.cols; j++)
        {
            in >> value;
            mat.data[i].push_back(value);
        }
    }
    mtx.unlock();
    return in;
}

template <typename T>
DWORD for_plus(LPVOID param)
{
    help<T> *ptr = (help<T> *)param;
    size_t cnt = ptr->i;
    mtx.unlock();
    for (size_t j = 0; j < ptr->mat1.get_cols(); j++)
    {
        ptr->tmp[cnt][j] = ptr->mat1.get_data()[cnt][j] + ptr->mat2.get_data()[cnt][j];
    }
    return 0;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> &mat)
{
    if (lines == mat.lines && cols == mat.cols)
    {
        Matrix<T> tmp(lines, cols, 0);
        HANDLE threads[lines];
        help<T> Helper;
        Helper.mat1 = *this;
        Helper.mat2 = mat;
        Helper.tmp = tmp.data;
        Helper.i = 0;
        size_t lim = LIMIT;
        size_t countOfThreads = 0;
        for (size_t i = 0; i < lines; i++)
        {
            if (lim != 0)
            {
                mtx.lock();
                threads[i] = CreateThread(NULL, 0, for_plus<T>, (void *)&Helper, 0, 0);
                Helper.i = i;
                lim--;
            }
            else
            {
                while (lim != LIMIT)
                {
                    WaitForSingleObject(threads[countOfThreads], INFINITE);
                    countOfThreads++;
                    lim++;
                }
                i--;
            }
        }
        while (lim != LIMIT)
        {
            WaitForSingleObject(threads[countOfThreads], INFINITE);
            countOfThreads++;
            lim++;
        }
        tmp.data = Helper.tmp;
        return tmp;
    }
    else
    {
        try
        {
            throw logic_error("Невозможно суммировать матрицы разных размеров!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        return *this;
    }
}

template <typename T>
DWORD for_minus(LPVOID param)
{
    help<T> *ptr = (help<T> *)param;
    size_t cnt = ptr->i;
    mtx.unlock();
    for (size_t j = 0; j < ptr->mat1.get_cols(); j++)
    {
        ptr->tmp[cnt][j] = ptr->mat1.get_data()[cnt][j] - ptr->mat2.get_data()[cnt][j];
    }
    return 0;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> &mat)
{
    if (lines == mat.lines && cols == mat.cols)
    {
        Matrix<T> tmp(lines, cols, 0);
        HANDLE threads[lines];
        help<T> Helper;
        Helper.mat1 = *this;
        Helper.mat2 = mat;
        Helper.tmp = tmp.data;
        Helper.i = 0;
        size_t lim = LIMIT;
        size_t countOfThreads = 0;
        for (size_t i = 0; i < lines; i++)
        {
            if (lim != 0)
            {
                mtx.lock();
                threads[i] = CreateThread(NULL, 0, for_minus<T>, (void *)&Helper, 0, 0);
                Helper.i = i;
                lim--;
            }
            else
            {
                while (lim != LIMIT)
                {
                    WaitForSingleObject(threads[countOfThreads], INFINITE);
                    countOfThreads++;
                    lim++;
                }
                i--;
            }
        }
        while (lim != LIMIT)
        {
            WaitForSingleObject(threads[countOfThreads], INFINITE);
            countOfThreads++;
            lim++;
        }
        tmp.data = Helper.tmp;
        return tmp;
    }
    else
    {
        try
        {
            throw logic_error("Нельзя вычитать матрицы разных размеров!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        return *this;
    }
}

template <typename T>
DWORD for_multiply(LPVOID param)
{
    help<T> *ptr = (help<T> *)param;
    size_t cnt_i = ptr->i;
    size_t cnt_j = ptr->j;
    mtx.unlock();
    for (size_t k = 0; k < ptr->mat1.get_lines(); k++)
    {
        ptr->tmp[cnt_i][cnt_j] += ptr->mat1.get_data()[cnt_i][k] * ptr->mat2.get_data()[k][cnt_j];
    }
    return 0;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &mat)
{
    if (cols == mat.lines)
    {
        Matrix<T> tmp(lines, mat.cols, 0);
        HANDLE threads[mat.cols];
        help<T> Helper;
        Helper.mat1 = *this;
        Helper.mat2 = mat;
        Helper.tmp = tmp.data;
        Helper.i = 0;
        Helper.j = 0;
        size_t lim = LIMIT;
        size_t countOfThreads = 0;
        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                if (lim != 0)
                {
                    mtx.lock();
                    threads[j] = CreateThread(NULL, 0, for_multiply<T>, (void *)&Helper, 0, 0);
                    Helper.i = i;
                    Helper.j = j;
                    lim--;
                }
                else
                {
                    while (lim != LIMIT)
                    {
                        WaitForSingleObject(threads[countOfThreads], INFINITE);
                        countOfThreads++;
                        if (countOfThreads == mat.cols)
                        {
                            countOfThreads %= mat.cols;
                        }
                        lim++;
                    }
                    j--;
                }
            }
        }
        while (lim != LIMIT)
        {
            WaitForSingleObject(threads[countOfThreads], INFINITE);
            countOfThreads++;
            if (countOfThreads == mat.cols)
            {
                countOfThreads %= mat.cols;
            }
            lim++;
        }
        tmp.data = Helper.tmp;
        return tmp;
    }
    else
    {
        try
        {
            throw logic_error("Матрицы некорректных размеров!!!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        return *this;
    }
}

template <typename T>
DWORD for_multiply_with_value(LPVOID param)
{
    help<T> *ptr = (help<T> *)param;
    size_t cnt = ptr->i;
    mtx.unlock();
    for (size_t j = 0; j < ptr->mat1.get_cols(); j++)
    {
        ptr->tmp[cnt][j] = ptr->mat1.get_data()[cnt][j] * ptr->value;
    }
    return 0;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T value)
{
    if (!data.empty())
    {
        Matrix<T> tmp(lines, cols, 0);
        HANDLE threads[lines];
        help<T> Helper;
        Helper.mat1 = *this;
        Helper.tmp = tmp.data;
        Helper.i = 0;
        Helper.value = value;
        size_t lim = LIMIT;
        size_t countOfThreads = 0;
        for (size_t i = 0; i < lines; i++)
        {
            if (lim != 0)
            {
                mtx.lock();
                threads[i] = CreateThread(NULL, 0, for_multiply_with_value<T>, (void *)&Helper, 0, 0);
                Helper.i = i;
                lim--;
            }
            else
            {
                while (lim != LIMIT)
                {
                    WaitForSingleObject(threads[countOfThreads], INFINITE);
                    countOfThreads++;
                    lim++;
                }
                i--;
            }
        }
        while (lim != LIMIT)
        {
            WaitForSingleObject(threads[countOfThreads], INFINITE);
            countOfThreads++;
            lim++;
        }
        tmp.data = Helper.tmp;
        return tmp;
    }
    else
    {
        try
        {
            throw logic_error("Матрица пуста!!!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        return *this;
    }
}

template <typename T>
DWORD for_oBratka(LPVOID param)
{
    help<T> *ptr = (help<T> *)param;
    size_t cnt = ptr->i;
    mtx.unlock();
    for (size_t j = 0; j < ptr->mat1.get_cols(); j++)
    {
        ptr->tmp[cnt][j] = ptr->mat1.minor(cnt, j).det() * ((1 / ptr->mat1.det()) * pow(-1, cnt + j));
    }
    return 0;
}

template <typename T>
Matrix<T> Matrix<T>::operator~() const
{
    if (isSquare() && det() != 0)
    {
        Matrix<T> tmp(lines, cols, 0);
        HANDLE threads[lines];
        help<T> Helper;
        Helper.mat1 = *this;
        Helper.tmp = tmp.data;
        Helper.i = 0;
        size_t lim = LIMIT;
        size_t countOfThreads = 0;
        for (size_t i = 0; i < lines; i++)
        {
            if (lim != 0)
            {
                mtx.lock();
                threads[i] = CreateThread(NULL, 0, for_oBratka<T>, (void *)&Helper, 0, 0);
                Helper.i = i;
                lim--;
            }
            else
            {
                while (lim != LIMIT)
                {
                    WaitForSingleObject(threads[countOfThreads], INFINITE);
                    countOfThreads++;
                    lim++;
                }
                i--;
            }
        }
        while (lim != LIMIT)
        {
            WaitForSingleObject(threads[countOfThreads], INFINITE);
            countOfThreads++;
            lim++;
        }
        tmp.data = Helper.tmp;
        return tmp.trans();
    }
    else
    {
        try
        {
            throw logic_error("Невозможно вычислить обратную матрицу!!!");
        }
        catch (const exception &ex)
        {
            cout << ex.what() << endl;
        }
        return *this;
    }
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &mat)
{
    lines = mat.lines;
    cols = mat.cols;
    data = mat.data;
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&mat)
{
    lines = mat.lines;
    cols = mat.cols;
    data = mat.data;
    mat.lines = 0;
    mat.cols = 0;
    mat.data.clear();
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(Matrix<T> &mat)
{
    if (lines != mat.lines || cols != mat.cols || data != mat.data)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <typename T>
bool Matrix<T>::operator==(T value)
{
    Matrix<T> mat(lines, cols, value);
    if (*this == mat)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Matrix<T>::operator<=(Matrix<T> &mat)
{
    if (lines + cols <= mat.cols + mat.lines)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Matrix<T>::operator>=(Matrix<T> &mat)
{
    if (lines + cols >= mat.cols + mat.lines)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Matrix<T>::operator<(Matrix<T> &mat)
{
    if (lines + cols <= mat.cols + mat.lines)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Matrix<T>::operator>(Matrix<T> &mat)
{
    if (lines + cols >= mat.cols + mat.lines)
    {
        return true;
    }
    else
    {
        return false;
    }
}