#ifndef __HEADER_CUSERCMD__
#define __HEADER_CUSERCMD__
#pragma once

#include "main.h"

namespace Lua
{
	namespace CUserCmd
	{
		int l_SetTickCount(lua_State* state);
		int l_GetRandomSeed(lua_State* state);

		void RegisterMetaMethods(lua_State* state);
	}
}

#endif