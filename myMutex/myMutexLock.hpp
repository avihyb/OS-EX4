/*
    myMutexLock: Concrete derived class implementing the lock function specific to myMutexLock.
*/

#ifndef MY_MUTEX_LOCK_HPP
#define MY_MUTEX_LOCK_HPP

#include "myMutex.hpp"

class myMutexLock : public myMutex {
public:
    void lock() override;
    void unlock() override;
    ~myMutexLock() {}
};

#endif // MY_MUTEX_LOCK_HPP
