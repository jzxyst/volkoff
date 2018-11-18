//=============================================================================
/*! 
    @addtogroup 
    @file       Grenade.cpp
    @brief     弾オブジェクト
    
    Grenadeクラスの実装
    
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
#include "./Grenade.h"
#include "./Player.h"
#include "./../Effect/Effect_1.h"
#include "./attackedobject.h"
#include "../Map/MapManager.h"
#include"../Game/GameManager.h"
//---------------------------------------------------------------------------
/*! 
	@brief Grenade::Grenade

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Grenade::Grenade()
{
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::~Grenade

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Grenade::~Grenade()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Grenade::Initialize()
{
	//setAttackedGroup( ATKGROUP_ENEMY );
	this->Release();
	this->mScore = 0; 
	this->mPanel = LBatchPanel::create(20.0f,20.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-10, 10, 0);
	this->mPanel->SetTexture(Assets::loadTexture(g_szGrenadeFilePath/*,0xffffffff*/));
	this->mPanel->SetPosition(this->mPosition);
	this->mPanel->SetVisible(true);
	this->mFrameCnt = 0;
	this->mGeneObjType = OBJ_CHARACTER;
	this->mRangeRate = 1;
	this-> mCriticalRate = 1;
	this->mBrowVec = Vector3::Zero;
	this->mStunFrame = 0;
	this->mDamage = 1;
	this->mFallSpeed = 0;
	this->mRandStun = 1;
	this->mRandBrowX = 1;
	this->mRandBrowY = 1;
	//this->mGeneObjType = OBJ_ENEMY;
	//this->setObjType(OBJ_Grenade);
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Grenade::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Grenade::Update()
{

	//mVelocity 
	//mVelocity.x=100;
	mVelocity.y-= mFallSpeed;
	if((this->getDirection()==CHARADIR_LEFT)&&(mFrameCnt == 0))
	{
		mVelocity.x*=-1;
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

	LRect AttackLect;

	AttackLect.x = rect.x -80;
	AttackLect.y = rect.y +40;
	AttackLect.width = 160;
	AttackLect.height = 160;

	++mFrameCnt;



	//一応範囲外にいったら消す
	if((this->getPosition().x>=2000)||(this->getPosition().y>=2000)||(this->getPosition().x<=0)||(this->getPosition().y<=0))
	{
		this->setExit(true);
	}
	bool result = MapManager::getInstance()->BulletCollision(rect);  
	if(result)
	{
		//printf("グレネード内damage%d\n",mDamage);
		LVector3 v(this->mPosition);
		v.z = 0.f;
		new Effect_Explosion(v);
		GameAudio::PlaySE("./Data/Sound/SE/Explosion01.ogg",0.30,1.30);

		HitObjectList*  obj_list;
		if(this->mGeneObjType == OBJ_CHARACTER)
		{
			setAttackedGroup( ATKGROUP_PLAYER );
			obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(AttackLect,OBJ_ENEMY);
		}
		else
		{
			setAttackedGroup( ATKGROUP_ENEMY );
			obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(AttackLect,OBJ_CHARACTER);	
		}
		if ( obj_list->size() > 0 )
		{
			HitObjectList::iterator itr = obj_list->begin();
			HitObjectList::iterator end = obj_list->end();
			for ( ; itr != end; ++itr )
			{
				if(this->mGeneObjType == OBJ_CHARACTER)
				{
					//なぜかプレイヤーにあたるので
				//	if((*itr)->getObjType() != OBJ_CHARACTER)
				//	{	
						(*itr)->attackEffect(this,mDamage,mRangeRate,mCriticalRate,LVector3(mBrowVec.x+rand()%mRandBrowX,mBrowVec.y+rand()%mRandBrowY,0),mStunFrame+rand()%mRandStun);	
				//	}
				}
				else
				{
					GameManager::getInstance()->getPlayer()->attackEffect(this,mDamage,mRangeRate,mCriticalRate,LVector3(mBrowVec.x+rand()%mRandBrowX,mBrowVec.y+rand()%mRandBrowY,0),mStunFrame+rand()%mRandStun);			
				}
				this->setExit(true);
				//GameObjectManager::getInstance()->deleteObject( this );	
			}
			return 1;
	    }
		this->setExit(true);
		//GameObjectManager::getInstance()->deleteObject( this );
	}
	return 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Grenade::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Grenade::HandleEvent(u32 event_,void *args_)
{
	return true;
}

//
// Grenade::getBoundingRect
//
// 当たり判定を返す
//
const LRect* Grenade::getBoundingRect()
{
	mColRect.Set( mPosition.x+8, mPosition.y-8, 4, 4 );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================
