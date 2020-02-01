#ifndef __ASSERT_H__
#define __ASSERT_H__

#include "Defs.h"
#include "Types.h"

INFRA_API void assertFailed(const char * expr, const char * function, const char * file, long line);

INFRA_API void assertFailedMsg(const char * expr, const char * function, const char * file, long line, const char* msg);


#endif



