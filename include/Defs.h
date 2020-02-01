
#ifndef __DEFS_H__
#define __DEFS_H__

#include <stddef.h>

#ifdef _MSC_VER

#ifdef DLL_BUILD
#define INFRA_API _declspec(dllexport) 
#elif define INFRA_DLL_USE
#define INFRA_API _declspec(dllimport)
#else
#define INFRA_API
#endif

#else

#define INFRA_API

#endif

#ifndef NULL
#define NULL (void*)0
#endif

#endif

