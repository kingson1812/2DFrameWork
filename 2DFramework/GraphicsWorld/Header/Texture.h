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

class Texture
{
public:
	Texture();
	~Texture();
	Texture(GLuint id, const char* &path);

	void Init(WrapMode wm = WM_REPEAT, MipMap mmMin = MM_LINEAR_LINEAR, MipMap mmMag = MM_LINEAR);
	void GenTexture();
	void BindTexture();
	void UnbindTexture();

	void LoadTexture();
	void SetWrapMode(WrapMode wm);
	void SetFilter(MipMap min, MipMap mag);
	void GBLTexture();
private:
	int m_width, m_height, m_bpp;
	unsigned char * m_data;
	char* m_filePath;
	GLuint m_id;
	GLuint		m_textureID;
};
