//CPU-Only (Sequential) Version
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

const int N = 1000000; // Large data set

// Function to generate random numbers
void generateData(vector<int> &arr) {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }
}

// Sequential (CPU) computation: Sum of squares
long long sumOfSquaresCPU(const vector<int> &arr) {
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += arr[i] * arr[i];
    }
    return sum;
}

int main() {
    vector<int> data(N);

    generateData(data);

    // Measure CPU time
    auto startCPU = high_resolution_clock::now();
    long long resultCPU = sumOfSquaresCPU(data);
    auto endCPU = high_resolution_clock::now();

    // Calculate time in milliseconds
    double timeCPU = duration<double, milli>(endCPU - startCPU).count();

    cout << "Sum of squares (CPU): " << resultCPU << endl;
    cout << "Execution Time (CPU): " << timeCPU << " ms" << endl;

    return 0;
}
