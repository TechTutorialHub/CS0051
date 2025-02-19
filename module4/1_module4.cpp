//Semaphores
#include <iostream>
#include <thread>
#include <semaphore>

using namespace std; 

binary_semaphore sem(1); // Initialize semaphore with value 1 (binary semaphore)

void critical_section(int id) {
    sem.acquire(); // Wait for semaphore
    cout << "Thread " << id << " is in the critical section.\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate work
    cout << "Thread " << id << " is leaving the critical section.\n";
    sem.release(); // Release semaphore
}

int main() {
    thread t1(critical_section, 1); // Create thread 1
    thread t2(critical_section, 2); // Create thread 2
    t1.join(); // Wait for thread 1 to finish
    t2.join(); // Wait for thread 2 to finish
    return 0;
}
