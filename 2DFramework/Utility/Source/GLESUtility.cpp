#include <GLESUtility.h>
#include <WindowUtility.h>
#include <stdio.h>

EGLBoolean CreateWindowEGL(EGLNativeWindowType eglNativeWinType,
	EGLDisplay* eglDisplay,
	EGLContext* eglContext,
	EGLSurface* eglSurface,
	EGLint attArray[])
{
	EGLint numConfigs;
	EGLint superVersion;
	EGLint minorVersion;
	EGLDisplay _eglDisplay;
	EGLContext _eglContext;
	EGLSurface _eglSurface;
	EGLConfig eglConfig;
	EGLint ctxArray[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	// Get Display
	_eglDisplay = eglGetDisplay(GetDC(eglNativeWinType));
	if (_eglDisplay == EGL_NO_DISPLAY)
	{
		return EGL_FALSE;
	}

	// Initialize EGL
	if (!eglInitialize(_eglDisplay, &superVersion, &minorVersion))
	{
		return EGL_FALSE;
	}

	// Get configs
	if (!eglGetConfigs(_eglDisplay, NULL, 0, &numConfigs))
	{
		return EGL_FALSE;
	}

	// Choose config
	if (!eglChooseConfig(_eglDisplay, attArray, &eglConfig, 1, &numConfigs))
	{
		return EGL_FALSE;
	}

	// Create a surface
	_eglSurface = eglCreateWindowSurface(_eglDisplay, eglConfig, eglNativeWinType, NULL);
	if (_eglSurface == EGL_NO_SURFACE)
	{
		return EGL_FALSE;
	}

	// Create a GL context
	_eglContext = eglCreateContext(_eglDisplay, eglConfig, EGL_NO_CONTEXT, ctxArray);
	if (_eglContext == EGL_NO_CONTEXT)
	{
		return EGL_FALSE;
	}

	// Set current context
	if (!eglMakeCurrent(_eglDisplay, _eglSurface, _eglSurface, _eglContext))
	{
		return EGL_FALSE;
	}

	*eglDisplay = _eglDisplay;
	*eglSurface = _eglSurface;
	*eglContext = _eglContext;

	return EGL_TRUE;
}

//Create a frame
//@esFrame: frame
//@frameWidth: width of frame
//@frameHeight: height of frame
//@title: name of frame
//@flag: to use EGL params
GLboolean ESUTILITYAPI CreateFrame(ESFRAME* esFrame, GLuint frameWidth, GLuint frameHeight, const char *title, GLuint flag)
{
	EGLint attArray[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, (flag & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
		EGL_DEPTH_SIZE, (flag & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
		EGL_STENCIL_SIZE, (flag & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, (flag & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
		EGL_NONE
	};

	if (esFrame == NULL)
	{
		return GL_FALSE;
	}

	esFrame->m_width = frameWidth;
	esFrame->m_height = frameHeight;

	if (!_CreateWindow(esFrame, title))
	{
		return GL_FALSE;
	}

	if (!CreateWindowEGL(esFrame->m_eglWindowHandler,
		&esFrame->m_eglDisplay,
		&esFrame->m_eglFrame,
		&esFrame->m_eglSurface,
		attArray))
	{
		return GL_FALSE;
	}

	return GL_TRUE;
}

GLuint ESUTILITYAPI LoadShader(GLenum type, char *path)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
		return 0;

	// Load the shader source
	FILE * pf;
	if ((pf = fopen(path, "rb")) == 0)
		return NULL;
	fseek(pf, 0, SEEK_END);
	long size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	char * shaderSrc = new char[size + 1];
	fread(shaderSrc, sizeof(char), size, pf);
	shaderSrc[size] = 0;
	fclose(pf);

	glShaderSource(shader, 1, (const char **)&shaderSrc, NULL);
	delete[] shaderSrc;

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1)
		{
			char* infoLog = new char[infoLen];
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
#ifdef WIN32
			LogMessage("[GLESU]>> Error compiling shader:\n%s\n", infoLog);
#endif           
			delete[] infoLog;
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

GLuint ESUTILITYAPI LoadProgram(GLuint vsID, GLuint fsID)
{

	GLuint programObject;
	GLint linked;

	// Create the program object
	programObject = glCreateProgram();

	if (programObject == 0)
		return 0;

	glAttachShader(programObject, vsID);
	glAttachShader(programObject, fsID);

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1)
		{
			char* infoLog = new char[sizeof(char) * infoLen];
			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
#ifdef WIN32
			LogMessage("[GLESU]>> Error linking program:\n%s\n", infoLog);
#endif          
			delete infoLog;
		}
		glDeleteProgram(programObject);
		return 0;
	}
	return programObject;
}

void ESUTILITYAPI InitFrame(ESFRAME *esFrame)
{
	if (esFrame != NULL)
	{
		memset(esFrame, 0, sizeof(ESFRAME));
	}
}

void ESUTILITYAPI MainLoop(ESFRAME *esFrame)
{
	_WinLoop(esFrame);
}

void ESUTILITYAPI RegisterDrawFnc(ESFRAME *esFrame, void (ESCALLBACK* cbDrawFnc)(ESFRAME*))
{
	esFrame->drawFnc = cbDrawFnc;
}

void ESUTILITYAPI RegisterKeyFnc(ESFRAME *esFrame, void (ESCALLBACK* cbKeyFnc)(ESFRAME*, unsigned char keycode, bool pressed))
{
	esFrame->keyFnc = cbKeyFnc;
}

void ESUTILITYAPI RegisterUpdateFnc(ESFRAME *esFrame, void (ESCALLBACK* cbUpdateFnc)(ESFRAME*, float deltaTime))
{
	esFrame->updateFnc = cbUpdateFnc;
}

void ESUTILITYAPI RegisterMouseDownFnc(ESFRAME *esFrame, void (ESCALLBACK *cbMouseDownFnc) (ESFRAME*, int, int))
{
	esFrame->mouseDownFnc = cbMouseDownFnc;
}

void ESUTILITYAPI RegisterMouseUpFnc(ESFRAME * esFrame, void (ESCALLBACK *cbMouseUpFnc) (ESFRAME*, int, int))
{
	esFrame->mouseUpFnc = cbMouseUpFnc;
}

void ESUTILITYAPI RegisterMouseMoveFunc(ESFRAME *esFrame, void (ESCALLBACK *cbMouseMoveFunc) (ESFRAME*, int, int))
{
	esFrame->mouseMoveFnc = cbMouseMoveFunc;
}
void ESUTILITYAPI LogMessage(const char* string, ...)
{
	va_list params;
	char buff[2048];

	va_start(params, string);
	vsprintf_s(buff, sizeof(buff), string, params);

	printf("%s", buff);
	OutputDebugString(buff);

	va_end(params);
}