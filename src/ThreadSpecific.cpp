
#include "ThreadSpecific.h"

#if defined(WIN32) || defined(_WIN64)
#include <Windows.h>

struct ThreadSpecificInternal
{
    DWORD dwTlsIndex;
};

/// 构造函数，分配 TSS 索引
CThreadSpecific::CThreadSpecific()
{
    m_internal = new ThreadSpecificInternal;
    m_internal->dwTlsIndex = TlsAlloc();
}

CThreadSpecific::~CThreadSpecific()
{
    if (vaild())
    {
        TlsFree(m_internal->dwTlsIndex);
    }
    delete m_internal;
}

/// TSS 索引是否可用
bool CThreadSpecific::vaild()
{
    return m_internal->dwTlsIndex != TLS_OUT_OF_INDEXES;
}

bool CThreadSpecific::setValue(void const* value)
{
    if (vaild())
    {
        return !!TlsSetValue(m_internal->dwTlsIndex, (LPVOID)value);
    }
    else
    {
        return false;
    }
}

bool CThreadSpecific::getValue(void** pvalue)
{
    if (vaild())
    {
        *pvalue = TlsGetValue(m_internal->dwTlsIndex);
        return true;
    }
    else
    {
        return false;
    }
}


#elif defined(__linux__) || defined(_POSIX_THREADS) || defined(__mac__)
#inclue <thread.h>


#endif
