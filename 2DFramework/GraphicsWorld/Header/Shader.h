#pragma once
#include <GameUtility.h>
class Shader
{
private:
	GLuint m_vertexShader, m_fragmentShader;
public:
	GLuint m_program;
	GLuint m_numStates, m_sttCulling, m_sttDepthTest, m_sttBlend;
	GLuint m_Id;

	char m_vsPath[MAX_CHAR], m_fsPath[MAX_CHAR];

	GLint m_posAttribute;
	GLint m_uvAttribute;
	GLint m_uniformArray[MAX_UNIFORM];

	Shader();
	Shader(GLuint id, char * vsPath, char * fsPath);
	~Shader();

	int InitVariables();
	int InitShaders(char * vsPath, char * fsPath);
};