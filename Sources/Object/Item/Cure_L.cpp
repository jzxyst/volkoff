//=============================================================================
/*! 
    @addtogroup 
    @file       Cure_L.cpp
    @brief     回復　(大)オブジェクト
    
    Cure_Lクラスの実装
    
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
#include "./Cure_L.h"


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Cure_L

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_L::Cure_L()
    : mGuideNamePlate   ( NULL )
{
	this->mColRect.Set(
		this->mPosition.x+( 11 * this->mScale.x ),
		this->mPosition.y, ( 19 * this->mScale.x ) + ( 11 * this->mScale.x ),
		34 * this->mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::~Cure_L

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Cure_L::~Cure_L()
{
    
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_L::Initialize()
{
	this->Release();
	this->mScore = 1000;
	this->mPanel = Sprite3D::Create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-20, 20, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szCure_LFilePath));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_L::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Cure_L::Update()
{
	this->mPanel->SetPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Cure_L::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Cure_L::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// Ladder::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* Cure_L::getBoundingRect()
{
	this->mColRect.Set(
		this->mPosition.x+( 11 * this->mScale.x ),
		this->mPosition.y, ( 19 * this->mScale.x ) + ( 11 * this->mScale.x ),
		34 * this->mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================