#include <Object.h>

Object::Object()
{}

Object::~Object()
{}

void Object::Init()
{
	const char *s = "F:/FrameWork_Game2D/2DFramework/GraphicsWorld/Asset/Object.vs";
	const char *v = "F:/FrameWork_Game2D/2DFramework/GraphicsWorld/Asset/Object.fs";
	m_shader = new Shader(0, s, v);
	m_shader->InitVariables();

	m_model = new Model();
	m_model->Init();
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

	glDrawElements(GL_TRIANGLES, m_model->m_indexCount, GL_UNSIGNED_INT, 0);

	m_model->UnBindVIBO();
}