#include <iostream>
#include <cstdlib>
#include <ctime>
#include <openacc.h>

using namespace std;

const int N = 8; // Array Size

// Function to generate a random array
void generateArray(int arr[N]) {
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 10;  // Random values from 0-9
}

// Function to print an array
void printArray(const string &name, int arr[N]) {
    cout << name << ": ";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    srand(time(0));

    int arr[N], prefixSum[N];

    generateArray(arr);
    printArray("Original Array", arr);

    // Copy the initial value to start prefix sum calculation
    prefixSum[0] = arr[0];

    // OpenACC Parallel Prefix Sum using Data Synchronization
    #pragma acc data copyin(arr) copyout(prefixSum)
    {
        for (int i = 1; i < N; i++) {
            #pragma acc parallel loop
            for (int j = i; j < N; j++) {
                prefixSum[j] += arr[i - 1];

                // Ensure synchronization between iterations
                #pragma acc atomic
                cout << "Iteration " << j << ": prefixSum[" << j << "] = " << prefixSum[j] << endl;
            }
        }
    }

    printArray("Prefix Sum", prefixSum);

    return 0;
}
