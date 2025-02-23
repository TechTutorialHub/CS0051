#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    const int SIZE = 4096; // Shared memory size
    const char* name = "SharedMemory"; // Shared memory object name

    // Open shared memory object
    int shm_fd = shm_open(name, O_RDONLY, 0666);

    // Map shared memory into process address space
    void* ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // Read message from shared memory
    cout << "Consumer: Message read from shared memory: " << (char*)ptr << endl;

    // Unlink shared memory (removes it from the system)
    shm_unlink(name);

    return 0;
}
