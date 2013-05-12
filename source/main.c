#include "main.h"
#include "pngsample_png.h"

#define SCREEN_W 848
#define SCREEN_H 512

extern int luaopen_screen(lua_State *l);
extern int luaopen_draw(lua_State *l);
extern int luaopen_controls(lua_State *l);
extern int luaopen_image(lua_State *l);


char *script_lua = 
{
"while true do\n"
"    screen.clear()\n"
"    screen.begindrawing()\n"
"    draw.rect(50, 50, 175, 40, 0xFF0000FF)\n"
"    draw.fillrect(200, 60, 75, 80, 0x00FF00FF)\n"
"    screen.print(15, 15, \"Lua4PS3 RUNNING!!\")\n"
"    screen.flip()\n"
"end\n"	
};

/*
while true do
	screen.clear()
	screen.begindrawing()
	draw.rect(50, 50, 175, 40, 0xFF0000FF)
	draw.fillrect(200, 60, 75, 80, 0x00FF00FF)
	screen.print(15, 15, "Lua4PS3 RUNNING!!")
	screen.flip()
end	
*/

int main(int argc, char *argv[])
{
	printf("Lua4PS3 version: %.2f\n", _LUA4PS3_VERSION_ );
	//Init PS3 stuff
	//Init Lua
		lua4ps3_init();
		lua_State *L = luaL_newstate();
		luaL_openlibs(L);
		luaopen_draw(L);
		luaopen_screen(L);
		luaopen_controls(L);
		luaopen_image(L);
		
	//Loop Lua
		/*
		int s = luaL_loadstring(L, script_lua);
		while(1)
		{
				if (!s)
				{
					s = lua_pcall(L, 0, 0, 0);
				}
				if (s)
				{
					if (lua_tostring(L, -1))
					{
						lua4ps3_screen_clear();
						lua4ps3_screen_begin_drawing();
						DrawFormatString(30, 30, "Error: %s", lua_tostring(L, -1));
						DrawString(30, 45, "Press HOME to exit.");
						lua4ps3_screen_flip();
						lua_pop(L, 1);
					}
					lua4ps3_controls_read();
					lua4ps3_screen_flip();
					sysUtilCheckCallback();
				}
		}
	*/
	
	lua4ps3_texture *texture = lua4ps3_loadPNGfromBuffer((void *)pngsample_png, pngsample_png_size);
	float angle = 0.0f;
	int x = 50, y = 100;
	int size = 50;
	while(1)
	{
		lua4ps3_screen_clear();
		lua4ps3_screen_begin_drawing();
		lua4ps3_controls_read();
		
		DrawFormatString(15, 15, "Lua4PS3 version: %.2f ----- by xerpi\n", _LUA4PS3_VERSION_ );
		
		if(lua4ps3_paddata[0].BTN_RIGHT) x+=10;
		if(lua4ps3_paddata[0].BTN_LEFT)  x-=10;
		if(lua4ps3_paddata[0].BTN_DOWN)  y+=10;
		if(lua4ps3_paddata[0].BTN_UP)    y-=10;
		if(lua4ps3_paddata[0].BTN_CROSS)  lua4ps3_draw_fillrect(200, 350, 100, 100, rand());
		
		if(x > (SCREEN_W-size)) x = SCREEN_W-size;
		if(x<0) x = 0;
		if(y > (SCREEN_H-size)) y = SCREEN_H-size;
		if(y<0) y = 0;
						
		
		lua4ps3_blitTetxure(50, 90, texture);
		lua4ps3_blitRotateTetxure(500, 310, angle, texture);
		
		lua4ps3_draw_fillrect(x, y, size, size, 0xFF0000FF);
			
		lua4ps3_screen_flip();
		if(lua4ps3_paddata[0].BTN_START) break;
		angle += 0.05f;
	}
	
	//Cleanup
		lua_close(L);
		lua4ps3_end();
		lua4ps3_freeTexture(texture);
	return 0;
}
