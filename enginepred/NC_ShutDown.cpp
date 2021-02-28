#include "NC_ShutDown.h"

static char* CallShutdownHook()
{
	char* pRet = nullptr;

	GLUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		GLUA->GetField(-1, "hook");

			GLUA->GetField(-1, "Run");

				GLUA->PushString("NetChannel_Shutdown");

			GLUA->Call(1, 1);

			if (GLUA->IsType(-1, GarrysMod::Lua::Type::STRING))
			{
				pRet = _strdup(GLUA->GetString(-1));
			}

			GLUA->Pop();

		GLUA->Pop();

	GLUA->Pop();

	return pRet;
}

void __fastcall Hooks::NetChan::Shutdown(INetChannelInfo* pThis, void*, const char* reason)
{
	pVmt->Unhook();
	delete pVmt;
	pVmt = nullptr;

	auto pszCustomReason = CallShutdownHook();

	pThis->Shutdown(pszCustomReason ? pszCustomReason : reason);

	if (pszCustomReason)
	{
		free(pszCustomReason);
	}
}