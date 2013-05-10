#include <tiny3d.h>
#include <libfont.h>
#include <io/pad.h>
#include "lua4ps3.h"


void lua4ps3_init()
{
	lua4ps3_clear_color = 0x0;
	ioPadInit(7);
	
	//Tiny 3D
		tiny3d_Init(1024 * 1024);
		
		lua4ps3_texture_mem = tiny3d_AllocTexture(64*1024*1024); 
		lua4ps3_texture_pointer = lua4ps3_texture_mem;
		
		//Load default font
			ResetFont();
			lua4ps3_texture_pointer =
			   (u32 *) AddFontFromBitmapArray((u8 *) msxfont, (u8 *) lua4ps3_texture_pointer,  0, 254,  8,  8, 1, BIT7_FIRST_PIXEL);
			SetCurrentFont(DEFAULT_FONT);
			SetFontColor(0xffffffff, 0x0);
			SetFontSize(12, 24);
		
}

void lua4ps3_end()
{
	ioPadEnd();
	tiny3d_Exit();
}

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
	
//Draw module
	void lua4ps3_draw_rect(int x, int y, int w, int h, u32 color)
	{
		tiny3d_SetPolygon(TINY3D_LINE_STRIP);
			tiny3d_VertexColor(color);
			tiny3d_VertexPos(x, y, 65535);
			tiny3d_VertexPos(x, y+h, 65535);
			tiny3d_VertexPos(x+w, y+h, 65535);
			tiny3d_VertexPos(x+w, y, 65535);
		tiny3d_End();		
	}
	
	void lua4ps3_draw_fillrect(int x, int y, int w, int h, u32 color)
	{
		tiny3d_SetPolygon(TINY3D_TRIANGLE_STRIP);
			tiny3d_VertexColor(color);
			tiny3d_VertexPos(x, y, 65535);
			tiny3d_VertexPos(x, y+h, 65535);
			tiny3d_VertexPos(x+w, y, 65535);
			tiny3d_VertexPos(x+w, y+h, 65535);
		tiny3d_End();		
	}
		
//Controls module
	void lua4ps3_controls_read()
	{
		int i;
		ioPadGetInfo2(&lua4ps3_padinfo);
		for(i = 0; i < MAX_PORT_NUM; i++)
		{		 
			if(lua4ps3_padinfo.port_status[i])
			{
				ioPadGetData(i, &lua4ps3_paddata[i]);	 
			}
		}	
	}
	
