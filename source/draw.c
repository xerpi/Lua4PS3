#include "draw.h"

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
