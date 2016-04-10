//=============================================================================
/*! 
    @addtogroup 
    @file       Singleton.h
    @brief      Singletonクラスヘッダ
    
    Singletonテンプレートクラス
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/06/20
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
//=============================================================================
    @par        History
    - 2011/06/20 Hi-ra Mizuo
      -# 作成
    - 2011/06/28 Hi-ra Mizuno
      -# JZXから除外
*/
//=============================================================================


/*! @par Include Guard */
#ifndef __INCLUDE_SINGLETON_H__
#define __INCLUDE_SINGLETON_H__


/*! @par include */


/*! @class Singleton
    @brief Singletonクラス

	シングルトンを平易に実装するテンプレートクラス
*/
template <typename Ty> class Singleton
{
public:
	/*! @par publicメンバ変数 */

private:
	/*! @par privateメンバ変数 */


private:
	/*! @par 例外処理 */
	Singleton(const Singleton &obj);

	Singleton &operator = (const Singleton &obj);

public:
	/*! @par コンストラクタ・デストラクタ */

protected:
	/*! @par Singleton */
	//---------------------------------------------------------------------------
	/*! 
		@brief Singleton::Singleton
	
	    デフォルトコンストラクタ
	
		@param[in]      void
	    @return         none
	    @exception      none
	*/
	//---------------------------------------------------------------------------
	Singleton() {;}

	//---------------------------------------------------------------------------
	/*! 
		@brief Singleton::~Singleton
	
	    デストラクタ
	
		@param[in]      void
	    @return         none
	    @exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~Singleton() {;}

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! 
		@brief Singleton::getInstance
	
	    インスタンスを返す
	
		@param[in]      void
	    @return         Ty*
	    @exception      none
	*/
	//---------------------------------------------------------------------------
	static Ty* getInstance() {static Ty CInstance; return &CInstance;}

private:
	/*! @par privateメンバ関数 */

};


#endif //End of Include Guard


//=============================================================================
//								End of File
//=============================================================================