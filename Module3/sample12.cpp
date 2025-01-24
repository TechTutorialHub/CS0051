//Starvation
//Starvation occurs when a thread is unable to gain access to a necessary resource because other threads are monopolizing 
//The highPriorityThread simulates work by sleeping for 200 milliseconds, while the lowPriorityThread simulates work by sleeping for 100 milliseconds.
//The highPriorityThread monopolizes the lock, preventing the lowPriorityThread from acquiring it

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;  // Mutex to protect shared resource

// High-priority thread function
void highPriorityThread() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();  // Acquire the lock
        cout << "High-priority thread is working in iteration " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(200));  // Simulate work
        mtx.unlock();  // Release the lock
    }
}

// Low-priority thread function
void lowPriorityThread() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();  // Acquire the lock
        cout << "Low-priority thread is working in iteration " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate work
        mtx.unlock();  // Release the lock
    }
}

int main() {
    cout << "Starting starvation simulation..." << endl;

    // Create threads
    thread highPriority(highPriorityThread);
    thread lowPriority(lowPriorityThread);

    // Join threads
    highPriority.join();
    lowPriority.join();

    cout << "Starvation simulation completed." << endl;
    return 0;
}
