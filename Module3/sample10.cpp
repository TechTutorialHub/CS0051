//A deadlock occurs when two or more threads are blocked forever, each waiting for the other to release a lock.
//this program, Thread 1 locks mutex 1 and then tries to lock mutex 2, while Thread 2 locks mutex 2 and then tries to lock mutex 1.
//Both threads end up waiting for each other, causing a deadlock.
//How the Deadlock Happens:
//Thread 1 locks mutex 1 and then tries to lock mutex 2.
//At the same time, Thread 2 locks mutex 2 and then tries to lock mutex 1.
//Since both threads are holding one lock and waiting for the other, they are stuck forever.


#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx1;  // First mutex
mutex mtx2;  // Second mutex

// Function for Thread 1
void thread1() {
    for (int i = 0; i < 3; ++i) {
        mtx1.lock();  // Lock mutex 1
        cout << "Thread 1 locked mutex 1 in iteration " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate work

        mtx2.lock();  // Try to lock mutex 2 (will cause deadlock)
        cout << "Thread 1 locked mutex 2 in iteration " << i << endl;

        // Critical section (never reached due to deadlock)
        cout << "Thread 1 is working in iteration " << i << endl;

        mtx2.unlock();  // Unlock mutex 2
        mtx1.unlock();  // Unlock mutex 1
    }
}

// Function for Thread 2
void thread2() {
    for (int i = 0; i < 3; ++i) {
        mtx2.lock();  // Lock mutex 2
        cout << "Thread 2 locked mutex 2 in iteration " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate work

        mtx1.lock();  // Try to lock mutex 1 (will cause deadlock)
        cout << "Thread 2 locked mutex 1 in iteration " << i << endl;

        // Critical section (never reached due to deadlock)
        cout << "Thread 2 is working in iteration " << i << endl;

        mtx1.unlock();  // Unlock mutex 1
        mtx2.unlock();  // Unlock mutex 2
    }
}

int main() {
    cout << "Starting deadlock simulation..." << endl;

    thread t1(thread1);  // Create Thread 1
    thread t2(thread2);  // Create Thread 2

    t1.join();  // Wait for Thread 1 to finish (will never happen due to deadlock)
    t2.join();  // Wait for Thread 2 to finish (will never happen due to deadlock)

    cout << "Program completed." << endl;  // This line will never be reached
    return 0;
}
