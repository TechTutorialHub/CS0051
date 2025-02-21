//additional code for Async programming


#include <iostream>
#include <future>
#include <chrono>
#include <thread>
using namespace std; 

int computeSum(int a, int b) {
    this_thread::sleep_for(chrono::seconds(3)); // Simulate long-running task
    return a+b;
}

int main() {
    cout << "Starting asynchronous computation \n";
    future<int> result = async(launch::async, computeSum, 10,20);
    cout << "Main thread is doin other work \n";
    int sum = result.get();
    cout << "Sum is " << sum << endl;
    return 0;
}
