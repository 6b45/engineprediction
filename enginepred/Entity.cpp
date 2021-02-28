#include "Entity.h"

using namespace Lua;

int Entity::l_GetSimulationTime(lua_State* state)
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

	int idx;

	LUA->ReferencePush(ref);

		LUA->GetField(-1, "EntIndex");

			LUA->ReferencePush(ref);

		LUA->Call(1, 1);

		idx = (int)LUA->GetNumber(-1);
		LUA->Pop();

	LUA->Pop();

	LUA->ReferenceFree(ref);

	auto pEntity = g_pEntityList->GetClientEntity(idx);
	if (pEntity == nullptr)
	{
		LUA->ThrowError("Invalid argument #1 (Entity was NULL)");
		return 0;
	}

	LUA->PushNumber((double)pEntity->GetSimulationTime());

	return 1;
}

void Entity::RegisterMetaMethods(lua_State* state)
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->GetField(-1, "FindMetaTable");

			LUA->PushString("Entity");

		LUA->Call(1, 1);

		LUA->PushCFunction(l_GetSimulationTime);
		LUA->SetField(-2, "GetSimulationTime");

		LUA->Pop();

	LUA->Pop();
}