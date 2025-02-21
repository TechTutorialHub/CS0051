//acquire()
//Function: Decrements the internal counter or blocks the thread until the counter can be decremented.


#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

using namespace std;

counting_semaphore<1> sem(1); // Initialize semaphore with 1 (resource is available)

void worker(int id) {
    cout << "Worker is trying to acquire the resource...\n";
    sem.acquire(); // Acquire the resource
    cout << "Worker " << id << " has acquired the resource \n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate work
    cout << "Worker " << id << " has resealse the resource \n";
    //sem.release(); // Release the resource if remarks means cannot proceed with 2nd thread value is 0
}

int main() {
    thread t1(worker,1);
    thread t2(worker,2);
    t1.join();
    t2.join();
    return 0;
}
