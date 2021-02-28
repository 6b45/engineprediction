#ifndef __HEADER_CREATEMOVE__
#define __HEADER_CREATEMOVE__
#pragma once

#include "main.h"

namespace Hooks
{
	namespace Client
	{
		extern CVMTHookManager* pVmt;

		void __fastcall CreateMove(IBaseClientDLL* pThis, void*, int s, float sm, bool a);
	}
}

#endif