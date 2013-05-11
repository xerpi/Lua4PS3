#include "image.h"


u32 lua4ps3_loadPNGfromFile(char* filename, lua4ps3_texture* texture)
{
	pngData png;
	if(pngLoadFromFile(filename, &png))
	{
		texture->data   = png.bmp_out;
		texture->width  = png.width;
		texture->height = png.height;
		texture->pitch  = png.pitch;
		texture->format = TINY3D_TEX_FORMAT_A8R8G8B8;
		texture->texture_offset = tiny3d_TextureOffset(texture->data);
		return 1;
	}
	return 0;
}

u32  lua4ps3_loadPNGfromBuffer(void *buffer, u32 buf_size, lua4ps3_texture* texture)
{
	pngData png;
	if(pngLoadFromBuffer(buffer, buf_size, &png))
	{
		texture->data   = png.bmp_out;
		texture->width  = png.width;
		texture->height = png.height;
		texture->pitch  = png.pitch;
		texture->format = TINY3D_TEX_FORMAT_A8R8G8B8;
		texture->texture_offset = tiny3d_TextureOffset(texture->data);
		return 1;
	}
	return 0;
}

void lua4ps3_blitTetxure(int x, int y, lua4ps3_texture* tex)
{
	if(tex->data == NULL) return;

	tiny3d_SetTexture(0, tex->texture_offset, tex->width, tex->height, tex->pitch, tex->format, TEXTURE_LINEAR);
	
	tiny3d_SetPolygon(TINY3D_TRIANGLE_STRIP);
		tiny3d_VertexPos(x, y, 65535);
		tiny3d_VertexTexture(0.0f, 0.0f);
		
		tiny3d_VertexPos(x, y+tex->height, 65535);
		tiny3d_VertexTexture(0.0f, 1.0f);
		
		tiny3d_VertexPos(x+tex->width, y, 65535);
		tiny3d_VertexTexture(1.0f, 0.0f);
		
		tiny3d_VertexPos(x+tex->width, y+tex->height, 65535);
		tiny3d_VertexTexture(1.0f, 1.0f);
	tiny3d_End();		
	
}
