
//Read-Write Lock  C++14
//Readers: Multiple readers can read the shared data simultaneously using lock_shared().
//Writers: Only one writer can modify the shared data at a time using lock().
//Thread Safety: The custom read-write lock ensures that readers and writers do not interfere with each other, preventing data races.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class ReadWriteLock {
private:
    mutex mtx;
    condition_variable cv;
    int readers = 0;
    bool writer = false;

public:
    void lock_shared() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return !writer; });  // Wait until no writer is active
        readers++;
    }

    void unlock_shared() {
        unique_lock<mutex> lock(mtx);
        readers--;
        if (readers == 0) {
            cv.notify_all();  // Notify waiting writers
        }
    }

    void lock() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return !writer && readers == 0; });  // Wait until no readers or writers
        writer = true;
    }

    void unlock() {
        unique_lock<mutex> lock(mtx);
        writer = false;
        cv.notify_all();  // Notify waiting readers and writers
    }
};

ReadWriteLock rwMutex;  // Custom read-write lock
int data = 0;  // Shared data

// Reader function
void reader(int id) {
    for (int i = 0; i < 3; ++i) {
        rwMutex.lock_shared();  // Acquire shared lock for reading
        cout << "Reader " << id << " read data: " << data << " in iteration " << i << endl;
        rwMutex.unlock_shared();  // Release shared lock
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate reading
    }
}

// Writer function
void writer(int id) {
    for (int i = 0; i < 2; ++i) {
        rwMutex.lock();  // Acquire exclusive lock for writing
        data++;
        cout << "Writer " << id << " updated data to: " << data << " in iteration " << i << endl;
        rwMutex.unlock();  // Release exclusive lock
        this_thread::sleep_for(chrono::milliseconds(200));  // Simulate writing
    }
}

int main() {
    thread readers[2];  // Array of reader threads
    thread writers[2];  // Array of writer threads

    // Create reader threads
    for (int i = 0; i < 2; ++i) {
        readers[i] = thread(reader, i);
    }

    // Create writer threads
    for (int i = 0; i < 2; ++i) {
        writers[i] = thread(writer, i);
    }

    // Join reader threads
    for (int i = 0; i < 2; ++i) {
        readers[i].join();
    }

    // Join writer threads
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    return 0;
}
