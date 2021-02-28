#ifndef __HEADER_CVMTHOOKMANAGER__
#define __HEADER_CVMTHOOKMANAGER__
#pragma once

#include "main.h"

class CVMTHookManager
{
public:
	CVMTHookManager(void* pVmt);
	~CVMTHookManager();

	void Hook(bool bHook);
	void Unhook();
	void Rehook();

	void HookFunction(int idx, void* pFunction);
	void UnhookFunction(int idx);
private:
	void*** m_pppBase;
	void** m_ppOriginal;
	void** m_ppNew;
};

#endif