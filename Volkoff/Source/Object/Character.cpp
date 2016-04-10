//=============================================================================
/*! 
    @addtogroup 
    @file       Character.cpp
    @brief      
    
    キャラクタークラスの実装
    
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
      -# 作成
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

	デフォルトコンストラクタ

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
	this->m_pszName = '\0'; //一時的。後で適当な名前を代入する
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

	デストラクタ

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
// ● キャラクターの向きを設定する
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
// ● ワールド座標空間上での当たり判定矩形を返す
//---------------------------------------------------------------------
const LRect* Character::getBoundingRect()
{
    const LRect* rc = mCollision->getDmgCollisionByIndex( getAnimePuttern() );
    if ( rc )
    {
        // 右向き
        if ( m_eDirection == CHARADIR_RIGHT )
        {
            mWorldBoundingRect.Set(
                static_cast< int >( mPosition.x - ( mOrigin.x - rc->x ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->width, rc->height );
            return &mWorldBoundingRect;
        }
        // 左向き
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
// ● ローカル座標空間上での当たり判定矩形を返す (左上からの位置)
//---------------------------------------------------------------------
const LRect* Character::getLocalBoundingRect()
{
    static LRect tmp;

    const LRect* rc = mCollision->getDmgCollisionByIndex( getAnimePuttern() );
    if ( rc )
    {
        // 右向き
        //if ( m_eDirection == CHARADIR_RIGHT )
        {
            tmp.Set( rc->x, rc->y, rc->width, rc->height );
            return &tmp;
        }
        // 左向き
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
// ● ワールド座標空間上での攻撃当たり判定矩形を返す
//---------------------------------------------------------------------
const LRect* Character::getAttackBoundingRect()
{
    static LRect tmp;

    const LRect* rc = mCollision->getAtkCollisionByIndex( getAnimePuttern() );
    if ( rc )
    {
        // 右向き
        if ( m_eDirection == CHARADIR_RIGHT )
        {
            tmp.Set(
                static_cast< int >( mPosition.x - ( mOrigin.x - rc->x ) ),
                static_cast< int >( mPosition.y + ( mOrigin.y - rc->y ) ),
                rc->width, rc->height );
            return &tmp;
        }
        // 左向き
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
// ● アニメーションパターンの設定
//---------------------------------------------------------------------
void Character::setAnimePuttern( int puttern_ )
{
    m_AnimePuttern = puttern_;

    int x = ( m_AnimePuttern % 12 ) * 160;
    int y = ( m_AnimePuttern / 12 ) * 160;




    /*
    // 左上 X 座標の計算
    int x = ( m_AnimePuttern % 6 ) * 160;
    if ( m_AnimePuttern >= 72 )
    {
        x += 960;
    }

    // 左上 Y 座標の計算
    int y = ( m_AnimePuttern / 6 ) * 160;
    if ( m_AnimePuttern >= 72 )
    {
        y %= 1920;
    }
    */

    mCharaPanel->SetSrcRect( LRect( x, y, 160, 160 ) );

    // 原点も設定する
	mOrigin.Set(
		this->mCollision->getOriginByIndex( m_AnimePuttern ).x,
		this->mCollision->getOriginByIndex( m_AnimePuttern ).y,
		0.0f );
	this->mCharaPanel->SetCenter( mOrigin.x - 80, -mOrigin.y + 80, 0 );
}

