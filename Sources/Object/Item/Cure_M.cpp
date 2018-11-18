//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_M.cpp
    @brief     回復　(中)オブジェクト
    
    Cure_Mクラスの実装
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/31
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/31 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "./Cure_M.h"


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Cure_M

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_M::Cure_M()
    : mGuideNamePlate   ( NULL )
{
	mColRect.Set( mPosition.x+(13*mScale.x), mPosition.y, (15*mScale.x)+(13*mScale.x), 27*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::~Cure_M

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_M::~Cure_M()
{
	this->Release();
}


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
bool Cure_M::Initialize()
{
	this->Release();
	this->mScore = 500;
	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-20, 20, 0);
	this->mPanel->SetTexture(Assets::loadTexture(g_szCure_MFilePath));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

	return true;
}


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
bool Cure_M::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_M::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_M::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


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
int Cure_M::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// Cure_M::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* Cure_M::getBoundingRect()
{
	mColRect.Set( mPosition.x+(13*mScale.x), mPosition.y, (15*mScale.x)+(13*mScale.x), 27*mScale.y );

	return &mColRect;
}



//=============================================================================
//								End of File
//=============================================================================