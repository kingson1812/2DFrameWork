#pragma once 

#include <MathVectorMatrix.h>

struct Vertex
{
	Vector3	m_pos;
	Vector2	m_uv;

	Vertex();
	~Vertex();

	Vertex(Vector3 pos, Vector2 uv);
};

#define	OFFSET_POS	0
#define	OFFSET_UV	12