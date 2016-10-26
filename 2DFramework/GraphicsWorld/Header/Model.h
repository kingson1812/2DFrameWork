#pragma once
#include "Vertex.h"

class Model
{
public:
	Model();
	Model(const char* & filePath,const GLuint &id);
	~Model();
	
	GLuint m_id;
	GLuint m_indexCount, m_vertexCount;


	void LoadModel();
	void Init();

	void GenVIBO();

	void BindBuffVIBO();
	void BuffDataVIBO();
	void UnBindVIBO();

private:
	GLuint m_iboID;
	GLuint m_vboID;

	Vertex* m_vertexArray;
	unsigned int *m_indexArray;
	char * m_filePath;
};