#include "myMutex.hpp"
#include "myMutexLock.hpp"

myMutex* myMutex::instance = nullptr;
pthread_mutex_t myMutex::mutex = PTHREAD_MUTEX_INITIALIZER;

myMutex* myMutex::create() {
    if (instance == nullptr) {
        pthread_mutex_lock(&mutex);
        if (instance == nullptr) {
            instance = new myMutexLock();
        }
        pthread_mutex_unlock(&mutex);
    }
    return instance;
}
