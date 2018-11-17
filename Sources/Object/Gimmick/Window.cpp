//=============================================================================
/*! 
    @addtogroup 
    @file       Window.cpp
    @brief      窓オブジェクト
    
    Windowクラスの定義
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/22
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/22 matsui
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "./Window.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../Enemy.h"


//---------------------------------------------------------------------------
/*! 
	@brief Window::Window

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Window::Window()
{
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::~Window

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Window::~Window()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Window::Initialize()
{
	this->Release();

	this->mPanel = Sprite3D::Create(128.0f,192.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-64, 96, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szWindowFilePath));
	this->mPanel->SetSrcRect(LRect(0,0,128,192));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Window::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Window::Update()
{
	++this->m_nFrame;
	this->mPanel->SetPosition(this->mPosition);

	//発動条件（適当）//上下差が200以下 かつ 左右差が10以下
	const int y = 150;
	const int x = 100;
	LVector3 myPos = this->mPosition;
	myPos.x += 50;
	myPos.y -= 100;
	if(abs(myPos.y - GameManager::getInstance()->getPlayer()->getPosition().y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && this->m_bActive && !this->m_bStart)
	{
		//Enemy *pEnemy = NULL;
		//for(int i = 0;i < this->m_nEnemyNum;++i)
		//{
		//	pEnemy = Enemy::create(NULL);
		//	pEnemy->setPosition(LVector3(this->getPosition().x + 62,this->getPosition().y - 80,this->getPosition().z));
		//	pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));
		//}

		GameAudio::PlaySE("./Data/Sound/SE/crash_grass2.wav",0.60,0.30);
		GameAudio::PlaySE("./Data/Sound/SE/crash_grass2.wav",0.60,0.50);
		GameAudio::PlaySE("./Data/Sound/SE/crash_grass2.wav",0.60,0.65);
		GameAudio::PlaySE("./Data/Sound/SE/crash_grass2.wav",0.60,1.00);
		GameAudio::PlaySE("./Data/Sound/SE/crash_grass2.wav",0.60,0.80);
		this->m_bStart = true;
	}

	if(this->m_bActive)
	{
		if(this->m_bStart)
		{
			//窓アニメーション
			if(this->m_nAnime < 8)
			{
				this->m_nAnime++;
				this->mPanel->SetSrcRect(LRect(this->m_nAnime * 128,0,128,192));
			}

			//敵出現
			if(!(this->m_nFrame % 6)) //2フレームに1回
			{
				if(this->m_nEnemyNum)
				{
					Enemy* pEnemy = Enemy::createRandom();
					pEnemy->setPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
					pEnemy->setDefPosition(LVector3(this->mPosition.x + 62,this->mPosition.y - 80,this->mPosition.z));
					pEnemy->setVelocity(LVector3(::rand() % 10 - 5,0,0));

					this->m_nEnemyNum -= 1;
				}
			}
		}

	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Window::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Window::HandleEvent(u32 event_,void *args_)
{
	return true;
}



//=============================================================================
//								End of File
//=============================================================================
