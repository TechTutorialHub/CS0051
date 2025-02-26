#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <sys/mman.h> // For shared memory
#include <fcntl.h>    // For file control options
#include <unistd.h>   // For ftruncate()
#include <cstring>    // For memset()

using namespace std;

int main() {
    const int SIZE = 4096; // Shared memory size
    const char* name = "RandomNumbers"; // Shared memory name
    const int NUM_COUNT = 10; // Number of random numbers to generate

    // Create shared memory object
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE); // Set the size of shared memory

    // Map shared memory into process address space
    int* ptr = (int*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Generate random numbers and write to shared memory
    srand(time(0)); // Seed for random number generation
    int sum = 0; // Variable to store the sum of numbers

    ptr[0] = NUM_COUNT; // Store the count of numbers in shared memory
    for (int i = 1; i <= NUM_COUNT; ++i) {
        ptr[i] = rand() % 100; // Generate random numbers between 0 and 99
        sum += ptr[i]; // Add to sum
        cout << "Producer: Generated number " << ptr[i] << endl;
    }

    cout << "Producer: Sum of numbers = " << sum << endl;
    cout << "Producer: Finished generating numbers." << endl;

    return 0;
}
