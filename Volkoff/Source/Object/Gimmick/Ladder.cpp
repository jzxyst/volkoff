//=============================================================================
/*! 
    @addtogroup 
    @file       Ladder.cpp
    @brief      はしごオブジェクト
    
    Ladderクラスの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "./Ladder.h"


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Ladder

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Ladder::Ladder()
{
	mColRect.Set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::~Ladder

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Ladder::~Ladder()
{
	this->Release();
}


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
bool Ladder::Initialize()
{
	this->Release();

	this->mPanel = Sprite3D::Create(60.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-30, 10, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szLaderFilePath));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);




	return true;
}


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
bool Ladder::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Ladder::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Ladder::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


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
int Ladder::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// Ladder::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* Ladder::getBoundingRect()
{
	mColRect.Set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================