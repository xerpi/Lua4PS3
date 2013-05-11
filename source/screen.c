#include "screen.h"

extern u32 lua4ps3_clear_color;

//Screen

	void lua4ps3_screen_clear()
	{
		tiny3d_Clear(lua4ps3_clear_color, TINY3D_CLEAR_ALL);

		// Enable alpha Test
		tiny3d_AlphaTest(1, 0x10, TINY3D_ALPHA_FUNC_GEQUAL);

		// Enable alpha blending.
		tiny3d_BlendFunc(1, TINY3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA | TINY3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
							TINY3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA | TINY3D_BLEND_FUNC_DST_ALPHA_ZERO,
							TINY3D_BLEND_RGB_FUNC_ADD | TINY3D_BLEND_ALPHA_FUNC_ADD);

	}
	
	void lua4ps3_screen_set_clear_color(u32 new_color)
	{
		lua4ps3_clear_color = new_color;
	}
	
	void lua4ps3_screen_begin_drawing()
	{
		tiny3d_Project2D();
	}

	void lua4ps3_screen_flip()
	{
		tiny3d_Flip();
	}
