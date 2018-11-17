//=============================================================================
/*! 
    @addtogroup 
    @file       Valfirle.h
    @brief      ヴァルファーレヘッダ
    
    ヴァルファーレ専用AIの定義
    
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


//Include Guard
#ifndef __INCLUDE_VALFIRLE_H__
#define __INCLUDE_VALFIRLE_H__


/*! @par include */
#include "./Character.h"
#include "Enemy.h"


/*! @par global */
//難易度調整用変数 //左からEasy,Normal,Hard,Valfirle
static const bool scg_bValfirleAttack1Permission[] = {true,true,true,true};    //攻撃1段目を出せるかどうか
static const bool scg_bValfirleAttack2Permission[] = {true,true,true,true};    //攻撃2段目を出せるかどうか
static const bool scg_bValfirleAttack3Permission[] = {true,true,true,true};    //攻撃3段目を出せるかどうか
static const int scg_nValfirleAttackRatio[] = {12,10,9,8};                     //攻撃を開始する比率。10であれば1/10で攻撃を開始する
static const int scg_nValfirleAttack2Ratio[] = {30,40,50,60};                  //攻撃2段目を行う比率。10であれば9/10で攻撃を開始する
static const int scg_nValfirleAttack3Ratio[] = {30,40,50,60};                  //攻撃3段目を行う比率。10であれば9/10で攻撃を開始する
static const int scg_nValfirleJumpAttackRatio[] = {4,4,4,4};                   //ジャンプ攻撃を行う割合。10であれば1/10でジャンプ攻撃を開始する
static const int scg_nValfirleSquatAttackRatio[] = {4,4,4,4};                  //しゃがみ攻撃を行う割合。10であれば1/10でじゃがみ攻撃を開始する
static const int scg_nValfirleStandbyRatio[] = {25,25,25,25};                  //観察を行う割合。10であれば1/10で観察を開始する
static const int scg_nValfirleGuardRatio[] = {70,60,50,40};                    //防御を行う割合。10であれば1/10で防御を開始する
static const int scg_nValfirleSquatGuardRatio[] = {100,90,85,80};              //しゃがみ防御を行う割合。10であれば1/10で防御を開始する
static const int scg_nValfirleSquatRatio[] = {50,50,50,50};                    //しゃがみを行う割合
static const int scg_nValfirleJumpRatio[] = {30,30,30,30};                     //ジャンプを行う割合
static const int scg_nValfirleEscapeRatio[] = {20,20,20,20};                   //逃走を行う割合
static const int scg_nValfirleLife[] = {1200,1200,1200,1200};                  //体力
static const int scg_nValfirleLifePhase2[] = {500,700,750,800};                //第二段階に入るHP


/*! @class Valfirle */
class Valfirle : public Character
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
	static const int scm_nSearchX = 400;       //X座標探索範囲
	static const int scm_nSearchY = 100;       //Y座標探索範囲
	static const int scm_nSearchRand = 10;     //探索範囲誤差
	static const int scm_nWalkIntv = 0;        //散歩間隔フレーム数
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

	int m_nPhase;             //ボスの段階

	int m_nNum[10];           //スクリプト側から使う変数

private:

    /// コンストラクタは使用不可。create() で作成すること。
    Valfirle();

	bool SearchPlayer();

	bool SearchAttack1Range();

	bool SearchJumpAttackRange();

	bool SearchAntiairAttackRange();

	void ChangePhase();

public:
    
    /// デストラクタ
    virtual ~Valfirle();

    /// オブジェクトを作成する (Initialize() はこの中で呼ばれる。通常、is_entity_ は true にしておくこと)
    static Valfirle* create( void* args_, bool is_entity_ = true );

	static Valfirle* createRandom();

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	const char* getName() const {return m_pszName;}

	const CharaState& getCharaState() const {return m_eCharaState;}

	const int& getAnimePuttern() const { return m_AnimePuttern; }

	const CharaDir& getDirection() const {return m_eDirection;}

    virtual ObjectType getObjType() const { return OBJ_ENEMY; }

	const int getPhase() const {return this->m_nPhase;}
    
	const int getNum(int nElm_) const {return this->m_nNum[nElm_];}

    /// 装備中武器の武器レベルの取得
    virtual u32 getWeaponLevel() const { return mWeaponLevel; }

	virtual u32 getExp() const { return mExp; }

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	void setNum(int nElm_,int nNum_) {this->m_nNum[nElm_] = nNum_;}
	

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
	bool Initialize( const CreateData& data_ );

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
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief Valfirle::Update

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
		@brief Valfirle::HandleEvent

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
