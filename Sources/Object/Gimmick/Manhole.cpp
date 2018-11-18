//=============================================================================
/*! 
    @addtogroup 
    @file       Manhole.cpp
    @brief      マンホールオブジェクト
    
    Manholeクラスの実装
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/12/1
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/1 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "./Manhole.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"



//---------------------------------------------------------------------------
/*! 
	@brief Manhole::Manhole

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Manhole::Manhole()
{
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Manhole::~Manhole

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Manhole::~Manhole()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Manhole::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Manhole::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(40.0f,40.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-20, 20, 0);
	this->mPanel->SetTexture(Assets::loadTexture(g_szManholeFilePath));
	this->mPanel->setSourceRect(LRect(0,0,40,40));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Manhole::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Manhole::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Manhole::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Manhole::Update()
{
	++this->m_nFrame;
	this->mPanel->SetPosition(this->mPosition);

	//発動条件（適当）//上下差が200以下 かつ 左右差が10以下
	const int y = 100;
	const int x = 200;
	LVector3 myPos = this->mPosition;
	myPos.x += 50;
	myPos.y -= 50;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && this->m_bActive && !this->m_bStart)
	{
		GameAudio::PlaySE("./Data/Sound/SE/manhole03.wav",1.00,1.50);
		GameAudio::PlaySE("./Data/Sound/SE/manhole02.wav",1.00,1.30);
		GameAudio::PlaySE("./Data/Sound/SE/manhole01.wav",1.00,1.00);
		this->m_bStart = true;
	}

	if(this->m_bActive)
	{
		if(this->m_bStart)
		{
			//アニメーション
			if(this->m_nAnime < 4)
			{
				this->m_nAnime++;
				this->mPanel->setSourceRect(LRect(this->m_nAnime * 40,0,40,40));
			}

			//敵出現
			if(!(this->m_nFrame % 8)) //2フレームに1回
			{
				if(this->m_nEnemyNum)
				{
					Enemy* pEnemy = Enemy::createRandom();
					pEnemy->setPosition(LVector3(this->mPosition.x + 40,this->mPosition.y - 42,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 40,this->mPosition.y - 42,this->mPosition.z));
					pEnemy->setVelocity(LVector3(::rand() % 10 - 5,10,0));
                    Enemy::CreateData data;

					this->m_nEnemyNum -= 1;
				}
			}
		}

	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Manhole::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Manhole::HandleEvent(u32 event_,void *args_)
{
	return true;
}


//=============================================================================
//								End of File
//=============================================================================