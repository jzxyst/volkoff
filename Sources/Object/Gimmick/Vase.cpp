//=============================================================================
/*! 
    @addtogroup 
    @file       Vase.cpp
    @brief      花瓶オブジェクト
    
    Vaseクラスの実装
    
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
#include "./Vase.h"
//#include "./Item/Cure_L.h"
#include "./../Player.h"
#include "./../../Game/GameManager.h"

//---------------------------------------------------------------------------
/*! 
	@brief Vase::Vase

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Vase::Vase()
{
	setAttackedGroup( ATKGROUP_ENEMY );
	mColRect.Set( mPosition.x+11, mPosition.y-7, 18*mScale.x, 33*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::~Vase

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Vase::~Vase()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Vase::Initialize()
{
	this->Release();
	this->mScore = 250;
	this->mPanel = Sprite3D::Create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-20, 20, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szVaseFilePath));
	this->mPanel->SetSrcRect(LRect(0,0,40,40));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

	this->mLife = 1;
	this->m_nAnime = 0;
	this->m_nFrame = 0;
	this->m_bCreate = false;
	this->mScore = 300;

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Vase::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Vase::Update()
{

	if ( this->mLife > 0 )
	{
		this->mPanel->SetPosition(this->mPosition);
	}



	if ( this->mLife <= 0)
	{
		this->mLife = 0;
		this->m_nFrame++;
		if(m_nFrame==1)
		{
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 
            
			GameAudio::PlaySE("./Data/Sound/SE/crash_grass2.wav",0.80,1.00);
			GameAudio::PlaySE("./Data/Sound/SE/crash_grass2.wav",0.80,1.30);
		}
		if(m_nFrame%1==0)
		{
			this->m_nAnime++;
			this->mPanel->SetSrcRect(LRect(this->m_nAnime * 40,0,40,40));
		}

		if(m_nAnime >=5)
		{
			this->setExit( true );
		}
		
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Vase::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Vase::HandleEvent(u32 event_,void *args_)
{
	AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
	{
		case EV_APPLY_DAMAGE:
			// ダメージ受けた時
			this->mLife -= 50;
			break;
	}

	return true;
}

// Box::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* Vase::getBoundingRect()
{
	mColRect.Set( mPosition.x+11, mPosition.y-7, 18*mScale.x, 33*mScale.y );

	return &mColRect;
}



//=============================================================================
//								End of File
//=============================================================================