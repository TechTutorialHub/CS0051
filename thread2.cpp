/******************************************************************************
Example 2 - Multiple threads with three functions
*******************************************************************************/

#include <iostream>
#include <thread>
using namespace std;

void task1();
void task2();
void task3();

int main()
{
    cout << "Main thread Id " << this_thread::get_id() << endl;
    //create new thread 
    thread t1(task1);
    thread t2(task2);
    thread t3(task3);
    
    t1.join();  //join t1 to the thread
    t2.join();
    t3.join();
    
    cout << "All the tasks is completed " <<endl;

    return 0;
}

void task1(){
    cout << "Task 1 is running on Thread ID " << this_thread::get_id() << endl;
    
}
void task2(){
    cout << "Task 2 is running on Thread ID " << this_thread::get_id() << endl;
    
}
void task3(){
    cout << "Task 3 is running on Thread ID " << this_thread::get_id() << endl;
    
}
