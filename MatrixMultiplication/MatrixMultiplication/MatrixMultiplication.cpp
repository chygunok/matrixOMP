// MatrixMultiplication.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

void fillMatrix(int** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = rand() % 7;
        }
    }
    return;
}

int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * n);
    }
    return matrix;
}


int main(int argc, char** argv) {

    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));

    int n = 1500;
    int** matrix1 = allocateMatrix(n);
    int** matrix2 = allocateMatrix(n);
    fillMatrix(matrix1, n);
    fillMatrix(matrix2, n);

    int** result = allocateMatrix(n);

    cout << "Кол-во потоков, время " << endl;
    for (int t = 1; t < 9; t++)
    {
        int threadsNum = t;
        omp_set_num_threads(threadsNum);
        int row, column, k;
        unsigned int start_time = clock();
        #pragma omp parallel for private(row, column, k)
        for (row = 0; row < n; row++) {
            for (column = 0; column < n; column++) {
                result[row][column] = 0;
                for (k = 0; k < n; k++) {
                    result[row][column] += (matrix1[row][k] * matrix2[k][column]);
                }
            }
        }
        unsigned int end_time = clock();
        cout <<t << "," << (end_time - start_time) / 1000 << endl;

    }
    return 0;
}
