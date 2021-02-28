#ifndef __HEADER_SDK__
#define __HEADER_SDK__
#pragma once

#include "main.h"

#define GET_VFUNC(FN, X, IDX) \
((FN)(((*(DWORD_PTR**)((DWORD_PTR)(X)))[(IDX)])))

class CGlobalVarsBase
{
public:
	float& curtime()
	{
		return *(float*)((DWORD_PTR)this + 0x0C);
	}

	float& frametime()
	{
		return *(float*)((DWORD_PTR)this + 0x10);
	}

	float& interval_per_tick()
	{
		return *(float*)((DWORD_PTR)this + 0x1C);
	}

	int& tickcount()
	{
		return *(int*)((DWORD_PTR)this + 0x18);
	}
};

class CUserCmd;
class CBasePlayer;
class IMoveHelper;
class CMoveData;

class ClientClass;

class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses()
	{
		return GET_VFUNC(ClientClass*(__thiscall*)(IBaseClientDLL*), this, 8)(this);
	}

	void CreateMove(int s, float sm, bool a)
	{
		return GET_VFUNC(void(__thiscall*)(IBaseClientDLL*, int, float, bool), this, 21)(this, s, sm, a);
	}

	void FrameStageNotify(int stage)
	{
		return GET_VFUNC(void(__thiscall*)(IBaseClientDLL*, int), this, 35)(this, stage);
	}
};

class INetChannelInfo
{
public:
	bool SendNetMsg(void* msg, bool forcereliable, bool voice)
	{
		return GET_VFUNC(bool(__thiscall*)(INetChannelInfo*, void*, bool, bool), this, 40)(this, msg, forcereliable, voice);
	}

	float GetLatency(int flow)
	{
		return GET_VFUNC(float(__thiscall*)(INetChannelInfo*, int), this, 9)(this, flow);
	}

	void Shutdown(const char* reason)
	{
		return GET_VFUNC(void(__thiscall*)(INetChannelInfo*, const char*), this, 36)(this, reason);
	}

	int SendDataGram(void* data)
	{
		return GET_VFUNC(int(__thiscall*)(INetChannelInfo*, void*), this, 46)(this, data);
	}

	int& m_nOutSequenceNr()
	{
		return *(int*)((DWORD_PTR)this + 0x08);
	}

	int& m_nInSequenceNr()
	{
		return *(int*)((DWORD_PTR)this + 0x0C);
	}

	int& m_nOutReliableState()
	{
		return *(int*)((DWORD_PTR)this + 0x14);
	}

	int& m_nInReliableState()
	{
		return *(int*)((DWORD_PTR)this + 0x18);
	}

	int& m_nChokedPackets()
	{
		return *(int*)((DWORD_PTR)this + 0x1C);
	}
};

class IVEngineClient
{
public:
	int GetLocalPlayer()
	{
		return GET_VFUNC(int(__thiscall*)(IVEngineClient*), this, 12)(this);
	}

	INetChannelInfo* GetNetChannelInfo()
	{
		return GET_VFUNC(INetChannelInfo*(__thiscall*)(IVEngineClient*), this, 72)(this);
	}
};

class IClientEntityList
{
public:
	CBasePlayer* IClientEntityList::GetClientEntity(int idx)
	{
		return GET_VFUNC(CBasePlayer*(__thiscall*)(IClientEntityList*, int), this, 3)(this, idx);
	}
};

class IGameMovement
{
public:
	void ProcessMovement(CBasePlayer* player, CMoveData* movedata)
	{
		return GET_VFUNC(void(__thiscall*)(IGameMovement*, CBasePlayer*, CMoveData*), this, 1)(this, player, movedata);
	}

	CMoveData* GetMoveData()
	{
		return *(CMoveData**)((DWORD_PTR)this + 0x08);
	}
};

class IPrediction
{
public:
	void SetupMove(CBasePlayer* player, CUserCmd* cmd, IMoveHelper* movehelper, CMoveData* movedata)
	{
		return GET_VFUNC(void(__thiscall*)(IPrediction*, CBasePlayer*, CUserCmd*, IMoveHelper*, CMoveData*), this, 18)(this, player, cmd, movehelper, movedata);
	}

	void FinishMove(CBasePlayer* player, CUserCmd* cmd, CMoveData* movedata)
	{
		return GET_VFUNC(void(__thiscall*)(IPrediction*, CBasePlayer*, CUserCmd*, CMoveData*), this, 19)(this, player, cmd, movedata);
	}
};

class ConVar
{
public:
	void SetValue(int val)
	{
		*(int*)((DWORD_PTR)this + 0x30) = val;
	}

