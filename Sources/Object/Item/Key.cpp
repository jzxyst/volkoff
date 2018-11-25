//=============================================================================
/*! 
    @addtogroup 
    @file       GateKey.cpp
    @brief     鍵オブジェクト
    
    GateKeyクラスの実装
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/27
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/27 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "./Key.h"



//---------------------------------------------------------------------------
/*! 
	@brief GateKey::GateKey

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
GateKey::GateKey()
    : mGuideNamePlate   ( NULL )
{
	mColRect.set( mPosition.x, mPosition.y, 40*mScale.x, 40*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::~GateKey

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
GateKey::~GateKey()
{
	this->Release();
}


void GateKey::setExit( bool f_ )
{
    GameObject::setExit( f_ );
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool GateKey::Initialize()
{
	this->Release();
	this->mScore = 500; 
	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->setCenterPoint(-20, 20, 0);
	this->mPanel->setTexture(Assets::loadTexture(g_szKeyFilePath));
	this->mPanel->setPosition(this->mPosition);
	this->mPanel->setVisible(true);


    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 1, 20, 0 );

    //printf( "◆ key h:%d p:%p\n", this->getHandle(), this );
         
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool GateKey::Release()
{
    SAFE_DELETE( mGuideNamePlate );
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool GateKey::Update()
{
	this->mPanel->setPosition(this->mPosition);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GateKey::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int GateKey::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// GateKey::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* GateKey::getBoundingRect()
{
	mColRect.set( mPosition.x, mPosition.y, 40*mScale.x, 40*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================