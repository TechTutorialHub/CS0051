#include <iostream>
#include <cstdlib>
#include <ctime>
#include <openacc.h>

using namespace std;

const int N = 10; // Array Size

// Function to generate a random array
void generateArray(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 100;  // Random values between 0-99
}

// Function to print an array
void printArray(const string &name, int arr[], int size) {
    cout << name << ": ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Parallel Bubble Sort using OpenACC
void parallelBubbleSort(int arr[], int size) {
    #pragma acc data copy(arr)
    for (int i = 0; i < size - 1; i++) {
        #pragma acc parallel loop independent
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap without using `algorithm` library
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                // Print iteration output
                #pragma acc atomic
                cout << "Swapped " << arr[j] << " and " << arr[j + 1] << endl;
            }
        }
    }
}

int main() {
    int arr[N];

    generateArray(arr, N);
    printArray("Unsorted Array", arr, N);

    parallelBubbleSort(arr, N);

    printArray("Sorted Array", arr, N);

    return 0;
}
