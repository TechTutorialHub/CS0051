#include <iostream>
#include <thread>
using namespace std;

class HelloObject {
public:
    void objectFunction() {
        cout << "Hello from object function" << endl;
    }
};

int main() {
    cout << "Hello World from main()" << endl;
    HelloObject ho;
    thread t2(&HelloObject::objectFunction, &ho); // Create a thread that runs a member function
    t2.join(); // Wait for the thread to finish
    cout << "Main program ends..." << endl;
    return 0;
}
