//=============================================================================
/*! 
    @addtogroup 
    @file       Exit.cpp
    @brief      出口オブジェクト
    
    Exitクラスの定義
    
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
#include "./Exit.h"


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Exit

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit::Exit()
    : mGuideNamePlate   ( NULL )
{
	mColRect.Set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::~Exit

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Exit::~Exit()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(140.0f,80.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-70, 40, 0);
	this->mPanel->SetTexture(Assets::loadTexture(g_szExitFilePath));
	this->mPanel->setSourceRect(LRect(0,0,140,80));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 2, 70, 20 );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Exit::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Exit::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Exit::HandleEvent(u32 event_,void *args_)
{
	return true;
}
const LRect* Exit::getBoundingRect()
{
	mColRect.Set( mPosition.x+40, mPosition.y, 60*mScale.x, 80*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================