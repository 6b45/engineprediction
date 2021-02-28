#ifndef __HEADER_NETCHAN__
#define __HEADER_NETCHAN__
#pragma once

#include "main.h"

namespace Lua
{
	namespace NetChan
	{
		int l_GetLatency(lua_State* state);
		int l_GetOutSequenceNumber(lua_State* state);
		int l_SetOutSequenceNumber(lua_State* state);
		int l_GetInSequenceNumber(lua_State* state);
		int l_SetInSequenceNumber(lua_State* state);
		int l_GetChokedPackets(lua_State* state);
		int l_SetChokedPackets(lua_State* state);
	}
}

#endif