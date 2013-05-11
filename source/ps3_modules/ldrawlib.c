#include <tiny3d.h>
#include <io/pad.h>
#include "draw.h"

#define ldrawlib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


//(x,y,w,h,color)
static int draw_rect (lua_State *L)
{
	if(lua_gettop(L) >= 4)
	{
		int x = luaL_checkint(L, 1);
		int y = luaL_checkint(L, 2);
		int w = luaL_checkint(L, 3);
		int h = luaL_checkint(L, 4);         
		u32 color = luaL_checkunsigned(L, 5);         
		lua4ps3_draw_rect(x, y, w, h, color);
	}
	return 0;
}


//(x,y,w,h,color)
static int draw_fillrect (lua_State *L)
{
	if(lua_gettop(L) >= 4)
	{
		int x = luaL_checkint(L, 1);
		int y = luaL_checkint(L, 2);
		int w = luaL_checkint(L, 3);
		int h = luaL_checkint(L, 4);         
		u32 color = luaL_checkunsigned(L, 5);        
		lua4ps3_draw_fillrect(x, y, w, h, color);
	}
	return 0;
}



static const luaL_Reg drawlib[] =
{
  {"rect",   draw_rect},
  {"fillrect",   draw_fillrect},
  {NULL, NULL}
};


/*
** Open draw library
*/
LUAMOD_API int luaopen_draw (lua_State *L)
{
	luaL_newlib(L, drawlib);
	lua_setglobal(L, "draw");
	return 1;
}


