#include "matrix.cpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    auto start = chrono::high_resolution_clock::now();
    ofstream outputFile("outputFile.txt");
    ifstream inputFile("inputFile.txt");

    Matrix<double> s1, s2;

    s1.takeDataFrom(inputFile);
    s2.takeDataFrom(inputFile);
    //cout << s1 + s2;
    //cout << s1 * s2;
    //cout << ~s1;

    Matrix<int> mat({{{0,0},1},{{0,1},2},{{1,1},4},{{1,0},3}});
    cout << mat;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout << endl << "Программа выполнена за " << duration.count() << " с";
    return 0;
}
