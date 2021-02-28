#include "NetVars.h"

struct NetVar
{
	NetVar()
	{
		m_CRC = 0;
		m_Offset = 0;
		m_pNext = nullptr;
	}

	unsigned int m_CRC;
	size_t m_Offset;

	NetVar* m_pNext;
};

static NetVar s_First;

static size_t FindNetVar(const char* pszDataTable, const char* pszPropName)
{
	unsigned int crc;
	CRC32::Init(&crc);
	CRC32::ProcessBuffer(&crc, pszDataTable, strlen(pszDataTable));
	CRC32::ProcessBuffer(&crc, pszPropName, strlen(pszPropName));
	CRC32::Final(&crc);

	auto pNode = s_First.m_pNext;
	while (pNode)
	{
		if (pNode->m_CRC == crc)
		{
			return pNode->m_Offset;
		}

		pNode = pNode->m_pNext;
	}

	size_t offset = pMgr->GetOffset(pszDataTable, pszPropName);
	if (offset == 0x0) 
	{
		return 0;
	}

	auto pNetVar = new NetVar;
	pNetVar->m_CRC = crc;
	pNetVar->m_Offset = offset;

	pNode = &s_First;
	while (pNode->m_pNext)
	{
		pNode = pNode->m_pNext;
	}

	pNode->m_pNext = pNetVar;

	return offset;
}

bool NetVars::GetByte(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, byte& val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}
	
	val = *(byte*)((DWORD_PTR)pEntity + offset + extraoffset);
	return true;
}

bool NetVars::GetShort(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, short& val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val = *(short*)((DWORD_PTR)pEntity + offset + extraoffset);
	return true;
}

bool NetVars::GetInt(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int& val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val = *(int*)((DWORD_PTR)pEntity + offset + extraoffset);
	return true;
}

bool NetVars::GetFloat(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, float& val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val = *(float*)((DWORD_PTR)pEntity + offset + extraoffset);
	return true;
}

bool NetVars::GetVector(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, float* val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val[0] = *(float*)((DWORD_PTR)pEntity + offset + extraoffset);
	val[1] = *(float*)((DWORD_PTR)pEntity + offset + 0x4 + extraoffset);
	val[2] = *(float*)((DWORD_PTR)pEntity + offset + 0x8 + extraoffset);

	return true;
}

bool NetVars::SetByte(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, byte val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(byte*)((DWORD_PTR)pEntity + offset + extraoffset) = val;
	return true;
}

bool NetVars::SetShort(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, short val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(short*)((DWORD_PTR)pEntity + offset + extraoffset) = val;
	return true;
}

bool NetVars::SetInt(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(int*)((DWORD_PTR)pEntity + offset + extraoffset) = val;
	return true;
}

bool NetVars::SetFloat(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, float val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(float*)((DWORD_PTR)pEntity + offset + extraoffset) = val;
	return true;
}

bool NetVars::SetVector(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, float* val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(float*)((DWORD_PTR)pEntity + offset + extraoffset) = val[0];
	*(float*)((DWORD_PTR)pEntity + offset + extraoffset + 0x4) = val[1];
	*(float*)((DWORD_PTR)pEntity + offset + extraoffset + 0x8) = val[2];

	return true;
}

bool NetVars::GetByteFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, byte& val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val = *(byte*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(byte) * idx);

	return true;
}

bool NetVars::GetShortFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, short& val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val = *(short*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(short) * idx);

	return true;
}

bool NetVars::GetIntFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, int& val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val = *(int*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(int) * idx);

	return true;
}

bool NetVars::GetFloatFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, float& val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val = *(float*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(float) * idx);

	return true;
}

bool NetVars::GetVectorFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, float* val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	val[0] = *(float*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(float[3]) * idx);
	val[1] = *(float*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(float[3]) * idx + 0x4);
	val[2] = *(float*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(float[3]) * idx + 0x8);

	return true;
}

bool NetVars::SetByteFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, byte val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(byte*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(byte) * idx) = val;

	return true;
}

