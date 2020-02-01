
#include "Mutex.h"
#include "Assert.h"

#if defined(WIN32) || defined(_WIN64)

#include <Windows.h>

struct MutexInternal
{
    CRITICAL_SECTION mtx;
};

CMutex::CMutex()
{
    m_internal = new MutexInternal;
    ::InitializeCriticalSection(&m_internal->mtx);
}

CMutex::~CMutex()
{
    ::DeleteCriticalSection(&m_internal->mtx);
    delete m_internal;
    m_internal = NULL;
}

bool CMutex::enter()
{
    ::EnterCriticalSection(&m_internal->mtx);
    return true;
}

bool CMutex::tryEnter()
{
    return ::TryEnterCriticalSection(&m_internal->mtx);
}

bool CMutex::leave()
{
    ::LeaveCriticalSection(&m_internal->mtx);
    return true;
}

#elif defined(__linux__) || defined (_POSIX_THREADS) || defined(__mac__)

#include <stdlib.h>
#include <pthread.h>

struct MutexInternal
{
    pthread_mutex_t mtx;
};

CMutex::CMutex()
{
    m_internal = new MutexInternal;
    int ret = pthread_mutex_init(&m_internal->mtx, NULL);
    ASSERT(ret == 0);
    (void)ret;
}

CMutex::~CMutex()
{
    int ret = pthread_mutex_destory(&m_internal->mtx);
    if (ret == EBUSY)
    {
        errorf("CMutex::~CMutex() errno:EBUSY.\n");
    }
    else if (ret == EINVAL)
    {
        errorf("CMutex::~CMutex() errno:EINVAL.\n");
    }
    else if (ret != 0)
    {
        errorf("CMutex::~CMutex() errno:%d.\n", ret);
    }
    ASSERT(ret == 0);
    (void)ret;
}

bool CMutex::enter()
{
    return (pthread_mutex_lock(&m_internal->mtx) == 0);
}

bool CMutex::tryEnter()
{
    return (pthread_mutex_trylock(&m_internal->mtx) == 0);
}

bool CMutex::leave()
{
    return (pthread_mutex_unlock(&m_internal->mtx) == 0);
}

#endif

