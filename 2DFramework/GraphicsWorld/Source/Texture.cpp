#include <Texture.h>
#include <PNGLoader.h>
#include <Log.h>

Texture::Texture()
{}

Texture::~Texture()
{}

Texture::Texture(GLuint id, const char*& path) :m_filePath((char*)path), m_id(id)
{}

void Texture::GBLTexture()
{
	GenTexture();
	BindTexture();
	if (m_filePath != NULL)
	{
		LoadTexture();
	}
	else
	{
		LOG_D("Texture.cpp: m_filePath == Nulll\n");
	}
}
void Texture::Init(WrapMode wm, MipMap mmMin, MipMap mmMag)
{
	GBLTexture();
	SetWrapMode(wm);
	SetFilter(mmMin, mmMag);
}

void Texture::LoadTexture()
{
	m_data = LoadPNG(m_filePath, m_width, m_height, m_bpp);
	if (m_data == NULL)
	{
		LOG_D("Texture.cpp: Texture data is Null\n");
		return;
	}
	else
	{

		if (m_bpp == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
		}
		else if (m_bpp == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
		}
	}

	SAFE_DEL_ARR(m_data);
}

void Texture::SetWrapMode(WrapMode wm)
{
	switch (wm)
	{
	case WM_REPEAT:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	break;

	case WM_CLAMP:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	break;
	}
}

void Texture::SetFilter(MipMap min, MipMap mag)
{
	switch (mag)
	{
	case MM_LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	break;

	case MM_NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	break;

	default:
	{
		LOG_D("<!Texture.cpp> Warning: Mipmap mode for Magnify should be:  GL_LINEAR or GL_NEAREST\n");
	}
	break;
	}

	switch (min)
	{
	case MM_LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	break;

	case MM_LINEAR_LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	break;

	case MM_LINEAR_NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	break;

	case MM_NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	break;

	case MM_NEAREST_LINEAR:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	break;

	case MM_NEAREST_NEAREST:
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	break;

	default:
		break;
	}
}

void Texture::GenTexture()
{
	glGenTextures(1, &m_textureID);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}