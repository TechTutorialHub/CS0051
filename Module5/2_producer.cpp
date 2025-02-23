#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    const int SIZE = 4096;
    const char* name = "SharedMemory";
    const char* message = "Hello from Producer";

    // Create shared memory object
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE); // Set shared memory size

    // Map shared memory into process address space
    void* ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Use snprintf() instead of sprintf() for safer string copying
    snprintf((char*)ptr, SIZE, "%s", message);

    cout << "Message written to shared memory: " << message << endl;

    return 0;
}
