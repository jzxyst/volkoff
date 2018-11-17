//=============================================================================
/*! 
    @addtogroup 
    @file       Player.cpp
    @brief      
    
    �v���C���[�N���X�̎���
    
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
#include "Player.h"
#include "../Frontend/CharacterNamePlate.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Effect/Effect_1.h"

//---------------------------------------------------------------------------
/*! 
	@brief Player::Player

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Player::Player()
{
	this->m_pszName = '\0'; //�ꎞ�I�B��œK���Ȗ��O��������
	this->m_eCharaState = CHARASTATE_WAIT;

	this->m_AnimePuttern = 0;

    // �U���ΏۃO���[�v�̓v���C���[��
    setAttackedGroup( ATKGROUP_PLAYER );

    memset( mWeaponExps, 0, sizeof( mWeaponExps ) );
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::~Player

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Player::~Player()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Initialize()
{
    this->Release();

    memset( mWeaponExps, 0, sizeof( mWeaponExps ) );

    bool r = Character::Initialize();

    // �v���C���[�͌ォ��`�悷��悤�ɂ���
    //this->mCharaPanel->setPriority( 100 );



    // �v���C���[�L�����N�^�[�̃l�[���v���[�g�͕\�����Ȃ�
    this->mCharacterNamePlate->setVisible( false );

	this->mLevel = 1;
	this->mExp = 0;


#if 0 // �e�X�g�p
	mLevel = 10;
	this->mMaxLife = 150;
	mLife = 150;
	WeaponData data;
	data.WeaponType = WEAPON_STICK;
	data.UseCount = 40;
	this->changeWeapon(data);

#endif

    return r;
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //delete��Manager�ɔC����

	return true;
}


//---------------------------------------------------------------------
// �� ���݂̕��탌�x���̎擾
//---------------------------------------------------------------------
u32 Player::getWeaponLevel() const
{
    u32 level = 0;
    for ( int i = 0; i < 2; ++i )
    {
        if ( gWeaponBaseData[ mWeaponData.WeaponType ].NecessaryExp[ i ] <= mWeaponExps[ mWeaponData.WeaponType ] )
        {
            level = i + 1;
        }
    }
    return level + 1;
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::Update

	�t���[���X�V����

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Update()
{
	Character::Update();

	// �A�C�e���Ƃ̓����蔻��
	//CollisionToItem();


    //if ( Input.isOnTrigger( LN_BUTTON_L ) )
    //if ( Input.isPress( LN_BUTTON_L ) )
    //{
    //    NEW Effect_Test_1( getPosition() );
    //    GameAudio::PlaySE("./Data/Sound/SE/sword1.wav");
    //}

	//
	if((getCharaState()==CHARASTATE_GUARD)||((getCharaState()==CHARASTATE_SQGUARD)))
	{
		++mGuardFrame;
	}
	else
	{
		mGuardFrame = 0;
	}

	//���x���A�b�v�̏���
	if(this->mLevel<10)
	{
		//���x���A�b�v�ɕK�v�Ȍo���l�����܂����烌�x�����グ��
		u32 temp=0;
		for(int i= 0;i<mLevel;i++)
		{
			temp+=scg_nNextLevelExp[i];

		}
		//���x�����オ������ő僉�C�t�𑝂₷
		if(mExp>=temp)
		{
			this->mInvincibleFrame = 150;
			mLevel+=1;
			this->mMaxLife+=5;
			this->mLife+=30;
			if(mLevel==10)
			{
				this->mMaxLife+=5;
				mLife=mMaxLife;
			}
			if(this->mLife>=mMaxLife)
			{
				mLife=mMaxLife;
			}
			if(this->mMaxLife>=150)
			{
				this->mMaxLife = 150;
			}
			printf("LevelUP�I\n");
			printf("level%d\n",mLevel);

            GameFrontendManager::getInstance()->showLevelUp();
		}
	}
    

	return true;
}

//---------------------------------------------------------------------------
// �� �t���[���X�V���� (�I�u�W�F�N�g�ɉe����^���鏈��)
//---------------------------------------------------------------------------
bool Player::UpdateSelf()
{
	return Character::UpdateSelf();
}




//---------------------------------------------------------------------------
/*! 
	@brief Player::HandleEvent

	�C�x���g����

	@param[in]      EventType event_ �C�x���g�^�C�v
	@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Player::HandleEvent(::EventType event_,void *args_)
{
    return Character::HandleEvent( event_, args_ );
}


//---------------------------------------------------------------------------
// �� �R���e�B�j���[�ɔ����ď�Ԃ�ۑ�����
//---------------------------------------------------------------------------
void Player::commit()
{
    mBackup.Life = this->getLife();
    mBackup.Exp = mExp;
    mBackup.Level = mLevel;
    mBackup.WeaponData = this->getWeaponData();

    printf( "�� Player::commit  ����:%d ��:%d\n", mBackup.WeaponData.WeaponType, mBackup.WeaponData.UseCount );
}

//---------------------------------------------------------------------------
// �� commit() ���Ă񂾎��̏�Ԃɕ�������
//---------------------------------------------------------------------------
void Player::reset()
{
    this->Initialize();

    //this->setLife( mBackup.Life );
    mExp = mBackup.Exp;
    mLevel = mBackup.Level;
    this->changeWeapon( mBackup.WeaponData );

    this->setLife( this->getMaxLife() );

     printf( "�� Player::reset  ����:%d ��:%d\n", mBackup.WeaponData.WeaponType, mBackup.WeaponData.UseCount );
}


//=============================================================================
//								End of File
//=============================================================================
