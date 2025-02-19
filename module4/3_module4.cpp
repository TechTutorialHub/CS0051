//acquire()
//Function: Decrements the internal counter or blocks the thread until the counter can be decremented.


#include <iostream>
#include <thread>
#include <semaphore>

using namespace std;

counting_semaphore<1> sem(1); // Initialize semaphore with 1 (resource is available)

void worker() {
    cout << "Worker is trying to acquire the resource...\n";
    sem.acquire(); // Acquire the resource
    cout << "Worker has acquired the resource.\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate work
    sem.release(); // Release the resource
    cout << "Worker has released the resource.\n";
}

int main() {
    thread t(worker);
    t.join();
    return 0;
}
