/* very ghetto by me */

#include "main.h"

IBaseClientDLL* g_pClient;
IVEngineClient* g_pEngine;
IClientEntityList* g_pEntityList;
CGlobalVarsBase* g_pGlobals;
IGameMovement* g_pMovement;
IPrediction* g_pPrediction;
ICvar* g_pCvar;
CClientState* g_pClientState;

CNetVarManager* pMgr;

#include "Enums.h"

#include "CUserCmd.h"
#include "Entity.h"

#include "Interpolation.h"
#include "Misc.h"
#include "NetChan.h"
#include "NetVars.h"
#include "NVHooks.h"
#include "Prediction.h"

#include "CreateMove.h"
#include "FrameStageNotify.h"
#include "NC_ShutDown.h"
#include "SendDataGram.h"

lua_State* g_pLua;

CVMTHookManager* Hooks::Client::pVmt;
CVMTHookManager* Hooks::NetChan::pVmt;

static void InitInterfaces()
{
	g_pGlobals = *Memory::FindPattern<CGlobalVarsBase**>("68 ?? ?? ?? ?? 50 50 FF 12 ++ 1", "engine.dll");
	g_pClientState = *Memory::FindPattern<CClientState**>("B9 ?? ?? ?? ?? 5F 5E 5D E9 ++ 1", "engine.dll");

	g_pClient = (IBaseClientDLL*)BruteforceInterface("VClient", "client.dll");
	g_pEngine = (IVEngineClient*)BruteforceInterface("VEngineClient", "engine.dll");
	g_pEntityList = (IClientEntityList*)BruteforceInterface("VClientEntityList", "client.dll");;
	g_pMovement = (IGameMovement*)BruteforceInterface("GameMovement", "client.dll");
	g_pPrediction = (IPrediction*)BruteforceInterface("VClientPrediction", "client.dll");
	g_pCvar = (ICvar*)BruteforceInterface("VEngineCvar", "vstdlib.dll");
	
	pMgr = new CNetVarManager();
}

GMOD_MODULE_OPEN()
{
	g_pLua = state;
	InitInterfaces();

	PushEnums(state);

	Lua::CUserCmd::RegisterMetaMethods(state);
	Lua::Entity::RegisterMetaMethods(state);
	Lua::NetVars::RegisterMetaMethods(state);

	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->CreateTable();
		
		{ // Interpolation
			LUA->PushCFunction(Lua::Interpolation::l_SetEnabled);
			LUA->SetField(-2, "SetInterpolation");
		}

		{ // Misc
			LUA->PushCFunction(Lua::Misc::l_FullUpdate);
			LUA->SetField(-2, "FullUpdate");

			LUA->PushCFunction(Lua::Misc::l_TickCount);
			LUA->SetField(-2, "TickCount");

			LUA->PushCFunction(Lua::Misc::l_MD5PseudoRandom);
			LUA->SetField(-2, "MD5PseudoRandom");

			LUA->PushCFunction(Lua::Misc::l_ChangeName);
			LUA->SetField(-2, "ChangeName");

			LUA->PushCFunction(Lua::Misc::l_RandomFloat);
			LUA->SetField(-2, "RandomFloat");

			LUA->PushCFunction(Lua::Misc::l_RandomSeed);
			LUA->SetField(-2, "RandomSeed");

			LUA->PushCFunction(Lua::Misc::l_RandomInt);
			LUA->SetField(-2, "RandomInt");

			LUA->PushCFunction(Lua::Misc::l_StringCmd);
			LUA->SetField(-2, "StringCmd");

			LUA->PushCFunction(Lua::Misc::l_GetSpreadVector);
			LUA->SetField(-2, "GetSpreadVector");
		}

		{ // Netchan
			LUA->PushCFunction(Lua::NetChan::l_GetLatency);
			LUA->SetField(-2, "GetLatency");

			LUA->PushCFunction(Lua::NetChan::l_GetOutSequenceNumber);
			LUA->SetField(-2, "GetOutSequenceNumber");

			LUA->PushCFunction(Lua::NetChan::l_SetOutSequenceNumber);
			LUA->SetField(-2, "SetOutSequenceNumber");

			LUA->PushCFunction(Lua::NetChan::l_GetInSequenceNumber);
			LUA->SetField(-2, "GetInSequenceNumber");

			LUA->PushCFunction(Lua::NetChan::l_SetInSequenceNumber);
			LUA->SetField(-2, "SetInSequenceNumber");

			LUA->PushCFunction(Lua::NetChan::l_GetChokedPackets);
			LUA->SetField(-2, "GetChokedPackets");

			LUA->PushCFunction(Lua::NetChan::l_SetChokedPackets);
			LUA->SetField(-2, "SetChokedPackets");
		}

		{ // NVHooks
			LUA->PushCFunction(Lua::NVHooks::l_HookProp);
			LUA->SetField(-2, "HookProp");

			LUA->PushCFunction(Lua::NVHooks::l_UnhookProp);
			LUA->SetField(-2, "UnhookProp");
		}

		{ // Pred
			LUA->PushCFunction(Lua::Prediction::l_Start);
			LUA->SetField(-2, "StartPrediction");

			LUA->PushCFunction(Lua::Prediction::l_Finish);
			LUA->SetField(-2, "FinishPrediction");
		}

		LUA->SetField(-2, "big");

	LUA->Pop();

	Hooks::Client::pVmt = new CVMTHookManager(g_pClient);
	Hooks::Client::pVmt->HookFunction(21, Hooks::Client::CreateMove);
	Hooks::Client::pVmt->HookFunction(35, Hooks::Client::FrameStageNotify);
	Hooks::Client::pVmt->Hook(true);

	auto pNetChan = g_pEngine->GetNetChannelInfo();
	if (pNetChan)
	{
		Hooks::NetChan::pVmt = new CVMTHookManager(pNetChan);
		Hooks::NetChan::pVmt->HookFunction(36, Hooks::NetChan::Shutdown);
		Hooks::NetChan::pVmt->HookFunction(46, Hooks::NetChan::SendDataGram);
		Hooks::NetChan::pVmt->Hook(true);
	}
	else
	{
		Hooks::NetChan::pVmt = nullptr;
	}
	
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		LUA->GetField(-1, XorStr("print"));	

			LUA->PushString(XorStr("Big 1.0 loaded >> by razor <<"));

		LUA->Call(1, 0);

	LUA->Pop();

	return 0;
}

GMOD_MODULE_CLOSE()
{
	NetVars::ClearNetVars();
	NVHooks::RemoveAllNetVarHooks();

	delete pMgr;

	if (Hooks::NetChan::pVmt)
	{
		Hooks::NetChan::pVmt->Unhook();
		delete Hooks::NetChan::pVmt;
	}

	Hooks::Client::pVmt->Unhook();
	delete Hooks::Client::pVmt;

	return 0;
}