//---------------------------------------------------------------------------
/*! 
	@brief Character::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Initialize()
{
	this->Release();

	//this->m_pszName = '\0'; //一時的。後で適当な名前を代入する    Enemy の initialize で名前設定するときに不便だったのでカット
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

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //deleteはManagerに任せる
	SAFE_DELETE( this->mCollision );
    SAFE_DELETE( mCharacterNamePlate );

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Character::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Character::Update()
{
    // スクリプトを使って更新
    CharacterScriptInterface::getInstance()->update( this );


    // 死亡モーション中の場合 (とりあえず。必要があればスクリプトに移す)
    //if ( getCharaState() == CHARASTATE_DEAD ) // 吹っ飛びアニメのままフェードアウトとかの場合はコレじゃダメ
    if ( isDead() )
    {
		mClimbLadder = false;
        setAnimePuttern( 102 + mFrameCount / 10 );
        mCharaPanel->SetOpacity( 1.0f - ( static_cast< float >( mFrameCount ) * 0.025641f ) ); // 0.025641f は 39 の逆数
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
    // ▼ 移動とジャンプ、地形との当たり判定の処理

	// ジャンプ
	if ( mJump )
	{
		//mVelocity.Y += scg_fJumpHeight;
	}

	// 空中にいる場合
	if ( !mOnGround )
	{
        // 地面の上にいなければ重力で加速
		mAccel.y -= GRAVITY_ACCEL;

		if(mVelocity.x>=16)
			mVelocity.x=16;
		if(mVelocity.x<=-16)
			mVelocity.x=-16;
	}
    // 地面上にいる場合
	else if ( !mClimbLadder || mStandOnObject )
	{
		// 地面に当たっていて、下方向の加速度がある場合はリセットする
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
	//アニメーション
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

	case CHARASTATE_LADDER_WAIT:    //はしご待機
		this->mVelocity.y = 0;
		break;

	// ▼ はしご昇降速度変更はここ----------------
	case CHARASTATE_LADDER_UP:      //はしご上り

		if ( this->mClimbLadder )
		{
			this->mVelocity.y = static_cast< float >( scg_fRunSpeed*0.9f );
		}
		else
		{
			getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
		}
		break;

	case CHARASTATE_LADDER_DOWN:    //はしご降り

		if ( this->mClimbLadder )
		{
			this->mVelocity.y = static_cast< float >( -scg_fRunSpeed*0.9f );
		}
		else
		{
			getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
		}
		
		break;
	// ▲ はしご昇降速度変更はここ----------------
	}


	// 梯子につかまってるときは横方向の速度、重力による加速度を消す
	if ( mClimbLadder )
	{
		mVelocity.x = 0;
		if ( !mJump ) mAccel.y = 0;
	}
	// それ以外は普通に加速
	else
	{
		mVelocity += mAccel;
		if ( mVelocity.y < -10.0f )
		{
			mVelocity.y = -10.0f;
		}
	}

    // 当たり判定全般は、判定用の矩形がある場合にのみ行う
    const LRect* rc = getBoundingRect();
    if ( rc )
    {
        LRect col_rect = *rc;

        // 移動した後の座標
	    LVector3 d_pos = mPosition + mVelocity;

        // 移動前の判定用矩形の座標
        float px = static_cast< float >( col_rect.x );
        float py = static_cast< float >( col_rect.y );

        // 矩形を移動させて、移動後の判定領域にする
        col_rect.x += static_cast< int >( mVelocity.x );
        col_rect.y += static_cast< int >( mVelocity.y );
        
	    // 移動量 (いまはつかわないかも)
	    LVector3 dest = mPosition - d_pos;

	    // マップとの当たり判定結果の、修正後の座標を格納する変数
	    LVector3 result_pos;
  		//MapManager::getInstance()->BulletCollision(col_rect);      
	    u32 result = MapManager::getInstance()->collision( col_rect, dest, &result_pos );

        // 移動前と比べて、移動量を求める
        float dx = result_pos.x - px;
        float dy = result_pos.y - py;

        // 上が当たっている場合はジャンプの加算を0にする
		if ( result & MAPCOLL_UP )
			mVelocity.y = 0;

       
		
        


	// ▼ 地上判定-------------------------------
		// 以下の場合は地面の上にいるとする
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
	// ▲ 地上判定-------------------------------

        
        

		// 実際の座標に反映させる
	    mPosition.x += dx;//result_pos.X + ( mOrigin.X - getLocalBoundingRect()->x );
        mPosition.y += dy;//result_pos.Y - ( mOrigin.Y - getLocalBoundingRect()->y );

        // オブジェクトとの当たり判定
		CollisionToObj();
    }

    // 最終的にパネルをポジションに合わせる
    this->mPosition.z = -5.0f;
    this->mCharaPanel->SetPosition(this->mPosition);

	++mFrameCount;

    // のけぞっている場合は残りフレーム数を減らしていく
    if ( mStunFrame > 0 )
    {
        --mStunFrame;
        if ( mStunFrame == 0 )
        {
            setCharaState( CHARASTATE_DEFAULT );
        }
    }

    // アイテム取得待ち中
    if ( getCharaState() == CHARASTATE_ITEMGET )
    {
        --mItemGetWaitCount;

        // タイムアウト。姿勢を元に戻す
        if ( mItemGetWaitCount <= 0 )
        {
            setCharaState( CHARASTATE_DEFAULT );
        }
    }


    mCharacterNamePlate->update();

	return true;
}

//---------------------------------------------------------------------------
// ● フレーム更新処理 (オブジェクトに影響を与える処理)
//---------------------------------------------------------------------------
bool Character::UpdateSelf()
{
    // このへんのキー入力はあとで Player に移動する予定

    // 死亡 (死亡モーション中) は入力を受け付けない
    if ( isDead() )
    {
        return true;
    }

    // 基本モーション中で武器破壊フラグがたっている場合は素手にする
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

    // 移動できる場合 (のけぞり中等ではない)
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
        // 攻撃動作中の場合
        if ( isAttacking() )
        {
			// 行動制限解除（=出し終わり）してないと操作不可
			if ( !mAttackLocked )
			{
				// 向きを変えるための処理
				if ( right )
				{
					setDirection( CHARADIR_RIGHT );
				}
				else if ( left )
				{
					setDirection( CHARADIR_LEFT );
				}

				// 連続攻撃
				if ( Input::IsTriggered( LN_BUTTON_A ) )
				{
					// 行動制限
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
            if ( !Guard && !this->mClimbLadder && Input::IsTriggered( LN_BUTTON_A ) && m_eCharaState != EV_ACTION_ATTACK_1 )  // 後ろのは仮
            {
                // ジャンプ中の場合
                if ( !mOnGround )
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
				else if ( !this->mClimbLadder && Up )
				{
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
				}
                // 以上以外は通常攻撃
                else
                {
					// 攻撃のため行動制限
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_1, NULL, 0 );
                }

                return true;
            }

			// ガード
			if ( !Down && Guard && this->mOnGround && !this->mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
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

			//// 右移動
			//if ( !mClimbLadder && right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
			//{
			//	// 方向をつけて EV_ACTION_RUN イベントを送る。
			//	// このあと、HandleEvent() で実際に移動を開始する。
			//	// このイベントはキューイングせず、即座に HandleEvent() に送られる。
			//	//u32 dir = CHARADIR_RIGHT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		//getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}
			//// 左移動
			//else if( !mClimbLadder && left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) )
			//{
			//	//u32 dir = CHARADIR_LEFT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		//getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}


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

			// ジャンプ開始
			if ( button_B && this->m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder || mStandOnObject ) )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				return true;
			}

			// しゃがみ開始
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// しゃがみながらガードした場合
				// ガードしながらしゃがんだ場合
				if ( ( ( GuardTrigger ) || ( DownTrigger && Guard ) ) && this->m_eCharaState != CHARASTATE_SQGUARD )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT_GUARD, NULL, 0 );
				}
				else if ( !Guard && this->m_eCharaState != CHARASTATE_SQUAT )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT, NULL, 0 );
				}
			}

			// はしごつかみ
			if ( this->mTouchLadder
				&& this->m_eCharaState != CHARASTATE_LADDER_UP
				&& this->m_eCharaState != CHARASTATE_LADDER_DOWN
				&& this->m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				bool Catch = false;

				// 上、下を押した瞬間
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

			// はしご上昇
			if ( Up && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_UP )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				return true;
			}
			// はしご下降
			else if ( Down && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_DOWN )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				return true;
			}
			// はしご待機
			else if ( !Up && !Down && this->mClimbLadder && this->m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_WAIT, NULL, 0 );

				return true;
			}

			//アクションボタン
			if ( Input::IsTriggered( LN_BUTTON_X ) )
			{
				const LRect* rc = getBoundingRect();
				if ( rc )
				{
					//出口とのあたり判定
					u32 exit_handle =getManager()->judgeCollitionTypeSpecified( *rc, OBJ_EXIT );
					u32 exit_lock_handle =getManager()->judgeCollitionTypeSpecified( *rc, OBJ_EXIT_LOCK);
					if(exit_handle)
					{

								
					}

					if(exit_lock_handle)
					{
						//printf("鍵付き出口\n");
						if(GameManager::getInstance()->getKeyflag())
						{
// コンティニューに備えてバックアップを取る
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


                    // 武器との当たり判定
					u32 item_handle = getManager()->judgeCollitionTypeSpecified( *rc, OBJ_WEAPON );
                    if ( item_handle )
                    {
                        // アイテムを取得するためにサーバにメッセージを送る。
                        ItemRequestArgs args;
                        args.GetterHandle  = this->getHandle();
                        args.ItemObjHandle = item_handle;
                        GameManager::getInstance()->getGameSession()->sendToServer( 
                            SYSEV_ITEM_REQUEST, &args, sizeof( ItemRequestArgs ) );
                    
                        // アイテム取得アクション開始
                        //getManager()->postEvent( getHandle(), EV_ACTION_ITEM_GET, NULL, 0 );

					    return true;
                    }

                    // 鍵・アイテムとの当たり判定
                    // item_handle = getManager()->judgeCollitionTypeSpecified( *rc, OBJ_ITEM_BEGIN, OBJ_ITEM_END );
                    //if ( item_handle )
                    //{
                    //    _p("あいてむ");
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

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Character::HandleEvent(u32 event_,void *args_)
{
    AttackedObject::HandleEvent( event_, args_ );

    switch ( event_ )
    {
        ///////////////////////////////////////// 待機開始
        case EV_ACTION_WAIT:
            setCharaState( CHARASTATE_WAIT );
            break;

        ///////////////////////////////////////// 走り開始
        case EV_ACTION_RUN:
			setCharaState( CHARASTATE_RUN );
			//setDirection( *( (CharaDir*)args_ ) );
            break;

		///////////////////////////////////////// ジャンプ開始
		case EV_ACTION_JUMP:
			setCharaState( CHARASTATE_JUMP );
			this->JumpStart();
			break;

		///////////////////////////////////////// しゃがみ開始
		case EV_ACTION_SQUAT:
			setCharaState( CHARASTATE_SQUAT );
			break;

        ///////////////////////////////////////// のけぞり開始
        case EV_ACTION_STUN:
            mStunFrame = *( reinterpret_cast< u32* >( args_ ) );
            setCharaState( CHARASTATE_STUN );
            mClimbLadder = false;
            mJump = true;
            break;

		///////////////////////////////////////// ふっとび開始
		case EV_ACTION_BLOW:
			mStunFrame = *( reinterpret_cast< u32* >( args_ ) );
			setCharaState( CHARASTATE_BLOW );
			break;

		///////////////////////////////////////// はしご待機開始
		case EV_ACTION_LADDER_WAIT:
			setCharaState( CHARASTATE_LADDER_WAIT );
			break;

		///////////////////////////////////////// はしご登り開始
		case EV_ACTION_LADDER_UP:
			setCharaState( CHARASTATE_LADDER_UP );
			break;

		///////////////////////////////////////// はしご降り開始
		case EV_ACTION_LADDER_DOWN:
			setCharaState( CHARASTATE_LADDER_DOWN );
			break;

        ///////////////////////////////////////// アイテム取得開始
        case EV_ACTION_ITEM_GET:
            setCharaState( CHARASTATE_ITEMGET );
            mItemGetWaitCount = ITEMGET_WAIT_COUNT;     // タイムアウト時間
            break;

        ///////////////////////////////////////// 通常攻撃 1 段目
		case EV_ACTION_ATTACK_1:
			setCharaState( CHARASTATE_ATTACK_1 );
			break;

		///////////////////////////////////////// 通常攻撃 2 段目
		case EV_ACTION_ATTACK_2:
			setCharaState( CHARASTATE_ATTACK_2 );
			break;

		///////////////////////////////////////// 通常攻撃 3 段目
		case EV_ACTION_ATTACK_3:
			setCharaState( CHARASTATE_ATTACK_3 );
			break;

		///////////////////////////////////////// ジャンプ攻撃
		case EV_ACTION_ATTACK_JUMP_ATTACK:
			setCharaState( CHARASTATE_ATTACK_JUMP_ATTACK );
			break;

		///////////////////////////////////////// しゃがみ攻撃
		case EV_ACTION_ATTACK_SQUAT_ATTACK:
			setCharaState( CHARASTATE_ATTACK_SQUAT_ATTACK );
			break;

		///////////////////////////////////////// 対空攻撃
		case EV_ACTION_ATTACK_ANTIAIR_ATTACK:
			setCharaState( CHARASTATE_ATTACK_ANTIAIR_ATTACK );
			break;

		///////////////////////////////////////// ガード
		case EV_ACTION_GUARD:
			setCharaState( CHARASTATE_GUARD );
			break;

		///////////////////////////////////////// しゃがみガード
		case EV_ACTION_SQUAT_GUARD:
			setCharaState( CHARASTATE_SQGUARD );
			break;

        ///////////////////////////////////////// 戦闘不能開始
        case EV_ACTION_START_DEAD:
            setCharaState( CHARASTATE_DEAD );
            break;

        ///////////////////////////////////////// ダメージを与える
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

            // ダメージポップの表示
            if ( arg->Damage > 0 )
            {
                int type = ( arg->Criticalflag ) ? 3 : 1;
                LVector3 pos( this->mPosition.x + 10,  this->mPosition.y + 70, -5 );
                GameFrontendManager::getInstance()->getDamagePopManager()->popNumber( pos, arg->Damage, type );
            }
			if(mLife>0)
			{
				mLife -= arg->Damage;
				// 戦闘不能
				if ( mLife < 0 )
				{
					mLife = 0;
					// 死亡モーション開始
					getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
				}
			}


            // HP バーを表示する
            mCharacterNamePlate->startShow();

			

            //if ( mLife <= 0 )
            //{
            //    mLife = 0;

            //    // 死亡モーション開始
            //    getManager()->postEvent( getHandle(), EV_ACTION_START_DEAD, NULL, 0 );
            //}
            // まだ生きてる
            //else
            //{
                setVelocity( arg->BrowVector );
           // }
            break;
        }

        ///////////////////////////////////////// サーバから武器が送られてきた
        case EV_GET_WEAPON:
            //_p(EV_GET_WEAPON);

            WeaponData* data = reinterpret_cast< WeaponData* >( args_ );

            printf( "◆武器取得 種類:%d  使用回数:%d \n", data->WeaponType, data->UseCount );

            changeWeapon( *data );

            // 通常状態にする
            setCharaState( CHARASTATE_DEFAULT );
            break;

    }
	return 0;
}

//---------------------------------------------------------------------
// ● キャラクターの状態を変更する
//---------------------------------------------------------------------
void Character::setCharaState( CharaState state_ )
{
	// 状態に合わせた既定のモーションにする場合
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

    // とりあえず、死亡モーション中は変更を受け付けない (蘇生するとかなったら変更する必要があるけど)
 //   if ( m_eCharaState == CHARASTATE_DEAD )
 //   {
 //       mFrameCount = 0;
 //   }
	//else
	//{
	//	
	//}
	

    // アイテム取得状態以外になる場合、不具合防止のために取得待ち中カウントをリセットする
    if ( this->m_eCharaState != CHARASTATE_ITEMGET )
    {
        mItemGetWaitCount = 0;
    }
}

//---------------------------------------------------------------------
// ● 武器を変更する
//---------------------------------------------------------------------
void Character::changeWeapon( const WeaponData& weapon_data_ )
{
    // 装備が素手以外の場合
    if ( mWeaponData.WeaponType != WEAPON_NON )
    {
        // 現在持っている武器を新しいオブジェクトとしてマップ上に生成する (サーバへオブジェクト作成を送信)
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

    // 受け取った武器を装備武器として設定する
    mWeaponData = weapon_data_;


    // 当たり判定データ
    const char* filename = CharaResourceNames[ mWeaponData.WeaponType ].Collision;
    if ( !filename )
    {
        printf( "当たり判定データファイル名が NULL。代わりに素手のモノを使用\n" );
        filename = CharaResourceNames[ WEAPON_NON ].Collision;
    }
    mCollision->LoadFile( filename );

    // キャラクター画像
    filename = CharaResourceNames[mWeaponData.WeaponType].Character;
    if ( !filename )
    {
        printf( "武器テクスチャ名が NULL。代わりに素手のモノを使用\n" );
        filename = CharaResourceNames[ WEAPON_NON ].Character;
    }
    mCharaPanel->SetTexture(Assets::LoadTexture(filename));//,0xffffffff));

    // 装備を変更したことをサーバに伝える (サーバから他のホストに通知してもらう)


    // プレイヤーの場合はフロントエンドに伝えられればベストかも
}

//
// Character::AttackLock
// 攻撃時の行動制限
//
// 呼ぶとロックがかかります。
// 攻撃モーションをジャンプなどでキャンセルさせないため
//
void Character::AttackLock()
{
	mAttackLocked = true;
}

//
// Character::AttackUnLock
// 攻撃時の行動制限解除
//
// 呼ぶとロックがはずれます。
// 攻撃モーション終了時には必ず呼んでください
//
void Character::AttackUnLock()
{
	mAttackLocked = false;
}

//
// Character::JumpStart
// ジャンプ開始時に呼ぶ
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
// オブジェクトとの当たり判定
//
// 当たっている場合は
// 各種処理をする
//
void Character::CollisionToObj()
{
	//
	// 画像同士のめり込み量
	// 木箱に乗るときに必要
	//
	LVector2 overValue;
	overValue.Set( 0, 0 );

	// [11/11/15 山本] getBoundingRect() で同じ矩形がとれるので修正
    const LRect* nowRect = getBoundingRect();

	if ( nowRect )
    {
        LRect adv_rect = *nowRect;
        adv_rect.x += mVelocity.x;
        adv_rect.y += ceil( mVelocity.y );

        //_p(ceil( mVelocity.Y ));


		mOldTouchObj = mNewTouchObj;
		mNewTouchObj = static_cast< ObjectType >( GameObjectManager::getInstance()->CollisionToObject( this->getObjType(), *nowRect, &mDistance, &overValue ) );

		// 各種オブジェクトにあたったときの動作
		// 各種～についてはGameObjectManager.h 内
		//                 _ENUM_OBJECT_TYPE 参照のこと

        // 一度何にものっていない状態にする
        mStandOnObject = false;

        

	// ▼ はしご---------------------------------
        
		// はしご、はしご上端に触れているとき
		if ( this->mNewTouchObj == OBJ_LADDERTOP
			|| this->mNewTouchObj == OBJ_LADDER )
		{
			this->mTouchLadder = true;

			// はしご上端に触れているとき
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
        
	// ▲ はしご---------------------------------

#if 0
	// ▼ 木箱-----------------------------------

		if ( mNewTouchObj == OBJ_BOX )
		{
            mPosition += overValue;

            // 上にずらす必要がある場合、上に乗っているとする
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
        
	// ▲ 木箱-----------------------------------
		
	// ▼ 上に乗れるオブジェクト-----------------
		if ( mNewTouchObj != OBJ_BOX && mNewTouchObj != OBJ_LADDERTOP )
		{
            //printf("上に乗れるオブジェクト 未実装\n");
			//this->mStandOnObject = false;
		}
	// ▲ 上に乗れるオブジェクト-----------------
	

	// ▼ 回復アイテム---------------------------
		if ( this->mLife > 0 && this->getObjType() == OBJ_CHARACTER )
		{
			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_CURE_S ) )
			{
				printf("回復アイテム取得　小\n");
				GameAudio::PlaySE("./Data/Sound/SE/Powerup23.wav",1.00,1.50);

				static const int CURE_S_VALUE_ = static_cast< int >( this->mMaxLife * 0.30f );

				// 最大値を超える回復量の場合は最大値で固定
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
				printf("回復アイテム取得　中\n");
				GameAudio::PlaySE("./Data/Sound/SE/Powerup23.wav",1.00,1.50);

				static const int CURE_M_VALUE_ = static_cast< int >( this->mMaxLife * 0.60f );

				// 最大値を超える回復量の場合は最大値で固定
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
				printf("回復アイテム取得　大\n");
				GameAudio::PlaySE("./Data/Sound/SE/Powerup23.wav",1.00,1.50);

				static const int CURE_L_VALUE_ = static_cast< int >( this->mMaxLife * 0.80f );

				// 最大値を超える回復量の場合は最大値で固定
				if ( this->mLife + CURE_L_VALUE_ > this->mMaxLife )
				{
					this->mLife = this->mMaxLife;
				}
				else
				{
					this->mLife += CURE_L_VALUE_;
				}
			}
	// ▲ 回復アイテム---------------------------

	// ▼ 鍵-------------------------------------
			if ( GameObjectManager::getInstance()->judgeCollitionTypeSpecifiedAndDelete( *nowRect, OBJ_KEY ) )
			{
				printf("アイテム取得  鍵\n");
				GameManager::getInstance()->setKeyflag(1);
			}
		}
	// ▲ 鍵-------------------------------------
    }



    //---------------------------------------------------------
    // ▼ 木箱との判定



    // 自分のワールド上の左、上、右、下。
    // 上 > 下 な点に注意。下の方が 0 に近い。
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

            // ターゲットのワールド上の左、上、右、下。
            int tl = target_rc->x;
            int tt = target_rc->y;
            int tr = target_rc->x + target_rc->width;
            int tb = target_rc->y - target_rc->height;
            LVector2 tc( tl + ( tr - tl ) / 2, tb + ( tt - tb ) / 2 );
          

            // 縦方向の判定
            if ( pl + pwh < tr && pr - pwh > tl && pt >= tb && pb <= tt )
            {
                // 落下中
                if ( pc.y > tc.y )  // mVelocity.Y < 0 && 
                {
                    dy = tt - pb + 1;     // この値はプラスになる
                }
                // 上昇中、自分が対象の下にいる場合
                else if ( pc.y < tc.y ) // mVelocity.Y > 0 && 
                {
                    dy = tb - pt - 1;     // この値はマイナスになる
                }
                // Y 座標の修正
                if ( dy != 0 )
                {
                    pt += dy;
                    pb = pt - nowRect->height;
                    mPosition.y += dy;
                    mVelocity.y = 0;
                }
            }
            
            // 横の判定
            if ( pl <= tr && pr >= tl && pt >= tb && pb <= tt )
            {
                // 自分が対象の左にいる場合
                if ( pl < tl )
                {
                    dx = tl - pr - 1;     // この値はマイナスになる
                }
                // 自分が対象の右にいる場合
                else
                {
                    dx = tr - pl + 1;     // この値はプラスになる
                }

                // X 座標の修正
                pl += dx;
                pr = pl + nowRect->width;
                mPosition.x += dx;
            }
            
            // 修正後、自分のすぐ下に箱があれば乗っている
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
