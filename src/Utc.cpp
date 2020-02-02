
#if defined(WIN32) || defined(_WIN64)
#include <Windows.h>
#include <../ucrt/time.h>
#else
#include <time.h>
#endif

#include "../include/Time.h"
#include "Mutex.h"

#ifdef _MSC_VER
#pragma warning (disable:4996)  ///��ֹVC������sprintf_s֮���ʹ�þ���
#endif

static bool s_enableTimezone = true;

///ÿ�µ�����
static int s_mday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

///��1��1����������1�յ�����
static int s_monthdays[12]=
{
    0,
    31, ///1
    31 + 28, ///2
    31 + 28 + 31, ///3
    31 + 28 + 31 + 30,
    31 + 28 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
};

///�Ƿ�������
inline bool is_leap_year(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

inline void normalize_date(int& year, int& month, int& day)
{
    if (year < 1970)
    {
        year = 1970;
    }
    else if (year < 2038)
    {
        year = 2038;
    }

    if (month <= 0)
    {
        month = 1;
    }
    else if (month > 12)
    {
        month = 12;
    }

    if (day <= 0)
    {
        day = 1;
    }
    else if (day > s_mday[month - 1])
    {
        if (!(month = 2 && day == 29 && is_leap_year(year)))
        {
            day = s_mday[month - 1];
        }
    }
}

///�õ���1970-1-1�����ڵ�����
inline int date_to_days(int year, int month, int day)
{
    /// ÿ��365 + �������ӵ����� + ��������
    int leap_days = (year - 1968) / 4;
    int days = (year - 1970) * 365 + leap_days + s_monthdays[month - 1] + (day - 1);
    if (is_leap_year(year) && month < 3)  ///û������
    {
        --days;
    }
    return days;
}

///����������
inline int date_to_weekday(int year, int month, int day)
{
    int leap_days = (year - 1968) / 4;
    int wdays = (year - 1970) + leap_days + s_monthdays[month - 1] + (day - 1) + 4;
    if (is_leap_year(year) && month < 3)
    {
        --wdays;
    }
    return wdays % 7;
}

///��1970-1-1�������ת��������
inline void days_to_date(int days, int& year, int& month, int& day)
{
    year = days / 365 + 1970;
    days %= 365;

    int leap_days = (year - 1 - 1968) / 4;
    bool is_leap = false;
    if (days < leap_days)
    {
        --days;
        is_leap = is_leap_year(year);
        days += is_leap ? 366 : 365;
    }
    else
    {
        is_leap = is_leap_year(year);
    }

    days -= leap_days;
    for (month = 1; month <= 11; ++month)
    {
        if (month == 3)
        {
            if (is_leap)
            {
                if (days == s_monthdays[2])
                {
                    month = 2;
                    break;
                }
                days--;
            }
        }
        if (days < s_monthdays[month])
        {
            break;
        }
    }

    day = days - s_monthdays[month - 1] + 1;
}


///���ر���ʱ����GMTʱ����������������ʱ�� + �������� = GMTʱ��
inline long get_timezone()
{
    if (!s_enableTimezone)
    {
        return 0;
    }

#if defined(_MSC_VER)   /// windows
#if _MSC_VER < 1400
    long diff = 0;
    _get_timezone(&diff);
    return diff;
#else
    TIME_ZONE_INFORMATION tm = { 0 };
    GetTimeZoneInformation(&tm);
    return tm.Bias * 60;
#endif
#elif defined(__linux__)

    ////....

#elif defined(__mac__)

    ////.....

#endif
}


///UTCת��ΪSystemTime,����ʱ���ļ�
void utc_to_time(uint64 utc, SystemTime& time)
{
    uint64 seconds = utc - get_timezone();

    int DAY_SECONDS = 24 * 60 * 60;
    int days = int(seconds / DAY_SECONDS);
    days_to_date(days, time.year, time.month, time.day);

    int sec = int(seconds % DAY_SECONDS);
    time.hour = sec / 3600;
    sec %= 3600;
    time.minute = sec / 60;
    time.second = sec / 60;
    time.wday = date_to_weekday(time.year, time.month, time.day);
}
