//=============================================================================
/*! 
    @addtogroup 
    @file       Manhole.h
    @brief      マンホールオブジェクト
    
    Manholeクラスの定義
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/12/1
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/1 matsui
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_Manhole_H__
#define __INCLUDE_Manhole_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
static const char g_szManholeFilePath[] = "./Data/Graphics/Object/Manhole.png";


/*! @class Ladder */
class Manhole : public GameObject
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
	virtual ObjectType getObjType() const { return OBJ_MANHOLE; }

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	void setEnemyNum(int nEnemyNum_) {this->m_nEnemyNum = nEnemyNum_;}

	void setActive(bool bActive_) {this->m_bActive = bActive_;}

	//---------------------------------------------------------------------------
	/*! 
		@brief Manhole::Manhole

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Manhole();

	//---------------------------------------------------------------------------
	/*! 
		@brief Manhole::~Manhole

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Manhole();

	//---------------------------------------------------------------------------
	/*! 
		@brief Manhole::Initialize

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
		@brief Manhole::Release

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
		@brief Manhole::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Manhole::HandleEvent

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