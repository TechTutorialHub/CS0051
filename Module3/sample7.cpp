//Nested Function Calls with Reentrant Lock
//reentrant lock allows the same thread to lock the mutex multiple times without causing a deadlock.
//mutex keeps track of how many times it has been locked by the owning thread and must be unlocked the same number of times.
//outerFunction locks the reentrant mutex and calls the middleFunction.
//middleFunction locks the reentrant mutex again and calls the innerFunction.
//innerFunction locks the reentrant mutex once more.
//Each function locks the mutex at the beginning and unlocks it at the end
//Since the mutex is reentrant, the same thread can lock it multiple times without blocking itself.
//functions are called in the order: outerFunction → middleFunction → innerFunction.

#include <iostream>
#include <mutex>

using namespace std;

recursive_mutex rmtx;  // Reentrant mutex

// Inner function
void innerFunction(int level) {
    rmtx.lock();  // Lock the reentrant mutex
    cout << "Entering innerFunction. Level = " << level << endl;
    cout << "Exiting innerFunction. Level = " << level << endl;
    rmtx.unlock();  // Unlock the reentrant mutex
}

// Middle function
void middleFunction(int level) {
    rmtx.lock();  // Lock the reentrant mutex
    cout << "Entering middleFunction. Level = " << level << endl;
    innerFunction(level + 1);  // Call the inner function
    cout << "Exiting middleFunction. Level = " << level << endl;
    rmtx.unlock();  // Unlock the reentrant mutex
}

// Outer function
void outerFunction(int level) {
    rmtx.lock();  // Lock the reentrant mutex
    cout << "Entering outerFunction. Level = " << level << endl;
    middleFunction(level + 1);  // Call the middle function
    cout << "Exiting outerFunction. Level = " << level << endl;
    rmtx.unlock();  // Unlock the reentrant mutex
}

int main() {
    cout << "Starting nested function calls with reentrant lock..." << endl;
    outerFunction(1);  // Start the nested calls with level 1
    cout << "Nested function calls completed." << endl;
    return 0;
}
