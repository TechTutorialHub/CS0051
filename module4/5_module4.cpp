//try_acquire_for()
//Function: Tries to decrement the internal counter, blocking for up to a specified duration. Returns true if successful, otherwise false.

#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

using namespace std; 

counting_semaphore<1> sem(0); // Initialize semaphore with 0 (resource is unavailable)

void worker() {
    auto deadline = chrono::system_clock::now() + chrono::seconds(2); // Set deadline 2 seconds from now
    cout << "Worker is trying to acquire the resource until the deadline...\n";
    if (sem.try_acquire_until(deadline)) {
        cout << "Worker has acquired the resource.\n";
    } else {
        cout << "Worker failed to acquire the resource before the deadline.\n";
    }
}

int main() {
    thread t(worker);
    this_thread::sleep_for(chrono::seconds(3)); // Simulate a delay longer than the deadline
    sem.release(); // Release the resource
    t.join();
    return 0;
}
