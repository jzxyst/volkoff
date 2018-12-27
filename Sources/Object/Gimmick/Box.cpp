//=============================================================================
/*! 
    @addtogroup 
    @file       Box.cpp
    @brief     箱オブジェクト
    
    Boxクラスの実装
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/10/26
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/26 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "./Box.h"
#include "./../Weapon.h"
#include "./../Player.h"
#include "./../../Game/GameManager.h"

//---------------------------------------------------------------------------
/*! 
	@brief Box::Box

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
::Box::Box()
{
	// 攻撃対象グループは敵側
    setAttackedGroup( ATKGROUP_ENEMY );
	mColRect.set( mPosition.x+20, mPosition.y-20, 60*mScale.x, 60*mScale.y );
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::~Box

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
::Box::~Box()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool ::Box::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(100.0f,80.0f);
    this->mPanel->setCenterPoint(-50, 40, 0);
	this->mPanel->setTexture(Assets::loadTexture(g_szBoxFilePath));
	this->mPanel->setSourceRect(LRect(0,0,100,80));
	this->mPanel->setPosition(this->mPosition);
	this->mPanel->setVisible(true);

	this->mLife = 1;
	this->m_nAnime = 0;
	this->m_nFrame = 0;
	this->m_bCreate = false;
	this->mScore = 500;

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool ::Box::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool ::Box::Update()
{
	if ( this->mLife > 0 )
	{
		this->mPanel->setPosition(this->mPosition);
	}



	if ( this->mLife <= 0)
	{
		this->mLife = 0;
		this->m_nFrame++;
		if(m_nFrame==1)
		{
			GameAudio::playSE("./Data/Sound/SE/don01.wav",0.50,1.70);
			GameAudio::playSE("./Data/Sound/SE/don01.wav",0.50,1.20);
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 
    
		}
		if(m_nFrame%2==0)
		{
			this->m_nAnime++;
			this->mPanel->setSourceRect(LRect(this->m_nAnime * 100,0,100,80));
		}

		if(m_nAnime >=5)
		{
			this->setExit( true );
		}
		
	}

	//アイテムを出す
	if ( this->mLife <= 0 && !this->m_bCreate)
	{
		// 出現率の総和
		int rate_max = 0;
		for ( int i = 0; i < WEAPON_NORMAL_MAX_NUM; ++i )
		{
			if ( gWeaponBaseData[ i ].BoxRate )
			{
				rate_max += gWeaponBaseData[ i ].BoxRate;
			}
		}

		// 値をひとつ決める
		int value = rand() % rate_max;

		// 値に対応する武器を探す
		int i = 0;
		for ( ; 0 < WEAPON_NORMAL_MAX_NUM; ++i )
		{
			int rating = gWeaponBaseData[ i ].BoxRate;
			if ( rating > 0 )
			{
				if ( rating > value )
				{
					break;
				}
				value -= rating;
			}
		}

		if(i)
		{
			Weapon::CreateData wdata;

			wdata.Data.WeaponType  = static_cast<WeaponType>(i);
			wdata.Data.UseCount    = gWeaponBaseData[i].UseCount;

			LVector3 v = this->mPosition;
			//v.y += 100;
			wdata.Position = v;
			Weapon::create( &wdata );
		}

		this->m_bCreate = true;
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Box::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int ::Box::HandleEvent(u32 event_,void *args_)
{
	AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
	{
		case EV_APPLY_DAMAGE:
			// ダメージ受けた時
			this->mLife -= 50;
			break;
	}

	//if ( this->mLife <= 0 )
	//{
	//	this->mLife = 0;
	//		this->setExit( true );
	//		return true;
	//}

	return true;
}

//
// Box::getBoundingRect
//
// 細田追加・当たり判定を返す
//
const LRect* ::Box::getBoundingRect()
{
	mColRect.set( mPosition.x+20, mPosition.y-20, 60*mScale.x, 60*mScale.y );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================