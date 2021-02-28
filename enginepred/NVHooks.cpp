#include "NVHooks.h"

struct NVHook
{
	NVHook()
	{
		m_pszTable = 0;
		m_pszProp = 0;
		m_iHookRef = 0;
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}

	NVHook(const char* pszTable, const char* pszProp, int iRef)
	{
		if(pszTable) m_pszTable = _strdup(pszTable);
		if(pszProp) m_pszProp = _strdup(pszProp);
		m_iHookRef = iRef;
	}

	~NVHook()
	{
		if (m_pszTable && m_pszProp)
		{
			void* temp;
			pMgr->HookProp(m_pszTable, m_pszProp, m_pOld, &temp);
		}

		if(m_pszTable) free(m_pszTable);
		if(m_pszProp) free(m_pszProp);
		if (m_iHookRef) GLUA->ReferenceFree(m_iHookRef);
	}

	char* m_pszTable = nullptr;
	char* m_pszProp = nullptr;
	void* m_pOld = nullptr;
	int m_iHookRef = 0;

	NVHook* m_pNext = nullptr;
	NVHook* m_pPrev = nullptr;
};

static NVHook s_First;

struct Data
{
	CRecvProxyData* m_pData;
	void* m_pStruct;
	void* m_pOut;
};

static Data* UnpackMe(lua_State* state)
{
	LUA->GetField(1, "__usrdata_ref");
	GarrysMod::Lua::UserData* pUserData = (GarrysMod::Lua::UserData*)(LUA->GetUserdata(-1));
	LUA->Pop();

	if (pUserData == nullptr || pUserData->type != 241) return nullptr;

	auto pData = (Data*)(pUserData->data);
	if (pData == nullptr) return nullptr;

	return pData;
}

static int GetFloat(lua_State* state)
{
	Data* pData;

	if ((pData = UnpackMe(state)) != nullptr)
	{
		LUA->PushNumber((double)pData->m_pData->m_Value.m_Float);
		return 1;
	}
	else
	{
		LUA->ThrowError("Invalid argument #1 (ProxyData needed)");
	}

	return 0;
}

static int GetInt(lua_State* state)
{
	Data* pData;

	if ((pData = UnpackMe(state)) != nullptr)
	{
		LUA->PushNumber((double)pData->m_pData->m_Value.m_Int);
		return 1;
	}
	else
	{
		LUA->ThrowError("Invalid argument #1 (ProxyData needed)");
	}

	return 0;
}

static int GetVector(lua_State* state)
{
	Data* pData;

	if ((pData = UnpackMe(state)) != nullptr)
	{
		int ref;

		LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->GetField(-1, "Vector");
		ref = LUA->ReferenceCreate();

		LUA->Pop();

		LUA->ReferencePush(ref);

		LUA->PushNumber((double)pData->m_pData->m_Value.m_Vector[0]);
		LUA->PushNumber((double)pData->m_pData->m_Value.m_Vector[1]);
		LUA->PushNumber((double)pData->m_pData->m_Value.m_Vector[2]);

		GLUA->Call(3, 1);

		GLUA->ReferenceFree(ref);
		return 1;
	}
	else
	{
		LUA->ThrowError("Invalid argument #1 (ProxyData needed)");
	}

	return 0;
}

static int SetFloat(lua_State* state)
{
	Data* pData;

	if ((pData = UnpackMe(state)) != nullptr)
	{
		if (!LUA->IsType(2, GarrysMod::Lua::Type::NUMBER))
		{
			LUA->ThrowError("Invalid argument #2 (Number needed)");
			return 0;
		}

		*(float*)pData->m_pOut = (float)LUA->GetNumber(2);
	}
	else
	{
		LUA->ThrowError("Invalid argument #1 (ProxyData needed)");
	}

	return 0;
}

static int SetInt(lua_State* state)
{
	Data* pData;

	if ((pData = UnpackMe(state)) != nullptr)
	{
		if (!LUA->IsType(2, GarrysMod::Lua::Type::NUMBER))
		{
			LUA->ThrowError("Invalid argument #2 (Number needed)");
			return 0;
		}

		*(int*)pData->m_pOut = (int)LUA->GetNumber(2);
	}
	else
	{
		LUA->ThrowError("Invalid argument #1 (ProxyData needed)");
	}

	return 0;
}

