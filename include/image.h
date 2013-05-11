#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <tiny3d.h>
#include <pngdec/pngdec.h>

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
u32  lua4ps3_loadPNGfromBuffer(void *buffer, u32 buf_size, lua4ps3_texture* texture);

void lua4ps3_blitTetxure(int x, int y, lua4ps3_texture* tex);

#endif
