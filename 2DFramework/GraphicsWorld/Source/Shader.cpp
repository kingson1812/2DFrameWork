#include <Shader.h>

Shader::Shader()
{}

Shader::Shader(GLuint id, const char * &vs, const char * &fs) :m_id(id)
{
	strcpy(m_vsPath, vs);
	strcpy(m_fsPath, fs);
	memset(m_uniformArray, -1, MAX_UNIFORM);//Set default value for all of uniforms
}

//return 0 = successful
//return -1 = vs error
//return -2 = fs error
int Shader::InitVariables()
{
	m_vertexShader = LoadShader(GL_VERTEX_SHADER, m_vsPath);
	
	if (m_vertexShader == 0)
		return -1;

	m_fragmentShader = LoadShader(GL_FRAGMENT_SHADER, m_fsPath);

	if (m_fragmentShader == 0)
	{
		glDeleteShader(m_vertexShader);
		return -2;
	}

	m_program = LoadProgram(m_vertexShader, m_fragmentShader);

	m_posAttribute = glGetAttribLocation(m_program, "a_posLocal");
	m_uvAttribute = glGetAttribLocation(m_program, "a_uvTexture");

	//find uniforms
	//m_uniformArray[0] = glGetUniformLocation(m_program, "u_MVP");
	m_uniformArray[0] = glGetUniformLocation(m_program, "u_texture2D");
	return 0;
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
}