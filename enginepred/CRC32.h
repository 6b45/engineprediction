#ifndef __HEADER_CRC32__
#define __HEADER_CRC32__
#pragma once

#include "main.h"

namespace CRC32
{
	void Init(unsigned int *pulCRC);
	void Final(unsigned int *pulCRC);
	unsigned int GetTableEntry(unsigned int slot);
	void ProcessBuffer(unsigned int *pulCRC, const void *pBuffer, int nBuffer);
	unsigned int HashString(const char* pszString);
}

#endif