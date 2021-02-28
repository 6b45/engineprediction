#include "CUserCmd.h"

int Lua::CUserCmd::l_SetTickCount(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::USERCMD))
	{
		LUA->ThrowError("Invalid argument #1 (CUserCmd needed)");
		return 0;
	}

	if (!LUA->IsType(2, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #2 (Number needed)");
		return 0;
	}

	::CUserCmd* cmd = *(::CUserCmd**)LUA->GetUserdata(1);

	cmd->tick_count() = (int)LUA->GetNumber(2);

	return 0;
}

int Lua::CUserCmd::l_GetRandomSeed(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::USERCMD))
	{
		LUA->ThrowError("Invalid argument #1 (CUserCmd needed)");
		return 0;
	}

	::CUserCmd* cmd = *(::CUserCmd**)LUA->GetUserdata(1);
	int seed = MD5_PseudoRandom(cmd->command_number()) & 0x7FFFFFFF;

	LUA->PushNumber((double)seed);

	return 1;
}

void Lua::CUserCmd::RegisterMetaMethods(lua_State* state)
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->GetField(-1, "FindMetaTable");

			LUA->PushString("CUserCmd");

		LUA->Call(1, 1);

		LUA->PushCFunction(l_SetTickCount);
		LUA->SetField(-2, "SetTickCount");

		LUA->PushCFunction(l_GetRandomSeed);
		LUA->SetField(-2, "GetRandomSeed");

		LUA->Pop();

	LUA->Pop();
}