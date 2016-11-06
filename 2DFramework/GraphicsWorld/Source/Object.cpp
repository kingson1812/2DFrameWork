#include <Object.h>

Object::Object()
{}

Object::~Object()
{}

void Object::Init()
{
	const char *s = "../GraphicsWorld/Asset/Object.vs";
	const char *v = "../GraphicsWorld/Asset/Object.fs";
	m_shader = new Shader(0, s, v);
	m_shader->InitVariables();

	m_model = new Model();
	m_model->Init();
	const char *p = "../Asset/Texture/stone.png";
	m_textureArray = new Texture(0, p);
	
	m_textureArray->Init();
}

void Object::Draw()
{
	glUseProgram(m_shader->m_program);

	m_model->BindBuffVIBO();
	if (m_shader->m_posAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader->m_posAttribute);
		glVertexAttribPointer(m_shader->m_posAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)OFFSET_POS);
	}

	if (m_shader->m_uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader->m_uvAttribute);
		glVertexAttribPointer(m_shader->m_uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)OFFSET_UV);
	}

	int m_numTextures = 1;
	//for (int i = 0; i<m_numTextures; i++)
//	{
		glActiveTexture(GL_TEXTURE0);
		m_textureArray->BindTexture();
		glUniform1i(m_shader->m_uniformArray[0], 0);
//	}

	glDrawElements(GL_TRIANGLES, m_model->m_indexCount, GL_UNSIGNED_INT, 0);

	m_model->UnBindVIBO();
	m_textureArray->UnbindTexture();
}