static int SetVector(lua_State* state)
{
	Data* pData;

	if ((pData = UnpackMe(state)) != nullptr)
	{
		if (!LUA->IsType(2, GarrysMod::Lua::Type::VECTOR))
		{
			LUA->ThrowError("Invalid argument #2 (Number needed)");
			return 0;
		}

		LUA->GetField(2, "x");
			float x = (float)LUA->GetNumber(-1);
		LUA->Pop();

		LUA->GetField(2, "y");
			float y = (float)LUA->GetNumber(-1);
		LUA->Pop();

		LUA->GetField(2, "z");
			float z = (float)LUA->GetNumber(-1);
		LUA->Pop();

		*(float*)((DWORD_PTR)pData->m_pOut + 0) = x;
		*(float*)((DWORD_PTR)pData->m_pOut + 4) = y;
		*(float*)((DWORD_PTR)pData->m_pOut + 8) = z;
	}
	else
	{
		LUA->ThrowError("Invalid argument #1 (ProxyData needed)");
	}

	return 0;
}

static int l_gc(lua_State* state)
{
	using GarrysMod::Lua::UserData;

	UserData* pUserData = (UserData*)(LUA->GetUserdata(1));
	if (pUserData == nullptr || pUserData->type != 241) return 0;

	auto pData = (Data*)(pUserData->data);
	if (pData == nullptr) return 0;

	delete pData;

	return 0;
}

static int GetEntity(lua_State* state)
{
	Data* pData;

	if ((pData = UnpackMe(state)) != nullptr)
	{
		int iRef;

		LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
			
			LUA->GetField(-1, "Entity");

				LUA->PushNumber((double)((CBasePlayer*)pData->m_pStruct)->EntIndex());

			LUA->Call(1, 1);
			iRef = LUA->ReferenceCreate();

		LUA->Pop();

		LUA->ReferencePush(iRef);
		LUA->ReferenceFree(iRef);

		return 1;
	}
	else
	{
		LUA->ThrowError("Invalid argument #1 (ProxyData needed)");
	}

	return 0;
}

static void CreateUserData(CRecvProxyData* _pData, void* pStruct, void* pOut)
{
	static int iUserMeta = 0;
	if (iUserMeta == 0)
	{
		GLUA->CreateTable();

		GLUA->PushCFunction(l_gc);
		GLUA->SetField(-2, "__gc");

		iUserMeta = GLUA->ReferenceCreate();
	}

	Data* pData = new Data;
	pData->m_pData = _pData;
	pData->m_pStruct = pStruct;
	pData->m_pOut = pOut;

	auto pUsrData = (GarrysMod::Lua::UserData*)GLUA->NewUserdata(sizeof(GarrysMod::Lua::UserData));
	pUsrData->data = pData;
	pUsrData->type = 241;

	int iRef = GLUA->ReferenceCreate();

	GLUA->ReferencePush(iRef);
		
		GLUA->ReferencePush(iUserMeta);
		GLUA->SetMetaTable(-2);

	GLUA->Pop();

	GLUA->CreateTable();

	GLUA->PushCFunction(GetFloat);
	GLUA->SetField(-2, "GetFloat");

	GLUA->PushCFunction(GetInt);
	GLUA->SetField(-2, "GetInt");

	GLUA->PushCFunction(GetVector);
	GLUA->SetField(-2, "GetVector");

	GLUA->PushCFunction(SetFloat);
	GLUA->SetField(-2, "SetFloat");

	GLUA->PushCFunction(SetInt);
	GLUA->SetField(-2, "SetInt");

	GLUA->PushCFunction(SetVector);
	GLUA->SetField(-2, "SetVector");

	GLUA->PushCFunction(GetEntity);
	GLUA->SetField(-2, "GetEntity");

	GLUA->ReferencePush(iRef);
	GLUA->SetField(-2, "__usrdata_ref");

	GLUA->ReferenceFree(iRef);
}

