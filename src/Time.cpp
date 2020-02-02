#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <algorithm>
#include "../include/Assert.h"
#include "../include/Time.h"

#if defined(WIN32) || defined(_WIN64)
#include <Windows.h>
#ifdef snprintf
#define snprintf _snprintf
#endif

#elif defined(__linux__) || defined(__mac__)


#endif

#include "Mutex.h"
//#include "Guard.h"
#include <list>

#ifdef _MSC_VER
#pragma warning (disable:4996)
#endif

static std::string s_format = "yyyy-MM-dd HH:mm:ss";
static char s_dateSeperator = '-';
static bool s_12hour = false;
static bool s_bTimeUpdatNow = false;



typedef struct _TIME_ZONE
{
    int index;          ///ʱ������
    int zone_time;      ///��������α�׼ʱ���ֵ
    const char* str;    ///ʱ����
}TimeZone;

TimeZone g_ntp_timezone_table[] =
{
    { 0, 0 * 3600, "GMT+00:00" },
    { 1, 1 * 3600, "GMT+01:00" },
    { 2, 2 * 3600, "GMT+02:00" },
    { 3, 3 * 3600, "GMT+03:00" },
    { 4, 4 * 3600, "GMT+04:00" },
    { 5, 5 * 3600, "GMT+05:00" },
    { 6, 6 * 3600, "GMT+06:00" },
    { 7, 7 * 3600, "GMT+07:00" },
    { 8, 8 * 3600, "GMT+08:00" },
    { 9, 9 * 3600, "GMT+09:00" },
    { 10, 10 * 3600, "GMT+10:00" },
};


void utc_to_time(uint64 utc, SystemTime& time);

void setSysCurrentTime(const CTime& time, int tolreanceSeconds);


typedef std::list <CTime::ModifyProc> ModifyProcList;

static CTime::SetCurrentTimeHook s_setTimeHook = setSysCurrentTime;

const CTime CTime::minTime(2000, 1, 1, 0, 0, 0);
const CTime CTime::maxTime(2038, 1, 1, 0, 0, 0);

static int s_indst = -1;  ///����Ƿ�������ʱ��-1��ʾ��ȷ����0��ʾ��������ʱ�� 1��ʾ������ʱ
static int s_TimeZoneDiffSec = 0x0fffffff; ///��Ǳ���ʱ��ʱ����UTCʱ����������

CTime::CTime()
{
    year = 0;
    month = 0;
    day = 0;
    wday = 0;
    hour = 0;
    minute = 0;
    second = 0;
    isdst = -1;
}

CTime::CTime(uint64 time)
{
    year = 0;
    month = 0;
    day = 0;
    wday = 0;
    hour = 0;
    minute = 0;
    second = 0;
    isdst = -1;

    breakTime(time);
}

void CTime::breakTime(uint64 time)
{
    time_t tt = (time_t)time;
    if (time != (uint64)tt)
    {
        ////errof("CTime::breakTime overflowed!\n");
    }
    utc_to_time(time, *this);
}