//Barrier (Race Start)
//The raceBarrier ensures that all runners must be ready before the race starts.


#include <iostream>
#include <thread>
#include <barrier>

using namespace std; 

barrier raceBarrier(4); // Barrier for 4 runners

void runner(int id) {
    cout << "Runner " << id << " is ready.\n";
    raceBarrier.arrive_and_wait(); // Wait for all runners to be ready
    cout << "Runner " << id << " starts running.\n";
}

int main() {
    thread runner1(runner, 1);
    thread runner2(runner, 2);
    thread runner3(runner, 3);
    thread runner4(runner, 4);
    runner1.join();
    runner2.join();
    runner3.join();
    runner4.join();
    return 0;
}
