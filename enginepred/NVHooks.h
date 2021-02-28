#ifndef __HEADER_NVHOOKS__
#define __HEADER_NVHOOKS__
#pragma once

#include "main.h"

namespace NVHooks
{
	bool AddNetVarHook(const char* pszTable, const char* pszProp, int iRef);
	void RemoveNetVarHook(const char* pszTable, const char* pszProp);
	void RemoveAllNetVarHooks();
}

namespace Lua
{
	namespace NVHooks
	{
		int l_HookProp(lua_State* state);
		int l_UnhookProp(lua_State* state);
	}
}

#endif