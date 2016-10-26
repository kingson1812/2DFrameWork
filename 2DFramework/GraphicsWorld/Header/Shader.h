#pragma once
#include <GameUtility.h>
class Shader
{
private:
	GLuint m_vertexShader, m_fragmentShader;
public:
	GLuint m_program;
	GLuint m_stateCount, m_sttCulling, m_sttDepthTest, m_sttBlend;
	GLuint m_id;

	char m_vsPath[MAX_CHAR], m_fsPath[MAX_CHAR];

	GLint m_posAttribute;
	GLint m_uvAttribute;
	GLint m_uniformArray[MAX_UNIFORM];

	Shader();
	Shader(GLuint id,const char * &vsPath,const char * &fsPath);
	~Shader();

	int InitVariables();
};