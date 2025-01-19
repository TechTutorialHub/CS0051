//WITH DEADLOCK

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx1, mtx2; // Two mutexes for synchronization

void task1() {
    cout << "Thread 1 is attempting to lock mtx1." << endl;
    mtx1.lock(); // Thread 1 locks mtx1
    cout << "Thread 1 has locked mtx1." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate some work
    
    cout << "Thread 1 is attempting to lock mtx2." << endl;
    mtx2.lock(); // Thread 1 waits for mtx2 (which is held by Thread 2)
    cout << "Thread 1 has locked mtx2." << endl;
    
    // Critical section
    cout << "Thread 1 is running." << endl;
    
    mtx2.unlock();
    mtx1.unlock();
}

void task2() {
    cout << "Thread 2 is attempting to lock mtx2." << endl;
    mtx2.lock(); // Thread 2 locks mtx2
    cout << "Thread 2 has locked mtx2." << endl;
    
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate some work
    
    cout << "Thread 2 is attempting to lock mtx1." << endl;
    mtx1.lock(); // Thread 2 waits for mtx1 (which is held by Thread 1)
    cout << "Thread 2 has locked mtx1." << endl;
    
    // Critical section
    cout << "Thread 2 is running." << endl;
    
    mtx1.unlock();
    mtx2.unlock();
}

int main() {
    cout << "Starting threads..." << endl;
    thread t1(task1); // Thread 1
    thread t2(task2); // Thread 2
    
    t1.join();
    t2.join();
    
    cout << "Both threads have finished." << endl;
    return 0;
}
