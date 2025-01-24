//Avoiding Deadlock
//Both thread1 and thread2 lock mtx1 first and then mtx2.
//ensures that no circular wait can occur, as both threads follow the same order.

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx1;  // First mutex
mutex mtx2;  // Second mutex

// Function for Thread 1
void thread1() {
    for (int i = 0; i < 3; ++i) {
        // Lock mutexes in a consistent order (mtx1 first, then mtx2)
        mtx1.lock();  // Lock mutex 1
        cout << "Thread 1 locked mutex 1 in iteration " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate work

        mtx2.lock();  // Lock mutex 2
        cout << "Thread 1 locked mutex 2 in iteration " << i << endl;

        // Critical section
        cout << "Thread 1 is working in iteration " << i << endl;

        // Unlock mutexes in reverse order
        mtx2.unlock();  // Unlock mutex 2
        mtx1.unlock();  // Unlock mutex 1
    }
}

// Function for Thread 2
void thread2() {
    for (int i = 0; i < 3; ++i) {
        // Lock mutexes in the SAME order as Thread 1 (mtx1 first, then mtx2)
        mtx1.lock();  // Lock mutex 1
        cout << "Thread 2 locked mutex 1 in iteration " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate work

        mtx2.lock();  // Lock mutex 2
        cout << "Thread 2 locked mutex 2 in iteration " << i << endl;

        // Critical section
        cout << "Thread 2 is working in iteration " << i << endl;

        // Unlock mutexes in reverse order
        mtx2.unlock();  // Unlock mutex 2
        mtx1.unlock();  // Unlock mutex 1
    }
}

int main() {
    cout << "Starting program to avoid deadlock..." << endl;

    thread t1(thread1);  // Create Thread 1
    thread t2(thread2);  // Create Thread 2

    t1.join();  // Wait for Thread 1 to finish
    t2.join();  // Wait for Thread 2 to finish

    cout << "Program completed successfully without deadlock." << endl;
    return 0;
}
