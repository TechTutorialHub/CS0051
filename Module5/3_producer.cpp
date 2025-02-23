//with user inout
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    const int SIZE = 4096; // Shared memory size
    const char* name = "SharedMemory"; // Shared memory object name
    char message[SIZE]; // Buffer to hold user input

    // Get user input
    cout << "Enter a message to store in shared memory: ";
    cin.getline(message, SIZE); // Read entire line of user input

    // Create shared memory object
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE); // Set shared memory size

    // Map shared memory into process address space
    void* ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Copy input message to shared memory safely
    snprintf((char*)ptr, SIZE, "%s", message);

    cout << "Producer: Message written to shared memory: " << message << endl;

    return 0;
}
