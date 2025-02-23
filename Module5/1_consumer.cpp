#include <iostream>
#include <sys/mman.h> // For shared memory
#include <fcntl.h>    // For file control options
#include <unistd.h>   // For shm_unlink()

using namespace std;

int main() {
    const int SIZE = 4096; // Shared memory size
    const char* name = "RandomNumbers"; // Shared memory name

    // Open shared memory object
    int shm_fd = shm_open(name, O_RDONLY, 0666);

    // Map shared memory into process address space
    int* ptr = (int*)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // Read the count of numbers from shared memory
    int num_count = ptr[0];
    int sum = 0;

    // Read and sum the numbers
    for (int i = 1; i <= num_count; ++i) {
        sum += ptr[i];
        cout << "Consumer: Read number " << ptr[i] << endl;
    }

    cout << "Consumer: Sum of numbers = " << sum << endl;

    // Unlink shared memory object
    shm_unlink(name);

    return 0;
}
