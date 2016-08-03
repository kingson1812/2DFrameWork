#include <Shader.h>

Shader::Shader()
{}

Shader::Shader(GLuint id, char * vs, char * fs):m_Id(id)
{
	strcpy(m_vsPath, vs);
	strcpy(m_fsPath, fs);
	memset(m_uniformArray, -1, MAX_UNIFORM);
}

int Shader::InitVariables()
{
	/*char filePath1[max];
	sprintf(filePath1, "%s%s", MOTHERFOLDER, fileVS);*/
	m_vertexShader = LoadShader(GL_VERTEX_SHADER, m_vsPath);

	if (m_vertexShader == 0)
		return -1;//Error

	/*char filePath2[256];
	sprintf(filePath2, "%s%s", MOTHERFOLDER, fileFS);*/
	m_fragmentShader = LoadShader(GL_FRAGMENT_SHADER, m_fsPath);

	if (m_fragmentShader == 0)
	{
		glDeleteShader(m_vertexShader);
		return -2;
	}



	m_program = LoadProgram(m_vertexShader, m_fragmentShader);

	//finding location of uniforms / attributes
	m_posAttribute = glGetAttribLocation(m_program, "a_posL");
	m_uvAttribute = glGetAttribLocation(m_program, "a_uv");

	m_uniformArray[0] = glGetUniformLocation(m_program, "u_MVP");//MVP
	return 0;
}

int Shader::InitShaders(char *vsPath, char *fsPath)
{
	m_vertexShader = LoadShader(GL_VERTEX_SHADER, vsPath);

	if (m_vertexShader == 0)
		return -1;

	m_fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fsPath);

	if (m_fragmentShader == 0)
	{
		glDeleteShader(m_vertexShader);
		return -2;
	}

	m_program = LoadProgram(m_vertexShader, m_fragmentShader);
	return 0;
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}