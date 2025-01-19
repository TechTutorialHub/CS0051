
#include <iostream>
#include <thread>
#include <string>
using namespace std;

void helloFunction(int n, string str) {
    for (int i = 0; i < n; i++) {
        cout << "Hello from function... " << str << endl;
    }
}

int main() {
    cout << "Hello World from main()" << endl;
    thread t1(helloFunction, 3, "FEUTECH"); // Create a thread with parameters
    t1.join(); // Wait for the thread to finish
    cout << "Main program ends..." << endl;
    return 0;
}
