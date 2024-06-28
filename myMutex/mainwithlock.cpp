/*
    In this program we put to use the myMutex class to protect a shared resource.
    The shared resource is a global variable called counter, which is incremented by each thread.
    The threads are created in the main function and they call the increment function.
    The increment function locks the mutex, increments the counter and unlocks the mutex.
    The main function waits for all threads to finish and then prints the final value of the counter.
    The output of the program is the final value of the counter, which should be equal to NUM_THREADS * NUM_INCREMENTS.
    The program uses the myMutex class to protect the shared resource, so the final value of the counter should be correct.
    If we remove the lock and unlock calls from the increment function, the program will get into race condition and the final value of the counter will be incorrect.
*/

#include "myMutex.hpp"
#include <pthread.h>
#include <iostream>

const int NUM_THREADS = 5;
const int NUM_INCREMENTS = 1000000;

int counter = 0;
myMutex* mutex = myMutex::create(); // Create a mutex

void* increment(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; ++i) {
        mutex->lock(); // Lock the mutex
        ++counter;
        mutex->unlock(); // Unlock the mutex
    }
    return nullptr;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], nullptr, increment, nullptr);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], nullptr);
    }

    std::cout << "Final counter value (WITH LOCK): " << counter << std::endl;

    return 0;
}
