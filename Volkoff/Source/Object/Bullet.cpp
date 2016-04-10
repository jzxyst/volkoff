//=============================================================================
/*! 
    @addtogroup 
    @file       Bullet.cpp
    @brief     �e�I�u�W�F�N�g
    
    Bullet�N���X�̎���
    
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
      -# �쐬
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

	�f�t�H���g�R���X�g���N�^

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

	�f�X�g���N�^

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

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
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

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
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

	�t���[���X�V����

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
	//������������e������
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
	//�ꉞ�͈͊O�ɂ����������
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
        // ���������I�u�W�F�N�g�̃n���h���� 

        int idx = 1;
        HitObjectList::iterator itr = obj_list->begin();
        HitObjectList::iterator end = obj_list->end();
        for ( ; itr != end; ++itr )
        {
		//	printf("�Ghit\n");
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

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
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
			// �_���[�W�󂯂���
			this->mLife -= 1;
			break;
	}

	return true;
}

//
// Bullet::getBoundingRect
//
// �����蔻���Ԃ�
//
const LRect* Bullet::getBoundingRect()
{
	mColRect.Set( mPosition.x+8, mPosition.y-8, 4, 4 );

	return &mColRect;
}


//=============================================================================
//								End of File
//=============================================================================
