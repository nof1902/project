#pragma once 
#include <pthread.h>

class Mutex
{
public:
    Mutex();
    bool Lock();
    bool UnLock();
    ~Mutex();
private:
    pthread_mutex_t m_mutex;
    bool m_IsLock;
    Mutex(const Mutex& other);
    Mutex& operator=(const Mutex& other);
};