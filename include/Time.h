#ifndef __TIME__H_
#define __TIME__H_
#include <string>
#include "Defs.h"
#include "Types.h"
#include <string.h>
#include "Function.h"


/// ����ʱ��,����ʱ��������ʱ������
struct SystemTime
{
    int year;       ///< �ꡣ
    int month;      ///< ��,January=1,February=2,and so on.
    int day;        ///< ��.
    int wday;       ///< ����,Sunday=O,Monday=1,and so on
    int hour;       ///< ʱ��
    int minute;     ///< �֡�
    int second;     ///< �롣
    int isdst;      ///< ����ʱ��ʶ�� <0��ʾδ֪ 0��������ʱ >0��������ʱ����ʱ��, ���������SystemTime��ǿ��
};
 
/// ����ʱ�䣬��������
struct SystemTimeEx
{        
    int year;       /// �ꡣ
    int month;      /// ��, January = 1, February = 2, and so on.
    int day;        /// ��
    int wday;       /// ����,Sunday=O,Monday=1,and so on
    int hour;       /// ʱ
    int minute;     /// ��
    int second;     /// ��
    int millisecond; ///����
    int isdst;      ///����ʱ��־
    int reserved[3];
};

/// \class CTime
/// \brief ʱ����, ʵ���˱���ʱ���ȡ. ���� ��ʽ�������ӡ�Ƚӿ�
/// \CTime�ദ���ʱ�䶼�Ǳ���ʱ��.��GMTʱ��Ļ����ϼ���ʱ��ƫ�ơ�
class INFRA_API CTime : public SystemTime
{
public:
    ///ʱ���޸Ļص�����
    typedef TFunction1<bool, SystemTime> ModifyProc;
    ///ʱ���޸ĺ���
    typedef TFunction2<void, const CTime&, int> SetCurrentTimeHook;
    typedef TFunction2<void, const SystemTimeEx&, int> SetCurrentTimeHookEx;
    
    ///����˳���ʽ
    enum DateFormat
    {
        ymd,
        mdy,
        dmy
    };
        /// ��ʽ��ģʽѡ��
    enum FormatMask
    {
        fmGeneral = 0,      /// ָֻ���Ƿ���ʾ�Լ���ʼֵ
        fmSeparator = 1,    /// ָ���ָ���
        fmDateFormat = 2,   /// ָ��������˳��
        fmHourFormat = 4,   /// ָ��Сʱ��ʽ
        fmAll = fmSeparator | fmDateFormat | fmHourFormat ///ָ�����и�ʽѡ��
    };

    /// ȱʡ���캯��
    CTime();

    ///�ڲ��᳢��ת��������ʱ��, ������ʱ���ļ����ü�, �ڲ�ͬƽ̨�����һ��
    CTime(uint64 time);

    CTime(uint64 time, bool addTimeZone);

    CTime(int year, int month, int day, int hour, int imn, int sec);

    /// ���Եõ�UNIX Epochʱ�䣬ָ��GMT 1970-1-1 00��00��00��ĳ��ʱ�侭��������
    uint64 makeTime() const;

    /// ��UNIX Epoch�����ֽ��������ʱ����
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

    /// ʱ���ʽ��
    void format(char* buf, const char* format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral) const;

    bool parse(const char* buf, const char* format = "yyyy-MM-dd HH:mm:ss", int mask = fmGeneral) const;

    /// ���̻�ȡ���ص�ǰϵͳʱ��
    static CTime getCurrentTime();

    static SystemTimeEx getCurrentTimeEx();

    static CTime getCurTimeForPrint();

    static void setCurrentTime(const CTime& time, int toleranceSecondes = 0);

    static bool setCurrentTimeEx(const CTime& time, int toleranceSecondes = 0);

    static bool setCurrentTime(const SystemTimeEx& time, int toleranceSecondes = 0);

    ///��ȡ��ϵͳ���������ڵĺ�����
    static uint64 getCurrentMilliSecond();

    ///��ȡ��ϵͳ���������ڵ�΢����
    static uint64 getCurrentMicroSecond();


public:
    static const CTime minTime; ///��Ч��Сʱ��
    static const CTime maxTime; ///��Ч���ʱ��

};

#endif
