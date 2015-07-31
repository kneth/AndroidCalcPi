#ifndef __UTIL_HPP__
#define __UTIL_HPP__

// Used by logging
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <android/log.h>

#define S64(x)  static_cast<int64_t>(x)

// undefine to disable logging
#define TRACE 1

#if TRACE
#  define ENTER() __android_log_print(ANDROID_LOG_DEBUG, "calcPi", "Enter %s", __FUNCTION__);
#  define ENTER_PTR(ptr) __android_log_print(ANDROID_LOG_DEBUG, "calcPi", "Enter %s %" PRId64, __FUNCTION__, static_cast<int64_t>(ptr));
#  define LEAVE() __android_log_print(ANDROID_LOG_DEBUG, "calcPi", "Leave %s", __FUNCTION__);
#  define LOG(...) __android_log_print(ANDROID_LOG_DEBUG, "calcPi", __VA_ARGS__);
#else
#  define ENTER()
#  define ENTER_PTR(ptr)
#  define LEAVE()
#  define LOG(...)
#endif

#endif // __UTIL_HPP__
