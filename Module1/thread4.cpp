#include <iostream>
#include <thread>
using namespace std;

void hellofunction(){
    cout << "Hello from hellofunction...ID "<< this_thread::get_id() << endl;
}

class HelloObject {
public:
    void objectfunction();
};
    void HelloObject::objectfunction(){
        cout << "Hello from object function ID"<< this_thread::get_id() <<endl;
    }


int main() {
    cout << "Hello World from main() id "<< this_thread::get_id() << endl;
    //create thread
    thread t1(hellofunction);
    HelloObject ho;
    thread t2(&HelloObject::objectfunction, &ho); 
    //runs HelloObject::objectfunction() on object ho
    t1.join();
    t2.join();
}


