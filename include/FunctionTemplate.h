
#define FUNCTION_FUNCTION MACRO_JOIN(TFunction, FUNCTION_NUMBER)

#if FUNCTION_NUMBER == 0
#define FUNCTION_COMMA
#else
#define FUNCTION_COMMA ,
#endif  ///FUNCTION_NUMBER > 0

#define FUNCTION_INVOKER                MACRO_JOIN(function_invoker, FUNCTION_NUMBER)
#define FUNCTION_VOID_INVOKER           MACRO_JOIN(function_void_invoker, FUNCTION_NUMBER)
#define GET_FUNCTION_INVOKER            MACRO_JOIN(get_function_invoker, FUNCTION_NUMBER)
#define MEM_FUNCTION_INVOKER            MACRO_JOIN(mem_function_invoker, FUNCTION_NUMBER)
#define MEM_FUNCTION_VOID_INVOKER       MACRO_JOIN(mem_function_void_invoker, FUNCTION_NUMBER)
#define GET_MEM_FUNCTION_INVOKER        MACRO_JOIN(get_mem_function_invoker, FUNCTION_NUMBER)

//========================================================================================

template<FUNCTION_CLASS_TYPES> struct FUNCTION_INVOKER
{
    template<class F>
    static typename function_return_type<R>::type invoke(F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
    {
        return f(FUNCTION_ARGS);
    }
};

template<FUNCTION_CLASS_TYPES> struct FUNCTION_VOID_INVOKER
{
    template<class F>
    static typename function_return_type<R>::type invoke(F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
    {
        FUNCTION_RETURN(f(FUNCTION_ARGS));
    }
};

template<class RT> struct GET_FUNCTION_INVOKER
{
    template<FUNCTION_CLASS_TYPES> struct Invoker
    {
        typedef FUNCTION_INVOKER<R FUNCTION_COMMA FUNCTION_TYPES> type;
    };
};

template<> struct GET_FUNCTION_INVOKER<void>
{
    template<FUNCTION_CLASS_TYPES> struct Invoker
    {
        typedef FUNCTION_INVOKER<R FUNCTION_COMMA FUNCTION_TYPES> type;
    };
};

//----------------------------------------------------------------------
template<FUNCTION_CLASS_TYPES> struct MEM_FUNCTION_INVOKER
{
    template<class O, class F>
    static typename function_return_type<R>::type invoke(O o, F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
    {
        return (o->*f)(FUNCTION_ARGS);
    }
};

template<FUNCTION_CLASS_TYPES> struct MEM_FUNCTION_VOID_INVOKER
{
    template<class O, class F>
    static typename function_return_type<R>::type invoke(O o, F f FUNCTION_COMMA FUNCTION_TYPE_ARGS)
    {
        return FUNCTION_RETURE((o->*f)(FUNCTION_ARGS));
    }
};

template<class RT> struct GET_MEM_FUNCTION_INVOKER
{
    template<FUNCTION_CLASS_TYPES> struct Invoker
    {
        typedef MEM_FUNCTION_INVOKER<R FUNCTION_COMMA FUNCTION_TYPES> type;
    };
};

template<> struct GET_MEM_FUNCTION_INVOKER<void>
{
    template<FUNCTION_CLASS_TYPES> struct Invoker
    {
        typedef MEM_FUNCTION_INVOKER<R FUNCTION_COMMA FUNCTION_TYPES> type;
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////
template <FUNCTION_CLASS_TYPES>
class FUNCTION_FUNCTION
{
    class X {};

    typedef R(X::*MEM_FUNCTION)(FUNCTION_TYPES);
    typedef R(*PTR_FUNCTION)(FUNCTION_TYPES);

public:
    enum FunctionType
    {
        typeEmpty,
        typeMember,
        typePointer,
        typeObject,
        typeReuse = 16,
        typeAllReuse = -1,
    };
    union
    {
        struct
        {
            MEM_FUNCTION proc;
            X* obj;
        }memFunction;
        PTR_FUNCTION ptrFunction;
    }m_function;

    FunctionType m_type;
    const char* m_objectType;

public:
    ///省缺构造函数
    FUNCTION_FUNCTION() :m_type(typeEmpty), m_objectType(0)
    {
    }

    /// 接受成员函数指针构造函数，将类的成员函数和类对象的指针绑定并保存
    template <typename O>
    FUNCTION_FUNCTION(R(O::*f)(FUNCTION_TYPES), const O *o, uint32 reuse)
    {
        if (reuse < (uint32)typeReuse)
        {
            m_type = typeEmpty;
            m_objectType = 0;
            return;
        }
        m_type = (FunctionType)reuse;
        m_function.memFunction.proc = horrible_cast<MEM_FUNCTION>(f);
        m_function.memFunction.obj = horrible_cast<X*>(o);
        m_objectType = typeid(o).name();
    }

    FUNCTION_FUNCTION(PTR_FUNCTION f)
    {
        if (f)
        {
            m_type = typePointer;
            m_function.ptrFunction = f;
            m_objectType = 0;
        }
        else
        {
            m_type = typeEmpty;
            m_objectType = 0;
        }
    }

    /// 拷贝函数
    FUNCTION_FUNCTION& operator=(const FUNCTION_FUNCTION& f)
    {
        if (&f == this)
        {
            return *this;
        }
        m_function = f.m_function;
        m_type = f.m_type;
        m_objectType = f.m_objectType;
        return *this;
    }

    template<typename O>
    void bind(R(O::*f)(FUNCTION_TYPES), const O * o)
    {
        *this = FUNCTION_FUNCTION(f, o);
    }

    bool empty() const
    {
        return (m_type == typeEmpty);
    }

    bool allReuse() const
    {
        return (m_type == typeAllReuse);
    }

    bool operator==(const FUNCTION_FUNCTION& f) const
    {
        if ((uint32)m_type >= (uint32)typeReuse && (uint32)f.m_type >= (uint32)typeReuse)
        {
            return (m_function.memFunction.proc == f.m_function.memFunction.proc
                && m_function.memFunction.obj == f.m_function.memFunction.obj);
        }
        else
        {
            return (m_type == f.m_type
                && m_function.memFunction.proc == f.m_function.memFunction.proc
                && m_function.memFunction.obj == f.m_function.memFunction.obj);
        }
        else if (m_type != f.m_type)
        {
            return false;
        }

        if (m_type == typeMember)
        {
            return (m_function.memFunction.proc == f.m_function.memFunction.proc
                && m_function.memFunction.obj == f.m_function.memFunction.obj);
        }
        else if (m_type == typePointer)
        {
            return (m_function.ptrFunction == f.m_function.ptrFunction);
        }
        else
        {
            return true;
        }
    }

    /// 重载()运算符
    inline typename function_return_type<R>::type operator() (FUNCTION_TYPE_ARGS)
    {
        if (m_type == typeMember)
        {
            typedef typename GET_MEM_FUNCTION_INVOKER<R>::template Invoker<R FUNCTION_COMMA FUNCTION_TYPES>::type Invoker;
            return Invoker::invoker(m_function.memFunction.obj, m_function.memFunction.proc FUNCTION_COMMA FUNCTION_ARGS);
        }
        else if (m_type == typePointer)
        {
            typedef typename GET_FUNCTION_INVOKER<R>::template Invoker<R FUNCTION_COMMA FUNCTION_TYPES>::type Invoker;
            return Invoker::invoker(m_function.ptrFunction FUNCTION_COMMA FUNCTION_ARGS);
        }
        else if ((uint32)m_type >= (uint32)typeReuse && m_type != typeAllReuse)
        {
            setCurrentFunctionReuse((uint32)m_type);
            typedef typename GET_MEM_FUNCTION_INVOKER<R>::template Invoker<R FUNCTION_COMMA FUNCTION_TYPES>::type Invoker;
            return Invoker::invoker(m_function.memFunction.obj, m_function.memFunction.proc FUNCTION_COMMA FUNCTION_ARGS);
        }
        else
        {
            typedef typename GET_MEM_FUNCTION_INVOKER<R>::template Invoker<R FUNCTION_COMMA FUNCTION_TYPES>::type Invoker;
            return Invoker::invoker(m_function.memFunction.obj, m_function.memFunction.proc FUNCTION_COMMA FUNCTION_ARGS);
        }
    }

    void* getObject()
    {
        return m_function.memFunction.obj;
    }

    const char* getObjectType()
    {
        return m_objectType;
    }
};

#undef FUNCTION_FUNCTION
#undef FUNCTION_COMMA
#undef FUNCTION_INVOKER
#undef FUNCTION_VOID_INVOKER
#undef GET_FUNCTION_INVOKER
#undef MEM_FUNCTION_INVOKER
#undef MEM_FUNCTION_VOID_INVOKER
#undef GET_MEM_FUNCTION_INVOKER
