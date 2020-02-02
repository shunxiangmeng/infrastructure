#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4786)
#endif

#include <assert.h>
#include <typeinfo.h>
#include <stdio.h>
#include "Defs.h"
#include "Types.h"

template<class R> struct function_return_type { typedef R type; };

#if defined(_MSC_VER) && (_MSC_VER < 1300)

struct unuasble
{
    unusable() {}
    template<class T> unusable(T const&) {}
};

template<> struct function_return_type<void> { typedef unusable type; };

#define FUNCTION_RETURN(x) x; return unusable()

#else

#define FUNCTION_RETURN(x) x

#endif



//////////////////////////////////////////////////////////////////////////////
template <class OutputClass, class InputClass>
union horrible_union 
{
    OutputClass out;
    InputClass in;
};

template <class OutputClass, class InputClass>
inline OutputClass horrible_cast(const InputClass input) 
{
    horrible_union<OutputClass, InputClass> u;

    typedef int ERROR_CantUseHorrible_cast[sizeof(InputClass) == sizeof(u) ? 1 : -1];

    ERROR_CantUseHorrible_cast dummy;

    (void)dummy;

    u.in = input;

    return u.out;
}


/// 设置当前线程函数复用ID
void INFRA_API setCurrentFunctionReuse(uint32 reuse);

/// 获取当前线程函数复用ID 
uint32 INFRA_API getCurrentFunctionReuse();

/// TFunction0
#define FUNCTION_NUMBER 0
#define FUNCTION_CLASS_TYPES typename R
#define FUNCTION_TYPES
#define FUNCTION_TYPE_ARGS
#define FUNCTION_ARGS
#include "FunctionTemplate.h"
#undef FUNCTION_NUMBER
#undef FUNCTION_CLASS_TYPES
#undef FUNCTION_TYPES
#undef FUNCTION_TYPE_ARGS
#undef FUNCTION_ARGS

/// TFunction1
#define FUNCTION_NUMBER 1
#define FUNCTION_CLASS_TYPES typename R, typename T1
#define FUNCTION_TYPES T1
#define FUNCTION_TYPE_ARGS T1 a1
#define FUNCTION_ARGS a1
#include "FunctionTemplate.h"
#undef FUNCTION_NUMBER
#undef FUNCTION_CLASS_TYPES
#undef FUNCTION_TYPES
#undef FUNCTION_TYPE_ARGS
#undef FUNCTION_ARGS

/// TFunction2
#define FUNCTION_NUMBER 2
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2
#define FUNCTION_TYPES T1, T2
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2
#define FUNCTION_ARGS a1, a2
#include "FunctionTemplate.h"
#undef FUNCTION_NUMBER
#undef FUNCTION_CLASS_TYPES
#undef FUNCTION_TYPES
#undef FUNCTION_TYPE_ARGS
#undef FUNCTION_ARGS

/// TFunction3
#define FUNCTION_NUMBER 3
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2, typename T3
#define FUNCTION_TYPES T1, T2, T3
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2, T3 a3
#define FUNCTION_ARGS a1, a2, a3
#include "FunctionTemplate.h"
#undef FUNCTION_NUMBER
#undef FUNCTION_CLASS_TYPES
#undef FUNCTION_TYPES
#undef FUNCTION_TYPE_ARGS
#undef FUNCTION_ARGS

/// TFunction4
#define FUNCTION_NUMBER 4
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2, typename T3, typename T4
#define FUNCTION_TYPES T1, T2, T3, T4
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2, T3 a3, T4 a4
#define FUNCTION_ARGS a1, a2, a3, a4
#include "FunctionTemplate.h"
#undef FUNCTION_NUMBER
#undef FUNCTION_CLASS_TYPES
#undef FUNCTION_TYPES
#undef FUNCTION_TYPE_ARGS
#undef FUNCTION_ARGS

/// TFunction5
#define FUNCTION_NUMBER 5
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2, typename T3, typename T4, typename T5
#define FUNCTION_TYPES T1, T2, T3, T4, T5
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2, T3 a3, T4 a4, T5 a5
#define FUNCTION_ARGS a1, a2, a3, a4, a5
#include "FunctionTemplate.h"
#undef FUNCTION_NUMBER
#undef FUNCTION_CLASS_TYPES
#undef FUNCTION_TYPES
#undef FUNCTION_TYPE_ARGS
#undef FUNCTION_ARGS

/// TFunction6
#define FUNCTION_NUMBER 6
#define FUNCTION_CLASS_TYPES typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
#define FUNCTION_TYPES T1, T2, T3, T4, T5, T6
#define FUNCTION_TYPE_ARGS T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6
#define FUNCTION_ARGS a1, a2, a3, a4, a5, a6
#include "FunctionTemplate.h"
#undef FUNCTION_NUMBER
#undef FUNCTION_CLASS_TYPES
#undef FUNCTION_TYPES
#undef FUNCTION_TYPE_ARGS
#undef FUNCTION_ARGS

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif
