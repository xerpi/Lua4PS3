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
"    screen.print(15, 15, \"Lua4PS3 running at\"..screen.fps())\n"
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
						ya2d_screenClear();
						ya2d_screenBeginDrawing();
						DrawFormatString(30, 30, "Error: %s", lua_tostring(L, -1));
						DrawString(30, 45, "Press HOME to exit.");
						ya2d_screenFlip();
						lua_pop(L, 1);
					}
					ya2d_controlsRead();
					ya2d_screenFlip();
					sysUtilCheckCallback();
				}
		}

	
	//Cleanup
		lua_close(L);
		lua4ps3_end();
	return 0;
}