static bool InvokeHook(const char* pszTable, const char* pszProp, CRecvProxyData* pData, void* pStruct, void* pOut)
{
	auto pNode = &s_First;
	while (pNode)
	{
		if (pNode->m_pszTable && pNode->m_pszProp)
		{
			if (!strcmp(pszTable, pNode->m_pszTable) && !strcmp(pszProp, pNode->m_pszProp))
			{
				GLUA->ReferencePush(pNode->m_iHookRef);

					CreateUserData(pData, pStruct, pOut);

				GLUA->Call(1, 0);

				return true;
			}
		}

		pNode = pNode->m_pNext;
	}

	return false;
}

static void NVProxyHook(CRecvProxyData* pData, void* pStruct, void* pOut)
{
	//const char* pszTable = pData->m_pRecvProp->m_pDataTable->m_pNetTableName;
	const char* pszTable = ((CBasePlayer*)pStruct)->GetClientClass()->m_pRecvTable->m_pNetTableName;
	const char* pszProp = pData->m_pRecvProp->m_pVarName;

	InvokeHook(pszTable, pszProp, pData, pStruct, pOut);
}

static bool HookExists(const char* pszTable, const char* pszProp)
{
	auto pNode = &s_First;
	while (pNode)
	{
		if (pNode->m_pszTable && pNode->m_pszProp)
		{
			if (!strcmp(pszTable, pNode->m_pszTable) && !strcmp(pszProp, pNode->m_pszProp))
			{
				return true;
			}
		}

		pNode = pNode->m_pNext;
	}

	return false;
}

bool NVHooks::AddNetVarHook(const char* pszTable, const char* pszProp, int iRef)
{
	if (HookExists(pszTable, pszProp))
	{
		RemoveNetVarHook(pszTable, pszProp);
	}

	auto pNode = &s_First;
	while (pNode->m_pNext)
	{
		pNode = pNode->m_pNext;
	}

	void* pOld = nullptr;
	if (!pMgr->HookProp(pszTable, pszProp, NVProxyHook, &pOld))
	{
		return false;
	}

	auto pNewNode = new NVHook(pszTable, pszProp, iRef);
	pNode->m_pNext = pNewNode;
	pNewNode->m_pPrev = pNode;

	pNewNode->m_pOld = pOld;

	return true;
}

void NVHooks::RemoveNetVarHook(const char* pszTable, const char* pszProp)
{
	if (!HookExists(pszTable, pszProp))
	{
		return;
	}

	auto pNode = &s_First;
	while (pNode)
	{
		if (pNode->m_pszTable && pNode->m_pszProp)
		{
			if (!strcmp(pszTable, pNode->m_pszTable) && !strcmp(pszProp, pNode->m_pszProp))
			{
				auto pNext = pNode->m_pNext;
				auto pPrev = pNode->m_pPrev;

				if (pNext)
				{
					pNext->m_pPrev = pPrev;
				}

				if (pPrev)
				{
					pPrev->m_pNext = pNext;
				}

				delete pNode;

				break;
			}
		}

		pNode = pNode->m_pNext;
	}
}

void NVHooks::RemoveAllNetVarHooks()
{
	auto pNode = s_First.m_pNext;
	while (pNode) 
	{
		auto pNext = pNode->m_pNext;

		delete pNode;

		pNode = pNext;
	}
}

int Lua::NVHooks::l_HookProp(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #1 (String needed)");
		return 0;
	}

	if (!LUA->IsType(2, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #2 (String needed)");
		return 0;
	}

	if (!LUA->IsType(3, GarrysMod::Lua::Type::FUNCTION))
	{
		LUA->ThrowError("Invalid argument #3 (Function needed)");
		return 0;
	}

	LUA->Push(3);
	int iRef = LUA->ReferenceCreate();

	if (!::NVHooks::AddNetVarHook(LUA->GetString(1), LUA->GetString(2), iRef))
	{
		LUA->ReferenceFree(iRef);
	}

	return 0;
}

int Lua::NVHooks::l_UnhookProp(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #1 (String needed)");
		return 0;
	}

	if (!LUA->IsType(2, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #2 (String needed)");
		return 0;
	}

	::NVHooks::RemoveNetVarHook(LUA->GetString(1), LUA->GetString(2));

	return 0;
}