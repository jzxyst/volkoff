//=============================================================================
/*! 
    @addtogroup 
    @file       Character.h
    @brief      キャラクター周り
    
    キャラクター周りの定義
    
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


//Include Guard
#ifndef __INCLUDE_CHARACTER_H__
#define __INCLUDE_CHARACTER_H__


/*! @par include */
#include "./GameObject.h"
//#include "AttackedObject.h"
#include "./Weapon.h"
#include "../Utility/Collision.h"
#include "../Game/GameManager.h"




/*! @enum CharaState */
typedef enum _ENUM_CHARACTER_STATE
{
    CHARASTATE_DEFAULT = 0,      ///< setCharaState() に設定することで基本の状態に戻す (正常な場合は CHARASTATE_WAIT、死亡中は CHARASTATE_DEAD にするなど。)
	CHARASTATE_WAIT,           //待機
	CHARASTATE_RUN,            //走り
	CHARASTATE_JUMP,           //ジャンプ
	CHARASTATE_SQUAT,          //しゃがみ
	CHARASTATE_STUN,           //のけぞり
	CHARASTATE_BLOW,           //吹っ飛び
	CHARASTATE_GUARD,          //ガード
	CHARASTATE_SQGUARD,        //しゃがみガード
	CHARASTATE_LADDER_WAIT,    //はしご待機
	CHARASTATE_LADDER_UP,      //はしご上り
	CHARASTATE_LADDER_DOWN,    //はしご降り
	CHARASTATE_ITENGET,        //アイテム拾い
	CHARASTATE_DEAD,           //死亡
    CHARASTATE_ITEMGET,         ///< アイテム取得のため、完了を待っている状態

    // ▼ ここから攻撃系
    CHARASTATE_ATTACK_BEGIN_,           ///< 定数の範囲の始まりを示す

	CHARASTATE_ATTACK_1,                ///< 通常攻撃1
	CHARASTATE_ATTACK_2,                ///< 通常攻撃2
	CHARASTATE_ATTACK_3,                ///< 通常攻撃3
	CHARASTATE_ATTACK_SQUAT_ATTACK,     ///< しゃがみ攻撃
	CHARASTATE_ATTACK_JUMP_ATTACK,      ///< ジャンプ攻撃
	CHARASTATE_ATTACK_ANTIAIR_ATTACK,   ///< 対空攻撃
	CHARASTATE_ATTACK_DUSH_ATTACK,      ///< ダッシュ攻撃

    CHARASTATE_ATTACK_END_              ///< 定数の範囲の終わりを示す

}CharaState;






/// キャラクター関係のリソース名をまとめた構造体
struct CharaResource
{
    const char* Character;  ///< キャラクターの画像ファイル名
    const char* Collision;  ///< 当たり判定データファイル名
    const char* Script;     ///< スクリプトファイル名
};

