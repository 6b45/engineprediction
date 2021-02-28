#ifndef __HEADER_NETVARS__
#define __HEADER_NETVARS__
#pragma once

#include "main.h"

#include "NetVars.h"
#include "CRC32.h"

namespace NetVars
{
	bool GetByte(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, byte& val, size_t extraoffset = 0);
	bool GetShort(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, short& val, size_t extraoffset = 0);
	bool GetInt(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int& val, size_t extraoffset = 0);
	bool GetFloat(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, float& val, size_t extraoffset = 0);
	bool GetVector(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, float* val, size_t extraoffset = 0);

	bool SetByte(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, byte val, size_t extraoffset = 0);
	bool SetShort(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, short val, size_t extraoffset = 0);
	bool SetInt(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int val, size_t extraoffset = 0);
	bool SetFloat(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, float val, size_t extraoffset = 0);
	bool SetVector(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, float* val, size_t extraoffset = 0);

	bool GetByteFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, byte& val, size_t extraoffset = 0);
	bool GetShortFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, short& val, size_t extraoffset = 0);
	bool GetIntFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, int& val, size_t extraoffset = 0);
	bool GetFloatFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, float& val, size_t extraoffset = 0);
	bool GetVectorFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, float* val, size_t extraoffset = 0);

	bool SetByteFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, byte val, size_t extraoffset = 0);
	bool SetShortFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, short val, size_t extraoffset = 0);
	bool SetIntFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, int val, size_t extraoffset = 0);
	bool SetFloatFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, float val, size_t extraoffset = 0);
	bool SetVectorFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, float* val, size_t extraoffset = 0);

	void ClearNetVars();
}

namespace Lua
{
	namespace NetVars
	{
		int l_GetNetVar(lua_State* state);
		int l_SetNetVar(lua_State* state);

		void RegisterMetaMethods(lua_State* state);
	}
}

#endif