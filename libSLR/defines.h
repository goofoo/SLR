//
//  defines.h
//
//  Created by 渡部 心 on 2015/07/08.
//  Copyright (c) 2015年 渡部 心. All rights reserved.
//

#ifndef SLR_defines_h
#define SLR_defines_h

// Platform defines
#if defined(_WIN32) || defined(_WIN64)
#   define SLR_Defs_Windows
#   if defined(__MINGW32__) // Defined for both 32 bit/64 bit MinGW
#       define SLR_Defs_MinGW
#   elif defined(_MSC_VER)
#       define SLR_Defs_MSVC
#   endif
#elif defined(__linux__)
#   define SLR_Defs_Linux
#elif defined(__APPLE__)
#   define SLR_Defs_OS_X
#elif defined(__OpenBSD__)
#   define SLR_Defs_OpenBSD
#endif

#ifdef SLR_Defs_MSVC
#   define NOMINMAX
#   define _USE_MATH_DEFINES
#   ifdef SLR_API_EXPORTS
#       define SLR_API __declspec(dllexport)
#   else
#       define SLR_API __declspec(dllimport)
#   endif
// MSVC 19.0 (Visual Studio 2015 Update 1) seems to have a problem related to a constexpr constructor.
#   define CONSTEXPR_CONSTRUCTOR
#   include <Windows.h>
#else
#   define SLR_API
#   define CONSTEXPR_CONSTRUCTOR constexpr
#endif

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstdarg>
#include <cmath>
#include <cfloat>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include <array>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <stack>

#include <chrono>
#include <limits>
#include <algorithm>
#include <memory>
#include <functional>

#ifdef DEBUG
#define ENABLE_ASSERT
#endif

#ifdef SLR_Defs_MSVC
SLR_API void debugPrintf(const char* fmt, ...);
#else
#   define debugPrintf(fmt, ...) printf(fmt, ##__VA_ARGS__);
#endif

#ifdef ENABLE_ASSERT
#   define SLRAssert(expr, fmt, ...) if (!(expr)) { debugPrintf("%s @%s: %u:\n", #expr, __FILE__, __LINE__); debugPrintf(fmt"\n", ##__VA_ARGS__); abort(); } 0
#else
#   define SLRAssert(expr, fmt, ...)
#endif

#define SLRAssert_NotDefined() SLRAssert(false, "Not defined!")
#define SLRAssert_NotImplemented() SLRAssert(false, "Not implemented!")

#define SLR_Minimum_Machine_Alignment 16
#define SLR_L1_Cacheline_Size 64

// For memalign, free, alignof
#if defined(SLR_Defs_MSVC)
#   include <malloc.h>
#   define SLR_memalign(size, alignment) _aligned_malloc(size, alignment)
#   define SLR_freealign(ptr) _aligned_free(ptr)
#   define SLR_alignof(T) __alignof(T)
#elif defined(SLR_Defs_OS_X) || defined(SLR_Defs_OpenBSD)
inline void* SLR_memalign(size_t size, size_t alignment) {
    void* ptr;
    if (posix_memalign(&ptr, alignment, size))
        ptr = nullptr;
    return ptr;
}
#   define SLR_freealign(ptr) ::free(ptr)
#   define SLR_alignof(T) alignof(T)
#elif defined(SLR_Defs_Linux)
#   define SLR_memalign(size, alignment) SLRAssert_NotImplemented
#   define SLR_freealign(ptr) SLRAssert_NotImplemented
#endif

// For getcwd
#if defined(SLR_Defs_MSVC)
#   define SLR_getcwd(size, buf) GetCurrentDirectory(size, buf)
#elif defined(SLR_Defs_OS_X) || defined(SLR_Defs_OpenBSD) || defined(SLR_Defs_Linux)
#   include <unistd.h>
#   define SLR_getcwd(size, buf) getcwd(buf, size)
#endif

namespace std {
    template <typename T>
    inline T clamp(const T &v, const T &min, const T &max) {
        return std::min(max, std::max(min, v));
    }
    
    template <typename T, typename ...Args>
    inline std::array<T, sizeof...(Args)> make_array(Args &&...args) {
        return std::array<T, sizeof...(Args)>{ std::forward<Args>(args)... };
    }
}

template <typename T>
bool realEq(T a, T b, T epsilon) {
    bool forAbsolute = std::fabs(a - b) < epsilon;
    bool forRelative = std::fabs(a - b) < epsilon * std::fmax(std::fabs(a), std::fabs(b));
    return forAbsolute || forRelative;
}
template <typename T>
bool realGE(T a, T b, T epsilon) { return a > b || realEq(a - b, (T)0, epsilon); }
template <typename T>
bool realLE(T a, T b, T epsilon) { return a < b || realEq(a - b, (T)0, epsilon); }

inline uint32_t prevPowerOf2(uint32_t x) {
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x - (x >> 1);
}

template <typename T, typename ...ArgTypes>
std::shared_ptr<T> createShared(ArgTypes&&... args) {
    return std::shared_ptr<T>(new T(std::forward<ArgTypes>(args)...));
}

template <typename T, typename ...ArgTypes>
std::unique_ptr<T> createUnique(ArgTypes&&... args) {
    return std::unique_ptr<T>(new T(std::forward<ArgTypes>(args)...));
}

#define Use_Spectral_Representation

#endif
