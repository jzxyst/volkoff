//=============================================================================
/*! 
    @addtogroup 
    @file       Convert.cpp
    @brief      文字操作系関数群
    
    Convertの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/06/23
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/06/23 Hi-ra Mizuno
      -# 作成
    - 2011/06/28
      -# ファイル名をJZStringからConvertに変更
    - 2011/08/25
      -# モノステートスタイルに変更
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "./Convert.h"
#include <vector>


//---------------------------------------------------------------------------
/*! 
	@brief Convert::StrAtoW

	char型からwchar_t型に変換する

	@param[in]      const char *c_pszStr_ :変換対象文字列
	@return         wchar_t*
	- 変換後文字列
	@exception      none
*/
//---------------------------------------------------------------------------
wchar_t* Convert::StrAtoW(const char *c_pszStr_)
{
	static std::vector<wchar_t> s_vwszBuff;
	size_t unLength = 0;

	if(s_vwszBuff.capacity() < ::strlen(c_pszStr_))
		s_vwszBuff.resize(::strlen(c_pszStr_) * sizeof(wchar_t));

	::mbstowcs_s(&unLength,&s_vwszBuff[0],s_vwszBuff.capacity(),c_pszStr_,_TRUNCATE);

	return &s_vwszBuff[0];
}


//---------------------------------------------------------------------------
/*! 
	@brief Convert::StrWtoA

	wchar_t型からchar型に変換する

	@param[in]      const wchar_t *c_pwszStr_ :変換対象文字列
	@return         char*
	- 変換後文字列
	@exception      none
*/
//---------------------------------------------------------------------------
char* Convert::StrWtoA(const wchar_t *c_pwszStr_)
{
	static std::vector<char> s_vszBuff;
	size_t unLength = 0;

	if(s_vszBuff.capacity() < ::wcslen(c_pwszStr_))
		s_vszBuff.resize(::wcslen(c_pwszStr_));

	if(::wcstombs_s(&unLength,&s_vszBuff[0],s_vszBuff.capacity(),c_pwszStr_,_TRUNCATE))
		return NULL;

	return &s_vszBuff[0];
}


//=============================================================================
//								End of File
//=============================================================================