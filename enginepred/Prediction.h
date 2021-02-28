#ifndef __HEADER_PREDICTION__
#define __HEADER_PREDICTION__
#pragma once

#include "main.h"

namespace Lua
{
	namespace Prediction
	{
		int l_Start(lua_State* state);
		int l_Finish(lua_State* state);
	}
}

#endif