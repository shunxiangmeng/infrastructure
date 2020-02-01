
#ifndef _THREAD_SPECIFIC_H_
#define _THREAD_SPECIFIC_H_

#include "Defs.h"

struct ThreadSpecificInternal;

class INFRA_API CThreadSpecific
{
public:
    CThreadSpecific();
    ~CThreadSpecific();

    ///TSS 索引是否可用
    bool vaild();

    bool setValue(void const* value);

    bool getValue(void** pvalue);

private:
    ThreadSpecificInternal* m_internal;
};

#endif