	void SetValue(float val)
	{
		*(float*)((DWORD_PTR)this + 0x2C) = val;
	}

	const char* GetString()
	{
		return *(const char**)((DWORD_PTR)this + 0x24);
	}

	float GetFloat()
	{
		return *(float*)((DWORD_PTR)this + 0x2C);
	}
};

class ICvar
{
public:
	ConVar* FindVar(const char* name)
	{
		return GET_VFUNC(ConVar*(__thiscall*)(ICvar*, const char*), this, 13)(this, name);
	}
};

class CUserCmd
{
public:
	int& command_number()
	{
		return *(int*)((DWORD_PTR)this + 0x04);
	}

	int& tick_count()
	{
		return *(int*)((DWORD_PTR)this + 0x08);
	}
};

class IMoveHelper
{
public:

};

class CClientState
{
public:
	int& m_nDeltaTick()
	{
		return *(int*)((DWORD_PTR)this + 416);
	}
};

extern IBaseClientDLL* g_pClient;
extern IVEngineClient* g_pEngine;
extern IClientEntityList* g_pEntityList;
extern CGlobalVarsBase* g_pGlobals;
extern IGameMovement* g_pMovement;
extern IPrediction* g_pPrediction;
extern ICvar* g_pCvar;
extern CClientState* g_pClientState;

__forceinline void* CreateInterface(const char* pszInterfaceName, const char* pszModule)
{
	using CreateInterfaceFn = void*(*)(const char*, int*);

	CreateInterfaceFn moduleFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(pszModule), "CreateInterface");
	if (moduleFactory == nullptr)
	{
		return nullptr;
	}

	return moduleFactory(pszInterfaceName, nullptr);
}

__forceinline void* BruteforceInterface(const char* pszInterfaceName, const char* pszModule)
{
	for (int nVersion = 100; nVersion >= 0; nVersion--)
	{
		char szBuf[128 + 1] = { 0 };
		sprintf_s(szBuf, "%s%03d", pszInterfaceName, nVersion);

		if (CreateInterface(szBuf, pszModule) != nullptr)
		{
			return CreateInterface(szBuf, pszModule);
		}
	}

	return nullptr;
}

__forceinline unsigned int MD5_PseudoRandom(int seed)
{
	static unsigned int(__cdecl* pMD5_PseudoRandom)(int) = Memory::FindPattern<unsigned int(__cdecl*)(int)>("55 8B EC 83 EC 68 6A 58", "client.dll");

	return pMD5_PseudoRandom(seed);
}

class CRecvTable;

class CRecvProp
{
public:
	const char* m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void *m_pExtraData;
	CRecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	CRecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};

class CRecvTable
{
public:
	CRecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	const char* m_pNetTableName;
	bool			m_bInitialized;
	bool			m_bInMainList;
};

class ClientClass
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	char* m_pNetworkName;
	CRecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class DVariant
{
public:
	union
	{
		float	m_Float;
		int		m_Int;
		const char	*m_pString;
		void	*m_pData;
		float	m_Vector[3];
	};
	int	m_Type;
};

class CRecvProxyData
{
public:
	const CRecvProp	*m_pRecvProp;
	DVariant		m_Value;
	int				m_iElement;
	int				m_ObjectID;
};

template< class _T >
class SmallVector
{
public:
	SmallVector()
	{
		m_pData = nullptr;
		m_nElements = 0;
	}

	SmallVector(const SmallVector& other)
	{
		Clear();
		Copy(other.m_pData, other.m_nElements);
	}

	~SmallVector()
	{
		Clear();
	}

	void Clear()
	{
		if (m_pData != nullptr)
		{
			free(m_pData);
		}

		m_pData = nullptr;
		m_nElements = 0;
	}

	void Copy(_T* pData, size_t nElements)
	{
		m_pData = (_T*)malloc(sizeof(_T) * nElements);

		memcpy(m_pData, pData, sizeof(_T) * nElements);
	}

	void Add(_T toAdd)
	{
		m_nElements++;

		if (m_pData != nullptr)
		{
			m_pData = (_T*)realloc(m_pData, sizeof(_T) * m_nElements);
			SetAt(m_nElements - 1, toAdd);
		}
		else
		{
			m_pData = (_T*)malloc(sizeof(_T));
			SetAt(0, toAdd);
		}
	}

	void SetAt(int idx, _T data)
	{
		m_pData[idx] = data;
	}

	_T GetAt(int idx)
	{
		return m_pData[idx];
	}

	size_t GetSize()
	{
		return m_nElements;
	}

