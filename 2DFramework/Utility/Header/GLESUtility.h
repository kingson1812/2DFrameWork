#pragma once

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#define ESUTILITYAPI	__cdecl
#define ESCALLBACK	__cdecl

class ESFRAME
{
public:
	GLint m_width;
	GLint m_height;

	EGLNativeWindowType m_eglWindowHandler;
	EGLDisplay m_eglDisplay;
	EGLContext m_eglFrame;
	EGLSurface m_eglSurface;

	void (ESCALLBACK * drawFnc) (ESFRAME*);
	void (ESCALLBACK * keyFnc) (ESFRAME*, unsigned char keycode, bool pressed);
	void (ESCALLBACK * updateFnc) (ESFRAME*, float deltaTime);
};

GLboolean ESUTILITYAPI CreateFrame(ESFRAME* esFrame, GLuint frameWidth, GLuint frameHeight, const char *title);
GLuint ESUTILITYAPI LoadShader(GLenum shaderType, char *shaderPath);
GLuint ESUTILITYAPI LoadProgram(GLuint vsID, GLuint fsID);

void ESUTILITYAPI InitFrame(ESFRAME* esFrame);
void ESUTILITYAPI MainLoop(ESFRAME *);
void ESUTILITYAPI RegisterDrawFnc(ESFRAME *esFrame, void (ESCALLBACK* cbDrawFnc)(ESFRAME*));
void ESUTILITYAPI RegisterKeyFnc(ESFRAME *esFrame, void (ESCALLBACK* cbKeyFnc)(ESFRAME*, unsigned char keycode, bool pressed));
void ESUTILITYAPI RegisterUpdateFnc(ESFRAME *esFrame, void (ESCALLBACK* cbUpdateFnc)(ESFRAME*, float deltaTime));
void ESUTILITYAPI LogMessage(const char* string, ...);

