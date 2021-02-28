#ifndef __HEADER_ENUMS__
#define __HEADER_ENUMS__
#pragma once

#include "main.h"

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

__forceinline void PushEnums(lua_State* state)
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

	LUA->PushNumber((double)NETVAR_BYTE);
	LUA->SetField(-2, "NETVAR_BYTE");

	LUA->PushNumber((double)NETVAR_SHORT);
	LUA->SetField(-2, "NETVAR_SHORT");

	LUA->PushNumber((double)NETVAR_INT);
	LUA->SetField(-2, "NETVAR_INT");

	LUA->PushNumber((double)NETVAR_FLOAT);
	LUA->SetField(-2, "NETVAR_FLOAT");

	LUA->PushNumber((double)NETVAR_VECTOR);
	LUA->SetField(-2, "NETVAR_VECTOR");

	LUA->PushNumber((double)NETVAR_BYTE_ARRAY);
	LUA->SetField(-2, "NETVAR_BYTE_ARRAY");

	LUA->PushNumber((double)NETVAR_SHORT_ARRAY);
	LUA->SetField(-2, "NETVAR_SHORT_ARRAY");

	LUA->PushNumber((double)NETVAR_INT_ARRAY);
	LUA->SetField(-2, "NETVAR_INT_ARRAY");

	LUA->PushNumber((double)NETVAR_FLOAT_ARRAY);
	LUA->SetField(-2, "NETVAR_FLOAT_ARRAY");

	LUA->PushNumber((double)NETVAR_VECTOR_ARRAY);
	LUA->SetField(-2, "NETVAR_VECTOR_ARRAY");

	/*ClientFrameStage_t*/

	enum ClientFrameStage_t
	{
		FRAME_UNDEFINED = -1,
		FRAME_START,
		FRAME_NET_UPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_END,
		FRAME_NET_UPDATE_END,
		FRAME_RENDER_START,
		FRAME_RENDER_END
	};

	LUA->PushNumber((double)FRAME_UNDEFINED);
	LUA->SetField(-2, "FRAME_UNDEFINED");

	LUA->PushNumber((double)FRAME_START);
	LUA->SetField(-2, "FRAME_START");

	LUA->PushNumber((double)FRAME_NET_UPDATE_START);
	LUA->SetField(-2, "FRAME_NET_UPDATE_START");

	LUA->PushNumber((double)FRAME_NET_UPDATE_POSTDATAUPDATE_START);
	LUA->SetField(-2, "FRAME_NET_UPDATE_POSTDATAUPDATE_START");

	LUA->PushNumber((double)FRAME_NET_UPDATE_POSTDATAUPDATE_END);
	LUA->SetField(-2, "FRAME_NET_UPDATE_POSTDATAUPDATE_END");

	LUA->PushNumber((double)FRAME_NET_UPDATE_END);
	LUA->SetField(-2, "FRAME_NET_UPDATE_END");

	LUA->PushNumber((double)FRAME_RENDER_START);
	LUA->SetField(-2, "FRAME_RENDER_START");

	LUA->PushNumber((double)FRAME_RENDER_END);
	LUA->SetField(-2, "FRAME_RENDER_END");

	/*Flows*/

	enum
	{
		FLOW_OUTGOING,
		FLOW_INCOMING,
		MAX_FLOWS
	};

	LUA->PushNumber((double)FLOW_OUTGOING);
	LUA->SetField(-2, "FLOW_OUTGOING");

	LUA->PushNumber((double)FLOW_INCOMING);
	LUA->SetField(-2, "FLOW_INCOMING");

	LUA->PushNumber((double)MAX_FLOWS);
	LUA->SetField(-2, "MAX_FLOWS");

	LUA->Pop();
}

#endif