	_T* GetData()
	{
		return m_pData;
	}

	_T operator[](int idx)
	{
		return GetAt(idx);
	}

	const _T operator[](int idx) const
	{
		return GetAt(idx);
	}
private:
	_T* m_pData;
	size_t m_nElements;
};

#undef GetProp

class CNetVarManager
{
public:
	CNetVarManager()
	{
		ClientClass* pClass = g_pClient->GetAllClasses();
		while (pClass)
		{
			m_vecRecvTable.Add(pClass->m_pRecvTable);
			pClass = pClass->m_pNext;
		}
	}

	size_t GetOffset(const char* pszTableName, const char* pszPropName)
	{
		return GetProp(pszTableName, pszPropName);
	}

	bool CNetVarManager::HookProp(const char* pszTableName, const char* pszPropName, void* pProxy, void** pOld)
	{
		CRecvProp* pProp = nullptr;
		GetProp(pszTableName, pszPropName, &pProp);

		if (pProp == nullptr) return false;

		*pOld = pProp->m_ProxyFn;
		pProp->m_ProxyFn = pProxy;
		return true;
	}
private:
	size_t GetProp(const char* pszTableName, const char* pszPropName, CRecvProp** pProps = nullptr)
	{
		CRecvTable* pRecvTable = GetTable(pszTableName);
		if (pRecvTable == nullptr)
		{
			return 0;
		}

		return GetProp(pRecvTable, pszPropName, pProps);
	}

	size_t GetProp(CRecvTable* pRecvTable, const char* pszPropName, CRecvProp** pProps = nullptr)
	{
		size_t curOffset = 0;

		for (int i = 0; i < pRecvTable->m_nProps; i++)
		{
			auto* pRecvProp = &pRecvTable->m_pProps[i];
			auto* child = pRecvProp->m_pDataTable;

			curOffset += (child && (child->m_nProps > 0) && GetProp(child, pszPropName, pProps)) ? pRecvProp->m_Offset + GetProp(child, pszPropName, pProps) : 0;

			if (_stricmp(pRecvProp->m_pVarName, pszPropName))
			{
				continue;
			}

			if (pProps)
			{
				*pProps = pRecvProp;
			}

			return pRecvProp->m_Offset + curOffset;
		}

		return curOffset;
	}

	CRecvTable* GetTable(const char* pszTableName)
	{
		for (int idx = 0; idx < m_vecRecvTable.GetSize(); idx++)
		{
			auto table = m_vecRecvTable[idx];

			if (!table)
			{
				continue;
			}

			if (!_stricmp(table->m_pNetTableName, pszTableName))
			{
				return table;
			}
		}

		return nullptr;
	}

	SmallVector<CRecvTable*> m_vecRecvTable;
};

extern CNetVarManager* pMgr;

class CBasePlayer
{
public:
	int GetTickBase()
	{
		static size_t offset = pMgr->GetOffset("DT_BasePlayer", "m_nTickBase");

		return *(int*)((DWORD_PTR)this + offset);
	}
	
	float GetSimulationTime()
	{
		static size_t offset = pMgr->GetOffset("DT_BaseEntity", "m_flSimulationTime");

		return *(float*)((DWORD_PTR)this + offset);
	}

	void SetCurrentCommand(CUserCmd* cmd)
	{
		static size_t offset = pMgr->GetOffset("DT_BasePlayer", "m_hConstraintEntity") - 0x4;

		*(CUserCmd**)((DWORD_PTR)this + offset) = cmd;
	}

	class IClientNetworkable;
	IClientNetworkable* GetNetworkable()
	{
		return (IClientNetworkable*)((DWORD_PTR)this + 0x8);
	}

	ClientClass* GetClientClass()
	{
		return GET_VFUNC(ClientClass*(__thiscall*)(IClientNetworkable*), GetNetworkable(), 2)(GetNetworkable());
	}

	int EntIndex()
	{
		return GET_VFUNC(int(__thiscall*)(IClientNetworkable*), GetNetworkable(), 9)(GetNetworkable());
	}
};

class NET_SetConVar
{
public:
	NET_SetConVar(const char* name, const char* value)
	{
		static int(__thiscall* _NET_SetConVar)(NET_SetConVar*, const char*, const char*) = Memory::FindPattern<int(__thiscall*)(NET_SetConVar*, const char*, const char*)>("55 8B EC 81 EC ?? ?? ?? ?? 56 57 8B F9 68", "engine.dll");
		_NET_SetConVar(this, name, value);
	}

	byte __NET_SetConVar[36];
};

#endif