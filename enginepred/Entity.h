#ifndef __HEADER_ENTITY__
#define __HEADER_ENTITY__
#pragma once

#include "main.h"

namespace Lua
{
	namespace Entity
	{
		int l_GetSimulationTime(lua_State* state);

		void RegisterMetaMethods(lua_State* state);
	}
}

#endif