//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_M.h
    @brief      回復（中）オブジェクト
    
    Cure_Mクラスの定義
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/10/31
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/31matsui
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_CURE_M_H__
#define __INCLUDE_CURE_M_H__


/*! @par include */
#include "./../GameObject.h"
#include "../../Frontend/GuideNamePlate.h"


/*! @par global */
static const char g_szCure_MFilePath[] = "./Data/Graphics/Object/Cure_M.png";


/*! @class Ladder */
class Cure_M : public GameObject
{
private:
	LBatchPanel mPanel;

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_CURE_M; }

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Cure_M::Cure_M

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Cure_M();

	//---------------------------------------------------------------------------
	/*! 
		@brief Cure_M::~Cure_M

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Cure_M();

	//---------------------------------------------------------------------------
	/*! 
		@brief Cure_M::Initialize

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
		@brief Cure_M::Release

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
		@brief Cure_M::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Cure_M::HandleEvent

		イベント処理

		@param[in]      EventType event_ イベントタイプ
		@param[in]      void      *args_ データ(適当にキャストする)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	// Cure_M::getBoundingRect
	//
	// 細田追加・当たり判定を返す
	//
	const LRect* getBoundingRect();

    /// 名前
    virtual const char* getName() const { return "Recover 2"; }

private:

    GuideNamePlate*     mGuideNamePlate;
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================