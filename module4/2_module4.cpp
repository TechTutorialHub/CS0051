//release()
//Function: Increments the internal counter and unblocks any threads waiting on the semaphore.

#include <iostream>
#include <thread>
#include <semaphore>

using namespace std; 

counting_semaphore<1> sem(0); // Initialize semaphore with 0 (resource is unavailable)

void worker() {
    cout << "Worker is waiting for the resource...\n";
    sem.acquire(); // Wait for the resource
    cout << "Worker has acquired the resource.\n";
}

int main() {
    thread t(worker);
    this_thread::sleep_for(chrono::seconds(2)); // Simulate some delay
    cout << "Main thread is releasing the resource.\n";
    sem.release(); // Release the resource
    t.join();
    return 0;
}
