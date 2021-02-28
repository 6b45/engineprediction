#ifndef __HEADER_MISC__
#define __HEADER_MISC__
#pragma once

#include "main.h"

namespace Lua
{
	namespace Misc
	{
		int l_FullUpdate(lua_State* state);
		int l_TickCount(lua_State* state);
		int l_MD5PseudoRandom(lua_State* state);
		int l_ChangeName(lua_State* state);
		int l_RandomFloat(lua_State* state);
		int l_RandomSeed(lua_State* state);
		int l_RandomInt(lua_State* state);
		int l_StringCmd(lua_State* state);
		int l_GetSpreadVector(lua_State* state);
	}
}

#endif