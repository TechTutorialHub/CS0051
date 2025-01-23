//ths program uses two threads
//both threads are accessing the same variable at the same time, we use a mutex to make sure only one thread can change the variable at a time
//prevents errors (like race conditions) that can happen when multiple threads try to change the same thing simultaneously.

#include <iostream>  // For input/output
#include <thread>    // For creating and managing threads
#include <mutex>     // For using mutex to protect shared resources
using namespace std;
// Shared resource
int counter = 0;

// Mutex to protect the shared resource
mutex mtx;

// Function to increment the counter
void incrementCounter(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        mtx.lock();    // Lock the mutex (only one thread can proceed)
        
        // Critical section: Only one thread can execute this at a time
        ++counter;
        cout << "Thread ID: " << this_thread::get_id() 
                  << ", Counter: " << counter 
                  << ", Iteration: " << i + 1 << endl;
        
        mtx.unlock();  // Unlock the mutex (other threads can now proceed)
    }
}

int main() {
    const int iterations = 5; // Number of times each thread will increment the counter

    // Create two threads
    thread t1(incrementCounter, iterations); // Thread 1
    thread t2(incrementCounter, iterations); // Thread 2

    // Wait for both threads to finish
    t1.join();
    t2.join();

    // Print the final value of the counter
    cout << "Final Counter Value: " << counter << endl;

    return 0;
}
