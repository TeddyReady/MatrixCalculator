#include "matrix.cpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    auto start = chrono::high_resolution_clock::now();
    ofstream outputFile("outputFile.txt");
    ifstream inputFile("inputFile.txt");

    Matrix<double> s1, s2, s3;

    s1.takeDataFrom(inputFile);
    s2.takeDataFrom(inputFile);
    s3 = s1 + s2; s3.writeTo(outputFile);
    s3 = s1 * s2; s3.writeTo(outputFile);
    s3 = ~s1; s3.writeTo(outputFile);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout << endl << "Программа выполнена за " << duration.count() << " с";
    return 0;
}
