#include <PNGLoader.h>
#include <GLESUtility.h>
#include <stb_image.h>

///<summary>
/// <para>dataPath: file path</para>
/// <para>width: get width of texture</para>
/// <para>height:  get height of texture</para>
/// <para>bpp : get color channel number [3 or 4]</para>
/// </summary> 
unsigned char* LoadPNG(char* &dataPath, int &width, int &height, int &bpp)
{
	return stbi_load(dataPath, &width, &height, &bpp, STBI_rgb_alpha);
}