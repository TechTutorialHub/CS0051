/******************************************************************************
Printer - Multiple Task
apply the join and detach methods
*******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono> //time, duration and clocks 

using namespace std;
//printer function

void task(string taskName, int duration);

int main()
{
   cout << "Main Thread ID " << this_thread::get_id()<< endl;
   //create task 
   thread t1(task, "Task 1 ",3); //task1 will run for 3 seconds 
   thread t2(task, "Task 2 ",2); //task2 will run for 2 seconds
   
   //join method 
   cout << "Joining Task 1 to wait for its completion " << endl;
   t1.join(); 
   //detach method 
   cout << "Detaching task 2, it will run independently " << endl;
   t2.detach();
   
   cout << "Main thread work continue "<< endl;
   
   this_thread::sleep_for(chrono::milliseconds(4));
   
   cout << "Main thread is finsh execution " << endl;

    return 0;
}
void task(string taskName, int duration){
    cout << taskName << "started on Thread ID "<< this_thread::get_id()<< endl;
    this_thread::sleep_for(chrono::milliseconds(duration));
    cout << taskName << " finished after " << duration << " seconds. "<< endl;
    
}
