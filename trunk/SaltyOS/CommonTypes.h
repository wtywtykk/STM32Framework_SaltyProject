#pragma once

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus
#define C_HEADER_BEGIN extern "C" {
#define C_HEADER_END }
#else
#define C_HEADER_BEGIN
#define C_HEADER_END
#endif

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#define DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
#define DEPRECATED_ATTRIBUTE __declspec(deprecated)
#else
#error Unsupported compiler!
#endif

#ifdef __cplusplus
#include <new>
//standard new will throw exceptions on allocation failures,but newlib can't process it.....
//define another "safe" new
//it returns NULL on allocation failures
#define new_noexcpt new(std::nothrow)
//disable original new.
DEPRECATED_ATTRIBUTE void *operator new(std::size_t size);
#endif

#ifndef __cplusplus
typedef unsigned char bool;
#define true 1
#define false 0
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef unsigned int uint;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef signed int sint;

typedef char* pstr;
typedef const char* pcstr;

typedef u16 STATUS;
#define S_OK 1
#define S_FAIL 0
