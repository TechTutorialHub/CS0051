#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    const int SIZE = 4096; // Shared memory size
    const char* name = "SharedMemory"; // Shared memory object name
    const int MAX_MESSAGES = 50; // Max messages to store
    const int MESSAGE_SIZE = 256; // Max size per message

    // Create shared memory object
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE); // Set shared memory size

    // Map shared memory into process address space
    void* ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    int* message_count = (int*)ptr; // First 4 bytes store the message count
    *message_count = 0; // Initialize message count
    char* message_ptr = (char*)(ptr) + sizeof(int); // Start after message count

    char message[MESSAGE_SIZE]; // Buffer for user input

    cout << "Enter messages (type 'exit' to stop):" << endl;

    while (true) {
        cout << "Message: ";
        cin.getline(message, MESSAGE_SIZE);

        if (strcmp(message, "exit") == 0) {
            break; // Stop writing messages
        }

        // Check if memory limit reached
        if (*message_count >= MAX_MESSAGES) {
            cout << "Shared memory is full. Cannot write more messages." << endl;
            break;
        }

        strcpy(message_ptr + (*message_count * MESSAGE_SIZE), message); // Store message
        (*message_count)++; // Increment message count
    }

    cout << "Producer: Finished writing " << *message_count << " messages to shared memory." << endl;

    return 0;
}
