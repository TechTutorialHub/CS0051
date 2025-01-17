
#include <iostream>
#include <thread>
using namespace std;

void printMessage();

int main()
{
    cout<<"Hello from the main thread "<<endl;
    cout << "Main Thread ID " << this_thread::get_id() << endl;
    //create a thread 
    thread t(printMessage);
    t.join();
    return 0;
}

void printMessage(){
    cout << "Hello from printMessage Thread " << endl;
    cout << "Thread id of printMessage function " << this_thread::get_id() << endl;
    
}
