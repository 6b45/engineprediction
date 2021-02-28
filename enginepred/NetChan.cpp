#include "NetChan.h"

using namespace Lua;

int NetChan::l_GetLatency(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #1 (Number needed)");
		return 0;
	}

	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		LUA->PushNumber(pNetChan->GetLatency(LUA->GetNumber(1)));
	}
	else
	{
		LUA->PushNumber(0.0);
	}

	return 1;
}

int NetChan::l_GetOutSequenceNumber(lua_State* state)
{
	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		LUA->PushNumber((double)pNetChan->m_nOutSequenceNr());
		return 1;
	}

	return 0;
}

int NetChan::l_SetOutSequenceNumber(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #1 (Number needed)");
		return 0;
	}

	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		pNetChan->m_nOutSequenceNr() = (int)LUA->GetNumber(1);
	}

	return 0;
}


int NetChan::l_GetInSequenceNumber(lua_State* state)
{
	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		LUA->PushNumber((double)pNetChan->m_nInSequenceNr());
		return 1;
	}

	return 0;
}

int NetChan::l_SetInSequenceNumber(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #1 (Number needed)");
		return 0;
	}

	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		pNetChan->m_nInSequenceNr() = (int)LUA->GetNumber(1);
	}

	return 0;
}

int NetChan::l_GetChokedPackets(lua_State* state)
{
	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		LUA->PushNumber((double)pNetChan->m_nChokedPackets());
		return 1;
	}

	return 0;
}

int NetChan::l_SetChokedPackets(lua_State* state)
{
	if (!LUA->IsType(1, GarrysMod::Lua::Type::NUMBER))
	{
		LUA->ThrowError("Invalid argument #1 (Number needed)");
		return 0;
	}

	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		pNetChan->m_nChokedPackets() = (int)LUA->GetNumber(1);
	}

	return 0;
}