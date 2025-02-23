/*
Traffic Light System: A semaphore can be used to control access to a shared resource, 
such as a traffic light at an intersection. Only one direction of traffic can pass at a time, 
similar to how a binary semaphore allows only one thread to access a critical section.
*/

#include <iostream>
#include <thread>
#include <semaphore>

using namespace std; 

binary_semaphore trafficLight(1); // Traffic light is green initially

void crossIntersection(int id) {
    trafficLight.acquire(); // Wait for green light
    cout << "Car " << id << " is crossing the intersection.\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate crossing time
    cout << "Car " << id << " has crossed the intersection.\n";
    trafficLight.release(); // Signal that the intersection is free
}

int main() {
    thread car1(crossIntersection, 1);
    thread car2(crossIntersection, 2);
    car1.join();
    car2.join();
    return 0;
}
