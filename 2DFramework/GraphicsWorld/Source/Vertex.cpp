#include <stdafx.h>
#include <Vertex.h>

Vertex::Vertex()
{}

Vertex::~Vertex()
{}

Vertex::Vertex(Vector3 pos, Vector2 uv) :m_pos(pos), m_uv(uv)
{}