static const CharaResource CharaResourceNames[] = {
    // 素手
    { 
        "Data/Graphics/Character/Char_BareHands.png",
        "Data/Collision/Char_BareHands_col.dat",
        "Data/Scripts/Character_BareHands.lua"
		//"Data/Graphics/Character/Char_Scythe.png",
  //      "Data/Collision/Char_Scythe_col.dat",
  //      "Data/Scripts/BOSS_Scythe.lua"	

    },
    // 棒
    { 
        "Data/Graphics/Character/Char_Stick.png",
        "Data/Collision/Char_Stick_col.dat",
        "Data/Scripts/Character_Stick.lua"
    },
	// 刀
	{
		"Data/Graphics/Character/Char_KATANA.png",
		"Data/Collision/Char_KATANA_col.dat",
		"Data/Scripts/Character_KATANA.lua"
    },
	//傘
	{
		"Data/Graphics/Character/Char_Umbrella.png",

		"Data/Collision/Char_Umbrella_col.dat",
		"Data/Scripts/Character_Umbrella.lua"			
	},
	//テコンドー
	{
		"Data/Graphics/Character/Char_Taekwondo.png",
		"Data/Collision/Char_Taekwondo_col.dat",
		"Data/Scripts/Character_Taekwondo.lua"			
	},
	//ナイフ
	{
		"Data/Graphics/Character/Char_Knife.png",
		"Data/Collision/Char_Knife_col.dat",
		"Data/Scripts/Character_Knife.lua"			
	},
	//グレネード
	{
		"Data/Graphics/Character/Char_Grenade.png",
		"Data/Collision/Char_Knife_col.dat",
		"Data/Scripts/Character_Grenade.lua"			
	},
	//ハンマー
	{
		"Data/Graphics/Character/Char_Hammer.png",
		"Data/Collision/Char_Hammer_col.dat",
		"Data/Scripts/Character_Hammer.lua"			
	},
	//ショットガン
	{
		"Data/Graphics/Character/Char_Shotgun.png",
		"Data/Collision/Char_Taekwondo_col.dat",
		"Data/Scripts/Character_Shotgun.lua"			
	},
	//鎌
	{
		"Data/Graphics/Character/Char_Scythe.png",
        "Data/Collision/Char_Scythe_col.dat",
        "Data/Scripts/Character_Scythe.lua"				
	},
	//enumの関係上、NULLを置いておく
	//{
	//	'\0',
	//	'\0',
	//	'\0'
	//},
	//ボス刀
	{
		"Data/Graphics/Character/Char_KATANA.png",
		"Data/Collision/Char_KATANA_col.dat",
		"Data/Scripts/BOSS_KATANA.lua"	
	},
	//ボステコンドー	
	{
		"Data/Graphics/Character/Char_Taekwondo.png",
		"Data/Collision/Char_Taekwondo_col.dat",
		"Data/Scripts/BOSS_Taekwondo.lua"	
	},
	//ボスナイフ
	{
		"Data/Graphics/Character/Char_Knife.png",
		"Data/Collision/Char_Knife_col.dat",
		"Data/Scripts/BOSS_Knife.lua"			
	},
	//ボス鎌
	{
		"Data/Graphics/Character/Char_Scythe.png",
        "Data/Collision/Char_Scythe_col.dat",
        "Data/Scripts/BOSS_Scythe.lua"			
	},
/////////////ヴァルファーレ
	{
		"Data/Graphics/Character/Char_Valfirle.png",
        "Data/Collision/Char_Valfirle_col.dat",
        "Data/Scripts/Valfirle.lua"	
	},
////////////////ヴァルファーレトークン
	{
		"Data/Graphics/Character/Char_Valfirle.png",
        "Data/Collision/Char_Valfirle_col.dat",
        "Data/Scripts/Valfirle_token.lua"	
	},
 //   // 剣
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // バット
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // ハンマー
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // ナイフ
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },

 //   // ハンドガン
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // ショットガン
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // マシンガン
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // 対物ライフル
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   },
 //   // 手榴弾
 //   {
 //       NULL,
 //       NULL,
 //       NULL
 //   }
	//},

};

static const float scg_fRunSpeed = 4.0f;//2.0f; //走る速さ

//static const float scg_fFallSpeed = 0.006f; // 落下速度 ( =重力加速度 )
//
//static const float scg_fJumpHeight = 3.0f; // ジャンプの高さ

//#define scg_fFallSpeed  0.112f    // [山本] GameObject に移動
#define scg_fJumpHeight 7.2f

class CharacterScriptInterface;
class CharacterNamePlate;

/*! @class Character */
class Character : public AttackedObject
{
protected:
    
	const char *m_pszName;
	CharaState  m_eCharaState;      ///< 現在のキャラクターの状態 (setCharState で変更すること)
	

	LBatchPanel mCharaPanel;

	//int m_nTime;

	//int mAnimetionCounter; // アニメーション切り替えのためのカウンタ
	int m_AnimePuttern;     // 現在のコマ数

	Collision* mCollision; // 当たり判定

	//int m_nAnime; //後で削除する  

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual const char* getName() const {return m_pszName;}

	const CharaState& getCharaState() const {return m_eCharaState;}

	const int& getAnimePuttern() const { return m_AnimePuttern; }

	/// キャラクターの向きを設定する
    virtual void setDirection( CharaDir dir_ );


    /// アニメーションフレーム数の取得 (主にスクリプトから使う)
    int getFrameCount() const { return mFrameCount; }

    /// 武器データの取得
    const WeaponData& getWeaponData() const { return mWeaponData; }


    /// ワールド座標空間上での当たり判定矩形を返す
	virtual const LRect* getBoundingRect();

    /// ローカル座標空間上での当たり判定矩形を返す (左上からの位置)
	virtual const LRect* getLocalBoundingRect();

    /// ワールド座標空間上での攻撃当たり判定矩形を返す
	virtual const LRect* getAttackBoundingRect();

    /// キャラクターが攻撃動作中かを判定する
    bool isAttacking() const { return ( CHARASTATE_ATTACK_BEGIN_ < getCharaState() && getCharaState() < CHARASTATE_ATTACK_END_ ); }

	// キャラクタが地上にいるか判定する（スクリプトで使用）
	const bool getOnGround() const { return mOnGround; }

