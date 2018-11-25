//=============================================================================
//【 AttackedObject 】
//=============================================================================

#include "AttackedObject.h"
#include "attackedobject.h"
#include "../Game/GameManager.h"
//#include "Character.h"
#include "Player.h"
//=============================================================================
// ■ AttackedObject クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
AttackedObject::AttackedObject()
    : mAttackedGroup    ( 0 )
{
    getManager()->addAttackedObject( this );
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
AttackedObject::~AttackedObject()
{
    getManager()->removeAttackedObject( this );
}

//---------------------------------------------------------------------
// ● このオブジェクトに攻撃を与える
//---------------------------------------------------------------------
void AttackedObject::attackEffect( GameObject* attacker_, int damage_, u32 range_rate_, u32 critical_rate_, const LVector3& brow_vec__, u32 stun_frame_ )
{
    LVector3 brow_vec_ = brow_vec__;

    // ちゃんとクリティカルとかの計算をして damage に入れておく

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
	//敵の銃弾が強すぎるため
	if((attacker_->getObjType() == OBJ_BULLET)&&(this->getObjType() ==OBJ_CHARACTER))
	{
		damage=damage/2;
	}
	//難易度による被ダメージの計算
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
	//プレイヤーの現在レベルよりもフロア数のほうが大きかった場合敵のクリティカル率を難易度によってあげる
	if((attacker_->getObjType()==OBJ_ENEMY)&&(Level<Floor+1))
	{
		critical_rate_+=(Rank+1)*(Floor+1);
		//printf("クリティカル率%d\n",critical_rate_);
	}
	//

	//プレイヤーのレベルが２以上ならクリティカル率を上げる
	if((attacker_->getObjType()==OBJ_CHARACTER)&&(Level>=2))
	{
		critical_rate_+=Level*3;
	}

	//プレイヤー瀕死時にクリティカル率アップ
	if((attacker_->getLife()<=20)&&(attacker_->getObjType()==OBJ_CHARACTER)&&(critical_rate_<=50))
	{
		critical_rate_=50;
	}

    // 一定確率でガードするような場合は、EV_ATTACK_EFFECT を送る前に ガード開始イベントを送る。

	Character* chara = dynamic_cast< Character* >( this );
	if ( chara )
	{

		// ガードする場合
		if ((chara->getCharaState()==CHARASTATE_GUARD)||(chara->getCharaState()==CHARASTATE_SQGUARD))
		{
			guardflag=1;
			//ガード中ダメージを減らす
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
			//プレイヤーはガードした瞬間のダメージを零にする
			if((chara->getObjType()==OBJ_CHARACTER)&&(10+Level*2>=GameManager::getInstance()->getPlayer()->getGuardFrame()))
			{
				//printf("ジャストが-ど\n");
				damage=0;
			}
			//ガード中削り殺されないようにする
			if(this->getLife()<=3)
			{
				damage=0;
			}
			//一定以上のスタンフレームの攻撃を受けたらのけぞらせる
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

		// ガードしないで攻撃を受ける場合
			//クリティカルの計算
			if(rand()%100<=critical_rate_)
			{
				damage*=2;
				criticalflag=1;
				//printf("クリティカル");
			}

		}
		//プレイヤーのけぞり時無敵
		//if((chara->getCharaState()==CHARASTATE_STUN)&&(this->getObjType() == OBJ_CHARACTER))
		//プレイヤーのけぞり時無敵　イージー以外の時　プレイヤーのレベルよりフロア数が1以上多い場合無効
		if((chara->getCharaState()==CHARASTATE_STUN)&&(this->getObjType() == OBJ_CHARACTER)&&((Level+1 > Floor)||(Rank == RANK_EASY)))
		//if(chara->getObjType()==OBJ_CHARACTER)//デバッグ用
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
		//無敵時間中無敵
		if(chara->getInvincibleFrame()>0)
		{
			//printf("muteki\n");
			criticalflag=0;
			damage=0;
			stun_frame_=0;
			brow_vec_.y=0;
			brow_vec_.x=0;		
		}

		//難易度ハード以上でボスを一定確率でダウンしづらくする
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
		// ふっとばす
		getManager()->postEvent( getHandle(), EV_ACTION_BLOW, &stun_frame_, sizeof( u32 ) );
	}
	else
	{
		// のけぞらせる
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
    arg.BrowVector.x *= ( attacker_->getDirection() == CHARADIR_LEFT ) ? -1.0f : 1.0f;  // 攻撃側の向きによってふっ飛ばし方向を反転する
	arg.AttackerHandle = attacker_->getHandle();
    getManager()->postEvent( getHandle(), EV_APPLY_DAMAGE, &arg, sizeof( AttackEventArg ) );

    

    // ここではまだ mLife の減算など、メンバ変数は操作しない。
    // それは HandleEvent() で EV_ATTACK_EFFECT を受け取った時に行う。

    // これは HandleEvent で。
    //if ( mLife <= 0 )
    //{
    //    // 戦闘不能開始 (受け取った側で、モーションを開始するとか)
    //    getManager()->postEvent( 0xffffffff, EV_ACTION_START_DEAD, &mHandle, sizeof( mHandle ) );
    //}
}

//---------------------------------------------------------------------
// ● イベント処理
//---------------------------------------------------------------------
int AttackedObject::HandleEvent( u32 event_,void *args_ )
{
    //switch ( event_ )
    {
        // のけぞり開始 (Character で定義)
        //case EV_ACTION_STUN:

        // ダメージを与える (継承先で定義)
        //case EV_APPLY_DAMAGE:

        
    }

    return 0;
}


//=============================================================================
//								end of file
//=============================================================================
