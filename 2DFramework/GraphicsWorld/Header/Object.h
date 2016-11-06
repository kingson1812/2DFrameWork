#pragma once
#include <stdio.h>
#include <GameUtility.h>
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

enum ObjectType
{
	OT_NORMAL = 0,
	OT_SKYBOX,//3D only 
	OT_TERRAIN,
};

class Object
{
public:
	Object();
	~Object();

//	Object(const GLuint &)

	void Init();

	Model* m_model;
	Shader* m_shader;
	Texture* m_textureArray;
	
	void Draw();
	void Update(float deltaTime);

private:
	Vector3 m_rotation;
	Vector3 m_scale;
	Vector3 m_translation;

	Matrix m_world;
	Matrix m_view;
	Matrix m_projection;

};