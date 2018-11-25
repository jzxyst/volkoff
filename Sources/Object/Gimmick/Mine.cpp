//=============================================================================
/*! 
    @addtogroup 
    @file       Mine.cpp
    @brief      地雷オブジェクト
    
    Mineクラスの実装
    
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
#include "./Mine.h"
#include "./../../Game/GameManager.h"
#include "./../Player.h"
#include "./../../Effect/Effect_1.h"
#include "./../attackedobject.h"


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Mine

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Mine::Mine()
{
	this->m_bActive = false;
	this->m_bStart = false;
	this->m_nAnime = 0;
	this->m_nEnemyNum = 0;
	this->m_nFrame = 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::~Mine

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Mine::~Mine()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Initialize()
{
	this->Release();

	this->mPanel = LBatchPanel::create(20.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->setCenterPoint(-10, 10, 0);
	this->mPanel->setTexture(Assets::loadTexture(g_szMineFilePath));
	this->mPanel->setPosition(this->mPosition);
	this->mPanel->setVisible(true);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Mine::Update()
{
	++this->m_nFrame;
	this->mPanel->setPosition(this->mPosition);

	//発動条件（適当）//上下差が200以下 かつ 左右差が10以下
	const int y = 20;
	const int x = 6;
	LVector3 myPos = this->mPosition;
	myPos.x += 10;
	//myPos.y -= 50;
	if(::abs(GameManager::getInstance()->getPlayer()->getPosition().y - myPos.y) <= y && abs(myPos.x - GameManager::getInstance()->getPlayer()->getPosition().x) <= x && !this->m_bStart)
	{
		LVector3 v(this->mPosition);
		v.z = 0.f;
		new Effect_Explosion(v);
		this->m_bStart = true;

		//ダメージを与えたい場合はここに書く
		GameManager::getInstance()->getPlayer()->attackEffect(GameManager::getInstance()->getPlayer(),100,1,1,LVector3(0,6,0),65);
		GameAudio::playSE("./Data/Sound/SE/Explosion01.ogg",0.50,1.30);
		//ここまで

		GameObjectManager::getInstance()->deleteObject(this);
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Mine::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Mine::HandleEvent(u32 event_,void *args_)
{
	return true;
}


//=============================================================================
//								End of File
//=============================================================================