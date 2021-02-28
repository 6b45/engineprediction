#ifndef __HEADER_SHUTDOWN__
#define __HEADER_SHUTDOWN__
#pragma once

#include "main.h"

namespace Hooks
{
	namespace NetChan
	{
		extern CVMTHookManager* pVmt;

		void __fastcall Shutdown(INetChannelInfo* pThis, void*, const char* reason);
	}
}

#endif