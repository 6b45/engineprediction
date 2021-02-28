#ifndef __HEADER_XORSTRING__
#define __HEADER_XORSTRING__
#pragma once

#define SEED ((__TIME__[7] - '0') * 1  + (__TIME__[6] - '0') * 10  + \
              (__TIME__[4] - '0') * 60   + (__TIME__[3] - '0') * 600 + \
              (__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000)

namespace Util
{
	constexpr int LinearCongruentGenerator(int nRounds)
	{
		return 1013904223 + 1664525 * ((nRounds> 0) ? LinearCongruentGenerator(nRounds - 1) : SEED & 0xFFFFFFFF);
	}

	template<size_t nLen, int nCounter>
	class CXorStr
	{
	public:
		constexpr __forceinline CXorStr(const char* pszString) : m_bDecoded(false), m_uiKey(LinearCongruentGenerator(nCounter)), m_szEncrypted{ 0 }
		{
			EncodeString<nLen>(pszString);
		}

		template<size_t nCur>
		constexpr __forceinline void EncodeString(const char* pszString)
		{
			m_szEncrypted[nCur] = Encode<nCur>(pszString[nCur]);
			EncodeString<nCur - 1>(pszString);
		}

		template<>
		constexpr __forceinline void EncodeString<size_t(-1)>(const char* pszString)
		{

		}

		__forceinline const char* GetString()
		{
			if (m_bDecoded) return m_szEncrypted;

			for (size_t i = 0; i < nLen; i++)
			{
				m_szEncrypted[i] ^= ((m_uiKey >> (8 * (i % 4))) & 0xFF);
			}

			m_szEncrypted[nLen] = '\0';
			m_bDecoded = true;
			return m_szEncrypted;
		}
	private:
		template<size_t nCur>
		__forceinline constexpr char Encode(char c) const
		{
			return c ^ ((m_uiKey >> (8 * (nCur % 4))) & 0xFF);
		}
		const unsigned int m_uiKey;
		mutable char m_szEncrypted[nLen + 1];
		bool m_bDecoded;
	};

	template<size_t nLen, int nCounter>
	class CWXorStr {
	public:
		constexpr __forceinline CWXorStr(const wchar_t* pszString) : m_bDecoded(false), m_uiKey(LinearCongruentGenerator(nCounter)), m_szEncrypted{ 0 }
		{
			EncodeString<nLen>(pszString);
		}

		template<size_t nCur>
		constexpr __forceinline void EncodeString(const wchar_t* pszString)
		{
			m_szEncrypted[nCur] = Encode<nCur>(pszString[nCur]);
			EncodeString<nCur - 1>(pszString);
		}

		template<>
		constexpr __forceinline void EncodeString<size_t(-1)>(const wchar_t* pszString)
		{

		}

		__forceinline const wchar_t* GetString()
		{
			if (m_bDecoded) return m_szEncrypted;

			for (size_t i = 0; i < nLen; i++)
			{
				m_szEncrypted[i] ^= ((m_uiKey >> (8 * (i % 4))) & 0xFF);
			}

			m_szEncrypted[nLen] = '\0';
			m_bDecoded = true;
			return m_szEncrypted;
		}
	private:
		template<size_t nCur>
		__forceinline constexpr wchar_t Encode(wchar_t c) const
		{
			return c ^ ((m_uiKey >> (8 * (nCur % 4))) & 0xFF);
		}
		const unsigned int m_uiKey;
		mutable wchar_t m_szEncrypted[nLen + 1];
		bool m_bDecoded;
	};
}

#undef SEED

#define XorStr_Expand(s) (Util::CXorStr<sizeof(s) - 1, __COUNTER__>(s).GetString())
#define XorStr(s) XorStr_Expand(s)

#define WXorStr_Expand(s) (Util::CWXorStr<sizeof(s) / sizeof(wchar_t) - 1, __COUNTER__>(s).GetString())
#define WXorStr(s) WXorStr_Expand(s)

#define WXorS_Expand(x, s) Util::CWXorStr<sizeof(s) / sizeof(wchar_t) - 1, __COUNTER__> x(s);
#define WXorS(x, s) WXorS_Expand(x, s)

#define SWXorStr_Expand(x, s) static WXorS(x, s)
#define SWXorStr(x, s) SWXorStr_Expand(x, s)

#endif