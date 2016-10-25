//Define all macros, const, flags

#pragma once
#if _WIN32_
#define _CRT_SECURE_NO_WARNINGS
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#define		PI											M_PI
#define		D2R(a)								(float)((a) * PI / 180.0f)
#define		MODEL_H							1
#define		MODEL_W							1

#define		SAFE_DEL(a)						{if((a) != NULL ) delete(a);}
#define		SAFE_DEL_ARR(a)				{if((a) != NULL ) delete[](a);}
#define		MAX_CHAR							512
#define		MAX_UNIFORM					256

#define ENABLE_LOG 1

#if ENABLE_LOG
#if _WIN32_ //_WIN32_
#include <stdio.h>
#include <stdarg.h>
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