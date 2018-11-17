//=============================================================================
/*! 
    @addtogroup 
    @file       Enemy.h
    @brief      エネミー
    
    エネミー周りの定義
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/11/07
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/07 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_ENEMY_H__
#define __INCLUDE_ENEMY_H__


/*! @par include */
#include "./Character.h"


/*! @par global */
//難易度調整用変数 //左からEasy,Normal,Hard,Valfirle
static const bool scg_bAttack1Permission[] = {true,true,true,true};    //攻撃1段目を出せるかどうか
static const bool scg_bAttack2Permission[] = {false,true,true,true};   //攻撃2段目を出せるかどうか
static const bool scg_bAttack3Permission[] = {false,false,false,true}; //攻撃3段目を出せるかどうか
static const int scg_nAttackRatio[] = {50,40,30,20};                   //攻撃を開始する比率。10であれば1/10で攻撃を開始する
static const int scg_nAttack2Ratio[] = {5,7,8,12};                     //攻撃2段目を行う比率。10であれば9/10で攻撃を開始する
static const int scg_nAttack3Ratio[] = {5,7,8,12};                     //攻撃3段目を行う比率。10であれば9/10で攻撃を開始する
static const int scg_nJumpAttackRatio[] = {6,6,6,6};                   //ジャンプ攻撃を行う割合。10であれば1/10でジャンプ攻撃を開始する
static const int scg_nSquatAttackRatio[] = {6,6,6,6};                  //しゃがみ攻撃を行う割合。10であれば1/10でじゃがみ攻撃を開始する
static const int scg_nStandbyRatio[] = {20,20,20,20};                  //観察を行う割合。10であれば1/10で観察を開始する
static const int scg_nGuardRatio[] = {100,90,85,80};                   //防御を行う割合。10であれば1/10で防御を開始する
static const int scg_nSquatGuardRatio[] = {100,90,85,80};              //しゃがみ防御を行う割合。10であれば1/10で防御を開始する
static const int scg_nSquatRatio[] = {120,120,120,120};                //しゃがみを行う割合
static const int scg_nJumpRatio[] = {120,120,120,120};                 //ジャンプを行う割合
static const int scg_nEscapeRatio[] = {60,60,60,60};                   //逃走を行う割合
static const int scg_nLife[] = {50,70,90,100};                         //体力


	
/*! @enum WeaponType */
typedef enum _ENUM_ENEMY_ACTION
{
	ENEMY_ACT_UNDEF,        //未定義
	ENEMY_ACT_WAIT,         //待機
	ENEMY_ACT_SEARCH,       //探索
	ENEMY_ACT_WALK,         //散歩
	ENEMY_ACT_CHASE,        //追跡
	ENEMY_ACT_STANDBY,      //観察
	ENEMY_ACT_ESCAPE,       //逃走
	ENEMY_ACT_ATTACK_RANGE, //攻撃範囲内
	ENEMY_ACT_ATTACK,       //攻撃
	ENEMY_ACT_GUARD,        //防御
	ENEMY_ACT_SQUAT,        //しゃがみ
	ENEMY_ACT_SQUAT_GUARD,  //しゃがみガード
}EnemyAction;


/*! @class Enemy */
class Enemy : public Character
{
public:

    struct CreateData
    {
        LVector3    Position;
        LVector3    Velocity;
		u32			WeaponType;	
        u32         WeaponLevel;    ///< 武器レベル (1～3)
		

        /// 念のための初期値
        CreateData()
            : WeaponType	( WEAPON_NON )
			, WeaponLevel	( 1 )
        {}
    };

protected:
	static const int scm_nSearchX = 450;         //X座標探索範囲
	static const int scm_nSearchY = 100;         //Y座標探索範囲
	static const int scm_nSearchRand = 10;       //探索範囲誤差
	static const int scm_nWalkIntv = 130;        //散歩間隔フレーム数
	static const int scm_nWalkRange = 50;        //散歩範囲
	static const int scm_nAttackRangeRand = 80;  //攻撃範囲誤差 //50
	static const int scm_nEscapeRange = 60;      //逃走範囲
	static const int scm_nStandbyRange = 250;    //観察範囲
	static const int scm_nStandbyIntv = 120;     //観察フレーム数
	static const int scm_nGuardIntv = 100;       //防御フレーム数

	EnemyAction m_eAction;

	bool m_bCreateWeapon;

	int m_nAttackDelay;     //累積攻撃ディレイ分
	int m_nRandAttackDelay; //ランダムディレイ
	int m_nAttackRangeRand; //攻撃範囲誤差
	int m_nRandAttackRange; //ランダム攻撃範囲
	int m_nRandSearchRange; //ランダム探索範囲
	int m_nWalkIntvCnt;     //散歩までの累積フレーム数
	int m_nWalkRangeCnt;    //散歩残り歩数
	bool m_bWalkDir;        //散歩方向
	int m_nEscapeRangeCnt;  //逃走残り歩数
	int m_nStandbyCnt;      //観察残りフレーム数
	int m_nGuardCnt;        //防御残りフレーム数
	int m_nSquatCnt;        //しゃがみ残りフレーム数

	u32 mExp;//倒した時得られる経験値

private:

    /// コンストラクタは使用不可。create() で作成すること。
    Enemy();

	bool SearchPlayer();

	bool SearchAttack1Range();

	bool SearchJumpAttackRange();

	bool SearchAntiairAttackRange();



public:
    
    /// デストラクタ
    virtual ~Enemy();

    /// オブジェクトを作成する (Initialize() はこの中で呼ばれる。通常、is_entity_ は true にしておくこと)
    static Enemy* create( void* args_, bool is_entity_ = true );

	static Enemy* createRandom();

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual const char* getName() const {return m_pszName;}

	const CharaState& getCharaState() const {return m_eCharaState;}

	const int& getAnimePuttern() const { return m_AnimePuttern; }

	const CharaDir& getDirection() const {return m_eDirection;}

    
    virtual ObjectType getObjType() const { return OBJ_ENEMY; }
    


    /// 装備中武器の武器レベルの取得
    virtual u32 getWeaponLevel() const { return mWeaponLevel; }

    virtual u32 getExp() const { return mExp; }
	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	

	//---------------------------------------------------------------------------
	/*! 
		@brief Enemy::Initialize

		初期化処理

		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize( const CreateData& data_ );

	//---------------------------------------------------------------------------
	/*! 
		@brief Enemy::Release

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
		@brief Enemy::Update

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
		@brief Enemy::HandleEvent

		イベント処理

		@param[in]      EventType event_ イベントタイプ
		@param[in]      void      *args_ データ(適当にキャストする)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	virtual int HandleEvent(u32 event_,void *args_);

protected:

    Character*  mTargetCharacter;   ///< 攻撃対象
    u32         mWeaponLevel;       ///< 武器レベル (初期化時に指定)
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
