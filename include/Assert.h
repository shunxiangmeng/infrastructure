#ifndef __ASSERT_H__
#define __ASSERT_H__

#include "Defs.h"
#include "Types.h"

INFRA_API void assertionFailed(const char * expr, const char * function, const char * file, long line);

INFRA_API void assertionFailedMsg(const char * expr, const char * function, const char * file, long line, const char* msg);

#undef ASSERT
#if defined(NDEBUG)
#define ASSERT(expr) ((void)0)
#else
#define ASSERT(expr) ((expr) ? ((void)0) : assertionFailed(#expr, __FUNCTION__, __FILE__, __LINE__))
#endif

#undef ASSERT_MSG
#if defined(NDEBUG)
#define ASSERT_MSG(expr, msg) ((void)0)
#else
#define ASSERT_MSG(expr, msg) ((expr) ? ((void)0) : assertionFailedMsg(#expr, __FUNCTION__, __FILE__, __LINE__, msg))
#endif

#endif


