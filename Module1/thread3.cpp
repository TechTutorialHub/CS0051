/******************************************************************************
Printer - Multiple Pages

*******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono> //time, duration and clocks 
using namespace std;
//printer function
void printer(string documentName, int pages);

int main()
{
    cout << "Start printing task .... " << endl;
    //create thread
    thread t1(printer, "Document_A",3);//printer 1, prints doc A with 3 pages 
    thread t2(printer, "Document_B",5);//printer 2, prints doc B with 5 pages 
    thread t3(printer, "Document_C",2);//printer 3, prints doc C with 2 pages 
    
    t1.join();
    t2.join();
    t3.join();
    
    cout << "All printing task is complete " <<endl;

    return 0;
}
void printer(string documentName, int pages){
    for (int i = 1; i<=pages;i++){
        cout << documentName << " - Printing page # " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << documentName << " printing completed !" << endl;
    
}







