#ifndef LOG_H
#define LOG_H

#include "../../../../../../../../Library/Android/sdk/ndk/23.1.7779620/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/android/log.h"

#define LOG_TAG "llk"

/** 日志控制开关
 * LOGCAT_PRINT_LIMIT：开启info以及的日志
 * LOGCAT_PRINT_CLOSE：关闭所有等级的日志
 *
将 LOGCAT_PRINT_FLAG 宏定义放到 gradle里边定义吧，方便区分编译版本
buildTypes {
    release {
        externalNativeBuild {
            cmake { cppFlags "-DLOGCAT_PRINT_LIMIT" }
        }
    }
}
 */



#ifdef LOGCAT_PRINT_LIMIT
#define LOGV(...)
#define LOGD(...)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#elif LOGCAT_PRINT_CLOSE
#define LOGV(...)
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#else
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif

#endif //LOG_H
