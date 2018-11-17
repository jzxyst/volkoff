//=============================================================================
/*! 
    @addtogroup 
    @file       Locker.h
    @brief      ロッカーオブジェクト
    
    Lockerクラスの定義
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/11/2
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/2 matsui
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_LOCKER_H__
#define __INCLUDE_LOCKER_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */

static const char g_szLockerFilePath[] = "./Data/Graphics/Object/Locker.png";


/*! @class Locker */
class Locker : public GameObject
{
private:
	LBatchPanel mPanel;
	bool m_bActive;
	bool m_bStart;
	int m_nAnime;
	int m_nEnemyNum;
	int m_nFrame;

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_LOCKER; }

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	void setEnemyNum(int nEnemyNum_) {this->m_nEnemyNum = nEnemyNum_;}

	void setActive(bool bActive_) {this->m_bActive = bActive_;}

	//---------------------------------------------------------------------------
	/*! 
		@brief Locker::Locker

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Locker();

	//---------------------------------------------------------------------------
	/*! 
		@brief Locker::~Locker

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Locker();

	//---------------------------------------------------------------------------
	/*! 
		@brief Locker::Initialize

		初期化処理

		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize();

	//---------------------------------------------------------------------------
	/*! 
		@brief Locker::Release

		終了処理

		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief Locker::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Locker::HandleEvent

		イベント処理

		@param[in]      EventType event_ イベントタイプ
		@param[in]      void      *args_ データ(適当にキャストする)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================