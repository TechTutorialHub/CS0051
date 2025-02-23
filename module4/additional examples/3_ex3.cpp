//Team Meeting: A barrier can be used to synchronize team members before starting a meeting. 
//All team members must arrive before the meeting can begin.
//meetingBarrier ensures that all team members must arrive before the meeting starts.

#include <iostream>
#include <thread>
#include <barrier>

using namespace std; // Include this line to avoid using "std::" prefix

barrier meetingBarrier(3); // Barrier for 3 team members

void teamMember(int id) {
    cout << "Team member " << id << " is preparing for the meeting.\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate preparation time
    meetingBarrier.arrive_and_wait(); // Wait for all team members to arrive
    cout << "Team member " << id << " is attending the meeting.\n";
}

int main() {
    thread member1(teamMember, 1);
    thread member2(teamMember, 2);
    thread member3(teamMember, 3);
    member1.join();
    member2.join();
    member3.join();
    return 0;
}
