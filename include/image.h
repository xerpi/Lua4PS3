#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <tiny3d.h>
#include <pngdec/pngdec.h>
#include <jpgdec/jpgdec.h>
#include <string.h>

typedef struct
{
	void *data;
	u32 pitch;
	u32 width;
	u32 height;
	text_format format;
	u32 texture_offset;
}lua4ps3_texture;


u32  lua4ps3_loadPNGfromFile(char *filename, lua4ps3_texture* texture);
lua4ps3_texture* lua4ps3_loadPNGfromBuffer(void *buffer, u32 buf_size);


u32  lua4ps3_loadJPGfromFile(char *filename, lua4ps3_texture* texture);
u32  lua4ps3_loadJPGfromBuffer(void *buffer, u32 buf_size, lua4ps3_texture* texture);

void lua4ps3_blitTetxure(int x, int y, lua4ps3_texture* tex);
void lua4ps3_blitRotateTetxure(int x, int y, float angle, lua4ps3_texture* tex);

void lua4ps3_freeTexture(lua4ps3_texture *texture);
lua4ps3_texture * lua4ps3_newTexture(int w, int h);

#endif
