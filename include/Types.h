
#ifndef __TYPES_H__
#define __TYPES_H__

typedef signed char         int8;
typedef signed short        int16;
typedef signed int          int32;
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;

#ifdef _MSC_VER
typedef __int64             int64;
typedef unsigned __int64    uint64;
#elif define(__GNUC__)
typedef long long           int64;
typedef unsigned long long  uint64;
#endif


#endif

