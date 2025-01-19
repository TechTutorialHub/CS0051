//Mutexes and Thread Synchronization

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx; // Mutex to protect shared data
int sharedData = 0;

void incrementData() {
    mtx.lock(); // Lock the mutex
    sharedData++;
    cout << "Shared Data: " << sharedData << endl;
    mtx.unlock(); // Unlock the mutex
}

int main() {
    thread t1(incrementData);
    thread t2(incrementData);
    t1.join();
    t2.join();
    return 0;
}

