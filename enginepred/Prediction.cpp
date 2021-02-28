#include "Prediction.h"

using namespace Lua;

static float s_flOldCurTime;
static float s_flOldFrameTime;

int Prediction::l_Start(lua_State* state)
{
	//C7 05 ? ? ? ? ? ? ? ? C3 8B 41 30  x64 
	static int* s_pPredictionSeed = *Memory::FindPattern<int**>("C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 5D C3 8B 40 34 ++ 2", "client.dll");
	static CBasePlayer** s_pPredictionPlayer = *Memory::FindPattern<CBasePlayer***>("89 3D ?? ?? ?? ?? F3 0F 2A 87 ++ 2", "client.dll");
	static IMoveHelper* s_pMoveHelper = *Memory::FindPattern<IMoveHelper**>("8B 0D ?? ?? ?? ?? 52 F3 0F 10 80 ++ 2", "client.dll");

	static bool(__thiscall* s_pPhysicsRunThink)(CBasePlayer*, int) = Memory::FindPattern<bool(__thiscall*)(CBasePlayer*, int)>("55 8B EC 53 8B D9 56 57 8B 83", "client.dll");
	static int(__thiscall* s_pGetNextThinkTick)(CBasePlayer*, const char*) = Memory::FindPattern<int(__thiscall*)(CBasePlayer*, const char*)>("55 8B EC 8B 45 08 56 8B F1 85 C0 75 13", "client.dll");
	static void(__thiscall* s_pSetNextThink)(CBasePlayer*, float, const char*) = Memory::FindPattern<void(__thiscall*)(CBasePlayer*, float, const char*)>("55 8B EC F3 0F 10 45 ?? 0F 2E 05 ?? ?? ?? ?? 53", "client.dll");

	if (!LUA->IsType(1, GarrysMod::Lua::Type::USERCMD))
	{
		LUA->ThrowError("Invalid argument #1 (CUserCmd needed)");
		return 0;
	}

	CBasePlayer* pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());

	CUserCmd* cmd = *(CUserCmd**)LUA->GetUserdata(1);
	if (cmd->command_number() == 0)
	{
		LUA->ThrowError("Can't call engine prediction when cmd->command_number == 0!");
		return 0;
	}

	{
		s_flOldCurTime = g_pGlobals->curtime();
		s_flOldFrameTime = g_pGlobals->frametime();

		g_pGlobals->curtime() = pLocal->GetTickBase() * g_pGlobals->interval_per_tick();
		g_pGlobals->frametime() = g_pGlobals->interval_per_tick();

		*s_pPredictionPlayer = pLocal;
		*s_pPredictionSeed = MD5_PseudoRandom(cmd->command_number()) & 0x7FFFFFFF;
		pLocal->SetCurrentCommand(cmd);
	}

	{ // prethink

		if (s_pPhysicsRunThink(pLocal, 0))
		{
			GET_VFUNC(void(__thiscall*)(CBasePlayer*), pLocal, 308)(pLocal);
		}

	}

	{ // think

		int nNextThinkTick = s_pGetNextThinkTick(pLocal, nullptr);
		if (!(nNextThinkTick <= 0 || nNextThinkTick > pLocal->GetTickBase()))
		{
			s_pSetNextThink(pLocal, -1.f, nullptr);

			GET_VFUNC(void(__thiscall*)(CBasePlayer*), pLocal, 120)(pLocal);
		}

	}

	static auto sv_footsteps = g_pCvar->FindVar("sv_footsteps");
	float flOld = sv_footsteps->GetFloat();
	sv_footsteps->SetValue(0.f);

	g_pPrediction->SetupMove(pLocal, cmd, s_pMoveHelper, g_pMovement->GetMoveData());
	g_pMovement->ProcessMovement(pLocal, g_pMovement->GetMoveData());
	g_pPrediction->FinishMove(pLocal, cmd, g_pMovement->GetMoveData());

	sv_footsteps->SetValue(flOld);

	return 0;
}

int Prediction::l_Finish(lua_State* state)
{
	static int* s_pPredictionSeed = *Memory::FindPattern<int**>("C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 5D C3 8B 40 34 ++ 2", "client.dll");
	static CBasePlayer** s_pPredictionPlayer = *Memory::FindPattern<CBasePlayer***>("89 3D ?? ?? ?? ?? F3 0F 2A 87 ++ 2", "client.dll");

	CBasePlayer* pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());

	g_pGlobals->curtime() = s_flOldCurTime;
	g_pGlobals->frametime() = s_flOldFrameTime;

	*s_pPredictionPlayer = nullptr;
	*s_pPredictionSeed = -1;

	pLocal->SetCurrentCommand(nullptr);

	return 0;
}