//Mapping	
//Parallel Sorting (Dynamic Schedule)	
//Efficient execution

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

const int N = 10; // Array Size

// Function to generate random numbers for the array
void generateArray(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 100; // Random numbers between 0-99
}

// Function to print array
void printArray(const string &name, int arr[], int size) {
    cout << name << ": ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Parallel Bubble Sort using OpenMP
void parallelBubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        // Parallelizing the inner loop with dynamic scheduling
        #pragma omp parallel for schedule(dynamic)
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap without using `algorithm` library
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
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
