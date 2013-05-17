#include <ya2d/ya2d.h>

#define limagelib_c
#define LUA_LIB

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"


//([n,] BUTTON)
static int image_loadpngmemory (lua_State *L)
{
	/*int pad = 0;
	int button = luaL_checkint(L, 1);
	if(lua_gettop(L) > 1)
	{
		pad = button;
		button = luaL_checkint(L, 2);
	}
	lua_pushboolean(L, lua4ps3_paddata[pad].BTN_CROSS);*/
	return 0;
}



static const luaL_Reg imagelib[] =
{
	{"loadpngmemory",   image_loadpngmemory},
	{NULL, NULL}
};


/*
** Open image library
*/
LUAMOD_API int luaopen_image (lua_State *L)
{
	luaL_newlib(L, imagelib);
	lua_setglobal(L, "image");
	return 1;
}
