//=============================================================================
/*! 
    @addtogroup 
    @file       Valfirle.cpp
    @brief      ヴァルファーレクラスの実装
    
    ヴァルファーレ専用AI
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2012/02/15
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2012 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2012/02/15 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "Valfirle.h"
#include "Player.h"
#include "./../Game/GameManager.h"

//---------------------------------------------------------------------------
// ● オブジェクトを作成する
//---------------------------------------------------------------------------
Valfirle* Valfirle::create( void* args_, bool is_entity_ )
{
    Valfirle* o = NEW Valfirle();
    o->Initialize( *static_cast< CreateData* >( args_ ) );
    o->mIsEntity = is_entity_;

    // 自分がこのホストで作成されたものであれば、自分以外のホストに生成したことを送信する
    if ( is_entity_ )
    {
        GameManager::getInstance()->getGameSession()->sendCreatedObjectEvent( OBJ_ENEMY, args_, sizeof( CreateData ) );
    }

    return o;
}


//---------------------------------------------------------------------------
// ● オブジェクトをランダムで作成する
//---------------------------------------------------------------------------
Valfirle* Valfirle::createRandom()
{
    Valfirle::CreateData data;
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
	Valfirle* pEnemy = Valfirle::create( &data );

    return pEnemy;
}


//---------------------------------------------------------------------------
/*! 
	@brief Valfirle::Valfirle

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Valfirle::Valfirle()
    : mWeaponLevel  ( 1 )
{
	this->m_pszName = "Valfirle"; //一時的。後で適当な名前を代入する
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
	this->m_nPhase = 0;

	for(int i = 0;i < 10;++i)
	{
		this->m_nNum[i] = 0;
	}

    // 攻撃対象グループは敵側
    setAttackedGroup( ATKGROUP_ENEMY );
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::~Enemy

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Valfirle::~Valfirle()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Valfirle::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Valfirle::Initialize( const CreateData& data_ )
{
	this->mScore = 100000;
	this->mExp = 500;

    this->mPosition = data_.Position;
    this->mVelocity = data_.Velocity;
    mWeaponLevel    = data_.WeaponLevel;
    
	bool r = Character::Initialize();
	this->mCharaPanel->SetColorScale(Color(0.8f,0.8f,0.95f));
    this->m_pszName = "Valfirle"; //一時的。後で適当な名前を代入する
	this->mLife = this->mMaxLife = scg_nValfirleLife[GameManager::getInstance()->getRank()];

	this->m_nRandAttackRange = ::rand() % 40 - 20;
	this->m_nRandAttackDelay = ::rand() % 40 - 10;
	this->m_nRandSearchRange = this->scm_nSearchX;

	WeaponData data;
	data.UseCount = -1;
	data.WeaponType =  static_cast<WeaponType>(data_.WeaponType);
	this->changeWeapon(data);


    GameManager::getInstance()->setLastBossCharacter( this );

    // デバッグ用
    this->mLife = 1;

	return r;
}


//---------------------------------------------------------------------------
/*! 
	@brief Valfirle::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Valfirle::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //deleteはManagerに任せる

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Valfirle::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Valfirle::Update()
{
    return Character::Update();
}

//---------------------------------------------------------------------------
// ● フレーム更新処理 (オブジェクトに影響を与える処理)
//---------------------------------------------------------------------------
bool Valfirle::UpdateSelf()
{
	//死んだ際に持っている武器を落とす
	if(this->mLife <= 0 && !this->m_bCreateWeapon)
	{
		this->m_bCreateWeapon = true;
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
	//未定義
	case ENEMY_ACT_UNDEF:
		this->m_eAction = ENEMY_ACT_WAIT;
		break;

	//待機
	case ENEMY_ACT_WAIT:
		//フェーズの移行をチェックする
		this->ChangePhase();

		//範囲内探索を行う
		if(this->SearchPlayer())
		{
			//範囲内であれば追跡を開始する
			this->m_eAction = ENEMY_ACT_CHASE;
			break;
		}

		//散歩を開始する
		if(this->m_nWalkIntvCnt > this->scm_nWalkIntv)
		{
			this->m_nWalkRangeCnt = ::rand() % this->scm_nWalkRange; //散歩距離の設定
			this->m_nWalkIntvCnt = 0;
			this->m_bWalkDir = static_cast<bool>(::rand() % 2);
			this->m_eAction = ENEMY_ACT_WALK;
		}
		else
		{
			++this->m_nWalkIntvCnt;
		}
		break;

	//散歩
	case ENEMY_ACT_WALK:
		//散歩を行っている
		if(this->m_nWalkRangeCnt)
		{
			if(this->m_bWalkDir)
				right = true;
			else
				left = true;

			--this->m_nWalkRangeCnt;
		}
		//散歩終わり
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//追跡
	case ENEMY_ACT_CHASE:
		//フェーズの移行をチェックする
		this->ChangePhase();

		//プレイヤーが探索範囲内である
		if(this->SearchPlayer())
		{
			//Playerは右にいる
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				right = true;
			}
			//Playerは左にいる
			else
			{
				left = true;
			}

			//まれにジャンプする
			if(!(::rand() % scg_nValfirleJumpRatio[GameManager::getInstance()->getRank()]))
			{
				button_B = true;
			}

			//プレイヤーが観察範囲内である
			if(::abs(this->mPosition.x + ::rand() % this->scm_nSearchRand - pPlayer->getPosition().x) <= this->scm_nStandbyRange)
			{
				//ランダムで観察を開始する
				if(!(::rand() % scg_nValfirleStandbyRatio[GameManager::getInstance()->getRank()]))
				{
					this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
					this->m_eAction = ENEMY_ACT_STANDBY;
					break;
				}
			}

			//プレイヤーが攻撃範囲内である
			if(this->SearchAttack1Range())
			{
				this->m_eAction = ENEMY_ACT_ATTACK_RANGE;
				break;
			}
		}
		else
		{
			//探索範囲外であれば待機に戻す
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//観察
	case ENEMY_ACT_STANDBY:
		//プレイヤーがジャンプした瞬間対空攻撃を行う
		if(pPlayer->getCharaState() == CHARASTATE_JUMP)
		{
			//this->m_nStandbyCnt = 0;
			break;
		}

		//観察を行う
		if(this->m_nStandbyCnt)
		{
			--this->m_nStandbyCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//逃走
	case ENEMY_ACT_ESCAPE:
		if(this->m_nEscapeRangeCnt)
		{
			//Playerは右にいる
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				left = true;
			}
			//Playerは左にいる
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

	//攻撃範囲内
	case ENEMY_ACT_ATTACK_RANGE:
		if(this->SearchAttack1Range())
		{
			//ランダムで攻撃を開始する
			if(!(::rand() % scg_nValfirleAttackRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_eAction = ENEMY_ACT_ATTACK;
				break;
			}
			//ランダムで防御を開始する
			if(!(::rand() % scg_nValfirleGuardRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_GUARD;
				break;
			}
			//ランダムで観察を開始する
			if(!(::rand() % scg_nValfirleStandbyRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_STANDBY;
				break;
			}
			//ランダムでしゃがみガードを開始する
			if(!(::rand() % scg_nValfirleSquatGuardRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_SQUAT_GUARD;
				break;
			}
			//ランダムでしゃがみを開始する
			if(!(::rand() % scg_nValfirleSquatRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nSquatCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_SQUAT;
				break;
			}
			//ランダムで逃走を開始する
			if(!(::rand() % scg_nValfirleEscapeRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nEscapeRangeCnt = ::rand() % this->scm_nEscapeRange;
				this->m_eAction = ENEMY_ACT_ESCAPE;
				break;
			}
		}
		//攻撃範囲外
		else
		{
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//攻撃中
	case ENEMY_ACT_ATTACK:
		if(this->SearchAttack1Range())
		{
			switch(this->m_eCharaState)
			{
			case CHARASTATE_ATTACK_SQUAT_ATTACK:
			case CHARASTATE_ATTACK_JUMP_ATTACK:
			case CHARASTATE_ATTACK_ANTIAIR_ATTACK:
			case CHARASTATE_ATTACK_DUSH_ATTACK:
				//特殊攻撃後は待機に戻す
				this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_1:
				//通常攻撃2段目
				if(scg_bValfirleAttack2Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nValfirleAttack2Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_2:
				//通常攻撃3段目
				if(scg_bValfirleAttack3Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nValfirleAttack3Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			default:
				//ジャンプ攻撃は事前にジャンプする
				if(!(::rand() % scg_nValfirleJumpAttackRatio[GameManager::getInstance()->getRank()]))
				{
					button_B = true;
					break;
				}
				//しゃがみ攻撃
				if(!(::rand() % scg_nValfirleSquatAttackRatio[GameManager::getInstance()->getRank()]))
				{
					Down = true;
				}

				//通常攻撃1段目
				button_A = true;

				break;
			}

			//Player座標が上であれば、対空攻撃をする
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

	//防御
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

	//しゃがみガード
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

	//しゃがみ
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

    // 死亡 (死亡モーション中) は入力を受け付けない
    if ( isDead() )
    {
        return true;
    }

    // 移動できる場合 (のけぞり中等ではない)
    if ( mStunFrame == 0 )
    {
        //------------------------------------------------------
        // 攻撃動作中の場合
        if ( isAttacking() )
        {
			// 行動制限解除（=出し終わり）してないと操作不可
			if ( !mAttackLocked )
			{
				// 連続攻撃
				if ( button_A )
				{
					// 行動制限
					this->AttackLock();

					switch( m_eCharaState )
					{
					case CHARASTATE_ATTACK_1:
						if(scg_bValfirleAttack2Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_2, NULL, 0 );
						break;

					case CHARASTATE_ATTACK_2:
						if(scg_bValfirleAttack3Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_3, NULL, 0 );
						break;

					default:
						// 万が一おかしい値になったらロック解除
						this->AttackUnLock();
						break;
					}
				}
			}
        }
        //------------------------------------------------------
        // 攻撃動作中ではない場合
        else
        {
			
			// 攻撃開始
            if ( button_A && m_eCharaState != EV_ACTION_ATTACK_1 )  // 後ろのは仮
            {
                // ジャンプ中の場合
                if ( mJump )
                {
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_JUMP_ATTACK, NULL, 0 );
                }
                // しゃがみ中の場合
                else if ( Down )
                {
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_SQUAT_ATTACK, NULL, 0 );
                }
				// 上を押しながらの場合
				else if ( !mTouchLadder && Up )
				{
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
					this->m_nAttackDelay = 0;
				}
                // 以上以外は通常攻撃
                else
                {
					// 攻撃のため行動制限
					if(scg_bValfirleAttack1Permission[GameManager::getInstance()->getRank()])
					{
						this->AttackLock();
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_1, NULL, 0 );
					}
                }

                return true;
            }

			// ガード
			if ( !Down && Guard && mOnGround && !mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_GUARD, NULL, 0 );
				return true;
			}

			// 向きを変えるための処理
			if ( right )
			{
				setDirection( CHARADIR_RIGHT );
			}
			else if ( left )
			{
				setDirection( CHARADIR_LEFT );
			}

			// 右移動
			//if ( !mClimbLadder && right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
			//{
			//	// 方向をつけて EV_ACTION_RUN イベントを送る。
			//	// このあと、HandleEvent() で実際に移動を開始する。
			//	// このイベントはキューイングせず、即座に HandleEvent() に送られる。
			//	//u32 dir = CHARADIR_RIGHT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		// getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}
			//// 左移動
			//else if( !mClimbLadder && left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) )
			//{
			//	//u32 dir = CHARADIR_LEFT;

			// 移動
			if ( ( !Guard && !this->mClimbLadder && right && !left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
				|| ( !Guard && !this->mClimbLadder && left && !right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) ) )
			{
				if ( !Down )
					getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			}
			// 左右のいずれも押されていない場合は待機にする
			// 梯子離したときも待機で。
			// (後ろの mState != CHARASTATE_WAIT は、待機中に連続でイベントが送られないようにするために必要)
			else if ( ( !Guard && this->mOnGround && ( ( !right && !left ) || ( right && left ) ) && !Down && !this->mClimbLadder && m_eCharaState != CHARASTATE_WAIT )
				|| this->mNewTouchObj != OBJ_LADDER && this->mOldTouchObj == OBJ_LADDER && m_eCharaState != CHARASTATE_WAIT && m_eCharaState != CHARASTATE_JUMP && m_eCharaState != CHARASTATE_RUN )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
			}

			// ジャンプ開始
			if ( button_B && m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder ) )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				return true;
			}

			// しゃがみ開始
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// しゃがみながらガードした場合
				// ガードしながらしゃがんだ場合
				if ( ( ( GuardTrigger ) || ( DownTrigger && Guard ) ) && m_eCharaState != CHARASTATE_SQGUARD )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT_GUARD, NULL, 0 );
				}
				else if ( !Guard && m_eCharaState != CHARASTATE_SQUAT )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT, NULL, 0 );
				}
			}

			// はしごつかみ
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

			// はしご上昇
			if ( Up && m_eCharaState != CHARASTATE_LADDER_UP && mClimbLadder )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				return true;
			}
			// はしご下降
			else if ( Down && m_eCharaState != CHARASTATE_LADDER_DOWN && mClimbLadder )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				return true;
			}
			// はしご待機
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
	@brief Valfirle::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Valfirle::HandleEvent(u32 event_,void *args_)
{
	///////////////////////////////////////// 戦闘不能開始
	switch ( event_ )
	{
        case EV_ACTION_START_DEAD:
			//経験値の処理
			GameManager::getInstance()->getPlayer()->setExp(GameManager::getInstance()->getPlayer()->getExp()+this->mExp);

			printf("score%d\n",this->mScore);
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2))); 
            break;
	}
	return Character::HandleEvent( event_, args_ );
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::SearchPlayer

	プレイヤーの探索を行う

	@return         bool
	- true  範囲内
	- false 範囲外
	@exception      none
*/
//---------------------------------------------------------------------------
bool Valfirle::SearchPlayer()
{
	bool bRes = false;
	Player *pPlayer = GameManager::getInstance()->getPlayer();

	if(::abs(this->mPosition.y - pPlayer->getPosition().y) < this->scm_nSearchY)
	{
		//探索範囲内である
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) < this->m_nRandSearchRange)
		{
			bRes = true;
		}
	}

	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief Valfirle::SearchAttack1Range

	攻撃範囲探索を行う

	@return         bool
	- true  範囲内
	- false 範囲外
	@exception      none
*/
//---------------------------------------------------------------------------
bool Valfirle::SearchAttack1Range()
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
		//攻撃範囲内
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) <= r->x + r->width - 40) //40は一時的
		{
			bRes = true;
		}
	}

	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief Valfirle::ChangePhase

	フェーズの変更を行う

	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void Valfirle::ChangePhase()
{
	//第二段階への変更を行う
	if(this->mLife <= scg_nValfirleLifePhase2[GameManager::getInstance()->getRank()])
	{
		this->m_nPhase = 1;
	}

	return;
}


//=============================================================================
//								End of File
//=============================================================================
