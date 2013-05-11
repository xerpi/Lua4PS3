#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <tiny3d.h>

//Screen module
	void lua4ps3_screen_clear();
	void lua4ps3_screen_set_clear_color(u32 new_color);
	void lua4ps3_screen_flip();
	void lua4ps3_screen_begin_drawing();


#endif
