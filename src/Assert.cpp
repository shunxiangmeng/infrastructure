#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"
#include "Assert.h"

///����ʧ�ܴ�����
INFRA_API void assertionFailed(const char * exp, const char * func, const char * file, long line)
{
    fprintf(stderr, "assertion(%s),failed in %s:%s(%ld)\n", exp, func, file, line);
    abort();
}

///����ʧ�ܴ�����
INFRA_API void assertionFailedMsg(const char * exp, const char * func, const char * file, long line, const char* msg)
{
    fprintf(stderr, "assertion(%s),failed in %s:%s(%ld):%s\n", exp, func, file, line, msg);
    abort();
}
