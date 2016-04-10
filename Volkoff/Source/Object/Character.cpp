//=============================================================================
/*! 
    @addtogroup 
    @file       Character.cpp
    @brief      
    
    �L�����N�^�[�N���X�̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/17
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/17 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "Character.h"
#include "CharacterScriptInterface.h"
#include "../Map/MapManager.h"
#include "../Object/GameObjectManager.h"
#include"../Game/GameManager.h"
#include "../Frontend/CharacterNamePlate.h"
#include "../Frontend/GameFrontendManager.h"

//---------------------------------------------------------------------------
/*! 
	@brief Character::Character

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Character::Character()
	: mFrameCount   ( 0 )
    , mStunFrame    ( 0 )
    , mCharacterNamePlate   ( NULL )
{
	this->m_pszName = '\0'; //�ꎞ�I�B��œK���Ȗ��O��������
	this->m_eCharaState = CHARASTATE_WAIT;
	this->m_eDirection = CHARADIR_RIGHT;

	this->mJump = false;
	this->mOnGround = false;
	this->mTouchLadder = false;
	this->mClimbLadder = false;
	this->mStandOnObject = false;
	this->mAttackLocked = false;
	this->mBreakWeapon = false;
	this->mDistance.Set( 0, 0 );
	this->mCollision = NULL;
    this->mPosition.Set( 0, 0, -10.0f );
	this->mOldTouchObj = OBJ_UNDEF;
	this->mNewTouchObj = OBJ_UNDEF;
	this->mInvincibleFrame = 0;
}


//---------------------------------------------------------------------------
/*! 
	@brief Character::~Character

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Character::~Character()
{
	this->mCollision->Release();
	this->Release();

    
}

//---------------------------------------------------------------------
// �� �L�����N�^�[�̌�����ݒ肷��
//---------------------------------------------------------------------
void Character::setDirection( CharaDir dir_ )
{
    GameObject::setDirection( dir_ );

    if(this->m_eDirection == CHARADIR_RIGHT)
	{
		this->mCharaPanel->SetAngles(0,0,0);
	}
	else
	{
		this->mCharaPanel->SetAngles(0,Math::PI,0);
	}
}

//---------------------------------------------------------------------
// �� ���[���h���W��ԏ�ł̓����蔻���`��Ԃ�
//---------------------------------------------------------------------
const LRect* Character::getBoundingRect()
{
    const LRect* rc = mCollision->getDmgCollisionByIndex( getAnimePuttern() );
    if ( rc )
    {
        // �E����
        if ( m_eDirection == CHARADIR_RIGHT )
        {
            mWorldBoundingRect.Set(
                static_cast< int >( mPosition.x - ( mOrigin.x - rc->x ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->width, rc->height );
            return &mWorldBoundingRect;
        }
        // ������
        else
        {
            mWorldBoundingRect.Set(
                static_cast< int >( mPosition.x - ( rc->width - ( mOrigin.x - rc->x ) ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->width, rc->height );
            return &mWorldBoundingRect;
        }
    }
    return NULL;
}

//---------------------------------------------------------------------
// �� ���[�J�����W��ԏ�ł̓����蔻���`��Ԃ� (���ォ��̈ʒu)
//---------------------------------------------------------------------
const LRect* Character::getLocalBoundingRect()
{
    static LRect tmp;

    const LRect* rc = mCollision->getDmgCollisionByIndex( getAnimePuttern() );
    if ( rc )
    {
        // �E����
        //if ( m_eDirection == CHARADIR_RIGHT )
        {
            tmp.Set( rc->x, rc->y, rc->width, rc->height );
            return &tmp;
        }
        // ������
        /*
        else
        {
            tmp.set(
                160 - rc->x - rc->width,
                rc->y, rc->width, rc->height );
            return &tmp;
        }
        */
    }
    return NULL;
}


