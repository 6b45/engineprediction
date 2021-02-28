#include "Interpolation.h"

using namespace Lua;

int Interpolation::l_SetEnabled(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::BOOL))
	{
		LUA->ThrowError("Invalid argument #1 (Bool needed)");
		return 0;
	}

	static auto cl_interpolate = g_pCvar->FindVar("cl_interpolate");
	cl_interpolate->SetValue((int)LUA->GetBool(1));

	NET_SetConVar net_cl_interpolate("cl_interpolate", LUA->GetBool(1) ? "1" : "0");

	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		pNetChan->SendNetMsg(&net_cl_interpolate, true, false);
	}

	return 0;
}