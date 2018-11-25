//=============================================================================
/*! 
    @addtogroup 
    @file       Grenade.h
    @brief      弾オブジェクト
    
    Grenadeクラスの定義
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/12/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/13 matsui
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_GRENADE_H__
#define __INCLUDE_GRENADE_H__


/*! @par include */
#include "./AttackedObject.h"
#include "../Object/GameObjectManager.h"

/*! @par global */
static const char g_szGrenadeFilePath[] = "./Data/Graphics/Object/Grenade.png";


/*! @class Ladder */
class Grenade : public AttackedObject
{
private:
    Ref<LBatchPanel> mPanel;
 //int damage_, u32 range_rate_, u32 critical_rate_,  LVector3& brow_vec_, u32 stun_frame_ 
	int mDamage;
	u32 mRangeRate;
	u32 mCriticalRate;
	LVector3 mBrowVec;
	u32 mFrameCnt;
	u32 mStunFrame;
	ObjectType mGeneObjType;
	float mFallSpeed;
	int mRandBrowX;
	int mRandBrowY;
	u32   mRandStun;
public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
 
	virtual ObjectType getObjType() const { return OBJ_GRENADE; }
	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	void setGeneObjType(ObjectType gene_obj_type_) {mGeneObjType = gene_obj_type_;}
	//弾の威力の設定
	void setAttackParam(int damage_,u32 range_rate_,u32 critical_rate_, const LVector3& brow_vec_,u32 stun_frame_ ){
						mDamage = damage_;
						mRangeRate = range_rate_;
						mCriticalRate = critical_rate_;
						mBrowVec = brow_vec_;
						mStunFrame = stun_frame_;
						}
	void setFallSpeed(float fall_speed_) { mFallSpeed = fall_speed_;}

	//指定した数値分吹っ飛び方がランダムに変わる
	void setRandBrow(int rand_brow_x_,int rand_brow_y_) { mRandBrowX = rand_brow_x_; mRandBrowY = rand_brow_y_;}

	void setRandStun(u32 rand_stun_) { mRandStun = rand_stun_;}
	//---------------------------------------------------------------------------
	/*! 
		@brief Grenade::Grenade

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Grenade();

	//---------------------------------------------------------------------------
	/*! 
		@brief Grenade::~Grenade

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Grenade();

	//---------------------------------------------------------------------------
	/*! 
		@brief Grenade::Initialize

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
		@brief Grenade::Release

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
		@brief Grenade::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Grenade::HandleEvent

		イベント処理

		@param[in]      EventType event_ イベントタイプ
		@param[in]      void      *args_ データ(適当にキャストする)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	const LRect* getBoundingRect();
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================