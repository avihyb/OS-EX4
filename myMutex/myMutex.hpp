/*

Overview:
    Class myMutex: This is an abstract base class designed to define an interface for mutex operations (lock function).

Virtual (Abstract) Functions:
    lock();
    unlock();
    ~myMutex();

Static Members:
    static myMutex* instance;: Static member variable used for implementing the Singleton design pattern. It holds the single instance of myMutex.
    static pthread_mutex_t mutex;: Static pthread mutex used for synchronization.
    
*/

#ifndef MY_MUTEX_HPP
#define MY_MUTEX_HPP

#include <pthread.h>

class myMutex {
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual ~myMutex() {}
    static myMutex* create();

protected:
    myMutex() {}
    static pthread_mutex_t mutex;

private:
    static myMutex* instance;
    
};

#endif // MY_MUTEX_HPP
