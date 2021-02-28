#include "SendDataGram.h"

static void CallSendDataGramHook()
{
	GLUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		GLUA->GetField(-1, "hook");

			GLUA->GetField(-1, "Run");

				GLUA->PushString("SendDataGram");

			GLUA->Call(1, 0);

		GLUA->Pop();

	GLUA->Pop();
}

int __fastcall Hooks::NetChan::SendDataGram(INetChannelInfo* pThis, void*, void* data)
{
	CallSendDataGramHook();

	pVmt->Unhook();
	int iRet = pThis->SendDataGram(data);
	pVmt->Rehook();

	return iRet;
}