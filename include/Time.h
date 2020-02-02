#ifndef __TIME__H_
#define __TIME__H_
#include <string>
#include "Defs.h"
#include "Types.h"
#include <string.h>
#include "Function.h"


/// 本地时间,包含时区、夏令时等因素
struct SystemTime
{
    int year;       ///< 年。
    int month;      ///< 月,January=1,February=2,and so on.
    int day;        ///< 日.
    int wday;       ///< 星期,Sunday=O,Monday=1,and so on
    int hour;       ///< 时。
    int minute;     ///< 分。
    int second;     ///< 秒。
    int isdst;      ///< 夏令时标识。 <0表示未知 0不在夏令时 >0处在夏令时本地时间, 包含毫秒的SystemTime增强版
};
 
/// 本地时间，包含毫秒
struct SystemTimeEx
{        
    int year;       /// 年。
    int month;      /// 月, January = 1, February = 2, and so on.
    int day;        /// 日
    int wday;       /// 星期,Sunday=O,Monday=1,and so on
    int hour;       /// 时
    int minute;     /// 分
    int second;     /// 秒
    int millisecond; ///毫秒
    int isdst;      ///夏令时标志
    int reserved[3];
};

/// \class CTime
/// \brief 时间类, 实现了本地时间存取. 运算 格式控制与打印等接口
/// \CTime类处理的时间都是本地时间.在GMT时间的基础上加了时区偏移。
class INFRA_API CTime : public SystemTime
{
public:
    ///时间修改回调函数
    typedef TFunction1<bool, SystemTime> ModifyProc;
    ///时间修改函数
    typedef TFunction2<void, const CTime&, int> SetCurrentTimeHook;
    typedef TFunction2<void, const SystemTimeEx&, int> SetCurrentTimeHookEx;
    
    ///日期顺序格式
    enum DateFormat
    {
        ymd,
        mdy,
        dmy
    };
        /// 格式化模式选项
    enum FormatMask
    {
        fmGeneral = 0,      /// 只指定是否显示以及起始值
        fmSeparator = 1,    /// 指定分隔符
        fmDateFormat = 2,   /// 指定年月日顺序
        fmHourFormat = 4,   /// 指定小时制式
        fmAll = fmSeparator | fmDateFormat | fmHourFormat ///指定所有格式选项
    };

    /// 缺省构造函数
    CTime();

    ///内部会尝试转换到本地时区, 但由于时区文件被裁剪, 在不同平台结果不一样
    CTime(uint64 time);

    CTime(uint64 time, bool addTimeZone);

    CTime(int year, int month, int day, int hour, int imn, int sec);

    /// 尝试得到UNIX Epoch时间，指从GMT 1970-1-1 00：00：00到某个时间经过的秒数
    uint64 makeTime() const;

    /// 将UNIX Epoch秒数分解成年月日时分秒
    void breakTime(uint64 time);

    CTime operator + (int64 seconds) const;

    CTime operator - (int64 seconds) const;

    CTime operator - (const CTime& time) const;

    CTime operator += (int64 seconds);

    CTime operator -= (int64 seconds);

    CTime operator == (const CTime& time) const;

    CTime operator != (const CTime& time) const;

    CTime operator < (const CTime& time) const;

    CTime operator <= (const CTime& time) const;

    CTime operator > (const CTime& time) const;

    CTime operator >= (const CTime& time) const;

    /// 时间格式化
    void format(char* buf, const char* format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral) const;

    bool parse(const char* buf, const char* format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral) const;

    /// 立刻获取本地当前系统时间
    static CTime getCurrentTime();

    static SystemTimeEx getCurrentTimeEx();

    static CTime getCurTimeForPrint();

    static void setCurrentTime(const CTime& time, int toleranceSecondes = 0);

    static bool setCurrentTimeEx(const CTime& time, int toleranceSecondes = 0);

    static bool setCurrentTime(const SystemTimeEx& time, int toleranceSecondes = 0);

    ///获取从系统启动到现在的毫秒数
    static uint64 getCurrentMilliSecond();

    ///获取从系统启动到现在的微秒数
    static uint64 getCurrentMicroSecond();


public:
    static const CTime minTime; ///有效最小时间
    static const CTime maxTime; ///有效最大时间

};

#endif
