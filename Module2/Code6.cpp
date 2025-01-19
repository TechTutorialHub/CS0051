//Data Sharing and Race Conditions

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int sharedData = 0; // Shared data between threads
mutex mtx; // Mutex to protect shared data

void incrementData(int threadId) {
    for (int i = 0; i < 100000; i++) {
        mtx.lock(); // Lock the mutex before accessing shared data
        sharedData++; // Increment shared data
        cout << "Thread " << threadId << " incremented sharedData to: " << sharedData << endl;
        mtx.unlock(); // Unlock the mutex after accessing shared data
    }
}

int main() {
    // Create two threads
    thread t1(incrementData, 1); // Thread 1
    thread t2(incrementData, 2); // Thread 2
    
    // Wait for both threads to finish
    t1.join();
    t2.join();
    
    // Print the final value of sharedData
    cout << "Final Shared Data: " << sharedData << endl;
    return 0;
}
