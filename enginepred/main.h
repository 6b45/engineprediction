#ifndef __HEADER_MAIN__
#define __HEADER_MAIN__
#pragma once

#define GMMODULE

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <stdio.h>

#include "SigScan.h"
#include "CVMTHookManager.h"
#include "SDK.h"

#include "GarrysMod/Lua/Interface.h"

#include "XorStr.h"

extern lua_State* g_pLua;
#define GLUA g_pLua->luabase

#endif