    /// 装備中武器の武器レベルの取得 (Player Enemy の各継承先で定義する。プレイヤーは熟練度を持つが、エネミーは初期値で固定。)
    virtual u32 getWeaponLevel() const = 0;

	// 武器が壊れたかどうかを判断する（スクリプトで使用
	bool getBreakWeapon(){ return mBreakWeapon; }

	u32 getInvincibleFrame() {return mInvincibleFrame;}
	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	//武器の使用回数の設定
	void setWeponUseCount(int UseCount_){mWeaponData.UseCount = UseCount_;}
    /// アニメーションパターンの設定 (主にスクリプトから使う)
    void setAnimePuttern( int puttern_ );

    /// アニメーションフレーム数の設定 (主にスクリプトから使う)
    void setFrameCount( int count_ ) { mFrameCount = count_; }

	// 武器が壊れた場合にtrueを設定する(スクリプトで使用
	void setBreakWeapon( bool break_ ){ mBreakWeapon = break_; }

	void setVisible( bool flg_ ) {this->mCharaPanel->SetVisible(flg_); }
    
	void setInvincibleFrame(u32 invincible_frame_) {mInvincibleFrame = invincible_frame_;}

	void setOpacity(float opacity_) {this->mCharaPanel->SetOpacity(opacity_);}
	//---------------------------------------------------------------------------
	/*! 
		@brief Character::Character

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Character();

	//---------------------------------------------------------------------------
	/*! 
		@brief Character::~Character

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~Character();

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
	bool Initialize();

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
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief Character::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Update();

   
	/// フレーム更新処理 (オブジェクトに影響を与える処理)
    virtual bool UpdateSelf();


    
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
	virtual int HandleEvent(u32 event_,void *args_);

    //---------------------------------------------------------------------
    ///**
    //  @brief      キャラクターの状態を変更する
    //
    //  @par
    //              メンバ変数に直接値を代入するのではなく、
    //              必ずこの関数で変更すること。
    //*/
    //---------------------------------------------------------------------
    void setCharaState( CharaState state_ );

    
    //---------------------------------------------------------------------
    ///**
    //  @brief      武器を変更する
    //
    //  @par
    //              現在持っている武器はその辺に置く。
    //*/
    //---------------------------------------------------------------------
    void changeWeapon( const WeaponData& weapon_data_ );

	//
	// Character::JumpStart
	// ジャンプ開始時に呼ぶ
	//
	void JumpStart();

	//
	// Character::CollisionToObj
	// オブジェクトとの当たり判定
	//
	// 当たっている場合は
	// 各種処理をする
	//
	void CollisionToObj();

	//
	// Character::AttackLock
	// 攻撃時の行動制限
	//
	// 呼ぶとロックがかかります。
	// 攻撃モーションをジャンプなどでキャンセルさせないため
	//
	void AttackLock();

	//
	// Character::AttackUnLock
	// 攻撃時の行動制限解除
	//
	// 呼ぶとロックがはずれます。
	// 攻撃モーション終了時には必ず呼んでください
	//
	void AttackUnLock();

protected:

    static const int ITEMGET_WAIT_COUNT = 60 * 20;  /// (20秒)

protected:

	LVector3    mOrigin;    // 画像の基準点
    LRect       mWorldBoundingRect;

	bool		mJump;  // ジャンプしているかどうか
	//			mOnGround(GameObject に移動)

	ObjectType  mNewTouchObj; // 梯子を離した時の処理に使用、無いと挙動がおかしい
	ObjectType  mOldTouchObj;
	bool		mTouchLadder; // 梯子に触っているかどうか
	bool        mClimbLadder; // 梯子を登っているかどうか
	bool		mStandOnObject; // 立てるオブジェクトの上にいるかどうか
	bool		mAttackLocked; // 攻撃動作中かどうかを示す。trueなら行動制限
	LVector2    mDistance; // キャラクターの中心座標と、当たったオブジェクトの中心座標との距離

    int         mFrameCount;    ///< スクリプトでのアニメーション制御に使う、経過フレーム数 (update() 内で常に加算し続ける)
	bool		mBreakWeapon; // スクリプトで使用、武器破損時に使用

    WeaponData  mWeaponData;    ///< 装備中の武器データ (使用回数もこの中)

    u32         mStunFrame;         ///< 残りののけぞりフレーム数 (値がある場合、毎フレーム -1)
    u32         mItemGetWaitCount;  ///< 

	u32         mInvincibleFrame;   ///無敵フレーム
    CharacterNamePlate* mCharacterNamePlate;



};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
