//Deadlock Avoidance

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx1, mtx2; // Two mutexes for synchronization

void task1(int threadId) {
    cout << "Thread " << threadId << " is attempting to lock mtx1 and mtx2." << endl;
    scoped_lock lock(mtx1, mtx2); // Automatically locks both mutexes (deadlock-safe)
    cout << "Thread " << threadId << " has locked mtx1 and mtx2. Task 1 is running." << endl;
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    cout << "Thread " << threadId << " is releasing mtx1 and mtx2." << endl;
}

void task2(int threadId) {
    cout << "Thread " << threadId << " is attempting to lock mtx1 and mtx2." << endl;
    scoped_lock lock(mtx1, mtx2); // Automatically locks both mutexes (deadlock-safe)
    cout << "Thread " << threadId << " has locked mtx1 and mtx2. Task 2 is running." << endl;
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    cout << "Thread " << threadId << " is releasing mtx1 and mtx2." << endl;
}

int main() {
    cout << "Starting threads..." << endl;
    thread t1(task1, 1); // Thread 1 with ID 1
    thread t2(task2, 2); // Thread 2 with ID 2
    
    t1.join();
    t2.join();
    
    cout << "Both threads have finished." << endl;
    return 0;
}
