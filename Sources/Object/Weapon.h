//=============================================================================
/*! 
    @addtogroup 
    @file       Weapon.h
    @brief      武器周り
    
    武器周りの定義
    
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
#ifndef __INCLUDE_WEAPON_H__
#define __INCLUDE_WEAPON_H__


/*! @par include */
#include "./GameObject.h"


class GuideNamePlate;


/*! @enum WeaponType */
typedef enum _ENUM_WEAPON_TYPE
{
	WEAPON_NON = 0,     ///< 素手
	WEAPON_STICK,       ///< 棒
	WEAPON_KATANA,
	WEAPON_UMBRELLA,
	WEAPON_TAEKWONDO,
	WEAPON_KNIFE,
	WEAPON_GRENADE,
	WEAPON_HAMMER,
	WEAPON_SHOTGUN,
	WEAPON_SCYTHE,
	
	WEAPON_BOSS_KATANA,
	WEAPON_BOSS_TAEKWONDO,
	WEAPON_BOSS_KNIFE,
	WEAPON_BOSS_SCYTHE,
	WEAPON_VALFIRLE,
	WEAPON_VALFIRLE_TOKEN,
    WEAPON_MAX_NUM,     ///< 武器種類の数 (スクリプトで使うので)



	WEAPON_NORMAL_BEGIN = WEAPON_NON,
	WEAPON_NORMAL_END   = WEAPON_SCYTHE,


	WEAPON_BOSS_BEGIN = WEAPON_BOSS_KATANA,
	WEAPON_BOSS_END   =	WEAPON_BOSS_SCYTHE,

	WEAPON_NORMAL_MAX_NUM = ( WEAPON_NORMAL_END - WEAPON_NORMAL_BEGIN + 1 ),

	
    /*
    WEAPON_SWORD,       ///< 剣
    WEAPON_BAT,         ///< バット
    WEAPON_HAMMER,      ///< ハンマー
    WEAPON_KNIFE,       ///< ナイフ

    WEAPON_HANDGUN,     ///< ハンドガン
    WEAPON_SHOTGUN,     ///< ショットガン
    WEAPON_MACHINEGUN,  ///< マシンガン
    WEAPON_RIFLE,       ///< 対物ライフル
    WEAPON_GRENADE,     ///< 手榴弾
    */
    

}WeaponType;

/// 武器の名前
static const char* gWeaponNames[] =
{
    "NONE",
    "Stick",
    "KATANA",
    "Umbrella",
    "Taekwondo",
    "Knife",
	"Grenade",
	"Hammer",
	"Shotgun",
	"Scythe",

    "Boss1",    // 一応
    "Boss2"
};


/// 武器データ
struct WeaponData
{
    WeaponType  WeaponType;     ///< 武器の種類
    int         UseCount;       ///< 残り使用回数 (-1 で無限とする。素手とか)

    /// 現在の武器レベルの取得 (1～3)
    u32 getLevel() const;

    /// 指定したレベルに必要な経験値の取得
    //static u32 getLevelEXP( WeaponType type_, u32 level_ );
};


struct WeaponBaseData
{
    int     NecessaryExp[ 2 ];      ///< レベル2、3 になるために必要な累計経験値
	int     UseCount;               ///< 使用回数
	int     Rate;                   ///< 出現頻度(Enemy)
	int     BoxRate;                ///< 出現頻度(Box)
};

/// 武器毎の基本データ
extern const WeaponBaseData gWeaponBaseData[ WEAPON_MAX_NUM ];


/// 武器熟練度データ (武器の getLevelData() の戻り値。おもにインターフェイス関係で使う)
//struct WeaponLevelData
//{
//    int         Level;          ///< レベル (1～3)
//    int         Exp;            ///< 経験値 (武器によって変わる)
//    int         NextExp;        ///< 次のレベルまでの経験値
//};


/*
    Weapon クラスは、武器をステージ上に配置するために使うクラスとする。
    Weapon クラスは Initialize() で WeaponData を受け取ってメンバに保持し、
    その WeaponType によって画面に表示する武器イメージを決定する。

    Weapon 本体(isEnttiy() が true)を生成できるのはサーバだけ。

    こういう作り方にしておいた方が、「GameObject を GameObject の中に持たせる」
    とかなんか複雑なことにならなくてよさそうな気がする。
*/

/*! @class Weapon */
class Weapon : public GameObject
{
public:

    struct CreateData
    {
        WeaponData  Data;       ///< 武器データ
        LVector3    Position;   ///< 位置
    };

    //---------------------------------------------------------------------
    ///**
    //  @brief      オブジェクトを作成する
    //
    //  @param[in]  args_ : CreateData 構造体へのポインタ
    //
    //  @par
    //              Initialize() はこの中で呼ばれる。通常、is_entity_ は true にしておくこと。
    //*/
    //---------------------------------------------------------------------
    static Weapon* create( void* args_, bool is_entity_ = true );
	
    
    //---------------------------------------------------------------------
    ///**
    //  @brief      全ての武器の中からランダムに武器IDを返す (出現率も考慮している)
    //
    //  @return     見つからなかった場合は(困るけど)素手武器を返す。
    //*/
    //---------------------------------------------------------------------
    static int getRandWeaponID();

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
    virtual const char* getName() const {return gWeaponNames[ mWeaponData.WeaponType ];}

	virtual ObjectType getObjType() const { return OBJ_WEAPON; }
	
	const WeaponData& getWeaponData() const { return mWeaponData; }

    /// ワールド座標空間上での当たり判定矩形を返す
	virtual const LRect* getBoundingRect();

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief Hoge */
	//---------------------------------------------------------------------------
	Weapon();

    virtual ~Weapon();


	virtual bool Initialize( const CreateData& data_ );

    /// フレーム更新
    virtual bool Update();

	virtual int HandleEvent(::EventType event_, void *args_) { return 0; }

protected:

	WeaponData  mWeaponData;
    Ref<LBatchPanel>      mPanel;

    GuideNamePlate*     mGuideNamePlate;    
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
