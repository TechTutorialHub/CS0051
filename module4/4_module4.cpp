//try_acquire()
//Function: Tries to decrement the internal counter without blocking. Returns true if successful, otherwise false.


#include <iostream>
#include <thread>
#include <semaphore>

using namespace std; 

counting_semaphore<1> sem(0); // Initialize semaphore with 0 (resource is unavailable)

void worker() {
    if (sem.try_acquire()) {
        cout << "Worker has acquired the resource.\n";
    } else {
        cout << "Worker failed to acquire the resource.\n";
    }
}

int main() {
    thread t(worker);
    this_thread::sleep_for(chrono::seconds(1)); // Simulate some delay
    sem.release(); // Release the resource
    t.join();
    return 0;
}
