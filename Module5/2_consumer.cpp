// Consumer Process (Slide 3)
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096;
    const char* name = "SharedMemory";

    int shm_fd = shm_open(name, O_RDONLY, 0666);
    void* ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    std::cout << "Message read from shared memory: " << (char*)ptr << std::endl;

    shm_unlink(name);
    return 0;
}
