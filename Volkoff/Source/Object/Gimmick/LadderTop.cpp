//=============================================================================
/*! 
    @addtogroup 
    @file       LadderTop.cpp
    @brief      はしごオブジェクト
    
    LadderTopクラスの実装
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "./LadderTop.h"


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::LadderTop

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
LadderTop::LadderTop()
{
	mColRect.Set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::~LadderTop

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
LadderTop::~LadderTop()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool LadderTop::Initialize()
{
	this->Release();

	this->mPanel = Sprite3D::Create(60.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-30, 10, 0);
	this->mPanel->SetTexture(Assets::LoadTexture("./Data/Graphics/Object/Ladder.png"));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool LadderTop::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool LadderTop::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief LadderTop::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int LadderTop::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// LadderTop::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* LadderTop::getBoundingRect()
{
	mColRect.Set( mPosition.x, mPosition.y, 60*mScale.x, 40*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================