//---------------------------------------------------------------------
// �� ���[���h���W��ԏ�ł̍U�������蔻���`��Ԃ�
//---------------------------------------------------------------------
const LRect* Character::getAttackBoundingRect()
{
    static LRect tmp;

    const LRect* rc = mCollision->getAtkCollisionByIndex( getAnimePuttern() );
    if ( rc )
    {
        // �E����
        if ( m_eDirection == CHARADIR_RIGHT )
        {
            tmp.Set(
                static_cast< int >( mPosition.x - ( mOrigin.x - rc->x ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->width, rc->height );
            return &tmp;
        }
        // ������
        else
        {
            tmp.Set(
                static_cast< int >( mPosition.x - ( rc->width - ( mOrigin.x - rc->x ) ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->width, rc->height );
            return &tmp;
        }
    }
    return NULL;
}



//---------------------------------------------------------------------
// �� �A�j���[�V�����p�^�[���̐ݒ�
//---------------------------------------------------------------------
void Character::setAnimePuttern( int puttern_ )
{
    m_AnimePuttern = puttern_;

    int x = ( m_AnimePuttern % 12 ) * 160;
    int y = ( m_AnimePuttern / 12 ) * 160;




    /*
    // ���� X ���W�̌v�Z
    int x = ( m_AnimePuttern % 6 ) * 160;
    if ( m_AnimePuttern >= 72 )
    {
        x += 960;
    }

    // ���� Y ���W�̌v�Z
    int y = ( m_AnimePuttern / 6 ) * 160;
    if ( m_AnimePuttern >= 72 )
    {
        y %= 1920;
    }
    */

    mCharaPanel->SetSrcRect( LRect( x, y, 160, 160 ) );

    // ���_���ݒ肷��
	mOrigin.Set(
		this->mCollision->getOriginByIndex( m_AnimePuttern ).x,
		this->mCollision->getOriginByIndex( m_AnimePuttern ).y,
		0.0f );
	this->mCharaPanel->SetCenter( mOrigin.x - 80, -mOrigin.y + 80, 0 );
}

//---------------------------------------------------------------------------
/*! 
	@brief Character::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Initialize()
{
	this->Release();

	//this->m_pszName = '\0'; //�ꎞ�I�B��œK���Ȗ��O��������    Enemy �� initialize �Ŗ��O�ݒ肷��Ƃ��ɕs�ւ������̂ŃJ�b�g
	this->m_eCharaState = CHARASTATE_WAIT;
	this->m_eDirection = CHARADIR_RIGHT;
	this->mJump = false;
	this->mOnGround = false;
	this->mTouchLadder = false;
	this->mClimbLadder = false;
	this->mStandOnObject = false;
	this->mAttackLocked = false;
	this->mStandOnObject = false;
	this->mBreakWeapon = 0;
	this->m_AnimePuttern = 0;
	this->mOldTouchObj = OBJ_UNDEF;
	this->mNewTouchObj = OBJ_UNDEF;

	mWeaponData.WeaponType = WEAPON_NON;//WEAPON_STICK;//WEAPON_KATANA;
    mWeaponData.UseCount   = -1;
	

	this->mCharaPanel = Sprite3D::Create(160.0f,160.0f);//,LN_PANELDIR_UPPER_REFT);
    this->mCharaPanel->SetCenter(-80, 80, 0);
	this->mCharaPanel->SetTexture(Assets::LoadTexture(CharaResourceNames[mWeaponData.WeaponType].Character));//0xffffffff));
	this->mCharaPanel->SetCullingMode(CullingMode_None);
	//this->mCharaPanel->SetCenter(0.0f,0.0f,0.0f);
	this->mCharaPanel->SetSrcRect(LRect(0,0,160,160));
	this->mCharaPanel->SetPosition(0.0f,0.0f,0.0f);
	this->mCharaPanel->SetVisible(true);



    /*mCharaPanel->setEnableDepthTest( false );
    mCharaPanel->setEnableDepthWrite( false );*/
    //mCharaPanel->setBlendMode( LN_BLEND_NORMAL );

    this->mCollision = NEW Collision();
	this->mCollision->Initialize();
	
    changeWeapon( mWeaponData );
    setAnimePuttern( 0 );


    mCharacterNamePlate = NEW CharacterNamePlate();
    mCharacterNamePlate->initialize( this );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Character::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //delete��Manager�ɔC����
	SAFE_DELETE( this->mCollision );
    SAFE_DELETE( mCharacterNamePlate );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Character::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Update()
{
    // �X�N���v�g���g���čX�V
    CharacterScriptInterface::getInstance()->update( this );


    // ���S���[�V�������̏ꍇ (�Ƃ肠�����B�K�v������΃X�N���v�g�Ɉڂ�)
    //if ( getCharaState() == CHARASTATE_DEAD ) // ������уA�j���̂܂܃t�F�[�h�A�E�g�Ƃ��̏ꍇ�̓R������_��
    if ( isDead() )
    {
		mClimbLadder = false;
        setAnimePuttern( 102 + mFrameCount / 10 );
        mCharaPanel->SetOpacity( 1.0f - ( static_cast< float >( mFrameCount ) * 0.025641f ) ); // 0.025641f �� 39 �̋t��
        if ( mFrameCount == 39 )
        {
            setExit( true );
            return true;
        }
    };

	if(mInvincibleFrame>0)
	{
		--mInvincibleFrame;
	}

    //---------------------------------------------------------
    // �� �ړ��ƃW�����v�A�n�`�Ƃ̓����蔻��̏���

	// �W�����v
	if ( mJump )
	{
		//mVelocity.Y += scg_fJumpHeight;
	}

	// �󒆂ɂ���ꍇ
	if ( !mOnGround )
	{
        // �n�ʂ̏�ɂ��Ȃ���Ώd�͂ŉ���
		mAccel.y -= GRAVITY_ACCEL;

		if(mVelocity.x>=16)
			mVelocity.x=16;
		if(mVelocity.x<=-16)
			mVelocity.x=-16;
	}
    // �n�ʏ�ɂ���ꍇ
	else if ( !mClimbLadder || mStandOnObject )
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

        mVelocity *= FRICTION_COEFF;

        if ( mVelocity.GetLengthSquared() < 1.0f )
        {
            mVelocity = Vector3::Zero;
		}
	}
	//�A�j���[�V����
	switch(this->m_eCharaState)
	{
	case CHARASTATE_RUN:
		if(this->m_eDirection == CHARADIR_RIGHT)
		{
			mVelocity.x = scg_fRunSpeed;
		}
		else
		{
			mVelocity.x = -scg_fRunSpeed;
		}
		break;

	case CHARASTATE_JUMP:
		mClimbLadder = false;
		break;

	case CHARASTATE_SQUAT:
		break;

	case CHARASTATE_LADDER_WAIT:    //�͂����ҋ@
		this->mVelocity.y = 0;
		break;

	// �� �͂������~���x�ύX�͂���----------------
	case CHARASTATE_LADDER_UP:      //�͂������

		if ( this->mClimbLadder )
		{
			this->mVelocity.y = static_cast< float >( scg_fRunSpeed*0.9f );
		}
		else
		{
			getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
		}
		break;

	case CHARASTATE_LADDER_DOWN:    //�͂����~��

		if ( this->mClimbLadder )
		{
			this->mVelocity.y = static_cast< float >( -scg_fRunSpeed*0.9f );
		}
		else
		{
			getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
		}
		
		break;
	// �� �͂������~���x�ύX�͂���----------------
	}


	// ��q�ɂ��܂��Ă�Ƃ��͉������̑��x�A�d�͂ɂ������x������
	if ( mClimbLadder )
	{
		mVelocity.x = 0;
		if ( !mJump ) mAccel.y = 0;
	}
	// ����ȊO�͕��ʂɉ���
	else
	{
		mVelocity += mAccel;
		if ( mVelocity.y < -10.0f )
		{
			mVelocity.y = -10.0f;
		}
	}

    // �����蔻��S�ʂ́A����p�̋�`������ꍇ�ɂ̂ݍs��
    const LRect* rc = getBoundingRect();
    if ( rc )
    {
        LRect col_rect = *rc;

        // �ړ�������̍��W
	    LVector3 d_pos = mPosition + mVelocity;

        // �ړ��O�̔���p��`�̍��W
        float px = static_cast< float >( col_rect.x );
        float py = static_cast< float >( col_rect.y );

        // ��`���ړ������āA�ړ���̔���̈�ɂ���
        col_rect.x += static_cast< int >( mVelocity.x );
        col_rect.y += static_cast< int >( mVelocity.y );
        
	    // �ړ��� (���܂͂���Ȃ�����)
	    LVector3 dest = mPosition - d_pos;

	    // �}�b�v�Ƃ̓����蔻�茋�ʂ́A�C����̍��W���i�[����ϐ�
	    LVector3 result_pos;
  		//MapManager::getInstance()->BulletCollision(col_rect);      
	    u32 result = MapManager::getInstance()->collision( col_rect, dest, &result_pos );

        // �ړ��O�Ɣ�ׂāA�ړ��ʂ����߂�
        float dx = result_pos.x - px;
        float dy = result_pos.y - py;

        // �オ�������Ă���ꍇ�̓W�����v�̉��Z��0�ɂ���
		if ( result & MAPCOLL_UP )
			mVelocity.y = 0;

       
		
        


	// �� �n�㔻��-------------------------------
		// �ȉ��̏ꍇ�͒n�ʂ̏�ɂ���Ƃ���
		if ( result & MAPCOLL_DOWN || mClimbLadder || this->mStandOnObject )
	    {
		    mOnGround = true;
		    mJump = false;

			if ( result & MAPCOLL_DOWN )mClimbLadder = false;
	    }
		else
		{
			mOnGround = false;
		}
	// �� �n�㔻��-------------------------------

        
        

		// ���ۂ̍��W�ɔ��f������
	    mPosition.x += dx;//result_pos.X + ( mOrigin.X - getLocalBoundingRect()->x );
        mPosition.y += dy;//result_pos.Y - ( mOrigin.Y - getLocalBoundingRect()->y );

        // �I�u�W�F�N�g�Ƃ̓����蔻��
		CollisionToObj();
    }

    // �ŏI�I�Ƀp�l�����|�W�V�����ɍ��킹��
    this->mPosition.z = -5.0f;
    this->mCharaPanel->SetPosition(this->mPosition);

	++mFrameCount;

    // �̂������Ă���ꍇ�͎c��t���[���������炵�Ă���
    if ( mStunFrame > 0 )
    {
        --mStunFrame;
        if ( mStunFrame == 0 )
        {
            setCharaState( CHARASTATE_DEFAULT );
        }
    }

    // �A�C�e���擾�҂���
    if ( getCharaState() == CHARASTATE_ITEMGET )
    {
        --mItemGetWaitCount;

        // �^�C���A�E�g�B�p�������ɖ߂�
        if ( mItemGetWaitCount <= 0 )
        {
            setCharaState( CHARASTATE_DEFAULT );
        }
    }


    mCharacterNamePlate->update();

	return true;
}

//---------------------------------------------------------------------------
// �� �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
//---------------------------------------------------------------------------
bool Character::UpdateSelf()
{
    // ���̂ւ�̃L�[���͂͂��Ƃ� Player �Ɉړ�����\��

    // ���S (���S���[�V������) �͓��͂��󂯕t���Ȃ�
    if ( isDead() )
    {
        return true;
    }

    // ��{���[�V�������ŕ���j��t���O�������Ă���ꍇ�͑f��ɂ���
    if ( getCharaState() <= CHARASTATE_ATTACK_BEGIN_ && getWeaponData().WeaponType != WEAPON_NON && getWeaponData().UseCount <= 0 )//&& mBreakWeapon )
    {
        AttackUnLock();
        mFrameCount = 0;

        WeaponData temp;
		temp.WeaponType=WEAPON_NON;
		temp.UseCount=-1;
        changeWeapon(temp);

        mBreakWeapon = false;
    }

    // �ړ��ł���ꍇ (�̂����蒆���ł͂Ȃ�)
    if ( mStunFrame == 0 )
    {
        bool right = Input::IsPressed( LN_BUTTON_RIGHT );
        bool left  = Input::IsPressed( LN_BUTTON_LEFT );
		bool button_B  = Input::IsTriggered( LN_BUTTON_B );
		bool Up = Input::IsPressed( LN_BUTTON_UP );
		bool UpTrigger = Input::IsTriggered( LN_BUTTON_UP );
		bool Down = Input::IsPressed( LN_BUTTON_DOWN );
		bool DownTrigger = Input::IsTriggered( LN_BUTTON_DOWN );
		bool Guard = Input::IsPressed( LN_BUTTON_C );
		bool GuardTrigger = Input::IsTriggered( LN_BUTTON_C );

        //------------------------------------------------------
        // �U�����쒆�̏ꍇ
        if ( isAttacking() )
        {
			// �s�����������i=�o���I���j���ĂȂ��Ƒ���s��
			if ( !mAttackLocked )
			{
				// ������ς��邽�߂̏���
				if ( right )
				{
					setDirection( CHARADIR_RIGHT );
				}
				else if ( left )
				{
					setDirection( CHARADIR_LEFT );
				}

				// �A���U��
				if ( Input::IsTriggered( LN_BUTTON_A ) )
				{
					// �s������
					this->AttackLock();

					switch( m_eCharaState )
					{
					case CHARASTATE_ATTACK_1:
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_2, NULL, 0 );
						break;

					case CHARASTATE_ATTACK_2:
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_3, NULL, 0 );
						break;

					default:
						// �����ꂨ�������l�ɂȂ����烍�b�N����
						this->AttackUnLock();
						break;
					}
				}
			}
        }
        //------------------------------------------------------
        // �U�����쒆�ł͂Ȃ��ꍇ
        else
        {
			
			// �U���J�n
            if ( !Guard && !this->mClimbLadder && Input::IsTriggered( LN_BUTTON_A ) && m_eCharaState != EV_ACTION_ATTACK_1 )  // ���͉̂�
            {
                // �W�����v���̏ꍇ
                if ( !mOnGround )
                {
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_JUMP_ATTACK, NULL, 0 );
                }
                // ���Ⴊ�ݒ��̏ꍇ
                else if ( Down )
                {
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_SQUAT_ATTACK, NULL, 0 );
                }
				// ��������Ȃ���̏ꍇ
				else if ( !this->mClimbLadder && Up )
				{
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
				}
                // �ȏ�ȊO�͒ʏ�U��
                else
                {
					// �U���̂��ߍs������
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_1, NULL, 0 );
                }

                return true;
            }

			// �K�[�h
			if ( !Down && Guard && this->mOnGround && !this->mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_GUARD, NULL, 0 );
				return true;
			}

			// ������ς��邽�߂̏���
			if ( right )
			{
				setDirection( CHARADIR_RIGHT );
			}
			else if ( left )
			{
				setDirection( CHARADIR_LEFT );
			}

			//// �E�ړ�
			//if ( !mClimbLadder && right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
			//{
			//	// ���������� EV_ACTION_RUN �C�x���g�𑗂�B
			//	// ���̂��ƁAHandleEvent() �Ŏ��ۂɈړ����J�n����B
			//	// ���̃C�x���g�̓L���[�C���O�����A������ HandleEvent() �ɑ�����B
			//	//u32 dir = CHARADIR_RIGHT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		//getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}
			//// ���ړ�
			//else if( !mClimbLadder && left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) )
			//{
			//	//u32 dir = CHARADIR_LEFT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		//getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}


			// �ړ�
			if ( ( !Guard && !this->mClimbLadder && right && !left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
				|| ( !Guard && !this->mClimbLadder && left && !right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) ) )
			{
				if ( !Down )
					getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			}
			// ���E�̂������������Ă��Ȃ��ꍇ�͑ҋ@�ɂ���
			// ��q�������Ƃ����ҋ@�ŁB
			// (���� mState != CHARASTATE_WAIT �́A�ҋ@���ɘA���ŃC�x���g�������Ȃ��悤�ɂ��邽�߂ɕK�v)
			else if (
                !Guard &&
                this->mOnGround &&
                ( ( !right && !left ) || ( right && left ) ) &&
                !Down &&
                ( !this->mClimbLadder ) &&
                this->m_eCharaState != CHARASTATE_WAIT )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
			}

			// �W�����v�J�n
			if ( button_B && this->m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder || mStandOnObject ) )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				return true;
			}

			// ���Ⴊ�݊J�n
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// ���Ⴊ�݂Ȃ���K�[�h�����ꍇ
				// �K�[�h���Ȃ��炵�Ⴊ�񂾏ꍇ
				if ( ( ( GuardTrigger ) || ( DownTrigger && Guard ) ) && this->m_eCharaState != CHARASTATE_SQGUARD )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT_GUARD, NULL, 0 );
				}
				else if ( !Guard && this->m_eCharaState != CHARASTATE_SQUAT )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT, NULL, 0 );
				}
			}

			// �͂�������
			if ( this->mTouchLadder
				&& this->m_eCharaState != CHARASTATE_LADDER_UP
				&& this->m_eCharaState != CHARASTATE_LADDER_DOWN
				&& this->m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				bool Catch = false;

				// ��A�����������u��
				if ( ( UpTrigger && !this->mStandOnObject )
					|| ( DownTrigger ) )
				{
					Catch = true;
				}

				if ( Catch )
				{
					if ( this->mDistance.y > 0 )
					{
						this->mDistance.y = 0;
					}

					this->mPosition.Set(
						this->mPosition.x + this->mDistance.x,
						this->mPosition.y ,//+ this->mDistance.Y,
						this->mPosition.z
						);
					this->mClimbLadder = true;
					this->mOnGround = false;
				}
				else
				{
					this->mClimbLadder = false;
				}
			}

			// �͂����㏸
			if ( Up && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_UP )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				return true;
			}
			// �͂������~
			else if ( Down && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_DOWN )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				return true;
			}
			// �͂����ҋ@
			else if ( !Up && !Down && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_WAIT, NULL, 0 );

				return true;
			}

			//�A�N�V�����{�^��
			if ( Input::IsTriggered( LN_BUTTON_X ) )
			{
				const LRect* rc = getBoundingRect();
				if ( rc )
				{
					//�o���Ƃ̂����蔻��
					u32 exit_handle =getManager()->judgeCollitionTypeSpecified( *rc, OBJ_EXIT );
					u32 exit_lock_handle =getManager()->judgeCollitionTypeSpecified( *rc, OBJ_EXIT_LOCK);
					if(exit_handle)
					{

								
					}

					if(exit_lock_handle)
					{
						//printf("���t���o��\n");
						if(GameManager::getInstance()->getKeyflag())
						{
// �R���e�B�j���[�ɔ����ăo�b�N�A�b�v�����
							GameManager::getInstance()->commit();
							GameAudio::PlaySE("./Data/Sound/SE/open.wav",1.50,1.00);
							GameManager::getInstance()->setOpenflag(1);		
						}
						else
						{
							GameAudio::PlaySE("./Data/Sound/SE/lock.wav",1.50,1.00);
						}
						return true;
					}


                    // ����Ƃ̓����蔻��
					u32 item_handle = getManager()->judgeCollitionTypeSpecified( *rc, OBJ_WEAPON );
                    if ( item_handle )
                    {
                        // �A�C�e�����擾���邽�߂ɃT�[�o�Ƀ��b�Z�[�W�𑗂�B
                        ItemRequestArgs args;
                        args.GetterHandle  = this->getHandle();
                        args.ItemObjHandle = item_handle;
                        GameManager::getInstance()->getGameSession()->sendToServer( 
                            SYSEV_ITEM_REQUEST, &args, sizeof( ItemRequestArgs ) );
                    
                        // �A�C�e���擾�A�N�V�����J�n
                        //getManager()->postEvent( getHandle(), EV_ACTION_ITEM_GET, NULL, 0 );

					    return true;
                    }

                    // ���E�A�C�e���Ƃ̓����蔻��
                    // item_handle = getManager()->judgeCollitionTypeSpecified( *rc, OBJ_ITEM_BEGIN, OBJ_ITEM_END );
                    //if ( item_handle )
                    //{
                    //    _p("�����Ă�");
                    //}
				}
			}
        }
    }

    return true;
}




