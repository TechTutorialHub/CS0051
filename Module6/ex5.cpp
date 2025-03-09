#include <iostream>
#include <openacc.h>

using namespace std;

const int N = 5; // Array Size

int main() {
    int arr[N] = {10, 3, 5, 1, 4};

    // Parallel Bubble Sort
    #pragma acc data copy(arr)
    for (int i = 0; i < N - 1; i++) {
        #pragma acc parallel loop
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                // Print iteration output
                #pragma acc atomic
                cout << "Swapped " << arr[j] << " and " << arr[j + 1] << endl;
            }
        }
    }

    // Print the final sorted array
    cout << "Sorted Array: ";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
