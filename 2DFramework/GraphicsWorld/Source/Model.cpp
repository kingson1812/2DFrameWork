#include <Model.h>

Model::Model()
{}

Model::Model(const char* & filePath, const GLuint &id)
{
	m_filePath = (char*)filePath;
	m_id = id;
}

void Model::Init()
{
	LoadModel();
	GenVIBO();
	BindBuffVIBO();
	BuffDataVIBO();
}

void Model::LoadModel()
{
	m_vertexCount = 4;
	m_vertexArray = new Vertex[m_vertexCount];

	//make a model : 1x1 px^2
	m_vertexArray[0].m_pos = Vector3(-1.0, 1.0, 0.0);
	m_vertexArray[1].m_pos = Vector3(1.0, 1.0, 0.0);
	m_vertexArray[2].m_pos = Vector3(1.0, -1.0, 0.0);
	m_vertexArray[3].m_pos = Vector3(-1.0, -1.0, 0.0);

	//fully fill texture (stretch)
	m_vertexArray[0].m_uv = Vector2(0.0, 1.0);
	m_vertexArray[1].m_uv = Vector2(1.0, 1.0);
	m_vertexArray[2].m_uv = Vector2(1.0, 0.0);
	m_vertexArray[3].m_uv = Vector2(0.0, 0.0);

	//drawing sequence LT-RT-RB __ LT-RB-LB
	m_indexCount = 6;
	m_indexArray = new unsigned int[m_indexCount];
	m_indexArray[0] = 0;
	m_indexArray[1] = 1;
	m_indexArray[2] = 2;
	m_indexArray[3] = 0;
	m_indexArray[4] = 2;
	m_indexArray[5] = 3;
}

void Model::GenVIBO()
{
	glGenBuffers(1, &m_vboID);
	glGenBuffers(1, &m_iboID);
}

void Model::BindBuffVIBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
}

void Model::BuffDataVIBO()
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vertexCount, m_vertexArray, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_indexCount, m_indexArray, GL_DYNAMIC_DRAW);
}

void Model::UnBindVIBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}