//---------------------------------------------------------------------------
/*! 
	@brief Character::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Character::HandleEvent(u32 event_,void *args_)
{
    AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
    {
        ///////////////////////////////////////// �ҋ@�J�n
        case EV_ACTION_WAIT:
            setCharaState( CHARASTATE_WAIT );
            break;

        ///////////////////////////////////////// ����J�n
        case EV_ACTION_RUN:
			setCharaState( CHARASTATE_RUN );
			//setDirection( *( (CharaDir*)args_ ) );
            break;

		///////////////////////////////////////// �W�����v�J�n
		case EV_ACTION_JUMP:
			setCharaState( CHARASTATE_JUMP );
			this->JumpStart();
			break;

		///////////////////////////////////////// ���Ⴊ�݊J�n
		case EV_ACTION_SQUAT:
			setCharaState( CHARASTATE_SQUAT );
			break;

        ///////////////////////////////////////// �̂�����J�n
        case EV_ACTION_STUN:
            mStunFrame = *( reinterpret_cast< u32* >( args_ ) );
            setCharaState( CHARASTATE_STUN );
            mClimbLadder = false;
            mJump = true;
            break;

		///////////////////////////////////////// �ӂ��ƂъJ�n
		case EV_ACTION_BLOW:
			mStunFrame = *( reinterpret_cast< u32* >( args_ ) );
			setCharaState( CHARASTATE_BLOW );
			break;

		///////////////////////////////////////// �͂����ҋ@�J�n
		case EV_ACTION_LADDER_WAIT:
			setCharaState( CHARASTATE_LADDER_WAIT );
			break;

		///////////////////////////////////////// �͂����o��J�n
		case EV_ACTION_LADDER_UP:
			setCharaState( CHARASTATE_LADDER_UP );
			break;

		///////////////////////////////////////// �͂����~��J�n
		case EV_ACTION_LADDER_DOWN:
			setCharaState( CHARASTATE_LADDER_DOWN );
			break;

        ///////////////////////////////////////// �A�C�e���擾�J�n
        case EV_ACTION_ITEM_GET:
            setCharaState( CHARASTATE_ITEMGET );
            mItemGetWaitCount = ITEMGET_WAIT_COUNT;     // �^�C���A�E�g����
            break;

        ///////////////////////////////////////// �ʏ�U�� 1 �i��
		case EV_ACTION_ATTACK_1:
			setCharaState( CHARASTATE_ATTACK_1 );
			break;

		///////////////////////////////////////// �ʏ�U�� 2 �i��
		case EV_ACTION_ATTACK_2:
			setCharaState( CHARASTATE_ATTACK_2 );
			break;

		///////////////////////////////////////// �ʏ�U�� 3 �i��
		case EV_ACTION_ATTACK_3:
			setCharaState( CHARASTATE_ATTACK_3 );
			break;

		///////////////////////////////////////// �W�����v�U��
		case EV_ACTION_ATTACK_JUMP_ATTACK:
			setCharaState( CHARASTATE_ATTACK_JUMP_ATTACK );
			break;

		///////////////////////////////////////// ���Ⴊ�ݍU��
		case EV_ACTION_ATTACK_SQUAT_ATTACK:
			setCharaState( CHARASTATE_ATTACK_SQUAT_ATTACK );
			break;

		///////////////////////////////////////// �΋�U��
		case EV_ACTION_ATTACK_ANTIAIR_ATTACK:
			setCharaState( CHARASTATE_ATTACK_ANTIAIR_ATTACK );
			break;

		///////////////////////////////////////// �K�[�h
		case EV_ACTION_GUARD:
			setCharaState( CHARASTATE_GUARD );
			break;

		///////////////////////////////////////// ���Ⴊ�݃K�[�h
		case EV_ACTION_SQUAT_GUARD:
			setCharaState( CHARASTATE_SQGUARD );
			break;

        ///////////////////////////////////////// �퓬�s�\�J�n
        case EV_ACTION_START_DEAD:
            setCharaState( CHARASTATE_DEAD );
            break;

        ///////////////////////////////////////// �_���[�W��^����
        case EV_APPLY_DAMAGE:
        {
            AttackEventArg* arg = reinterpret_cast< AttackEventArg* >( args_ );



			GameObject* obj = GameObjectManager::getInstance()->findObject( arg->AttackerHandle );
			if ( obj )
			{

				if (( obj->getObjType() == OBJ_CHARACTER )||( obj->getObjType() == OBJ_ENEMY ))
				{
					if((!arg->Guardflag)&&( arg->Damage > 0 ))
					{
						switch ( ((Character*)obj)->getWeaponData().WeaponType )
						{
						case WEAPON_NON:
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav");
							break;
						case WEAPON_STICK:
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav",1.00,0.70);
							break;
						case WEAPON_KATANA:
							GameAudio::PlaySE("./Data/Sound/SE/KATANA_hit.wav",0.80,0.90);
							break;
						case WEAPON_UMBRELLA:
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav",0.80,0.75);
							GameAudio::PlaySE("./Data/Sound/SE/sen_ge_bun04.wav",0.80,1.50);
							break;
						case WEAPON_TAEKWONDO:
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav",0.85,0.70);
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav",0.90,0.50);
							GameAudio::PlaySE("./Data/Sound/SE/sen_ge_bun04.wav",0.80,1.10);
							GameAudio::PlaySE("./Data/Sound/SE/sen_ge_bun04.wav",0.80,1.20);
							break;
						case WEAPON_KNIFE:
							GameAudio::PlaySE("./Data/Sound/SE/KATANA_hit.wav",0.85,0.90);
							GameAudio::PlaySE("./Data/Sound/SE/KATANA_hit.wav",0.85,1.20);
							break;
						case WEAPON_HAMMER:
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav",0.85,0.70);
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav",0.90,0.50);
							GameAudio::PlaySE("./Data/Sound/SE/sen_ge_bun04.wav",0.80,0.90);
							GameAudio::PlaySE("./Data/Sound/SE/sen_ge_bun04.wav",0.80,1.00);
							break;
						case WEAPON_SCYTHE:
							GameAudio::PlaySE("./Data/Sound/SE/chop_knife2.wav",0.80,1.40);
						case WEAPON_BOSS_KATANA:
							GameAudio::PlaySE("./Data/Sound/SE/KATANA_hit.wav",0.80,0.90);
							break;
						case WEAPON_BOSS_TAEKWONDO:
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav",0.85,0.70);
							GameAudio::PlaySE("./Data/Sound/SE/b_dead.wav",0.90,0.50);
							GameAudio::PlaySE("./Data/Sound/SE/sen_ge_bun04.wav",0.80,1.10);
							GameAudio::PlaySE("./Data/Sound/SE/sen_ge_bun04.wav",0.80,1.20);
							break;
						case WEAPON_BOSS_KNIFE:
							GameAudio::PlaySE("./Data/Sound/SE/KATANA_hit.wav",0.75,0.90);
							GameAudio::PlaySE("./Data/Sound/SE/KATANA_hit.wav",0.75,1.20);
							break;
						case WEAPON_BOSS_SCYTHE:
							GameAudio::PlaySE("./Data/Sound/SE/chop_knife2.wav",0.80,0.90);
						case WEAPON_VALFIRLE:
							GameAudio::PlaySE("./Data/Sound/SE/KATANA_hit.wav",0.85,1.00);
							break;
						case WEAPON_VALFIRLE_TOKEN:
							GameAudio::PlaySE("./Data/Sound/SE/KATANA_hit.wav",0.85,1.00);
							break;

						}
					}

					if(arg->Guardflag)
					{
						GameAudio::PlaySE("./Data/Sound/SE/sen_ge_bun04.wav",0.70,0.80);
					}
				}
			}

            // �_���[�W�|�b�v�̕\��
            if ( arg->Damage > 0 )
            {
                int type = ( arg->Criticalflag ) ? 3 : 1;
                LVector3 pos( this->mPosition.x + 10,  this->mPosition.y + 70, -5 );
                GameFrontendManager::getInstance()->getDamagePopManager()->popNumber( pos, arg->Damage, type );
            }
			if(mLife>0)
			{
				mLife -= arg->Damage;
				// �퓬�s�\
				if ( mLife < 0 )
				{
					mLife = 0;
					// ���S���[�V�����J�n
					getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
				}
			}


            // HP �o�[��\������
            mCharacterNamePlate->startShow();

			

            //if ( mLife <= 0 )
            //{
            //    mLife = 0;

            //    // ���S���[�V�����J�n
            //    getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
            //}
            // �܂������Ă�
            //else
            //{
                setVelocity( arg->BrowVector );
           // }
            break;
        }

        ///////////////////////////////////////// �T�[�o���畐�킪�����Ă���
        case EV_GET_WEAPON:
            //_p(EV_GET_WEAPON);

            WeaponData* data = reinterpret_cast< WeaponData* >( args_ );

            printf( "������擾 ���:%d  �g�p��:%d \n", data->WeaponType, data->UseCount );

            changeWeapon( *data );

            // �ʏ��Ԃɂ���
            setCharaState( CHARASTATE_DEFAULT );
            break;

    }
	return 0;
}

//---------------------------------------------------------------------
// �� �L�����N�^�[�̏�Ԃ�ύX����
//---------------------------------------------------------------------
void Character::setCharaState( CharaState state_ )
{
	// ��Ԃɍ��킹������̃��[�V�����ɂ���ꍇ
	if ( state_ == CHARASTATE_DEFAULT )
	{
		if ( this->isDead() )
		{
			this->m_eCharaState = CHARASTATE_DEAD;
		}
		else
		{
			this->m_eCharaState = CHARASTATE_WAIT;
		}
	}
	else
	{
		this->m_eCharaState = state_;
	}

	mFrameCount = 0;

    // �Ƃ肠�����A���S���[�V�������͕ύX���󂯕t���Ȃ� (�h������Ƃ��Ȃ�����ύX����K�v�����邯��)
 //   if ( m_eCharaState == CHARASTATE_DEAD )
 //   {
 //       mFrameCount = 0;
 //   }
	//else
	//{
	//	
	//}
	

    // �A�C�e���擾��ԈȊO�ɂȂ�ꍇ�A�s��h�~�̂��߂Ɏ擾�҂����J�E���g�����Z�b�g����
    if ( this->m_eCharaState != CHARASTATE_ITEMGET )
    {
        mItemGetWaitCount = 0;
    }
}

//---------------------------------------------------------------------
// �� �����ύX����
//---------------------------------------------------------------------
void Character::changeWeapon( const WeaponData& weapon_data_ )
{
    // �������f��ȊO�̏ꍇ
    if ( mWeaponData.WeaponType != WEAPON_NON )
    {
        // ���ݎ����Ă��镐���V�����I�u�W�F�N�g�Ƃ��ă}�b�v��ɐ������� (�T�[�o�փI�u�W�F�N�g�쐬�𑗐M)
		if(this->mWeaponData.UseCount)
		{
			Weapon::CreateData data;
			data.Data       = mWeaponData;
			data.Position   = this->getPosition();
			data.Position.x += ::rand() % 20 - 10;
			data.Position.y += 100;
			Weapon* weapon = Weapon::create( &data );
		}
    }

    // �󂯎��������𑕔�����Ƃ��Đݒ肷��
    mWeaponData = weapon_data_;


    // �����蔻��f�[�^
    const char* filename = CharaResourceNames[ mWeaponData.WeaponType ].Collision;
    if ( !filename )
    {
        printf( "�����蔻��f�[�^�t�@�C������ NULL�B����ɑf��̃��m���g�p\n" );
        filename = CharaResourceNames[ WEAPON_NON ].Collision;
    }
    mCollision->LoadFile( filename );

    // �L�����N�^�[�摜
    filename = CharaResourceNames[mWeaponData.WeaponType].Character;
    if ( !filename )
    {
        printf( "����e�N�X�`������ NULL�B����ɑf��̃��m���g�p\n" );
        filename = CharaResourceNames[ WEAPON_NON ].Character;
    }
    mCharaPanel->SetTexture(Assets::LoadTexture(filename));//,0xffffffff));

    // ������ύX�������Ƃ��T�[�o�ɓ`���� (�T�[�o���瑼�̃z�X�g�ɒʒm���Ă��炤)


    // �v���C���[�̏ꍇ�̓t�����g�G���h�ɓ`������΃x�X�g����
}

//
// Character::AttackLock
// �U�����̍s������
//
// �ĂԂƃ��b�N��������܂��B
// �U�����[�V�������W�����v�ȂǂŃL�����Z�������Ȃ�����
//
void Character::AttackLock()
{
	mAttackLocked = true;
}

//
// Character::AttackUnLock
// �U�����̍s����������
//
// �ĂԂƃ��b�N���͂���܂��B
// �U�����[�V�����I�����ɂ͕K���Ă�ł�������
//
void Character::AttackUnLock()
{
	mAttackLocked = false;
}

//
// Character::JumpStart
// �W�����v�J�n���ɌĂ�
//
void Character::JumpStart()
{
	if ( !mJump )
	{
		mJump = true;
		mOnGround = false;
        mStandOnObject = false;

		mVelocity.y += scg_fJumpHeight;
	}
}


//
// Character::CollisionToObj
// �I�u�W�F�N�g�Ƃ̓����蔻��
//
// �������Ă���ꍇ��
// �e�폈��������
//
void Character::CollisionToObj()
{
	//
	// �摜���m�̂߂荞�ݗ�
	// �ؔ��ɏ��Ƃ��ɕK�v
	//
	LVector2 overValue;
	overValue.Set( 0, 0 );

	// [11/11/15 �R�{] getBoundingRect() �œ�����`���Ƃ��̂ŏC��
    const LRect* nowRect = getBoundingRect();

	if ( nowRect )
    {
        LRect adv_rect = *nowRect;
        adv_rect.x += mVelocity.x;
        adv_rect.y += ceil( mVelocity.y );

        //_p(ceil( mVelocity.Y ));


		mOldTouchObj = mNewTouchObj;
		mNewTouchObj = static_cast< ObjectType >( GameObjectManager::getInstance()->CollisionToObject( this->getObjType(), *nowRect, &mDistance, &overValue ) );

		// �e��I�u�W�F�N�g�ɂ��������Ƃ��̓���
		// �e��`�ɂ��Ă�GameObjectManager.h ��
		//                 _ENUM_OBJECT_TYPE �Q�Ƃ̂���

        // ��x���ɂ��̂��Ă��Ȃ���Ԃɂ���
        mStandOnObject = false;

        

	// �� �͂���---------------------------------
        
		// �͂����A�͂�����[�ɐG��Ă���Ƃ�
		if ( this->mNewTouchObj == OBJ_LADDERTOP
			|| this->mNewTouchObj == OBJ_LADDER )
		{
			this->mTouchLadder = true;

			// �͂�����[�ɐG��Ă���Ƃ�
			if ( this->mNewTouchObj == OBJ_LADDERTOP )
			{

                if ( !mClimbLadder && !mJump )
                {
                    mPosition += LVector3( overValue, 0 );
                    mStandOnObject = true;
                }

                /*
				if ( -10 <= overValue.Y && overValue.Y <= 5 && !this->mClimbLadder
					&& ( this->mOnGround || this->m_eCharaState == CHARASTATE_WAIT ) )
				{
					this->mPosition.Y -= overValue.Y;
					this->mStandOnObject = true;
				}
				else
				{
					this->mStandOnObject = false;
				}
                */
			}
		}
		else
		{
			if ( this->mOldTouchObj == OBJ_LADDERTOP && this->mClimbLadder )
			{
				this->mVelocity.y = 0;
			}

			this->mTouchLadder = false;
		    this->mClimbLadder = false;
		}	
        
	// �� �͂���---------------------------------

