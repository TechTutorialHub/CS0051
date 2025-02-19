//barrier

#include <iostream>
#include <thread>
#include <barrier>

using namespace std; 

barrier barrier_obj(3); // Barrier for 3 threads

void worker(int id) {
    cout << "Thread " << id << " is working.\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate work
    barrier_obj.arrive_and_wait(); // Wait for all threads to reach this point
    cout << "Thread " << id << " has passed the barrier.\n";
}

int main() {
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
/*
