#include "CVMTHookManager.h"

CVMTHookManager::CVMTHookManager(void* pVmt)
{
	size_t nSize = 0;

	m_pppBase = (void***)pVmt;
	m_ppOriginal = *m_pppBase;

	while (!IsBadCodePtr((FARPROC)m_ppOriginal[nSize]))
	{
		nSize++;
	}

	m_ppNew = new void*[nSize];
	for (; nSize > 0; nSize--)
	{
		m_ppNew[nSize - 1] = m_ppOriginal[nSize - 1];
	}
}

CVMTHookManager::~CVMTHookManager()
{
	delete[] m_ppNew;
}

void CVMTHookManager::Hook(bool bHook)
{
	*m_pppBase = (bHook) ? m_ppNew : m_ppOriginal;
}

void CVMTHookManager::Unhook()
{
	Hook(false);
}

void CVMTHookManager::Rehook()
{
	Hook(true);
}

void CVMTHookManager::HookFunction(int idx, void* pFunction)
{
	m_ppNew[idx] = pFunction;
}

void CVMTHookManager::UnhookFunction(int idx)
{
	m_ppNew[idx] = m_ppOriginal[idx];
}