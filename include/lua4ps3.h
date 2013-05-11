#ifndef _LUA4PS3_H_
#define _LUA4PS3_H_

#include <stdio.h>
#include <tiny3d.h>
#include <libfont.h>
#include <io/pad.h>
#include <sysutil/sysutil.h>
#include <sysmodule/sysmodule.h>

#define DEFAULT_FONT 0

u32 lua4ps3_clear_color;
extern unsigned char msxfont[];

u32* lua4ps3_texture_mem;
u32* lua4ps3_texture_pointer;

void lua4ps3_init();
void lua4ps3_end();


#endif
