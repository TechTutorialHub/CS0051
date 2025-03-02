#include <iostream>
#include <cstdlib>
#include <ctime>
#include <openacc.h>

using namespace std;

int main() {
    const int N = 10;
    int arr[N];

    srand(time(0));

    // Initialize array with random values
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    // Compute square of each element in parallel using OpenACC
    #pragma acc kernels
    for (int i = 0; i < N; i++) {
        arr[i] *= arr[i]; // Squaring each element
    }

    // Display output
    cout << "Squared Array: ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
