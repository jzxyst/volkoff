//=============================================================================
/*! 
    @addtogroup 
    @file       Player.h
    @brief      プレイヤー周り
    
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
#ifndef __INCLUDE_PLAYER_H__
#define __INCLUDE_PLAYER_H__


/*! @par include */
#include "./Character.h"
#include "./Weapon.h"


//#include "../Frontend/GameFrontendManager.h"
//#include "../Frontend/PlayerStateWindow.h"

/*! @par global */
//次のレベルまでに必要な経験値
static const int scg_nNextLevelExp[]        = {100,200,350,400 ,600 ,700 ,840 ,1200,1610};
static const int scg_nNextLevelExpTotal[]   = {100,300,650,1050,1650,2350,3190,4390,6000};
///////////////////////////////////////{100,300,650,1050,1650,2350,3190,4390,6000}累計

const int MAX_PLAYER_LEVELS = 10;   ///< 最大レベル。一応10 で固定だけど、念のため。

/*! @class Player */
class Player : public Character
{
private:

	u32 mExp;
	u8 mLevel;
    u32 mGuardFrame;//ガード経過フレーム
public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_CHARACTER; }

    /// 装備中の武器熟練度を取得する
    int getWeaponExp() { return mWeaponExps[ this->getWeaponData().WeaponType ]; }

    /// 装備中武器の武器レベルの取得
    virtual u32 getWeaponLevel() const;

	//プレイヤーの現在レベルの取得
	u8 getLevel(){return mLevel;}
	//プレイヤーの現在経験値の取得
	u32 getExp() {return mExp;}

	u32 getGuardFrame() {return mGuardFrame;}

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	void setExit(bool bExit_) {return;}
   
	void setLevel(u8 Level_) { mLevel = Level_;}

	void setExp(u32 Exp_) { mExp = Exp_;}


	//---------------------------------------------------------------------------
	/*! 
		@brief Player::Player

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Player();

	//---------------------------------------------------------------------------
	/*! 
		@brief Player::~Player

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual ~Player();

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
	bool Initialize();

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
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief Player::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual bool Update();

   
	/// フレーム更新処理 (オブジェクトに影響を与える処理)
    virtual bool UpdateSelf();

	void setOnGround( bool flag ){ mOnGround = flag; }
    
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
	virtual int HandleEvent(::EventType event_,void *args_);



    /// コンティニューに備えて状態を保存する
    void commit();

    /// commit() を呼んだ時の状態に復元する
    void reset();

protected:

    int     mWeaponExps[ WEAPON_MAX_NUM ];      ///< 武器熟練度の配列

    struct
    {
        int         Life;
        u32         Exp;
	    u8          Level;
        WeaponData  WeaponData;

    } mBackup;
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================