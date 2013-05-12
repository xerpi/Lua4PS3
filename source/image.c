#include "image.h"

extern u32* lua4ps3_texture_pointer;

u32 lua4ps3_loadPNGfromFile(char* filename, lua4ps3_texture* texture)
{
	pngData png;
	pngLoadFromFile(filename, &png);
	if(png.bmp_out)
	{
        memcpy(lua4ps3_texture_pointer, png.bmp_out, png.pitch * png.height);
        free(png.bmp_out);
        texture->data = lua4ps3_texture_pointer;
        lua4ps3_texture_pointer += (png.pitch * png.height + 3) & ~3; // aligned to 16 bytes
        texture->texture_offset = tiny3d_TextureOffset(texture->data); 	
		texture->width  = png.width;
		texture->height = png.height;
		texture->pitch  = png.pitch;
		texture->format = TINY3D_TEX_FORMAT_A8R8G8B8;
		return 1;
	}
	return 0;
}

u32  lua4ps3_loadPNGfromBuffer(void *buffer, u32 buf_size, lua4ps3_texture* texture)
{
	pngData png;
	pngLoadFromBuffer(buffer, buf_size, &png);
	if(png.bmp_out)
	{
        memcpy(lua4ps3_texture_pointer, png.bmp_out, png.pitch * png.height);
        free(png.bmp_out);
        texture->data = lua4ps3_texture_pointer;
        lua4ps3_texture_pointer += (png.pitch * png.height + 3) & ~3; // aligned to 16 bytes
        texture->texture_offset = tiny3d_TextureOffset(texture->data); 	
		texture->width  = png.width;
		texture->height = png.height;
		texture->pitch  = png.pitch;
		texture->format = TINY3D_TEX_FORMAT_A8R8G8B8;
		return 1;
	}
	return 0;
}

u32 lua4ps3_loadJPGfromFile(char* filename, lua4ps3_texture* texture)
{
	jpgData jpg;
	jpgLoadFromFile(filename, &jpg);
	if(jpg.bmp_out)
	{
        memcpy(lua4ps3_texture_pointer, jpg.bmp_out, jpg.pitch * jpg.height);
        free(jpg.bmp_out);
        texture->data = lua4ps3_texture_pointer;
        lua4ps3_texture_pointer += (jpg.pitch * jpg.height + 3) & ~3; // aligned to 16 bytes
        texture->texture_offset = tiny3d_TextureOffset(texture->data); 	
		texture->width  = jpg.width;
		texture->height = jpg.height;
		texture->pitch  = jpg.pitch;
		texture->format = TINY3D_TEX_FORMAT_A8R8G8B8;
		return 1;
	}
	return 0;
}

u32  lua4ps3_loadJPGfromBuffer(void *buffer, u32 buf_size, lua4ps3_texture* texture)
{
	jpgData jpg;
	jpgLoadFromBuffer(buffer, buf_size, &jpg);
	if(jpg.bmp_out)
	{
        memcpy(lua4ps3_texture_pointer, jpg.bmp_out, jpg.pitch * jpg.height);
        free(jpg.bmp_out);
        texture->data = lua4ps3_texture_pointer;
        lua4ps3_texture_pointer += (jpg.pitch * jpg.height + 3) & ~3; // aligned to 16 bytes
        texture->texture_offset = tiny3d_TextureOffset(texture->data); 	
		texture->data   = jpg.bmp_out;
		texture->width  = jpg.width;
		texture->height = jpg.height;
		texture->pitch  = jpg.pitch;
		texture->format = TINY3D_TEX_FORMAT_A8R8G8B8;
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

void lua4ps3_blitRotateTetxure(int x, int y, float angle, lua4ps3_texture* tex)
{
	if(tex->data == NULL) return;

	tiny3d_SetTexture(0, tex->texture_offset, tex->width, tex->height, tex->pitch, tex->format, TEXTURE_LINEAR);
	
	MATRIX matrix = MatrixTranslation(x + tex->width/2, y + tex->height/2, 65535.0f);
	matrix = MatrixMultiply(matrix, MatrixRotationZ(angle));
	matrix = MatrixMultiply(matrix,  MatrixTranslation(-tex->width/2, -tex->height/2, 65535.0f));
	
	tiny3d_SetMatrixModelView(&matrix);
	
	tiny3d_SetPolygon(TINY3D_TRIANGLE_STRIP);
		tiny3d_VertexPos(0, 0, 65535);
		tiny3d_VertexTexture(0.0f, 0.0f);
		
		tiny3d_VertexPos(0, tex->height, 65535);
		tiny3d_VertexTexture(0.0f, 1.0f);
		
		tiny3d_VertexPos(tex->width, 0, 65535);
		tiny3d_VertexTexture(1.0f, 0.0f);
		
		tiny3d_VertexPos(tex->width, tex->height, 65535);
		tiny3d_VertexTexture(1.0f, 1.0f);
	tiny3d_End();	
	
	tiny3d_SetMatrixModelView(NULL); // Identity
}
