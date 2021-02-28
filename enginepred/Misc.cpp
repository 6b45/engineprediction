#include "Misc.h"

using namespace Lua;

int Misc::l_FullUpdate(lua_State* state)
{
	g_pClientState->m_nDeltaTick() = -1;

	return 0;
}

int Misc::l_TickCount(lua_State* state)
{
	LUA->PushNumber((double)g_pGlobals->tickcount());

	return 1;
}

int Misc::l_MD5PseudoRandom(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #1 (Number needed)");
		return 0;
	}

	LUA->PushNumber((double)MD5_PseudoRandom((int)LUA->GetNumber(1)));
	return 1;
}

int Misc::l_ChangeName(lua_State* state)
{
	const char* pszName = nullptr;

	if (LUA->IsType(1, GarrysMod::Lua::Type::STRING))
	{
		pszName = LUA->GetString(1);
	}
	else
	{
		static auto name = g_pCvar->FindVar("name");
		
		pszName = name->GetString();
	}

	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan == nullptr)
	{
		return 0;
	}

	NET_SetConVar name("name", pszName);
	pNetChan->SendNetMsg(&name, false, false);

	return 0;
}

int Misc::l_RandomFloat(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #1 (Number needed)");
		return 0;
	}

	if (!LUA->IsType(2, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #2 (Number needed)");
		return 0;
	}

	static float(__cdecl* RandomFloat)(float, float) = (float(*)(float, float))GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat");

	LUA->PushNumber((double)RandomFloat((float)LUA->GetNumber(1), (float)LUA->GetNumber(2)));
	return 1;
}

int Misc::l_RandomSeed(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #1 (Number needed)");
		return 0;
	}

	static void(__cdecl* RandomSeed)(int) = (void(*)(int))GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed");

	RandomSeed((int)LUA->GetNumber(1));
	return 0;
}

int Misc::l_RandomInt(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #1 (Number needed)");
		return 0;
	}

	if (!LUA->IsType(2, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #2 (Number needed)");
		return 0;
	}

	static int(__cdecl* RandomInt)(int, int) = (int(*)(int, int))GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomInt");

	LUA->PushNumber((double)RandomInt((int)LUA->GetNumber(1), (int)LUA->GetNumber(2)));
	return 1;
}

int Misc::l_StringCmd(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::STRING))
	{
		LUA->ThrowError("Invalid argument #1 (String needed)");
		return 0;
	}

	static void(__thiscall* s_pSendStringCmd)(CClientState*, const char*) = Memory::FindPattern<void(__thiscall*)(CClientState*, const char*)>("55 8B EC 8B 49 10", "engine.dll");
	s_pSendStringCmd(g_pClientState, LUA->GetString(1));

	return 0;
}

int Misc::l_GetSpreadVector(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::USERCMD))
	{
		LUA->ThrowError("Invalid argument #1 (CUserCmd needed)");
		return 0;
	}

	if (!LUA->IsType(2, GarrysMod::Lua::Type::VECTOR))
	{
		LUA->ThrowError("Invalid argument #2 (Vector needed)");
		return 0;
	}

	float cone[2];

	LUA->GetField(2, "x");

		cone[0] = (float)LUA->GetNumber(-1);

	LUA->Pop();

	LUA->GetField(2, "y");

		cone[1] = (float)LUA->GetNumber(-1);

	LUA->Pop();

	CUserCmd* cmd = *(CUserCmd**)LUA->GetUserdata(1);
	static void(__cdecl* RandomSeed)(int) = (void(*)(int))GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed");
	static float(__cdecl* RandomFloat)(float, float) = (float(*)(float, float))GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat");

	RandomSeed((MD5_PseudoRandom(cmd->command_number()) & 0x7FFFFFFF) & 0xFF);

	float x, y;

	do
	{
		x = (RandomFloat(-1.0, 1.0f) * 0.5f) + (RandomFloat(-1.0, 1.0f) * 0.5f);
		y = (RandomFloat(-1.0, 1.0f) * 0.5f) + (RandomFloat(-1.0, 1.0f) * 0.5f);
	} while ((x * x + y * y) > 1.0f);

	cone[0] *= x;
	cone[1] *= y;

	int ref;
	
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->GetField(-1, "Vector");

			LUA->PushNumber((double)cone[0]);
			LUA->PushNumber((double)cone[1]);
			LUA->PushNumber(0.0);

		LUA->Call(3, 1);

		ref = LUA->ReferenceCreate();

	LUA->Pop();

	LUA->ReferencePush(ref);
	LUA->ReferenceFree(ref);

	return 1;
}