//Counting Semaphore (Parking Lot)
//The parkingLot semaphore allows up to 3 cars to park simultaneously. 
//If a fourth car arrives, it must wait until a space is freed.

#include <iostream>
#include <thread>
#include <semaphore>

using namespace std; 
counting_semaphore<3> parkingLot(3); // Parking lot with 3 spaces

void parkCar(int id) {
    parkingLot.acquire(); // Wait for a parking space
    cout << "Car " << id << " is parking.\n";
    this_thread::sleep_for(chrono::seconds(2)); // Simulate parking time
    cout << "Car " << id << " is leaving the parking lot.\n";
    parkingLot.release(); // Free up a parking space
}

int main() {
    thread car1(parkCar, 1);
    thread car2(parkCar, 2);
    thread car3(parkCar, 3);
    thread car4(parkCar, 4);
    car1.join();
    car2.join();
    car3.join();
    car4.join();
    return 0;
}
