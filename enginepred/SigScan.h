#ifndef __HEADER_SIGSCAN__
#define __HEADER_SIGSCAN__
#pragma once

#include "main.h"

#define TO_HEX(c) \
((c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10))

#define TO_BYTE(a, b) \
((TO_HEX(a) << 4) + TO_HEX(b))

namespace Memory
{
	inline bool CompareMemory(const char* pszPattern, size_t nLen, DWORD_PTR dwpAddr)
	{
		for (int nCur = 0; nCur < nLen; nCur += 3, dwpAddr++)
		{
			if (pszPattern[nCur] == '?')
			{
				continue;
			}

			if (pszPattern[nCur] == '+')
			{
				return true;
			}

			if (*(byte*)(dwpAddr) != TO_BYTE(pszPattern[nCur], pszPattern[nCur + 1]))
			{
				return false;
			}
		}

		return true;
	}

	template< typename _T >
	inline _T FindPattern(const char* pszPattern, const char* pszModule, size_t uSize = 0, size_t dStartOffset = 0)
	{
		size_t nLen = strlen(pszPattern);
		DWORD_PTR dwpBase = (DWORD_PTR)GetModuleHandleA(pszModule);
		size_t dAdd = 0;

		if (strstr(pszPattern, "++"))
		{
			const char* pszStart = strstr(pszPattern, "++") + 3;
			dAdd = strtoul(pszStart, nullptr, 0);
		}

		if (uSize == 0)
		{
			MODULEINFO info;
			GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(pszModule), &info, sizeof(info));

			uSize = info.SizeOfImage;
		}

		for (DWORD_PTR dwpAddress = (dwpBase + dStartOffset); (dwpAddress + (nLen / 3)) < (dwpBase + uSize); dwpAddress++)
		{
			if (CompareMemory(pszPattern, nLen, dwpAddress))
			{
				return (_T)(dwpAddress + dAdd);
			}
		}

		return _T(0);
	}
}

#undef TO_HEX
#undef TO_BYTE

#endif