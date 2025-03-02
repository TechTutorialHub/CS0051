
//Agglomeration	
//Merged Sum & Product	
//Reduces loop overhead


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

const int N = 8; // Array Size

void generateArray(int arr[N]) {
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 10 + 1;
}

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

    // Parallel computation (Agglomeration)
    #pragma omp parallel for reduction(+:sum) reduction(*:product)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
        product *= arr[i];
    }

    cout << "Sum: " << sum << endl;
    cout << "Product: " << product << endl;

    return 0;
}
