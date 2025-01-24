//Fixing Starvation
//the highPriorityThread waits until highPriorityTurn is true.
//Once it acquires the lock, it prints the boolean value (true), performs its work, sets highPriorityTurn to false, and notifies the other thread.

//The lowPriorityThread waits until highPriorityTurn is false.
//Once it acquires the lock, it prints the boolean value (false), performs its work, sets highPriorityTurn to true, and notifies the other thread.

//The condition_variable ensures that threads wait for their turn and are notified when the lock is available.
//The boolean flag (highPriorityTurn) ensures that threads alternate access, preventing one thread from monopolizing the lock.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;  // Mutex to protect shared resource
condition_variable cv;  // Condition variable for fair scheduling
bool highPriorityTurn = true;  // Flag to alternate access

// High-priority thread function
void highPriorityThread() {
    for (int i = 0; i < 5; ++i) {
        unique_lock<mutex> lock(mtx);  // Lock the mutex

        // Wait until it's the high-priority thread's turn
        cv.wait(lock, []() { return highPriorityTurn; });

        cout << "High-priority thread is working in iteration " << i << endl;
        cout << "Boolean value (highPriorityTurn): " << boolalpha << highPriorityTurn << endl;  // Print boolean value as true/false
        this_thread::sleep_for(chrono::milliseconds(200));  // Simulate work

        highPriorityTurn = false;  // Switch turn to low-priority thread
        cv.notify_all();  // Notify other threads
    }
}

// Low-priority thread function
void lowPriorityThread() {
    for (int i = 0; i < 5; ++i) {
        unique_lock<mutex> lock(mtx);  // Lock the mutex

        // Wait until it's the low-priority thread's turn
        cv.wait(lock, []() { return !highPriorityTurn; });

        cout << "Low-priority thread is working in iteration " << i << endl;
        cout << "Boolean value (highPriorityTurn): " << boolalpha << highPriorityTurn << endl;  // Print boolean value as true/false
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate work

        highPriorityTurn = true;  // Switch turn to high-priority thread
        cv.notify_all();  // Notify other threads
    }
}

int main() {
    cout << "Starting fair scheduling simulation..." << endl;

    // Create threads
    thread highPriority(highPriorityThread);
    thread lowPriority(lowPriorityThread);

    // Join threads
    highPriority.join();
    lowPriority.join();

    cout << "Fair scheduling simulation completed." << endl;
    return 0;
}
