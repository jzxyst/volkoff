//=============================================================================
/*! 
    @addtogroup 
    @file       GameObject.cpp
    @brief      オブジェクトベース
    
    オブジェクトベースの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


#include "GameObject.h"
#include "../Map/MapManager.h"
#include "../Game/GameManager.h"

GameObject::GameObject()
	: mHandle   ( 0 )
	, mScale	(1,1,1)
    , m_eDirection  ( CHARADIR_RIGHT )
	, mLife     (100)
    , mMaxLife  ( 100 )
	, mScore  (0)
	, mExit   (false)
    , mOnGround     ( false )
	, mPosition(Vector3::Zero)
	, mDefPosition(Vector3::Zero)
{
	GameObjectManager::getInstance()->AddObject(this);
}


GameObject::~GameObject()
{
    GameManager::getInstance()->getGameSession()->sendToServer( SYSEV_DELETE_GAMEOBJECT, &mHandle, sizeof( u32 ) );

	mExit = true;
}

// 長い名前書くのが面倒なのでこちらに実装
GameObjectManager* GameObject::getManager() { return GameObjectManager::getInstance(); }

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
bool GameObject::Update()
{
    // 空中にいる場合
	if ( !mOnGround )
	{
        // 地面の上にいなければ重力で加速
		mAccel.y -= GRAVITY_ACCEL;

		if ( mVelocity.y < -10.0f )
		{
			mVelocity.y = -10.0f;
		}
	}
    // 地面上にいる場合
	else
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

        if ( mVelocity.GetLengthSquared() < 1.0f )
        {
            mVelocity = Vector3::Zero;
		}
	}

    // 普通に移動
    mVelocity += mAccel;

    // 地形との当たり判定
    float dx, dy;
    u32 result = judgeCollisionToMap( &dx, &dy );
    if ( result )
    {
        // 下が当たっている場合は地面の上にいるとする
	    if ( result & MAPCOLL_DOWN )
        {
            mOnGround = true;
        }
    }
    else
    {
        mOnGround = false;
    }

    mPosition.x += dx;
    mPosition.y += dy;
    mPosition.z = -6.0f;

    return true;
}

//---------------------------------------------------------------------
// ● 地形との当たり判定を行う
//---------------------------------------------------------------------
u32 GameObject::judgeCollisionToMap( float* dx_, float* dy_ )
{
    *dx_ = *dy_ = 0.0f;

    // 当たり判定全般は、判定用の矩形がある場合にのみ行う
    const LRect* rc = getBoundingRect();
    if ( rc )
    {
        LRect col_rect = *rc;

        // 移動した後の座標
	    LVector3 d_pos = mPosition + mVelocity;

        // 移動前の判定用矩形の座標
        float px = col_rect.x;
        float py = col_rect.y;

        // 矩形を移動させて、移動後の判定領域にする
        col_rect.x += static_cast< int >( mVelocity.x );
        col_rect.y += static_cast< int >( mVelocity.y );
        
	    // 移動量 (いまはつかわないかも)
	    LVector3 dest = mPosition - d_pos;

	    // マップとの当たり判定結果の、修正後の座標を格納する変数
	    LVector3 result_pos;
		
        
	    u32 result = MapManager::getInstance()->collision( col_rect, dest, &result_pos );

        // 移動前と比べて、移動量を求める
        *dx_ = result_pos.x - px;
        *dy_ = result_pos.y - py;

		return result;
    }
    return 0;
}
    /// 速度の設定 (攻撃によるふっ飛ばし等で使う)
void GameObject::setVelocity(const LVector3& vel_ )
{
	if(!mOnGround)
	{
		if(vel_.x>=16)
			vel_.x=16;
		if(vel_.x<=-16)
			vel_.x=-16;		
	}
	mVelocity = vel_; 
}

//=============================================================================
//								End of File
//=============================================================================
