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