bool NetVars::SetShortFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, short val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(short*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(short) * idx) = val;

	return true;
}

bool NetVars::SetIntFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, int val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(int*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(int) * idx) = val;

	return true;
}

bool NetVars::SetFloatFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, float val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(float*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(float) * idx) = val;

	return true;
}

bool NetVars::SetVectorFromArray(CBasePlayer* pEntity, const char* pszDataTable, const char* pszPropName, int idx, float* val, size_t extraoffset)
{
	size_t offset = 0;
	if (pszDataTable && pszPropName)
	{
		offset = FindNetVar(pszDataTable, pszPropName);
		if (offset == 0x0)
		{
			return false;
		}
	}

	*(float*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(float[3]) * idx) = val[0];
	*(float*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(float[3]) * idx + 0x4) = val[1];
	*(float*)((DWORD_PTR)pEntity + offset + extraoffset + sizeof(float[3]) * idx + 0x8) = val[2];

	return true;
}

void NetVars::ClearNetVars()
{
	auto pNode = s_First.m_pNext;
	while (pNode)
	{
		auto pNext = pNode->m_pNext;

		delete pNode;

		pNode = pNext;
	}
}

#define NETVAR_BYTE				1
#define NETVAR_SHORT			2
#define NETVAR_INT				3
#define NETVAR_FLOAT			4
#define NETVAR_VECTOR			5
#define NETVAR_BYTE_ARRAY		6
#define NETVAR_SHORT_ARRAY		7
#define NETVAR_INT_ARRAY		8
#define NETVAR_FLOAT_ARRAY		9
#define NETVAR_VECTOR_ARRAY		10

