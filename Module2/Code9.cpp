//Using get_id() and sleep_for() to Manage Thread Execution

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void threadFunction() {
    cout << "Thread ID: " << this_thread::get_id() << " is running..." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate work by sleeping for 1 second
    cout << "Thread ID: " << this_thread::get_id() << " is finishing..." << endl;
}

int main() {
    cout << "Main thread starts..." << endl;
    thread t1(threadFunction); // Create the first thread
    thread t2(threadFunction); // Create the second thread
    
    cout << "Thread 1 ID: " << t1.get_id() << endl;
    cout << "Thread 2 ID: " << t2.get_id() << endl;
    
    t1.join(); // Wait for the first thread to finish
    t2.join(); // Wait for the second thread to finish
    
    cout << "Main thread ends..." << endl;
    return 0;
}

