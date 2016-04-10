//=============================================================================
/*! 
    @addtogroup 
    @file       File.h
    @brief      Fileクラスヘッダ
    
    ファイル操作をより平易にするクラス
    
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
    - 2011/06/28 Hi-ra Mizuno
      -# JZXから除外
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_FILE_H__
#define __INCLUDE_FILE_H__


/*! @par include */
#include <iostream>
#include <stdlib.h>
#include <vector>

namespace JZX
{

/*! @enum FileParam
    @brief  エラーコード
*/
typedef enum _ENUM_FILE_PARAM
{
	FILE_UNDEF = 0,
	FILE_OPEN_SUCCEED,
	FILE_OPEN_FAILED
}FileParam;


/*! @class File
	@brief Fileクラス

	ファイル操作をより平易にするクラス
*/
class File
{
public:
	/*! @par publicメンバ変数 */

private:
	/*! @par privateメンバ変数 */
	std::string m_strFileName;
	std::string m_strMode;

	std::vector<char> m_vszMode;
	FILE *m_pfFile;
	fpos_t m_nSize;

	FileParam m_eFileParam;


public:
	/*! @par 例外処理 */


public:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief File::File
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	File();

	//---------------------------------------------------------------------------
	/*! 
		@brief File::File
	
		コンストラクタ
	
		@param[in]      const char *c_pszFileName_ :ファイルパス
		@param[in]      const char *c_pszMode_     :モード
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	File(const char *c_pszFileName_,const char *c_pszMode_);

	//---------------------------------------------------------------------------
	/*! 
		@brief File::File
	
		コンストラクタ
	
		@param[in]      const wchar_t *c_pwszFileName_ :ファイルパス
		@param[in]      const char *c_pszMode_         :モード
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	File(const wchar_t *c_pwszFileName_,const char *c_pszMode_);

	//---------------------------------------------------------------------------
	/*! 
		@brief File::~File
	
		デストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~File();

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	FILE* getFile() const {return this->m_pfFile;}

	fpos_t getSize() const {return this->m_nSize;}

	FileParam getFileParam() const {return this->m_eFileParam;}

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief File::Open
	
		ファイルを開く
	
		@param[in]      const char *c_pszFileName_ :ファイルパス
		@param[in]      const char *c_pszMode_     :モード
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Open(const char *c_pszFileName_,const char *c_pszMode_);

	//---------------------------------------------------------------------------
	/*! 
		@brief File::Close
	
		ファイルを閉じる
	
		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Close();

private:
	/*! @par privateメンバ関数 */

};

} // namespace JZX

//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================