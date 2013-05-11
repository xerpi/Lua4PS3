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

	//Load modules
		sysModuleLoad(SYSMODULE_FS);
		sysModuleLoad(SYSMODULE_PNGDEC);
		sysModuleLoad(SYSMODULE_JPGDEC);
		
}

void lua4ps3_end()
{
	ioPadEnd();
	tiny3d_Exit();
	//Unload modules
		sysModuleUnload(SYSMODULE_FS);
		sysModuleUnload(SYSMODULE_PNGDEC);
		sysModuleUnload(SYSMODULE_JPGDEC);
}


