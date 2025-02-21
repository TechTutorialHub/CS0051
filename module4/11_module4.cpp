
//additonal code example for async


#include <iostream>
#include <future>
#include <chrono>
#include <thread>
using namespace std; 

int taskA(){
    this_thread::sleep_for(chrono::seconds(2));
    return 100;
}


int taskB(){
    this_thread::sleep_for(chrono::seconds(3));
    return 200;
}


int main(){
    cout << "Staring multiple async tasks...\n";
    future<int> resultA = async(launch::async, taskA);
    future<int> resultB = async(launch::async, taskB);
    
    cout << "Main thread is doing something......\n";
    
    int valueA = resultA.get();
    int valueB = resultB.get();
    
    cout << "Result A "<< valueA << " Result B " << valueB << endl;
    return 0;
}