#if 0
	// �� �ؔ�-----------------------------------

		if ( mNewTouchObj == OBJ_BOX )
		{
            mPosition += overValue;

            // ��ɂ��炷�K�v������ꍇ�A��ɏ���Ă���Ƃ���
            if ( overValue.X == 0 && overValue.Y >= 0 )
            {
                mStandOnObject = true;
            }

 
            
            /*
			if ( -15 < overValue.Y //&& overValue.Y < 15
				&& ( !mJump || this->mVelocity.Y <= 0 ) )
			{
				this->mPosition.Y -= overValue.Y;
				this->mStandOnObject = true;
			}
			else
			{
				this->mPosition.X -= overValue.X;
				this->mStandOnObject = false;
			}
            */
		}
#endif
        
	// �� �ؔ�-----------------------------------
		
	// �� ��ɏ���I�u�W�F�N�g-----------------
		if ( mNewTouchObj != OBJ_BOX && mNewTouchObj != OBJ_LADDERTOP )
		{
            //printf("��ɏ���I�u�W�F�N�g ������\n");
			//this->mStandOnObject = false;
		}
	// �� ��ɏ���I�u�W�F�N�g-----------------
	

	// �� �񕜃A�C�e��---------------------------
		if ( this->mLife > 0 && this->getObjType() == OBJ_CHARACTER )
		{
			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_CURE_S ) )
			{
				printf("�񕜃A�C�e���擾�@��\n");
				GameAudio::PlaySE("./Data/Sound/SE/Powerup23.wav",1.00,1.50);

				static const int CURE_S_VALUE_ = static_cast< int >( this->mMaxLife * 0.30f );

				// �ő�l�𒴂���񕜗ʂ̏ꍇ�͍ő�l�ŌŒ�
				if ( this->mLife + CURE_S_VALUE_ > this->mMaxLife )
				{
					this->mLife = this->mMaxLife;
				}
				else
				{
					this->mLife += CURE_S_VALUE_;
				}
			}

			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_CURE_M ) )
			{
				printf("�񕜃A�C�e���擾�@��\n");
				GameAudio::PlaySE("./Data/Sound/SE/Powerup23.wav",1.00,1.50);

				static const int CURE_M_VALUE_ = static_cast< int >( this->mMaxLife * 0.60f );

				// �ő�l�𒴂���񕜗ʂ̏ꍇ�͍ő�l�ŌŒ�
				if ( this->mLife + CURE_M_VALUE_ > this->mMaxLife )
				{
					this->mLife = this->mMaxLife;
				}
				else
				{
					this->mLife += CURE_M_VALUE_;
				}
			}

			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_CURE_L ) )
			{
				printf("�񕜃A�C�e���擾�@��\n");
				GameAudio::PlaySE("./Data/Sound/SE/Powerup23.wav",1.00,1.50);

				static const int CURE_L_VALUE_ = static_cast< int >( this->mMaxLife * 0.80f );

				// �ő�l�𒴂���񕜗ʂ̏ꍇ�͍ő�l�ŌŒ�
				if ( this->mLife + CURE_L_VALUE_ > this->mMaxLife )
				{
					this->mLife = this->mMaxLife;
				}
				else
				{
					this->mLife += CURE_L_VALUE_;
				}
			}
	// �� �񕜃A�C�e��---------------------------

	// �� ��-------------------------------------
			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_KEY ) )
			{
				printf("�A�C�e���擾  ��\n");
				GameManager::getInstance()->setKeyflag(1);
			}
		}
	// �� ��-------------------------------------
    }



    //---------------------------------------------------------
    // �� �ؔ��Ƃ̔���



    // �����̃��[���h��̍��A��A�E�A���B
    // �� > �� �ȓ_�ɒ��ӁB���̕��� 0 �ɋ߂��B
    int pl = nowRect->x;
    int pt = nowRect->y;
    int pr = nowRect->x + nowRect->width;
    int pb = nowRect->y - nowRect->height;
    int pwh = nowRect->width / 2;
    int phh = nowRect->height / 2;
    LVector2 pc( pl + ( pr - pl ) / 2, pb + ( pt - pb ) / 2 );

    GameObjectList& obj_list = GameObjectManager::getInstance()->getGameObjectList();
    GameObjectList::iterator itr = obj_list.begin();
    GameObjectList::iterator end = obj_list.end();
    for ( ;itr != end; ++itr )
    {
        u32          target_type = (*itr)->getObjType();
        const LRect* target_rc   = (*itr)->getBoundingRect();
        if ( target_type == OBJ_BOX && target_rc )
        {
            int dx = 0;
            int dy = 0;

            // �^�[�Q�b�g�̃��[���h��̍��A��A�E�A���B
            int tl = target_rc->x;
            int tt = target_rc->y;
            int tr = target_rc->x + target_rc->width;
            int tb = target_rc->y - target_rc->height;
            LVector2 tc( tl + ( tr - tl ) / 2, tb + ( tt - tb ) / 2 );
          

            // �c�����̔���
            if ( pl + pwh < tr && pr - pwh > tl && pt >= tb && pb <= tt )
            {
                // ������
                if ( pc.y > tc.y )  // mVelocity.Y < 0 && 
                {
                    dy = tt - pb + 1;     // ���̒l�̓v���X�ɂȂ�
                }
                // �㏸���A�������Ώۂ̉��ɂ���ꍇ
                else if ( pc.y < tc.y ) // mVelocity.Y > 0 && 
                {
                    dy = tb - pt - 1;     // ���̒l�̓}�C�i�X�ɂȂ�
                }
                // Y ���W�̏C��
                if ( dy != 0 )
                {
                    pt += dy;
                    pb = pt - nowRect->height;
                    mPosition.y += dy;
                    mVelocity.y = 0;
                }
            }
            
            // ���̔���
            if ( pl <= tr && pr >= tl && pt >= tb && pb <= tt )
            {
                // �������Ώۂ̍��ɂ���ꍇ
                if ( pl < tl )
                {
                    dx = tl - pr - 1;     // ���̒l�̓}�C�i�X�ɂȂ�
                }
                // �������Ώۂ̉E�ɂ���ꍇ
                else
                {
                    dx = tr - pl + 1;     // ���̒l�̓v���X�ɂȂ�
                }

                // X ���W�̏C��
                pl += dx;
                pr = pl + nowRect->width;
                mPosition.x += dx;
            }
            
            // �C����A�����̂������ɔ�������Ώ���Ă���
            if ( pl <= tr && pr >= tl && pt >= tb && pb - 1 <= tt )
            {
                mStandOnObject = true;
                //mOnGround = true;
            }
        }
    }
}

//=============================================================================
//								End of File
//=============================================================================
