//Using detach() to Run a Thread Independently

#include <iostream>
#include <thread>
using namespace std;

void threadFunction() {
    cout << "Thread is running..." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Simulate work by sleeping for 2 seconds
    cout << "Thread is finishing..." << endl;
}

int main() {
    cout << "Main thread starts..." << endl;
    thread t(threadFunction); // Create a thread that runs threadFunction
    t.detach(); // Detach the thread, allowing it to run independently
    cout << "Main thread ends..." << endl;
    return 0;
}
