//Latch (Concert Start)
//The concertLatch ensures that both performers must be ready before the concert starts.


#include <iostream>
#include <thread>
#include <latch>

using namespace std; 

latch concertLatch(2); // Latch for 2 performers

void performer(int id) {
    cout << "Performer " << id << " is getting ready.\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate preparation time
    concertLatch.count_down(); // Decrement the latch
    concertLatch.wait(); // Wait for the concert to start
    cout << "Performer " << id << " is on stage!\n";
}

int main() {
    thread performer1(performer, 1);
    thread performer2(performer, 2);
    performer1.join();
    performer2.join();
    return 0;
}

