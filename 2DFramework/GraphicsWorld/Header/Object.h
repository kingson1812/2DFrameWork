#pragma once
#include <stdio.h>
#include <GameUtility.h>

enum ObjectType
{
	OT_NORMAL = 0,
	OT_SKYBOX,
	OT_TERRAIN,
};

class Object
{
public:
	Object();
	~Object();
private:
	Vector3 m_rotation;
	Vector3 m_scale;
	Vector3 m_translation;

	Matrix m_world;
	Matrix m_view;
	Matrix m_projection;

};