#include <Texture.h>

Texture::Texture()
{}

Texture::~Texture()
{}

void Texture::Init(WrapMode wm = WM_REPEAT, MipMap mm = MM_LINEAR_LINEAR, MipMapOption mmo = MMO_MAG)
{
	LoadTexture("");
}