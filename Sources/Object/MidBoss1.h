//=============================================================================
/*! 
    @addtogroup 
    @file       MidBoss1.h
    @brief      エネミー
    
    中ボス周りの定義
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/12/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/13 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_MIDBOSS1_H__
#define __INCLUDE_MIDBOSS1_H__


/*! @par include */
#include "./Character.h"
#include "Enemy.h"


/*! @par global */
//難易度調整用変数 //左からEasy,Normal,Hard,Valfirle
static const bool scg_bMidBoss1Attack1Permission[] = {true,true,true,true};    //攻撃1段目を出せるかどうか
static const bool scg_bMidBoss1Attack2Permission[] = {true,true,true,true};    //攻撃2段目を出せるかどうか
static const bool scg_bMidBoss1Attack3Permission[] = {true,true,true,true};    //攻撃3段目を出せるかどうか
static const int scg_nMidBoss1AttackRatio[] = {15,12,12,10};                   //攻撃を開始する比率。10であれば1/10で攻撃を開始する
static const int scg_nMidBoss1Attack2Ratio[] = {25,35,40,40};                  //攻撃2段目を行う比率。10であれば9/10で攻撃を開始する
static const int scg_nMidBoss1Attack3Ratio[] = {25,35,40,40};                  //攻撃3段目を行う比率。10であれば9/10で攻撃を開始する
static const int scg_nMidBoss1JumpAttackRatio[] = {4,4,4,4};                   //ジャンプ攻撃を行う割合。10であれば1/10でジャンプ攻撃を開始する
static const int scg_nMidBoss1SquatAttackRatio[] = {4,4,4,4};                  //しゃがみ攻撃を行う割合。10であれば1/10でじゃがみ攻撃を開始する
static const int scg_nMidBoss1StandbyRatio[] = {20,19,18,17};                  //観察を行う割合。10であれば1/10で観察を開始する
static const int scg_nMidBoss1GuardRatio[] = {70,60,50,40};                    //防御を行う割合。10であれば1/10で防御を開始する
static const int scg_nMidBoss1SquatGuardRatio[] = {100,90,85,80};              //しゃがみ防御を行う割合。10であれば1/10で防御を開始する
static const int scg_nMidBoss1SquatRatio[] = {60,60,60,60};                    //しゃがみを行う割合
static const int scg_nMidBoss1JumpRatio[] = {40,40,40,40};                     //ジャンプを行う割合
static const int scg_nMidBoss1EscapeRatio[] = {20,20,20,20};                   //逃走を行う割合
static const int scg_nMidBoss1Life[] = {450,550,650,800};                      //体力


/*! @class MidBoss1 */
class MidBoss1 : public Character
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
	static const int scm_nSearchX = 350;       //X座標探索範囲
	static const int scm_nSearchY = 100;       //Y座標探索範囲
	static const int scm_nSearchRand = 10;     //探索範囲誤差
	static const int scm_nWalkIntv = 130;      //散歩間隔フレーム数
	static const int scm_nWalkRange = 50;      //散歩範囲
	static const int scm_nEscapeRange = 60;    //逃走範囲
	static const int scm_nStandbyRange = 200;  //観察範囲
	static const int scm_nStandbyIntv = 60;    //観察フレーム数
	static const int scm_nGuardIntv = 120;     //防御フレーム数

	EnemyAction m_eAction;

	bool m_bCreateWeapon;

	int m_nAttackDelay;     //累積攻撃ディレイ分
	int m_nRandAttackDelay; //ランダムディレイ
	int m_nRandAttackRange; //ランダム攻撃範囲
	int m_nRandSearchRange; //ランダム探索範囲
	int m_nWalkIntvCnt;     //散歩までの累積フレーム数
	int m_nWalkRangeCnt;    //散歩残り歩数
	bool m_bWalkDir;        //散歩方向
	int m_nEscapeRangeCnt;  //逃走残り歩数
	int m_nStandbyCnt;      //観察残りフレーム数
	int m_nGuardCnt;        //防御残りフレーム数
	int m_nSquatCnt;        //しゃがみ残りフレーム数
	
	u32 mExp; //倒した時取得できる経験値

private:

    /// コンストラクタは使用不可。create() で作成すること。
    MidBoss1();

	bool SearchPlayer();

	bool SearchAttack1Range();

	bool SearchJumpAttackRange();

	bool SearchAntiairAttackRange();

public:
    
    /// デストラクタ
    virtual ~MidBoss1();

    /// オブジェクトを作成する (Initialize() はこの中で呼ばれる。通常、is_entity_ は true にしておくこと)
    static MidBoss1* create( void* args_, bool is_entity_ = true );

	static MidBoss1* createRandom();

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	const char* getName() const {return m_pszName;}

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
		@brief MidBoss1::Initialize

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
		@brief MidBoss1::Release

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
		@brief MidBoss1::Update

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
		@brief MidBoss1::HandleEvent

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
