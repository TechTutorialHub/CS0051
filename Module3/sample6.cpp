//Nested Function Calls Without Reentrant Lock or Mutex
//program demonstrates nested function calls without any concurrency or synchronization mechanisms like mutexes or locks.
//Since there are no threads or shared resources, no locks or mutexes are needed.

#include <iostream>
using namespace std;
// Inner function
void innerFunction(int level) {
    cout << "Entering innerFunction. Level = " << level << endl;
    cout << "Exiting innerFunction. Level = " << level << endl;
}

// Middle function
void middleFunction(int level) {
    cout << "Entering middleFunction. Level = " << level << endl;
    innerFunction(level + 1);  // Call the inner function
    cout << "Exiting middleFunction. Level = " << level << endl;
}

// Outer function
void outerFunction(int level) {
    cout << "Entering outerFunction. Level = " << level << endl;
    middleFunction(level + 1);  // Call the middle function
    cout << "Exiting outerFunction. Level = " << level << endl;
}

int main() {
    cout << "Starting nested function calls..." << endl;
    outerFunction(1);  // Start the nested calls with level 1
    cout << "Nested function calls completed." << endl;
    return 0;
}
