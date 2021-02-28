#ifndef __HEADER_FRAMESTAGENOTIFY__
#define __HEADER_FRAMESTAGENOTIFY__
#pragma once

#include "main.h"

namespace Hooks
{
	namespace Client
	{
		extern CVMTHookManager* pVmt;

		void __fastcall FrameStageNotify(IBaseClientDLL* pThis, void*, int stage);
	}
}

#endif