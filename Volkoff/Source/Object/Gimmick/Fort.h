//=============================================================================
/*! 
    @addtogroup 
    @file       Fort.h
    @brief      自動機銃オブジェクト
    
    Fortクラスの定義
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/11/2
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/2 matsui
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_FORT_H__
#define __INCLUDE_FORT_H__


/*! @par include */
#include "./../GameObject.h"
#include "./../attackedobject.h"


/*! @par global */
static const char g_szFortFilePath[] = "./Data/Graphics/Object/Fort.png";
static const char g_szFortFilePath2[] = "./Data/Graphics/Object/Black.png";
static const int scg_nFortLife[] = {10,30,50,60};         //機銃の耐久力（体力）
static const int scg_nReactionSpeed[] = {2,2,2,2};        //機銃の角度を補正する間隔
static const int scg_nSearchRangeX[] = {400,400,400,400}; //機銃の反応距離 X座標
static const int scg_nSearchRangeY[] = {400,400,400,400}; //機銃の反応距離 Y座標
static const int scg_nAttackRangeX[] = {400,400,400,400}; //機銃の攻撃距離 X座標
static const int scg_nAttackRangeY[] = {400,400,400,400}; //機銃の攻撃距離 Y座標
static const int scg_nShootSpeed[] = {3,4,5,6};           //弾速
static const int scg_nShootDamage[] = {10,10,10,10};          //弾の威力
static const int scg_nAttackIntv[] = {150,120,130,130};   //機銃の攻撃間隔
static const int scg_nShootIntv[] = {5,4,2,4};            //1回の攻撃の発射間隔
static const int scg_nShootNum[] = {4,6,7,6};             //1回の攻撃の発射回数


/*! @enum FortAction */
typedef enum _ENUM_FORT_ACTION
{
	FORT_ACT_UNDEF,        //未定義
	FORT_ACT_WAIT,         //待機
	FORT_ACT_SEARCH,       //探索
	FORT_ACT_ATTACK_RANGE, //攻撃範囲内
	FORT_ACT_ATTACK,       //攻撃
}FortAction;


/*! @class Ladder */
class Fort : public AttackedObject
{
private:
	LBatchPanel mPanel;
	LBatchPanel mPanel2;
	int m_nFrame;
	int m_nAttackFrame;
	int m_nShootFrame;
	int m_nShootNum;
	LVector3 mShootVec;
	FortAction m_eAction;

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_FORT; }

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::Fort

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Fort();

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::~Fort

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Fort();

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::Initialize

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
		@brief Fort::Release

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
		@brief Fort::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Fort::HandleEvent

		イベント処理

		@param[in]      EventType event_ イベントタイプ
		@param[in]      void      *args_ データ(適当にキャストする)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	const LRect* getBoundingRect();
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================