
#include <stdio.h>
#include "Mutex.hpp"

Mutex::Mutex():
{
    if(pthread_mutex_init(&m_mutex,NULL))
    {
        perror("pthread_mutex_init");
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

bool Mutex::Lock()
{
    if(0 == pthread_mutex_lock(&m_mutex))
    {
        return true;
    }
}

bool Mutex::UnLock()
{
    if(0 == pthread_mutex_unlock(&m_mutex))
    {
        return false;
    }
}
