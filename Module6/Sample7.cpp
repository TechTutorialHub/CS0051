//Communication	
//Prefix Sum	
//Synchronizes shared data


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

const int N = 8; // Array Size

void generateArray(int arr[N]) {
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 10;
}

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

    // Parallel Prefix Sum
    prefixSum[0] = arr[0];

    #pragma omp parallel for
    for (int i = 1; i < N; i++)
        prefixSum[i] = prefixSum[i - 1] + arr[i];

    printArray("Prefix Sum", prefixSum);

    return 0;
}
