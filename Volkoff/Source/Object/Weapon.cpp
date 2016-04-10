//=============================================================================
/*! 
    @addtogroup 
    @file       Weapon.cpp
    @brief      武器周り
    
    Weaponヘッダの実装
    
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
#include "stdafx.h"
#include "Weapon.h"
#include "../Map/MapManager.h"
#include "../Frontend/GuideNamePlate.h"
#include "../Game/GameManager.h"


//=============================================================================
// ■ WeaponData 関係
//=============================================================================

const WeaponBaseData gWeaponBaseData[ WEAPON_MAX_NUM ] =
{
    // 素手
    { { 20, 30 }, -1, 100, 250 },

    // 棒
    { { 20, 30 }, 30, 150, 100  },

    // 刀
    { { 20, 30 }, 15, 50, 70 },
	//傘
    { { 20, 30 }, 20, 100, 40 },
	// テコンドー
    { { 20, 30 }, 25, 150, 100 },
	// ナイフ
    { { 20, 30 }, 40, 150, 100 },
	// グレネード
    { { 20, 30 }, 1, 10, 70 },
	// ハンマー
    { { 20, 30 }, 20, 150, 100 },
	// ショットガン
    { { 20, 30 }, 7, 30, 70 },
	// 鎌
    { { 20, 30 },15, 35, 70 },

    // ボス刀
    { { 20, 30 }, 15, -1 ,0},

	//ボステコンドー
    { { 20, 30 }, 15, -1 ,0},
	//ボスナイフ
    { { 20, 30 }, 15, -1 ,0},
	//ボス鎌
    { { 20, 30 }, 15, -1 ,0},

	//ヴァルファーレ
    { { 20, 30 }, 15, -1 ,0},
	//ヴァルファーレトークン
    { { 20, 30 }, 15, -1 ,0},
};

////---------------------------------------------------------------------------
//// ● 指定したレベルに必要な経験値の取得
////---------------------------------------------------------------------------
//u32 WeaponData::getLevelEXP( WeaponType type_, u32 level_ )
//{
//    return gWeaponBaseData[ type_ ].NecessaryExp[ level_ ];
//}


//=============================================================================
// ■ Weapon クラス
//=============================================================================

//---------------------------------------------------------------------------
// ● オブジェクトを作成する
//---------------------------------------------------------------------------
Weapon* Weapon::create( void* args_, bool is_entity_ )
{
    Weapon* o = NEW Weapon();
    o->Initialize( *static_cast< CreateData* >( args_ ) );
    o->mIsEntity = is_entity_;

    // 自分がこのホストで作成されたものであれば、自分以外のホストに生成したことを送信する
    if ( is_entity_ )
    {
        GameManager::getInstance()->getGameSession()->sendCreatedObjectEvent( OBJ_WEAPON, args_, sizeof( CreateData ) );
    }

    return o;
}

//---------------------------------------------------------------------
// ● 全ての武器の中からランダムに武器IDを返す (出現率も考慮している)
//---------------------------------------------------------------------
int Weapon::getRandWeaponID()
{
    // 出現率の総和
    int rate_max = 0;
    for ( int i = 0; i < WEAPON_MAX_NUM; ++i )
    {
        if ( gWeaponBaseData[ i ].Rate )
        {
            rate_max += gWeaponBaseData[ i ].Rate;
        }
    }

    // 値をひとつ決める
    int value = rand() % rate_max;

    // 値に対応する武器を探す
    for ( int i = 1; i < WEAPON_MAX_NUM; ++i )
	{
		int rating = gWeaponBaseData[ i ].Rate;
        if ( rating > 0 )
        {
		    if ( rating > value )
		    {
			    return i;
		    }
		    value -= rating;
        }
	}
    return 0;
}

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Weapon::Weapon()
{
	mWeaponData.WeaponType = WEAPON_NON;
    mWeaponData.UseCount   = 0;
    mGuideNamePlate = NULL;
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Weapon::~Weapon()
{
	SAFE_DELETE( mGuideNamePlate );
}

//---------------------------------------------------------------------
// ● 初期化
//---------------------------------------------------------------------
bool Weapon::Initialize( const CreateData& data_ )
{
    mWeaponData = data_.Data;

    mPanel = Sprite3D::Create( 80, 80);//,LN_PANELDIR_UPPER_REFT);
    this->mPanel->SetCenter(-40, 40, 0);
    mPanel->SetTexture(Assets::LoadTexture( "Data/Graphics/Object/Weapons.png"/*, 0xffffffff*/ ) );
    mPanel->SetSrcRect( 80 * mWeaponData.WeaponType, 0, 80, 80 );

    this->mPosition = data_.Position;
    this->mPosition.z = -5.f;

    mGuideNamePlate = NEW GuideNamePlate();
    mGuideNamePlate->initialize( this, 0, 30, -30 );

	return true;
}

//---------------------------------------------------------------------
// ● ワールド座標空間上での当たり判定矩形を返す
//---------------------------------------------------------------------
const LRect* Weapon::getBoundingRect()
{
    static LRect rc;
    rc.Set(
        static_cast< int >( mPosition.x ),
        static_cast< int >( mPosition.y ),
        80, 80 );
    return &rc;
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
bool Weapon::Update()
{
    GameObject::Update();

    mPanel->SetPosition( this->mPosition );

    return true;
}


//=============================================================================
//								End of File
//=============================================================================
