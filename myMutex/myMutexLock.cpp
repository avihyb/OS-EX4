/*
    myMutexLock.cpp provides the actual implementation of the lock function for myMutexLock.
*/

#include "myMutexLock.hpp"
#include "myMutex.hpp"
#include <iostream>

void myMutexLock::lock() {
   // std::cout << "Locking mutex" << std::endl;
    pthread_mutex_lock(&myMutex::mutex);
}

void myMutexLock::unlock() {
   // std::cout << "Unlocking mutex" << std::endl;
    pthread_mutex_unlock(&myMutex::mutex);
}


