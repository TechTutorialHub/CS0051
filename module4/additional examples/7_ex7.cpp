//Asynchronous File Download
//The std::async function downloads files in the background while the main thread remains responsive.

#include <iostream>
#include <future>
#include <chrono>

using namespace std;

void downloadFile(const string& fileName) {
    this_thread::sleep_for(chrono::seconds(3)); // Simulate download time
    cout << "File " << fileName << " has been downloaded.\n";
}

int main() {
    future<void> file1 = async(launch::async, downloadFile, "file1.txt");
    future<void> file2 = async(launch::async, downloadFile, "file2.txt");
    cout << "Main thread is doing other work...\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate other work
    file1.wait();
    file2.wait();
    return 0;
}
