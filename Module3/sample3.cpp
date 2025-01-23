//C++ Program: Recursive Function Without Mutex
//program demonstrates recursion without any concurrency or synchronization mechanisms like mutexes.
//function calls itself repeatedly until a base case is reached

#include <iostream>
using namespace std;
void recursiveFunction(int count) {
    // Base case: Stop recursion when count reaches 0
    if (count <= 0) {
        cout << "Base case reached. Count = " << count << endl;
        return;
    }

    // Print the current count
    cout << "Entering recursive function. Count = " << count << endl;

    // Recursive call with count - 1
    recursiveFunction(count - 1);

    // Print the count after returning from the recursive call
    cout << "Exiting recursive function. Count = " << count << endl;
}

int main() {
    cout << "Starting recursive function..." << endl;
    recursiveFunction(3);  // Call the recursive function with an initial count of 3
    cout << "Recursive function completed." << endl;
    return 0;
}
