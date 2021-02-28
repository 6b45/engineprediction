#include "CreateMove.h"

using namespace Hooks;

void __fastcall Client::CreateMove(IBaseClientDLL* pThis, void*, int s, float sm, bool a)
{
	pVmt->Unhook();
	pThis->CreateMove(s, sm, a);
	pVmt->Rehook();

	void* base;
	__asm
	{
		mov base, ebp
	}

	bool* bSendPacket = *(bool**)base - 0x1;

	GLUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		GLUA->GetField(-1, "bSendPacket");
		if (GLUA->IsType(-1, GarrysMod::Lua::Type::BOOL))
		{
			*bSendPacket = GLUA->GetBool(-1);
		}

		GLUA->Pop();
	
	GLUA->Pop();
}