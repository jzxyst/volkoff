//=============================================================================
/*! 
    @addtogroup 
    @file       Ladder.h
    @brief      はしごオブジェクト
    
    Ladderクラスの定義
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/17
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/17 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_LADDER_H__
#define __INCLUDE_LADDER_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
static const char g_szLaderFilePath[] = "./Data/Graphics/Object/Ladder.png";


/*! @class Ladder */
class Ladder : public GameObject
{
private:
	LBatchPanel mPanel;

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_LADDER; }

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Ladder::Ladder

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Ladder();

	//---------------------------------------------------------------------------
	/*! 
		@brief Ladder::~Ladder

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Ladder();

	//---------------------------------------------------------------------------
	/*! 
		@brief Ladder::Initialize

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
		@brief Ladder::Release

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
		@brief Ladder::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Ladder::HandleEvent

		イベント処理

		@param[in]      EventType event_ イベントタイプ
		@param[in]      void      *args_ データ(適当にキャストする)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	// Ladder::getBoundingRect
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