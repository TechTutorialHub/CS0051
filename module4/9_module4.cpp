//Program: Asynchronous Programming

#include <iostream>
#include <future>
#include <chrono>

using namespace std; 

int long_running_task() {
    this_thread::sleep_for(chrono::seconds(2)); // Simulate long-running task
    return 42;
}

int main() {
    future<int> result = async(launch::async, long_running_task);
    cout << "Doing other work...\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate other work
    int value = result.get(); // Wait for the result
    cout << "The result is: " << value << "\n";
    return 0;
