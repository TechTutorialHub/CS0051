#include <iostream>
#include <cstdlib>
#include <ctime>
#include <openacc.h>

using namespace std;

const int N = 8; // Array Size

// Function to generate an array with random values
void generateArray(int arr[N]) {
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 10 + 1; // Random numbers between 1-10
}

// Function to print the array
void printArray(const string &name, int arr[N]) {
    cout << name << ": ";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    srand(time(0));

    int arr[N];
    generateArray(arr);
    printArray("Original Array", arr);

    int sum = 0, product = 1;

    // OpenACC Parallel Computation (Agglomeration: Sum & Product Together)
    #pragma acc parallel loop reduction(+:sum) reduction(*:product)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
        product *= arr[i];

        // Print iteration output
        #pragma acc atomic
        cout << "Iteration " << i << ": sum += " << arr[i] 
             << ", product *= " << arr[i] << " --> Partial Sum: " 
             << sum << ", Partial Product: " << product << endl;
    }

    cout << "Final Sum: " << sum << endl;
    cout << "Final Product: " << product << endl;

    return 0;
}
