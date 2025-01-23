//recursive_mutex
//reentrant mutex allows the same thread to lock it multiple times without causing a deadlock.
//mutex keeps track of how many times it has been locked by the owning thread and must be unlocked the same number of times.
//recursiveFunction locks the reentrant mutex at the beginning of each call.
//If the count is greater than 0, the function calls itself recursively with count - 1
//After the recursive call, the mutex is unlocked.
//The mutex is locked and unlocked in each recursive call.
//mutex is reentrant, the same thread can lock it multiple times without blocking itself.

#include <iostream>
#include <mutex>
using namespace std;
recursive_mutex rmtx;  // Reentrant mutex

void recursiveFunction(int count) {
    rmtx.lock();  // Lock the reentrant mutex
    cout << "Lock acquired. Count = " << count << endl;

    if (count > 0) {
        recursiveFunction(count - 1);  // Recursive call
    }

    rmtx.unlock();  // Unlock the reentrant mutex
    cout << "Lock released. Count = " << count << endl;
}

int main() {
    cout << "Starting recursive function..." << endl;
    recursiveFunction(3);  // Call the recursive function
    recursiveFunction(5);  // Call the recursive function
    cout << "Recursive function completed." << endl;
    return 0;
}
