//this program demonstrate iteration without threads
//No Threads: There are no threads in this program. Everything runs in a single sequence.
//Shared Resource: The counter variable is still shared, but since there’s only one "worker" (the main program), there’s no risk of race conditions.
//Function Call: The incrementCounter function is called twice, one after the other. Each call runs completely before the next one starts.
//No Mutex: We don’t need a mutex because there’s no concurrency. Only one thing is happening at a time.

#include <iostream> 
using namespace std;
// Shared resource
int counter = 0;

// Function to increment the counter
void incrementCounter(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        // No mutex needed because there's only one "worker" (no threads)
        ++counter;
        cout << "Counter: " << counter 
                  << ", Iteration: " << i + 1 << endl;
    }
}

int main() {
    const int iterations = 5; // Number of iterations

    // Call the function twice (sequentially, not concurrently)
    incrementCounter(iterations); // First call
    incrementCounter(iterations); // Second call

    // Print the final value of the counter
    cout << "Final Counter Value: " << counter << endl;

    return 0;
}