int Lua::NetVars::l_GetNetVar(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::ENTITY))
	{
		LUA->ThrowError("Invalid argument #1 (Entity needed)");
		return 0;
	}

	LUA->Push(1);
	int ref = LUA->ReferenceCreate();

	bool bValid;

	LUA->ReferencePush(ref);

		LUA->GetField(-1, "IsValid");

			LUA->ReferencePush(ref);

		LUA->Call(1, 1);

		bValid = LUA->GetBool(-1);
		LUA->Pop();

	LUA->Pop();

	if (!bValid)
	{
		LUA->ReferenceFree(ref);

		LUA->ThrowError("Invalid argument #1 (Entity was NULL)");
		return 0;
	}

	int eidx;

	LUA->ReferencePush(ref);

		LUA->GetField(-1, "EntIndex");

			LUA->ReferencePush(ref);

		LUA->Call(1, 1);

		eidx = (int)LUA->GetNumber(-1);
		LUA->Pop();

	LUA->Pop();

	LUA->ReferenceFree(ref);

	auto pEntity = g_pEntityList->GetClientEntity(eidx);
	if (pEntity == nullptr)
	{
		LUA->ThrowError("Invalid argument #1 (Entity was NULL)");
		return 0;
	}

	/*if (!LUA->IsType(2, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #2 (String needed)");
		return 0;
	}

	if (!LUA->IsType(3, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #3 (String needed)");
		return 0;
	}*/

	if (!LUA->IsType(4, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #4 (Number needed)");
		return 0;
	}

	if (!LUA->IsType(5, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #5 (Number needed)");
		return 0;
	}

	int extraoffset = (int)LUA->GetNumber(4);
	int type = (int)LUA->GetNumber(5);
	int idx;

	if (type >= NETVAR_BYTE_ARRAY)
	{
		if (!LUA->IsType(6, GarrysMod::Lua::Type::NUMBER))
		{
			LUA->ThrowError("Invalid argument #6 (Number needed)");
			return 0;
		}

		idx = (int)LUA->GetNumber(6);
	}

	if (type == NETVAR_BYTE)
	{
		byte val;
		if (!::NetVars::GetByte(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		LUA->PushNumber((double)val);
		return 1;
	}

	if (type == NETVAR_BYTE_ARRAY)
	{
		byte val;
		if (!::NetVars::GetByteFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		LUA->PushNumber((double)val);
		return 1;
	}

	if (type == NETVAR_SHORT)
	{
		short val;
		if (!::NetVars::GetShort(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		LUA->PushNumber((double)val);
		return 1;
	}

	if (type == NETVAR_SHORT_ARRAY)
	{
		short val;
		if (!::NetVars::GetShortFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		LUA->PushNumber((double)val);
		return 1;
	}

	if (type == NETVAR_INT)
	{
		int val;
		if (!::NetVars::GetInt(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		LUA->PushNumber((double)val);
		return 1;
	}

	if (type == NETVAR_INT_ARRAY)
	{
		int val;
		if (!::NetVars::GetIntFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		LUA->PushNumber((double)val);
		return 1;
	}

	if (type == NETVAR_FLOAT)
	{
		float val;
		if (!::NetVars::GetFloat(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		LUA->PushNumber((double)val);
		return 1;
	}

	if (type == NETVAR_FLOAT_ARRAY)
	{
		float val;
		if (!::NetVars::GetFloatFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		LUA->PushNumber((double)val);
		return 1;
	}

	if (type == NETVAR_VECTOR)
	{
		float val[3];
		if (!::NetVars::GetVector(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		int ref;

		LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->GetField(-1, "Vector");

		LUA->PushNumber((double)val[0]);
		LUA->PushNumber((double)val[1]);
		LUA->PushNumber((double)val[2]);

		LUA->Call(3, 1);

		ref = LUA->ReferenceCreate();

		LUA->Pop();

		LUA->ReferencePush(ref);
		LUA->ReferenceFree(ref);

		return 1;
	}

	if (type == NETVAR_VECTOR_ARRAY)
	{
		float val[3];
		if (!::NetVars::GetVectorFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset))
		{
			LUA->ThrowError("Failed getting NetVar");
			return 0;
		}

		int ref;

		LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->GetField(-1, "Vector");

		LUA->PushNumber((double)val[0]);
		LUA->PushNumber((double)val[1]);
		LUA->PushNumber((double)val[2]);

		LUA->Call(3, 1);

		ref = LUA->ReferenceCreate();

		LUA->Pop();

		LUA->ReferencePush(ref);
		LUA->ReferenceFree(ref);

		return 1;
	}

	return 0;
}

int Lua::NetVars::l_SetNetVar(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::ENTITY))
	{
		LUA->ThrowError("Invalid argument #1 (Entity needed)");
		return 0;
	}

	LUA->Push(1);
	int ref = LUA->ReferenceCreate();

	bool bValid;

	LUA->ReferencePush(ref);

		LUA->GetField(-1, "IsValid");

			LUA->ReferencePush(ref);

		LUA->Call(1, 1);

		bValid = LUA->GetBool(-1);
		LUA->Pop();

	LUA->Pop();

	if (!bValid)
	{
		LUA->ReferenceFree(ref);

		LUA->ThrowError("Invalid argument #1 (Entity was NULL)");
		return 0;
	}

	int eidx;

	LUA->ReferencePush(ref);

		LUA->GetField(-1, "EntIndex");

			LUA->ReferencePush(ref);

		LUA->Call(1, 1);

		eidx = (int)LUA->GetNumber(-1);
		LUA->Pop();

	LUA->Pop();

	LUA->ReferenceFree(ref);

	auto pEntity = g_pEntityList->GetClientEntity(eidx);
	if (pEntity == nullptr)
	{
		LUA->ThrowError("Invalid argument #1 (Entity was NULL)");
		return 0;
	}

	/*if (!LUA->IsType(2, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #2 (String needed)");
		return 0;
	}

	if (!LUA->IsType(3, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #3 (String needed)");
		return 0;
	}*/

	if (!LUA->IsType(4, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #4 (Number needed)");
		return 0;
	}

	if (!LUA->IsType(6, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #5 (Number needed)");
		return 0;
	}

	int extraoffset = (int)LUA->GetNumber(4);
	int type = (int)LUA->GetNumber(6);
	int idx;

	if (type >= NETVAR_BYTE_ARRAY)
	{
		if (!LUA->IsType(7, GarrysMod::Lua::Type::NUMBER))
		{
			LUA->ThrowError("Invalid argument #6 (Number needed)");
			return 0;
		}

		idx = (int)LUA->GetNumber(6);
	}

	if (type == NETVAR_BYTE || type == NETVAR_BYTE_ARRAY || type == NETVAR_SHORT || type == NETVAR_SHORT_ARRAY || type == NETVAR_INT || type == NETVAR_INT_ARRAY || type == NETVAR_FLOAT || type == NETVAR_FLOAT_ARRAY)
	{
		if (!LUA->IsType(5, GarrysMod::Lua::Type::NUMBER))
		{
			LUA->ThrowError("Invalid argument #5 (Number needed)");
			return 0;
		}
	}

	if (type == NETVAR_VECTOR || type == NETVAR_VECTOR_ARRAY)
	{
		if (!LUA->IsType(5, GarrysMod::Lua::Type::NUMBER))
		{
			LUA->ThrowError("Invalid argument #5 (Vector needed)");
			return 0;
		}
	}

	if (type == NETVAR_BYTE)
	{
		byte val = (byte)LUA->GetNumber(5);

		::NetVars::SetByte(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset);
	}

	if (type == NETVAR_SHORT)
	{
		short val = (short)LUA->GetNumber(5);

		::NetVars::SetShort(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset);
	}

	if (type == NETVAR_INT)
	{
		int val = (int)LUA->GetNumber(5);

		::NetVars::SetInt(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset);
	}

	if (type == NETVAR_FLOAT)
	{
		float val = (float)LUA->GetNumber(5);

		::NetVars::SetFloat(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset);
	}

	if (type == NETVAR_VECTOR)
	{
		float val[3];

		LUA->Push(5);

		LUA->GetField(-1, "x");
		val[0] = LUA->GetNumber(-1);

		LUA->GetField(-1, "y");
		val[1] = LUA->GetNumber(-1);

		LUA->GetField(-1, "z");
		val[2] = LUA->GetNumber(-1);

		LUA->Pop();

		::NetVars::SetVector(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, val, extraoffset);
	}

	if (type == NETVAR_BYTE_ARRAY)
	{
		byte val = (byte)LUA->GetNumber(5);

		::NetVars::SetByteFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset);
	}

	if (type == NETVAR_SHORT_ARRAY)
	{
		short val = (short)LUA->GetNumber(5);

		::NetVars::SetShortFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset);
	}

	if (type == NETVAR_INT_ARRAY)
	{
		int val = (int)LUA->GetNumber(5);

		::NetVars::SetIntFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset);
	}

	if (type == NETVAR_FLOAT_ARRAY)
	{
		float val = (float)LUA->GetNumber(5);

		::NetVars::SetFloatFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset);
	}

	if (type == NETVAR_VECTOR_ARRAY)
	{
		float val[3];

		LUA->Push(5);

		LUA->GetField(-1, "x");
		val[0] = LUA->GetNumber(-1);

		LUA->GetField(-1, "y");
		val[1] = LUA->GetNumber(-1);

		LUA->GetField(-1, "z");
		val[2] = LUA->GetNumber(-1);

		LUA->Pop();

		::NetVars::SetVectorFromArray(pEntity, LUA->IsType(2, GarrysMod::Lua::Type::STRING) ? LUA->GetString(2) : nullptr, LUA->IsType(3, GarrysMod::Lua::Type::STRING) ? LUA->GetString(3) : nullptr, idx, val, extraoffset);
	}

	return 0;
}

void Lua::NetVars::RegisterMetaMethods(lua_State* state)
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->GetField(-1, "FindMetaTable");

			LUA->PushString("Entity");

		LUA->Call(1, 1);

		LUA->PushCFunction(l_GetNetVar);
		LUA->SetField(-2, "GetNetVar");

		LUA->PushCFunction(l_SetNetVar);
		LUA->SetField(-2, "SetNetVar");

		LUA->Pop();

	LUA->Pop();
}