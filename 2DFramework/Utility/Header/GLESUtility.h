#pragma once

#include <Define.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

#define ESUTILITYAPI	__cdecl
#define ESCALLBACK	__cdecl

//@flag - RGB color buffer
#define ES_WINDOW_RGB           0
//@flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1 
//@flag - depth buffer
#define ES_WINDOW_DEPTH         2 
//@flag - stencil buffer
#define ES_WINDOW_STENCIL       4
//@flag - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8

//Class ESFRAME for creating Window/EOS program.
class ESFRAME
{
public:
	GLint m_width;
	GLint m_height;

	EGLNativeWindowType m_eglWindowHandler;
	EGLDisplay m_eglDisplay;
	EGLContext m_eglFrame;
	EGLSurface m_eglSurface;

	//Functions: draw, key, update, mouse
	void (ESCALLBACK * drawFnc) (ESFRAME*);
	void (ESCALLBACK * keyFnc) (ESFRAME*, unsigned char keycode, bool pressed);
	void (ESCALLBACK * updateFnc) (ESFRAME*, float deltaTime);
	void (ESCALLBACK *mouseDownFnc) (ESFRAME*, int, int);
	void (ESCALLBACK *mouseUpFnc) (ESFRAME*, int, int);
	void (ESCALLBACK *mouseMoveFnc) (ESFRAME*, int, int);
	//End functions
};
//End 

//ES_Utility_API functions
GLboolean ESUTILITYAPI CreateFrame(ESFRAME* esFrame, GLuint frameWidth, GLuint frameHeight, const char *title, GLuint flags);
GLuint ESUTILITYAPI LoadShader(GLenum shaderType, char *shaderPath);
GLuint ESUTILITYAPI LoadProgram(GLuint vsID, GLuint fsID);
EGLBoolean CreateWindowEGL(EGLNativeWindowType eglNativeWinType, 
	EGLDisplay* eglDisplay,
	EGLContext* eglContext, 
	EGLSurface* eglSurface,
	EGLint attArray[]);

void ESUTILITYAPI InitFrame(ESFRAME* esFrame);
void ESUTILITYAPI MainLoop(ESFRAME *);
void ESUTILITYAPI RegisterDrawFnc(ESFRAME *esFrame, void (ESCALLBACK* cbDrawFnc)(ESFRAME*));
void ESUTILITYAPI RegisterKeyFnc(ESFRAME *esFrame, void (ESCALLBACK* cbKeyFnc)(ESFRAME*, unsigned char keycode, bool pressed));
void ESUTILITYAPI RegisterUpdateFnc(ESFRAME *esFrame, void (ESCALLBACK* cbUpdateFnc)(ESFRAME*, float deltaTime));
void ESUTILITYAPI RegisterMouseDownFnc(ESFRAME *esFrame, void (ESCALLBACK *cbMouseDownFnc) (ESFRAME*, int, int));
void ESUTILITYAPI RegisterMouseUpFnc(ESFRAME * esFrame, void (ESCALLBACK *cbMouseUpFnc) (ESFRAME*, int, int));
void ESUTILITYAPI RegisterMouseMoveFunc(ESFRAME *esFrame, void (ESCALLBACK *cbMouseMoveFunc) (ESFRAME*, int, int));
void ESUTILITYAPI LogMessage(const char* string, ...);

//End ES_Utility_Fncs