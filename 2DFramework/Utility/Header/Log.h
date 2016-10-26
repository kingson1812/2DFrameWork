#define ENABLE_LOG 1

#if ENABLE_LOG
#if _WIN32_ //_WIN32_
#include <stdio.h>
#define LOG_D(...)			printf(##__VA_ARGS__)
#elif _ANDROID_ //_ANDROID_
#include <android/log.h>
#define LOG_D(x, ...)		__android_log_print(ANDROID_LOG_DEBUG, x, ##__VA_ARGS__)
#define LOG_I(x, ...)		__android_log_print(ANDROID_LOG_INFO, x, ##__VA_ARGS__)
#define LOG_E(x, ...)		__android_log_print(ANDROID_LOG_ERROR, x, ##__VA_ARGS__)
#elif _IOS_ //
//Unknown
#endif
#endif //ENABLE_LOG