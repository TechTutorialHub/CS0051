//#pragma acc parallel loop reduction(+:sum)

#include <iostream>
#include <openacc.h>

using namespace std;

const int N = 10;

int main() {
    int arr[N];
    long long sum = 0;

    // Initialize array
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    // Parallel Sum Calculation
    #pragma acc parallel loop reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += arr[i];
        cout << "Iteration " << i << ": sum += " << arr[i] << " --> Partial sum: " << sum << endl;
    }

    cout << "Final Sum: " << sum << endl;
    return 0;
}
