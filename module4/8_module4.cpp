//Laches

#include <iostream>
#include <thread>
#include <latch>

using namespace std; 

latch latch_obj(3); // Latch for 3 threads

void worker(int id) {
    cout << "Thread " << id << " is working.\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate work
    latch_obj.count_down(); // Decrement the latch counter
    latch_obj.wait(); // Wait for the latch to reach zero
    cout << "Thread " << id << " has passed the latch.\n";
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
