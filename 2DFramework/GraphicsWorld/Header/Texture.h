#pragma once

#include <GameUtility.h>
#include <MathVectorMatrix.h>

enum MipMap
{
	MM_NEAREST = 0, 
	MM_LINEAR, 
	MM_NEAREST_NEAREST,
	MM_NEAREST_LINEAR, 
	MM_LINEAR_NEAREST, 
	MM_LINEAR_LINEAR
};

enum WrapMode
{
	WM_REPEAT = 0,
	WM_CLAMP
};

enum MipMapOption
{
	MMO_MAG = 0,
	MMO_MIN
};

class Texture
{
public:
	Texture();
	~Texture();
	int m_width, m_height, m_compression;
	char * m_data;
	GLuint m_id;
private:
	GLuint		m_textureID;
};
