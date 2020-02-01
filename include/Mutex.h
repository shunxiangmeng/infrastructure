
#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "Defs.h"
#include "Types.h"

struct MutexInternal;

class INFRA_API CMutex
{
    CMutex(CMutex const&);
    CMutex& operator = (CMutex const&);

public:
    CMutex();

    ~CMutex();

    bool enter();

    ///尝试进入临界区
    bool tryEnter();

    bool leave();

private:
    MutexInternal *m_internal;
};


#endif
