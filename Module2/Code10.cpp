//Download Manager (Multiple File Downloads)

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void downloadFile(string fileName, int downloadTime) {
    cout << "Downloading " << fileName << "..." << endl;
    this_thread::sleep_for(chrono::seconds(downloadTime)); // Simulate download time
    cout << fileName << " downloaded!" << endl;
}

int main() {
    // Arrays to store file names and download times
    string files[] = {"file1.zip", "file2.mp4", "file3.pdf"};
    int downloadTimes[] = {3, 5, 2}; // Simulated download times for each file
    const int numFiles = 3; // Number of files
    
    // Array to store thread objects
    thread threads[numFiles];
    
    // Start a thread for each file download
    for (int i = 0; i < numFiles; i++) {
        threads[i] = thread(downloadFile, files[i], downloadTimes[i]);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < numFiles; i++) {
        threads[i].join();
    }
    
    cout << "All downloads completed!" << endl;
    return 0;
}
