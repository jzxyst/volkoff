//=============================================================================
/*! 
    @addtogroup 
    @file       GameObject.cpp
    @brief      �I�u�W�F�N�g�x�[�X
    
    �I�u�W�F�N�g�x�[�X�̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


#include "GameObject.h"
#include "../Map/MapManager.h"
#include "../Game/GameManager.h"

GameObject::GameObject()
	: mHandle   ( 0 )
	, mScale	(1,1,1)
    , m_eDirection  ( CHARADIR_RIGHT )
	, mLife     (100)
    , mMaxLife  ( 100 )
	, mScore  (0)
	, mExit   (false)
    , mOnGround     ( false )
	, mPosition(Vector3::Zero)
	, mDefPosition(Vector3::Zero)
{
	GameObjectManager::getInstance()->AddObject(this);
}


GameObject::~GameObject()
{
    GameManager::getInstance()->getGameSession()->sendToServer( SYSEV_DELETE_GAMEOBJECT, &mHandle, sizeof( u32 ) );

	mExit = true;
}

// �������O�����̂��ʓ|�Ȃ̂ł�����Ɏ���
GameObjectManager* GameObject::getManager() { return GameObjectManager::getInstance(); }

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
bool GameObject::Update()
{
    // �󒆂ɂ���ꍇ
	if ( !mOnGround )
	{
        // �n�ʂ̏�ɂ��Ȃ���Ώd�͂ŉ���
		mAccel.y -= GRAVITY_ACCEL;

		if ( mVelocity.y < -10.0f )
		{
			mVelocity.y = -10.0f;
		}
	}
    // �n�ʏ�ɂ���ꍇ
	else
	{
		// �n�ʂɓ������Ă��āA�������̉����x������ꍇ�̓��Z�b�g����
		if ( mAccel.y < 0 )
		{
			mAccel.y = 0;
		}
		if ( mVelocity.y < 0 )
		{
			mVelocity.y = 0;
		}

        if ( mVelocity.GetLengthSquared() < 1.0f )
        {
            mVelocity = Vector3::Zero;
		}
	}

    // ���ʂɈړ�
    mVelocity += mAccel;

    // �n�`�Ƃ̓����蔻��
    float dx, dy;
    u32 result = judgeCollisionToMap( &dx, &dy );
    if ( result )
    {
        // �����������Ă���ꍇ�͒n�ʂ̏�ɂ���Ƃ���
	    if ( result & MAPCOLL_DOWN )
        {
            mOnGround = true;
        }
    }
    else
    {
        mOnGround = false;
    }

    mPosition.x += dx;
    mPosition.y += dy;
    mPosition.z = -6.0f;

    return true;
}

//---------------------------------------------------------------------
// �� �n�`�Ƃ̓����蔻����s��
//---------------------------------------------------------------------
u32 GameObject::judgeCollisionToMap( float* dx_, float* dy_ )
{
    *dx_ = *dy_ = 0.0f;

    // �����蔻��S�ʂ́A����p�̋�`������ꍇ�ɂ̂ݍs��
    const LRect* rc = getBoundingRect();
    if ( rc )
    {
        LRect col_rect = *rc;

        // �ړ�������̍��W
	    LVector3 d_pos = mPosition + mVelocity;

        // �ړ��O�̔���p��`�̍��W
        float px = col_rect.x;
        float py = col_rect.y;

        // ��`���ړ������āA�ړ���̔���̈�ɂ���
        col_rect.x += static_cast< int >( mVelocity.x );
        col_rect.y += static_cast< int >( mVelocity.y );
        
	    // �ړ��� (���܂͂���Ȃ�����)
	    LVector3 dest = mPosition - d_pos;

	    // �}�b�v�Ƃ̓����蔻�茋�ʂ́A�C����̍��W���i�[����ϐ�
	    LVector3 result_pos;
		
        
	    u32 result = MapManager::getInstance()->collision( col_rect, dest, &result_pos );

        // �ړ��O�Ɣ�ׂāA�ړ��ʂ����߂�
        *dx_ = result_pos.x - px;
        *dy_ = result_pos.y - py;

		return result;
    }
    return 0;
}
    /// ���x�̐ݒ� (�U���ɂ��ӂ���΂����Ŏg��)
void GameObject::setVelocity(const LVector3& vel_ )
{
	if(!mOnGround)
	{
		if(vel_.x>=16)
			vel_.x=16;
		if(vel_.x<=-16)
			vel_.x=-16;		
	}
	mVelocity = vel_; 
}

//=============================================================================
//								End of File
//=============================================================================
