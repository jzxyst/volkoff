//=============================================================================
//�y AttackedObject �z
//=============================================================================

#include "AttackedObject.h"
#include "attackedobject.h"
#include "../Game/GameManager.h"
//#include "Character.h"
#include "Player.h"
//=============================================================================
// �� AttackedObject �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
AttackedObject::AttackedObject()
    : mAttackedGroup    ( 0 )
{
    getManager()->addAttackedObject( this );
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
AttackedObject::~AttackedObject()
{
    getManager()->removeAttackedObject( this );
}

//---------------------------------------------------------------------
// �� ���̃I�u�W�F�N�g�ɍU����^����
//---------------------------------------------------------------------
void AttackedObject::attackEffect( GameObject* attacker_, int damage_, u32 range_rate_, u32 critical_rate_, const LVector3& brow_vec__, u32 stun_frame_ )
{
    LVector3 brow_vec_ = brow_vec__;

    // �����ƃN���e�B�J���Ƃ��̌v�Z������ damage �ɓ���Ă���

    float dmg_rate = static_cast< float >( ( 100 - range_rate_ ) + ( rand() % ( range_rate_ * 2 ) ) ) * 0.01f;
    u32 damage = dmg_rate * damage_;
	u8 criticalflag=0;
	u8 guardflag=0;

	u8 Level = GameManager::getInstance()->getPlayer()->getLevel();
	u32 Floor = GameManager::getInstance()->getFloorNum();
	u8 Rank = GameManager::getInstance()->getRank();


	if((attacker_->getObjType() == OBJ_GRENADE)&&(this->getObjType() ==OBJ_CHARACTER)&&(damage_>=60))
	{
		damage=50;
	}
	//�G�̏e�e���������邽��
	if((attacker_->getObjType() == OBJ_BULLET)&&(this->getObjType() ==OBJ_CHARACTER))
	{
		damage=damage/2;
	}
	//��Փx�ɂ���_���[�W�̌v�Z
	if(getObjType()==OBJ_CHARACTER)
	{

		switch(Rank)
		{
		case RANK_EASY:
			damage=damage/5;
			break;
		case RANK_NOMAL:
			damage=damage/2.5;
			break;
		case RANK_HARD:
			damage=damage/2;
			break;
		case RANK_VALFIRLE:
			damage=damage/2+damage/4;
			break;

		}
		if(damage==0)
			damage=1;
	}
	//�v���C���[�̌��݃��x�������t���A���̂ق����傫�������ꍇ�G�̃N���e�B�J�������Փx�ɂ���Ă�����
	if((attacker_->getObjType()==OBJ_ENEMY)&&(Level<Floor+1))
	{
		critical_rate_+=(Rank+1)*(Floor+1);
		//printf("�N���e�B�J����%d\n",critical_rate_);
	}
	//

	//�v���C���[�̃��x�����Q�ȏ�Ȃ�N���e�B�J�������グ��
	if((attacker_->getObjType()==OBJ_CHARACTER)&&(Level>=2))
	{
		critical_rate_+=Level*3;
	}

	//�v���C���[�m�����ɃN���e�B�J�����A�b�v
	if((attacker_->getLife()<=20)&&(attacker_->getObjType()==OBJ_CHARACTER)&&(critical_rate_<=50))
	{
		critical_rate_=50;
	}

    // ���m���ŃK�[�h����悤�ȏꍇ�́AEV_ATTACK_EFFECT �𑗂�O�� �K�[�h�J�n�C�x���g�𑗂�B

	Character* chara = dynamic_cast< Character* >( this );
	if ( chara )
	{

		// �K�[�h����ꍇ
		if ((chara->getCharaState()==CHARASTATE_GUARD)||(chara->getCharaState()==CHARASTATE_SQGUARD))
		{
			guardflag=1;
			//�K�[�h���_���[�W�����炷
			if(chara->getCharaState()==CHARASTATE_GUARD)
			{
				damage=damage/10+1;
				brow_vec_.y=0;
				brow_vec_.x=25;
			}
			else
			{
				damage=damage/7+1;
				brow_vec_.y=0;
				brow_vec_.x=15;			
			}
			//�v���C���[�̓K�[�h�����u�Ԃ̃_���[�W���ɂ���
			if((chara->getObjType()==OBJ_CHARACTER)&&(10+Level*2>=GameManager::getInstance()->getPlayer()->getGuardFrame()))
			{
				//printf("�W���X�g��-��\n");
				damage=0;
			}
			//�K�[�h�����E����Ȃ��悤�ɂ���
			if(this->getLife()<=3)
			{
				damage=0;
			}
			//���ȏ�̃X�^���t���[���̍U�����󂯂���̂����点��
			if(((stun_frame_>=60)&&(CHARASTATE_GUARD))||((stun_frame_>=40)&&(CHARASTATE_SQGUARD)))
			{
				stun_frame_=30;
			}
			else
			{
				stun_frame_=0;
			}

		}
		else
		{

		// �K�[�h���Ȃ��ōU�����󂯂�ꍇ
			//�N���e�B�J���̌v�Z
			if(rand()%100<=critical_rate_)
			{
				damage*=2;
				criticalflag=1;
				//printf("�N���e�B�J��");
			}

		}
		//�v���C���[�̂����莞���G
		//if((chara->getCharaState()==CHARASTATE_STUN)&&(this->getObjType() == OBJ_CHARACTER))
		//�v���C���[�̂����莞���G�@�C�[�W�[�ȊO�̎��@�v���C���[�̃��x�����t���A����1�ȏ㑽���ꍇ����
		if((chara->getCharaState()==CHARASTATE_STUN)&&(this->getObjType() == OBJ_CHARACTER)&&((Level+1 > Floor)||(Rank == RANK_EASY)))
		//if(chara->getObjType()==OBJ_CHARACTER)//�f�o�b�O�p
		{
			if(stun_frame_<=60)
			{
				criticalflag=0;
				damage=0;
				stun_frame_=0;
				brow_vec_.y=0;
				brow_vec_.x=0;	
			}
		}
		//���G���Ԓ����G
		if(chara->getInvincibleFrame()>0)
		{
			//printf("muteki\n");
			criticalflag=0;
			damage=0;
			stun_frame_=0;
			brow_vec_.y=0;
			brow_vec_.x=0;		
		}

		//��Փx�n�[�h�ȏ�Ń{�X�����m���Ń_�E�����Â炭����
		if((chara->getWeaponData().WeaponType>=WEAPON_BOSS_BEGIN)&&(rand()%2==1)&&(Rank>=2))
		{
			//printf("muteki\n");
			criticalflag=0;
			if(stun_frame_>=25)
				stun_frame_=25;
			if(damage>=10)
				damage=damage/2+damage/4;
		}
		if((chara->getWeaponData().WeaponType>=WEAPON_BOSS_BEGIN)&&(attacker_->getObjType() == OBJ_BULLET))
		{
			damage=damage/2;
		}
	}

	//if ( 0 < stun_frame_ && 0 != this->mVelocity.x && !this->mOnGround )
	if(60 <= stun_frame_)
	{
		// �ӂ��Ƃ΂�
		getManager()->postEvent( getHandle(), EV_ACTION_BLOW, &stun_frame_, sizeof( u32 ) );
	}
	else
	{
		// �̂����点��
		if(stun_frame_!=0)
		getManager()->postEvent( getHandle(), EV_ACTION_STUN, &stun_frame_, sizeof( u32 ) );
	}

	//
	//printf("damege%d\n",damage);
    AttackEventArg arg;
    arg.Damage      = damage;
	//    arg.Damage      = 0;//debug
	arg.Criticalflag=criticalflag;
	arg.Guardflag=guardflag;
    arg.BrowVector  = brow_vec_;
    arg.BrowVector.x *= ( attacker_->getDirection() == CHARADIR_LEFT ) ? -1.0f : 1.0f;  // �U�����̌����ɂ���Ăӂ���΂������𔽓]����
	arg.AttackerHandle = attacker_->getHandle();
    getManager()->postEvent( getHandle(), EV_APPLY_DAMAGE, &arg, sizeof( AttackEventArg ) );

    

    // �����ł͂܂� mLife �̌��Z�ȂǁA�����o�ϐ��͑��삵�Ȃ��B
    // ����� HandleEvent() �� EV_ATTACK_EFFECT ���󂯎�������ɍs���B

    // ����� HandleEvent �ŁB
    //if ( mLife <= 0 )
    //{
    //    // �퓬�s�\�J�n (�󂯎�������ŁA���[�V�������J�n����Ƃ�)
    //    getManager()->postEvent( 0xffffffff, EV_ACTION_START_DEAD, &mHandle, sizeof( mHandle ) );
    //}
}

//---------------------------------------------------------------------
// �� �C�x���g����
//---------------------------------------------------------------------
int AttackedObject::HandleEvent( u32 event_,void *args_ )
{
    //switch ( event_ )
    {
        // �̂�����J�n (Character �Œ�`)
        //case EV_ACTION_STUN:

        // �_���[�W��^���� (�p����Œ�`)
        //case EV_APPLY_DAMAGE:

        
    }

    return 0;
}


//=============================================================================
//								end of file
//=============================================================================
