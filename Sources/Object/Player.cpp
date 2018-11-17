//=============================================================================
/*! 
    @addtogroup 
    @file       Player.cpp
    @brief      
    
    プレイヤークラスの実装
    
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
#include "Player.h"
#include "../Frontend/CharacterNamePlate.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Effect/Effect_1.h"

//---------------------------------------------------------------------------
/*! 
	@brief Player::Player

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Player::Player()
{
	this->m_pszName = '\0'; //一時的。後で適当な名前を代入する
	this->m_eCharaState = CHARASTATE_WAIT;

	this->m_AnimePuttern = 0;

    // 攻撃対象グループはプレイヤー側
    setAttackedGroup( ATKGROUP_PLAYER );

    memset( mWeaponExps, 0, sizeof( mWeaponExps ) );
}


//---------------------------------------------------------------------------
/*! 
	@brief Player::~Player

	デストラクタ

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

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Initialize()
{
    this->Release();

    memset( mWeaponExps, 0, sizeof( mWeaponExps ) );

    bool r = Character::Initialize();

    // プレイヤーは後から描画するようにする
    //this->mCharaPanel->setPriority( 100 );



    // プレイヤーキャラクターのネームプレートは表示しない
    this->mCharacterNamePlate->setVisible( false );

	this->mLevel = 1;
	this->mExp = 0;


#if 0 // テスト用
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

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //deleteはManagerに任せる

	return true;
}


//---------------------------------------------------------------------
// ● 現在の武器レベルの取得
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

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Player::Update()
{
	Character::Update();

	// アイテムとの当たり判定
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

	//レベルアップの処理
	if(this->mLevel<10)
	{
		//レベルアップに必要な経験値がたまったらレベルを上げる
		u32 temp=0;
		for(int i= 0;i<mLevel;i++)
		{
			temp+=scg_nNextLevelExp[i];

		}
		//レベルが上がったら最大ライフを増やす
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
			printf("LevelUP！\n");
			printf("level%d\n",mLevel);

            GameFrontendManager::getInstance()->showLevelUp();
		}
	}
    

	return true;
}

//---------------------------------------------------------------------------
// ● フレーム更新処理 (オブジェクトに影響を与える処理)
//---------------------------------------------------------------------------
bool Player::UpdateSelf()
{
	return Character::UpdateSelf();
}




//---------------------------------------------------------------------------
/*! 
	@brief Player::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Player::HandleEvent(::EventType event_,void *args_)
{
    return Character::HandleEvent( event_, args_ );
}


//---------------------------------------------------------------------------
// ● コンティニューに備えて状態を保存する
//---------------------------------------------------------------------------
void Player::commit()
{
    mBackup.Life = this->getLife();
    mBackup.Exp = mExp;
    mBackup.Level = mLevel;
    mBackup.WeaponData = this->getWeaponData();

    printf( "◆ Player::commit  武器:%d 回数:%d\n", mBackup.WeaponData.WeaponType, mBackup.WeaponData.UseCount );
}

//---------------------------------------------------------------------------
// ● commit() を呼んだ時の状態に復元する
//---------------------------------------------------------------------------
void Player::reset()
{
    this->Initialize();

    //this->setLife( mBackup.Life );
    mExp = mBackup.Exp;
    mLevel = mBackup.Level;
    this->changeWeapon( mBackup.WeaponData );

    this->setLife( this->getMaxLife() );

     printf( "◆ Player::reset  武器:%d 回数:%d\n", mBackup.WeaponData.WeaponType, mBackup.WeaponData.UseCount );
}


//=============================================================================
//								End of File
//=============================================================================
