//=============================================================================
/*! 
    @addtogroup 
    @file       Bullet.h
    @brief      弾オブジェクト
    
    Bulletクラスの定義
    
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
#ifndef __INCLUDE_BULLET_H__
#define __INCLUDE_BULLET_H__


/*! @par include */
#include "./AttackedObject.h"
#include "../Object/GameObjectManager.h"

/*! @par global */
static const char g_szBulletFilePath[] = "./Data/Graphics/Object/Bullet.png";


/*! @class Ladder */
class Bullet : public AttackedObject
{
private:
	LBatchPanel mPanel;
 //int damage_, u32 range_rate_, u32 critical_rate_,  LVector3& brow_vec_, u32 stun_frame_ 
	int mDamage;
    u32 mLifeFrame;
	u32 mRangeRate;
	u32 mCriticalRate;
	LVector3 mBrowVec;
	u32 mFrameCnt;
	u32 mStunFrame;
	ObjectType mGeneObjType;
	float mSeVol;//音量
public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
 
	virtual ObjectType getObjType() const { return OBJ_BULLET; }
	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	void setGeneObjType(ObjectType gene_obj_type_) {mGeneObjType = gene_obj_type_;}
	//弾の威力の設定
	void setAttackParam(int damage_,u32 range_rate_,u32 critical_rate_,LVector3& brow_vec_,u32 stun_frame_ ){
						mDamage = damage_;
						mRangeRate = range_rate_;
						mCriticalRate = critical_rate_;
						mBrowVec = brow_vec_;
						mStunFrame = stun_frame_;
						}
	//弾の寿命
	void setLifeFrame(u32 life_frame_){mLifeFrame = life_frame_;}

	void setSeVol(int se_vol_){mSeVol = ((float)se_vol_) / 100.0;}
	//---------------------------------------------------------------------------
	/*! 
		@brief Bullet::Bullet

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Bullet();

	//---------------------------------------------------------------------------
	/*! 
		@brief Bullet::~Bullet

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Bullet();

	//---------------------------------------------------------------------------
	/*! 
		@brief Bullet::Initialize

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
		@brief Bullet::Release

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
		@brief Bullet::Update

		フレーム更新処理

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Bullet::HandleEvent

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