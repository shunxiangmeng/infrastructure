
#include <stdint.h>
#include "Function.h"
#include "ThreadSpecific.h"

static CThreadSpecific s_functionReuse;

void setCurrentFunctionReuse(uint32 reuse)
{
    s_functionReuse.setValue(reinterpret_cast<void const*>(reuse));
}

uint32 getCurrentFunctionReuse()
{
    void* value = 0;
    s_functionReuse.getValue(&value);
    return ((uint32)reinterpret_cast<intptr_t>(value));
}

