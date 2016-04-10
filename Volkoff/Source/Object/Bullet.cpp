//=============================================================================
/*! 
    @addtogroup 
    @file       Bullet.cpp
    @brief     弾オブジェクト
    
    Bulletクラスの実装
    
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
#include "stdafx.h"
#include "./Bullet.h"
#include "./Player.h"
#include "./../Effect/Effect_1.h"
#include "./attackedobject.h"
#include "../Map/MapManager.h"
#include"../Game/GameManager.h"
//---------------------------------------------------------------------------
/*! 
	@brief Bullet::Bullet

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Bullet::Bullet()
{
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::~Bullet

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Bullet::~Bullet()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Bullet::Initialize()
{
	//setAttackedGroup( ATKGROUP_ENEMY );
	this->Release();
	this->mScore = 0; 
	this->mPanel = Sprite3D::Create(20.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-10, 10, 0);
	this->mPanel->SetTexture(Assets::LoadTexture(g_szBulletFilePath/*,0xffffffff*/));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);
	this->mLife = 1;
	this->mFrameCnt = 0;
	this->mLifeFrame = 0;
	this->mGeneObjType = OBJ_CHARACTER;
	this->mRangeRate = 1;
	this-> mCriticalRate = 1;
	this->mBrowVec = Vector3::Zero;
	this->mStunFrame = 0;
	this->mDamage = 1;
	this->mSeVol = 0.30;
	//this->mGeneObjType = OBJ_ENEMY;
	//this->setObjType(OBJ_BULLET);
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Bullet::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Bullet::Update()
{

	//mVelocity 
	//mVelocity.x=100;
	if((this->getDirection()==CHARADIR_LEFT)&&(mFrameCnt == 0))
	{
		//mVelocity*=-1;
		//mBrowVec*=-1;
	}
	mPosition+=mVelocity;
	this->mPanel->SetPosition(this->mPosition );
	//printf("x%f,  y%f\n",mVelocity.x,mVelocity.y);
//	printf("x%f,  y%f\n",getPosition().x+8,getPosition().y+8);
    //float dx, dy;
    //u32 result = judgeCollisionToMap( &dx, &dy );
	LRect rect;
	rect.x=mPosition.x+8;
	rect.y=mPosition.y-8;
	rect.width=4;
	rect.height=4;

	++mFrameCnt;
	//寿命が来たら弾を消す
	if((mLifeFrame!=0)&&(mFrameCnt>=mLifeFrame))
	{
		GameObjectManager::getInstance()->deleteObject( this );		
	}

	if(this->mLife<=0)
	{
		LVector3 v(this->mPosition);
		v.z = 0.f;
		new Effect_Explosion2(v);
		GameAudio::PlaySE("./Data/Sound/SE/Explosion01.ogg",mSeVol,1.80);
		GameObjectManager::getInstance()->deleteObject( this );	
		//printf("sibou\n");
		this->setExit(true);
	}
	//一応範囲外にいったら消す
	if((this->getPosition().x>=2000)||(this->getPosition().y>=2000)||(this->getPosition().x<=0)||(this->getPosition().y<=0))
	{
		this->setExit(true);
	}


	HitObjectList*  obj_list;
	if(this->mGeneObjType == OBJ_CHARACTER)
	{
		setAttackedGroup( ATKGROUP_PLAYER );
		obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(rect,OBJ_ENEMY);
	}
	else
	{
		setAttackedGroup( ATKGROUP_ENEMY );
		obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(rect,OBJ_CHARACTER);	
	}
    if ( obj_list->size() > 0 )
    {
        // 当たったオブジェクトのハンドルを 

        int idx = 1;
        HitObjectList::iterator itr = obj_list->begin();
        HitObjectList::iterator end = obj_list->end();
        for ( ; itr != end; ++itr )
        {
		//	printf("敵hit\n");
			if(this->mGeneObjType == OBJ_CHARACTER)
			{
				(*itr)->attackEffect(this,mDamage,mRangeRate,mCriticalRate,mBrowVec,mStunFrame);	
			}
			else
			{
				GameManager::getInstance()->getPlayer()->attackEffect(this,mDamage,mRangeRate,mCriticalRate,mBrowVec,mStunFrame);			
			}
			LVector3 v(this->mPosition);
			v.z = 0.f;
			new Effect_Explosion2(v);
			GameAudio::PlaySE("./Data/Sound/SE/Explosion01.ogg",mSeVol,1.80);
			this->setExit(true);
			//GameObjectManager::getInstance()->deleteObject( this );	
        }
        return 1;
    }


	bool result = MapManager::getInstance()->BulletCollision(rect);      
	if(result)
	{
		//LVector3 v(this->mPosition);
		//v.z = 0.f;
		//new Effect_Explosion2(v);
		//GameAudio::PlaySE("./Data/Sound/SE/Explosion01.ogg",0.30,1.80);
		this->setExit(true);
		//GameObjectManager::getInstance()->deleteObject( this );
	}
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Bullet::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Bullet::HandleEvent(u32 event_,void *args_)
{
	AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
	{
		case EV_APPLY_DAMAGE:
			// ダメージ受けた時
			this->mLife -= 1;
			break;
	}

	return true;
}

//
// Bullet::getBoundingRect
//
// 当たり判定を返す
//
const LRect* Bullet::getBoundingRect()
{
	mColRect.Set( mPosition.x+8, mPosition.y-8, 4, 4 );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================
