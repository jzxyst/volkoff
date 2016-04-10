//=============================================================================
/*! 
    @addtogroup 
    @file       Entry.cpp
    @brief      入口オブジェクト
    
    Entryクラスの定義
    
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


/*! @par include */
#include "stdafx.h"
#include "./Entry.h"


//---------------------------------------------------------------------------
/*! 
	@brief Entry::Entry

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Entry::Entry()
{
}


//---------------------------------------------------------------------------
/*! 
	@brief Entry::~Entry

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Entry::~Entry()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Entry::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Entry::Initialize()
{
	this->Release();

	this->mPanel = Sprite3D::Create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-70, 40, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szEntryFilePath));
	this->mPanel->SetSrcRect(LRect(0,0,140,80));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);
	this->mFlameCnt = 0;
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Entry::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Entry::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Entry::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Entry::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	++mFlameCnt;

	if(mFlameCnt == 1)
	{
		GameAudio::PlaySE("./Data/Sound/SE/doorclose2.wav",1.00,1.00);
		GameAudio::PlaySE("./Data/Sound/SE/doorclose3.wav",0.90,0.80);	
	}
	if(mFlameCnt <= 5)
	{
		this->mPanel->SetSrcRect(LRect(this->mFlameCnt * 140,0,140,80));
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Entry::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Entry::HandleEvent(u32 event_,void *args_)
{
	return true;
}



//=============================================================================
//								End of File
//=============================================================================