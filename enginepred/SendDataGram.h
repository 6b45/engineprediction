#ifndef __HEADER_SENDDATAGRAM__
#define __HEADER_SENDDATAGRAM__
#pragma once

#include "main.h"

namespace Hooks
{
	namespace NetChan
	{
		extern CVMTHookManager* pVmt;

		int __fastcall SendDataGram(INetChannelInfo* pThis, void*, void* data);
	}
}

#endif