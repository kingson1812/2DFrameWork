#pragma once
#include <GLESUtility.h>
#include <Vertex.h>

class Model
{
public:
	Model();
	~Model();
	GLuint m_modelID;
private:
	GLuint m_iboID;
	GLuint m_vboID;

	Vertex* m_vertex;
	int m_numOfVertex;
};