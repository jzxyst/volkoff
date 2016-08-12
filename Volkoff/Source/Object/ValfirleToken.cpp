//=============================================================================
/*! 
    @addtogroup 
    @file       ValfirleToken.h
    @brief      ���@���t�@�[���g�[�N��
    
    ���@���t�@�[���g�[�N������̒�`
    
    @attention  -
    @note       -
    @author     matsui
    @date       2011/2/17
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011//2/17
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "ValfirleToken.h"
#include "Player.h"
#include "./../Game/GameManager.h"
#include "./Item/Cure_S.h"
//---------------------------------------------------------------------------
// �� �I�u�W�F�N�g���쐬����
//---------------------------------------------------------------------------
ValfirleToken* ValfirleToken::create( void* args_, bool is_entity_ )
{
    ValfirleToken* o = NEW ValfirleToken();
    o->Initialize( *static_cast< CreateData* >( args_ ) );
    o->mIsEntity = is_entity_;

    // ���������̃z�X�g�ō쐬���ꂽ���̂ł���΁A�����ȊO�̃z�X�g�ɐ����������Ƃ𑗐M����
    if ( is_entity_ )
    {
        GameManager::getInstance()->getGameSession()->sendCreatedObjectEvent( OBJ_ENEMY, args_, sizeof( CreateData ) );
    }

    return o;
}


//---------------------------------------------------------------------------
// �� �I�u�W�F�N�g�������_���ō쐬����
//---------------------------------------------------------------------------
ValfirleToken* ValfirleToken::createRandom()
{
    ValfirleToken::CreateData data;
    data.Position = LVector3(0,0,0);
    data.WeaponLevel = 1;
	data.WeaponType = WEAPON_NON;
	for(int i = 0;i < WEAPON_MAX_NUM;++i)
	{
		if(!(::rand() % gWeaponBaseData[i].Rate))
		{
			data.WeaponType = static_cast<WeaponType>(i);
			break;
		}
	}
	data.WeaponType = static_cast<WeaponType>(::rand() % WEAPON_NORMAL_MAX_NUM);
	//data.WeaponType = WEAPON_KATANA;
	ValfirleToken* pEnemy = ValfirleToken::create( &data );

    return pEnemy;
}


//---------------------------------------------------------------------------
/*! 
	@brief ValfirleToken::ValfirleToken

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
ValfirleToken::ValfirleToken()
    : mWeaponLevel  ( 1 )
{
	this->m_pszName = "����𔄂�R�{"; //�ꎞ�I�B��œK���Ȗ��O��������
	this->m_eCharaState = CHARASTATE_WAIT;

	this->m_AnimePuttern = 0;

	this->m_eAction = ENEMY_ACT_WAIT;

	this->m_bCreateWeapon = false;

	this->m_nAttackDelay = 0;
	this->m_nWalkIntvCnt = 0;
	this->m_nWalkRangeCnt = 0;
	this->m_bWalkDir = false;
	this->m_nEscapeRangeCnt = 0;
	this->m_nStandbyCnt = 0;
	this->m_nGuardCnt = 0;
	this->m_nSquatCnt = 0;
    // �U���ΏۃO���[�v�͓G��
    setAttackedGroup( ATKGROUP_ENEMY );
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::~Enemy

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
ValfirleToken::~ValfirleToken()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief ValfirleToken::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool ValfirleToken::Initialize( const CreateData& data_ )
{
	bool r = false;
	
	switch(data_.WeaponType)
	{
	case WEAPON_BOSS_KATANA:
		this->m_pszName = "����𔄂�??";
		r = Character::Initialize();
		this->mCharaPanel->SetColorScale(Color(0.25f,0.80f,0.25f));
		break;

	case WEAPON_BOSS_TAEKWONDO:
		this->m_pszName = "�Ԃ�??";
		r = Character::Initialize();
		this->mCharaPanel->SetColorScale(Color(0.95f,0.7f,0.7f));
		break;

	case WEAPON_BOSS_KNIFE:
		this->m_pszName = "�O�p�ؔn��??";
		r = Character::Initialize();
		this->mCharaPanel->SetColorScale(Color(0.7f,0.7f,0.95f));
		break;
	case WEAPON_VALFIRLE_TOKEN:
		this->m_pszName = "Valfirle";
		r = Character::Initialize();
		break;
	default:
		this->m_pszName = "����𔄂�??";
		r = Character::Initialize();
		break;
	}

	this->mScore = 10000;
	this->mExp = 30;

    this->mPosition = data_.Position;
    this->mVelocity = data_.Velocity;
    mWeaponLevel    = data_.WeaponLevel;
    
    //this->m_pszName = "MidBoss"; //�ꎞ�I�B��œK���Ȗ��O��������
	this->mLife = this->mMaxLife = scg_nValfirleTokenLife[GameManager::getInstance()->getRank()];

	this->m_nRandAttackRange = ::rand() % 40 - 20;
	this->m_nRandAttackDelay = ::rand() % 40 - 10;
	this->m_nRandSearchRange = this->scm_nSearchX;

	WeaponData data;
	data.UseCount = -1;
	data.WeaponType =  static_cast<WeaponType>(data_.WeaponType);
	this->changeWeapon(data);
	this->mDestructfrag =0;
	return r;
}


//---------------------------------------------------------------------------
/*! 
	@brief ValfirleToken::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool ValfirleToken::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //delete��Manager�ɔC����

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief ValfirleToken::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool ValfirleToken::Update()
{
    return Character::Update();
}

//---------------------------------------------------------------------------
// �� �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
//---------------------------------------------------------------------------
bool ValfirleToken::UpdateSelf()
{
	//if(this->mDestructfrag)
	//{
	//	printf("valval%d\n",this->mDestructfrag);
	//}
	//���񂾍ۂɎ����Ă��镐��𗎂Ƃ�
	if(this->mLife <= 0 && !this->m_bCreateWeapon)
	{
		//GameManager::getInstance()->setKeyflag(1);
		//if(this->mWeaponData.WeaponType)
		//{
		//	Weapon::CreateData wdata;

		//	wdata.Data.WeaponType  = this->mWeaponData.WeaponType;
		//	wdata.Data.UseCount    = gWeaponBaseData[this->mWeaponData.WeaponType].UseCount;

		//	LVector3 v = this->mPosition;
		//	v.y += 100;
		//	wdata.Position = v;
		//	Weapon::create( &wdata );

		//	this->m_bCreateWeapon = true;
		//}
	}

	bool right = false;
	bool left  = false;
	bool button_A  = false;
	bool button_B  = false;
	bool Up = false;
	bool UpTrigger = false;
	bool Down = false;
	bool DownTrigger = false;
	bool Guard = false;
	bool GuardTrigger = false;

	Player *pPlayer = GameManager::getInstance()->getPlayer();

	//AI
	switch(this->m_eAction)
	{
	//����`
	case ENEMY_ACT_UNDEF:
		this->m_eAction = ENEMY_ACT_WAIT;
		break;

	//�ҋ@
	case ENEMY_ACT_WAIT:
		//�͈͓��T�����s��
		if(this->SearchPlayer())
		{
			//�͈͓��ł���ΒǐՂ��J�n����
			this->m_eAction = ENEMY_ACT_CHASE;
			break;
		}

		//�U�����J�n����
		if(this->m_nWalkIntvCnt > this->scm_nWalkIntv)
		{
			this->m_nWalkRangeCnt = ::rand() % this->scm_nWalkRange; //�U�������̐ݒ�
			this->m_nWalkIntvCnt = 0;
			this->m_bWalkDir = static_cast<bool>(::rand() % 2);
			this->m_eAction = ENEMY_ACT_WALK;
		}
		else
		{
			++this->m_nWalkIntvCnt;
		}
		break;

	//�U��
	case ENEMY_ACT_WALK:
		//�U�����s���Ă���
		if(this->m_nWalkRangeCnt)
		{
			if(this->m_bWalkDir)
				right = true;
			else
				left = true;

			--this->m_nWalkRangeCnt;
		}
		//�U���I���
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//�ǐ�
	case ENEMY_ACT_CHASE:
		//�v���C���[���T���͈͓��ł���
		if(this->SearchPlayer())
		{
			//Player�͉E�ɂ���
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				right = true;
			}
			//Player�͍��ɂ���
			else
			{
				left = true;
			}

			//�܂�ɃW�����v����
			if(!(::rand() % scg_nValfirleTokenJumpRatio[GameManager::getInstance()->getRank()]))
			{
				button_B = true;
			}

			//�v���C���[���ώ@�͈͓��ł���
			if(::abs(this->mPosition.x + ::rand() % this->scm_nSearchRand - pPlayer->getPosition().x) <= this->scm_nStandbyRange)
			{
				//�����_���Ŋώ@���J�n����
				if(!(::rand() % scg_nValfirleTokenStandbyRatio[GameManager::getInstance()->getRank()]))
				{
					this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
					this->m_eAction = ENEMY_ACT_STANDBY;
					break;
				}
			}

			//�v���C���[���U���͈͓��ł���
			if(this->SearchAttack1Range())
			{
				this->m_eAction = ENEMY_ACT_ATTACK_RANGE;
				break;
			}
		}
		else
		{
			//�T���͈͊O�ł���Αҋ@�ɖ߂�
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//�ώ@
	case ENEMY_ACT_STANDBY:
		//�v���C���[���W�����v�����u�ԑ΋�U�����s��
		if(pPlayer->getCharaState() == CHARASTATE_JUMP)
		{
			//this->m_nStandbyCnt = 0;
			break;
		}

		//�ώ@���s��
		if(this->m_nStandbyCnt)
		{
			--this->m_nStandbyCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//����
	case ENEMY_ACT_ESCAPE:
		if(this->m_nEscapeRangeCnt)
		{
			//Player�͉E�ɂ���
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				left = true;
			}
			//Player�͍��ɂ���
			else
			{
				right = true;
			}

			--this->m_nEscapeRangeCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//�U���͈͓�
	case ENEMY_ACT_ATTACK_RANGE:
		if(this->SearchAttack1Range())
		{
			//�����_���ōU�����J�n����
			if(!(::rand() % scg_nValfirleTokenAttackRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_eAction = ENEMY_ACT_ATTACK;
				break;
			}
			//�����_���Ŗh����J�n����
			if(!(::rand() % scg_nValfirleTokenGuardRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_GUARD;
				break;
			}
			//�����_���Ŋώ@���J�n����
			if(!(::rand() % scg_nValfirleTokenStandbyRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_STANDBY;
				break;
			}
			//�����_���ł��Ⴊ�݃K�[�h���J�n����
			if(!(::rand() % scg_nValfirleTokenSquatGuardRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_SQUAT_GUARD;
				break;
			}
			//�����_���ł��Ⴊ�݂��J�n����
			if(!(::rand() % scg_nValfirleTokenSquatRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nSquatCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_SQUAT;
				break;
			}
			//�����_���œ������J�n����
			if(!(::rand() % scg_nValfirleTokenEscapeRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nEscapeRangeCnt = ::rand() % this->scm_nEscapeRange;
				this->m_eAction = ENEMY_ACT_ESCAPE;
				break;
			}
		}
		//�U���͈͊O
		else
		{
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//�U����
	case ENEMY_ACT_ATTACK:
		if(this->SearchAttack1Range())
		{
			switch(this->m_eCharaState)
			{
			case CHARASTATE_ATTACK_SQUAT_ATTACK:
			case CHARASTATE_ATTACK_JUMP_ATTACK:
			case CHARASTATE_ATTACK_ANTIAIR_ATTACK:
			case CHARASTATE_ATTACK_DUSH_ATTACK:
				//����U����͑ҋ@�ɖ߂�
				this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_1:
				//�ʏ�U��2�i��
				if(scg_bValfirleTokenAttack2Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nValfirleTokenAttack2Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_2:
				//�ʏ�U��3�i��
				if(scg_bValfirleTokenAttack3Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nValfirleTokenAttack3Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			default:
				//�W�����v�U���͎��O�ɃW�����v����
				if(!(::rand() % scg_nValfirleTokenJumpAttackRatio[GameManager::getInstance()->getRank()]))
				{
					button_B = true;
					break;
				}
				//���Ⴊ�ݍU��
				if(!(::rand() % scg_nValfirleTokenSquatAttackRatio[GameManager::getInstance()->getRank()]))
				{
					Down = true;
				}

				//�ʏ�U��1�i��
				button_A = true;

				break;
			}

			//Player���W����ł���΁A�΋�U��������
			if(this->mPosition.y < pPlayer->getPosition().y)
			{
				Up = true;
			}
		}
		else
		{
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//�h��
	case ENEMY_ACT_GUARD:
		if(this->m_nGuardCnt)
		{
			Guard = true;
			--this->m_nGuardCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//���Ⴊ�݃K�[�h
	case ENEMY_ACT_SQUAT_GUARD:
		if(this->m_nGuardCnt)
		{
			GuardTrigger = true;
			Guard = true;
			Down = true;
			--this->m_nGuardCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//���Ⴊ��
	case ENEMY_ACT_SQUAT:
		if(this->m_nSquatCnt)
		{
			Down = true;
			--this->m_nSquatCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	default:
		this->m_eAction = ENEMY_ACT_WAIT;
		break;
	}
	//AI end

    // ���S (���S���[�V������) �͓��͂��󂯕t���Ȃ�
    if ( isDead() )
    {
        return true;
    }

    // �ړ��ł���ꍇ (�̂����蒆���ł͂Ȃ�)
    if ( mStunFrame == 0 )
    {
        //------------------------------------------------------
        // �U�����쒆�̏ꍇ
        if ( isAttacking() )
        {
			// �s�����������i=�o���I���j���ĂȂ��Ƒ���s��
			if ( !mAttackLocked )
			{
				// �A���U��
				if ( button_A )
				{
					// �s������
					this->AttackLock();

					switch( m_eCharaState )
					{
					case CHARASTATE_ATTACK_1:
						if(scg_bValfirleTokenAttack2Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_2, NULL, 0 );
						break;

					case CHARASTATE_ATTACK_2:
						if(scg_bValfirleTokenAttack3Permission[GameManager::getInstance()->getRank()])
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
            if ( button_A && m_eCharaState != EV_ACTION_ATTACK_1 )  // ���͉̂�
            {
                // �W�����v���̏ꍇ
                if ( mJump )
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
				else if ( !mTouchLadder && Up )
				{
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
					this->m_nAttackDelay = 0;
				}
                // �ȏ�ȊO�͒ʏ�U��
                else
                {
					// �U���̂��ߍs������
					if(scg_bValfirleTokenAttack1Permission[GameManager::getInstance()->getRank()])
					{
						this->AttackLock();
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_1, NULL, 0 );
					}
                }

                return true;
            }

			// �K�[�h
			if ( !Down && Guard && mOnGround && !mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
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

			// �E�ړ�
			//if ( !mClimbLadder && right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
			//{
			//	// ���������� EV_ACTION_RUN �C�x���g�𑗂�B
			//	// ���̂��ƁAHandleEvent() �Ŏ��ۂɈړ����J�n����B
			//	// ���̃C�x���g�̓L���[�C���O�����A������ HandleEvent() �ɑ�����B
			//	//u32 dir = CHARADIR_RIGHT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		// getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}
			//// ���ړ�
			//else if( !mClimbLadder && left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) )
			//{
			//	//u32 dir = CHARADIR_LEFT;

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
			else if ( ( !Guard && this->mOnGround && ( ( !right && !left ) || ( right && left ) ) && !Down && !this->mClimbLadder && m_eCharaState != CHARASTATE_WAIT )
				|| this->mNewTouchObj != OBJ_LADDER && this->mOldTouchObj == OBJ_LADDER && m_eCharaState != CHARASTATE_WAIT && m_eCharaState != CHARASTATE_JUMP && m_eCharaState != CHARASTATE_RUN )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
			}

			// �W�����v�J�n
			if ( button_B && m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder ) )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				return true;
			}

			// ���Ⴊ�݊J�n
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// ���Ⴊ�݂Ȃ���K�[�h�����ꍇ
				// �K�[�h���Ȃ��炵�Ⴊ�񂾏ꍇ
				if ( ( ( GuardTrigger ) || ( DownTrigger && Guard ) ) && m_eCharaState != CHARASTATE_SQGUARD )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT_GUARD, NULL, 0 );
				}
				else if ( !Guard && m_eCharaState != CHARASTATE_SQUAT )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT, NULL, 0 );
				}
			}

			// �͂�������
			if ( mTouchLadder
				&& m_eCharaState != CHARASTATE_LADDER_UP
				&& m_eCharaState != CHARASTATE_LADDER_DOWN
				&& m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				bool Catch = false;

				if ( UpTrigger && mDistance.y > 0 )
					Catch = true;

				if ( DownTrigger && mDistance.y < 0 )
					Catch = true;

				if ( Catch )
				{
					this->mPosition.Set(
						mPosition.x + mDistance.x,
						mPosition.y,
						mPosition.z
						);
					mClimbLadder = true;
				}
			}

			// �͂����㏸
			if ( Up && m_eCharaState != CHARASTATE_LADDER_UP && mClimbLadder )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				return true;
			}
			// �͂������~
			else if ( Down && m_eCharaState != CHARASTATE_LADDER_DOWN && mClimbLadder )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				return true;
			}
			// �͂����ҋ@
			else if ( !Up && !Down && mClimbLadder && m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_WAIT, NULL, 0 );

				return true;
			}
        }
    }

    return true;
}




//---------------------------------------------------------------------------
/*! 
	@brief ValfirleToken::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int ValfirleToken::HandleEvent(u32 event_,void *args_)
{
	///////////////////////////////////////// �퓬�s�\�J�n
	switch ( event_ )
	{
        case EV_ACTION_START_DEAD:
			//�o���l�̏���
			GameManager::getInstance()->getPlayer()->setExp(GameManager::getInstance()->getPlayer()->getExp()+this->mExp);
			if(!(::rand() % 3))
			{
				Cure_S *pCure = new Cure_S();
				pCure->Initialize();

				LVector3 v = this->mPosition;
				v.x -= 30;
				v.y += 100;

				pCure->setPosition(v);
			}
			//printf("score%d\n",this->mScore);
			//GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 
            break;
	}
	return Character::HandleEvent( event_, args_ );
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::SearchPlayer

	�v���C���[�̒T�����s��

	@return         bool
	- true  �͈͓�
	- false �͈͊O
	@exception      none
*/
//---------------------------------------------------------------------------
bool ValfirleToken::SearchPlayer()
{
	bool bRes = false;
	Player *pPlayer = GameManager::getInstance()->getPlayer();

	if(::abs(this->mPosition.y - pPlayer->getPosition().y) < this->scm_nSearchY)
	{
		//�T���͈͓��ł���
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) < this->m_nRandSearchRange)
		{
			bRes = true;
		}
	}

	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief ValfirleToken::SearchAttack1Range

	�U���͈͒T�����s��

	@return         bool
	- true  �͈͓�
	- false �͈͊O
	@exception      none
*/
//---------------------------------------------------------------------------
bool ValfirleToken::SearchAttack1Range()
{
	bool bRes = false;
	LRect *r = NULL;
	Player *pPlayer = GameManager::getInstance()->getPlayer();

	for(int i = 6;i < 11;++i)
	{
		r = this->mCollision->getAtkCollisionByIndex(i);

		if(r)
			break;
	}

	if(r)
	{
		//�U���͈͓�
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) <= r->x + r->width - 40) //40�͈ꎞ�I
		{
			bRes = true;
		}
	}

	return bRes;
}


//=============================================================================
//								End of File
//=============================================================================
