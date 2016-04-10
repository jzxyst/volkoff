//=============================================================================
/*! 
    @addtogroup 
    @file       Exit_Lock.h
    @brief      鍵付き出口オブジェクト
    
    Exit_Lockクラスの定義
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/25
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/25 matsui
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_EXIT_LOCK_H__
#define __INCLUDE_EXIT_LOCK_H__


/*! @par include */
#include "./../GameObject.h"
#include "../../Frontend/GuideNamePlate.h"


/*! @par global */
static const char g_szExit_LockFilePath[] = "./Data/Graphics/Object/Exit_Lock.png";


/*! @class Exit_Lock */
class Exit_Lock : public GameObject
{
private:
	LBatchPanel mPanel;


	u32 mFlameCnt;

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_EXIT_LOCK; }

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Exit_Lock::Exit_Lock

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Exit_Lock();

	//---------------------------------------------------------------------------
	/*! 
		@brief Exit_Lock::~Exit_Lock

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Exit_Lock();

	//---------------------------------------------------------------------------
	/*! 
		@brief Exit_Lock::Initialize

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
		@brief Exit_Lock::Release

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
		@brief Exit_Lock::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Exit_Lock::HandleEvent

		イベント処理

		@param[in]      EventType event_ イベントタイプ
		@param[in]      void      *args_ データ(適当にキャストする)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	const LRect* getBoundingRect();

    /// 名前
    virtual const char* getName() const { return "Exit"; }

private:

    GuideNamePlate*     mGuideNamePlate;
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================