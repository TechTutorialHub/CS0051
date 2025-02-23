#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    const int SIZE = 4096; // Shared memory size
    const char* name = "SharedMemory"; // Shared memory object name
    const int MESSAGE_SIZE = 256; // Max size per message

    // Open shared memory object
    int shm_fd = shm_open(name, O_RDONLY, 0666);

    // Map shared memory into process address space
    void* ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    int* message_count = (int*)ptr; // First 4 bytes store the message count
    char* message_ptr = (char*)(ptr) + sizeof(int); // Start after message count

    cout << "Consumer: Reading " << *message_count << " messages from shared memory..." << endl;

    for (int i = 0; i < *message_count; ++i) {
        cout << "Consumer: Received message: " << (message_ptr + (i * MESSAGE_SIZE)) << endl;
    }

    cout << "Consumer: Finished reading messages." << endl;

    // Unlink shared memory object
    shm_unlink(name);

    return 0;
}
