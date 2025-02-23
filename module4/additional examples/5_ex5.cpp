//Rocket Launch Countdown: A latch can be used to synchronize the countdown of a rocket launch. 
//All systems must be ready before the countdown reaches zero.
//The launchLatch ensures that all systems must be ready before the rocket can launch.

#include <iostream>
#include <thread>
#include <latch>

using namespace std; // Include this line to avoid using "std::" prefix

latch launchLatch(3); // Latch for 3 systems

void systemCheck(int id) {
    cout << "System " << id << " is checking...\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate check time
    launchLatch.count_down(); // Decrement the latch
    cout << "System " << id << " is ready.\n";
    launchLatch.wait(); // Wait for the countdown to reach zero
    cout << "System " << id << " is launching!\n";
}

int main() {
    thread system1(systemCheck, 1);
    thread system2(systemCheck, 2);
    thread system3(systemCheck, 3);
    system1.join();
    system2.join();
    system3.join();
    return 0;
}
