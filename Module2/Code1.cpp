#include <iostream>
#include <thread>
using namespace std;

void helloFunction() {
    cout << "Hello from function..." << endl;
}

int main() {
    cout << "Hello World from main()" << endl;
    thread t1(helloFunction); // Create a thread that runs helloFunction
    t1.join(); // Wait for the thread to finish
    cout << "Main program ends..." << endl;
    return 0;
}
