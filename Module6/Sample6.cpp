//Partitioning	
//Matrix Addition	
//Splits work across CPU threads


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

const int N = 4; // Matrix Size

void generateMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10;
}

void printMatrix(const string &name, int matrix[N][N]) {
    cout << name << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

int main() {
    srand(time(0));

    int A[N][N], B[N][N], C[N][N];

    generateMatrix(A);
    generateMatrix(B);

    printMatrix("Matrix A", A);
    printMatrix("Matrix B", B);

    // Parallel Matrix Addition
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];

    printMatrix("Matrix C (A + B)", C);

    return 0;
}
