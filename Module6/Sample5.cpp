//GPU Parallel Version (Using OpenACC)
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <openacc.h>

using namespace std;
using namespace chrono;

const int N = 1000000;

// Function to generate random numbers
void generateData(vector<int> &arr) {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }
}

// Parallel GPU computation (OpenACC)
long long sumOfSquaresGPU(const vector<int> &arr) {
    long long sum = 0;

    #pragma acc kernels
    for (int i = 0; i < N; i++) {
        sum += arr[i] * arr[i];
    }
    
    return sum;
}

int main() {
    vector<int> data(N);
    generateData(data);

    // Measure GPU time
    auto startGPU = high_resolution_clock::now();
    long long resultGPU = sumOfSquaresGPU(data);
    auto endGPU = high_resolution_clock::now();

    double timeGPU = duration<double, milli>(endGPU - startGPU).count();

    cout << "Sum of squares (GPU): " << resultGPU << endl;
    cout << "Execution Time (GPU): " << timeGPU << " ms" << endl;

    return 0;
}
