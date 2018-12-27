//=============================================================================
/*! 
    @addtogroup 
    @file       Box.h
    @brief      箱オブジェクト
    
    Boxクラスの定義
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/10/26
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/26 matsui
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_BOX_H__
#define __INCLUDE_BOX_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
static const char g_szBoxFilePath[] = "./Data/Graphics/Object/Box.png";


/*! @class Ladder */
class Box : public AttackedObject
{
private:
    Ref<LBatchPanel> mPanel;
	int m_nAnime;
	int m_nFrame;
	bool m_bCreate;
public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_BOX; }

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::Box

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Box();

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::~Box

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Box();

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::Initialize

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
		@brief Box::Release

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
		@brief Box::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::HandleEvent

		イベント処理

		@param[in]      EventType event_ イベントタイプ
		@param[in]      void      *args_ データ(適当にキャストする)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	// Box::getBoundingRect
	//
	// 細田追加・当たり判定を返す
	//
	const LRect* getBoundingRect();
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================