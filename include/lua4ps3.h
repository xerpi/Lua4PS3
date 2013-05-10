#ifndef _LUA4PS3_H_
#define _LUA4PS3_H_

#define DEFAULT_FONT 0

padInfo2 lua4ps3_padinfo;
padData lua4ps3_paddata[7];
u32 lua4ps3_clear_color;
extern unsigned char msxfont[];

u32* lua4ps3_texture_mem;
u32* lua4ps3_texture_pointer;

void lua4ps3_init();
void lua4ps3_end();

//Screen module
	void lua4ps3_screen_clear();
	void lua4ps3_screen_set_clear_color(u32 new_color);
	void lua4ps3_screen_flip();
	void lua4ps3_screen_begin_drawing();

//Draw module
	void lua4ps3_draw_rect(int x, int y, int w, int h, u32 color);
	void lua4ps3_draw_fillrect(int x, int y, int w, int h, u32 color);
	
//Controls module
	void lua4ps3_controls_read();

#endif
