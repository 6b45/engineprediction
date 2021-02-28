#include "FrameStageNotify.h"

using namespace Hooks;

static void CallFSNHook(bool bPost, int stage)
{
	GLUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

		GLUA->GetField(-1, "hook");

			GLUA->GetField(-1, "Run");

				GLUA->PushString(bPost ? "PostFrameStageNotify" : "PreFrameStageNotfiy");
				GLUA->PushNumber((double)stage);

			GLUA->Call(2, 0);

		GLUA->Pop();

	GLUA->Pop();
}

void __fastcall Client::FrameStageNotify(IBaseClientDLL* pThis, void*, int stage)
{
	CallFSNHook(false, stage);

	pVmt->Unhook();
	pThis->FrameStageNotify(stage);
	pVmt->Rehook();

	CallFSNHook(true, stage);
}