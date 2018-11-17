//=============================================================================
/*! 
    @addtogroup 
    @file       MapManager.h
    @brief      
    
    マップを管理するクラスの定義
    
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

#pragma once 

/*! @par include */
#include "../Object/Gimmick/Ladder.h"
#include "../Object/Gimmick/LadderTop.h"
#include "../Object/Gimmick/Entry.h"
#include "../Object/Gimmick/Exit.h"
#include "../Object/Gimmick/Exit_Lock.h"
#include "../Object/Gimmick/Vase.h"
#include "../Object/Gimmick/Mine.h"
#include "../Object/Gimmick/Box.h"
#include "../Object/Gimmick/Fort.h"
#include "../Object/Gimmick/Locker.h"
#include "../Object/Gimmick/Window.h"
#include "../Object/Gimmick/Door.h"
#include "../Object/Gimmick/Manhole.h"
#include "../Object/Gimmick/Duct.h"
#include "../Object/Gimmick/TopWall.h"
#include "../Object/Gimmick/BottomWall.h"
#include "../Object/Gimmick/UBW.h"

#include "../Object/Item/Key.h"
#include "../Object/Item/Cure_S.h"
#include "../Object/Item/Cure_M.h"
#include "../Object/Item/Cure_L.h"

#include "../Object/Enemy.h"
#include "../Object/MidBoss1.h"
#include "../Object/MidBoss2.h"
#include "../Object/Valfirle.h"

#include"../Object/Player.h"
#include"../Object/Bullet.h"

/*! @enum MapType */
typedef enum _ENUM_MAP_TYPE
{
	MAP_NULL = 0,
	MAP_BLOCK,//壁ブロック
	MAP_BLOCK_THROUGH,//すり抜けられるブロック
	MAP_BLOCK_STEALTH,

	MAP_LADDER = 10,//はしご
	MAP_LADDERTOP,

	MAP_ENTRY = 20,//入口
	MAP_EXIT,//出口
	MAP_EXIT_LOCK,//かぎ付き出口
	MAP_ENTRYWALL,
//敵が出現するもの
	MAP_WINDOW_S = 30,//窓（少）
	MAP_WINDOW_L,//窓(多)
	MAP_WINDOW_HARD,//窓（HARD）
	MAP_LOCKER_S =33,//ロッカー
	MAP_LOCKER_L,
	MAP_LOCKER_HARD,
	MAP_MANHOLE_S = 36,//マンホール
	MAP_MANHOLE_L,
	MAP_MANHOLE_HARD,
	MAP_DOOR_S = 39 , //ドア
	MAP_DOOR_L,
	MAP_DOOR_HARD,
	MAP_WALL_S = 42, //壁壊し
	MAP_WALL_L,
	MAP_WALL_HARD,
	MAP_WALL2_S = 45,//壁壊し
	MAP_WALL2_L,
	MAP_WALL2_HARD,
	MAP_DUCT_S = 48,//ダクト
	MAP_DUCT_L,
/////


	MAP_FORT = 50,//自動機銃
	MAP_FORT_HARD,
	MAP_MINE,//地雷
	MAP_MINE_HARD,
	MAP_WINDOW_DUMMY,//窓ダミー
	MAP_LOCKER_DUMMY,//ロッカーダミー
	MAP_MANHOLE_DUMMY,//マンホールダミー
	MAP_DOOR_DUMMY,//ドアダミー
	MAP_DUCT_DUMMY,//ダクトダミー
	MAP_WALL_DUMMY,

	MAP_BOX =60 ,//箱
	MAP_DRUM,//ドラム缶
	MAP_VASE,//花瓶
	MAP_UBW, //ubw

	MAP_KEY =70,//鍵
	MAP_CURE_S,//回復アイテム
	MAP_CURE_M,
	MAP_CURE_L,
	MAP_GRENADE,


	MAP_ENEMY = 90,
	MAP_ENEMY_S,
	MAP_ENEMY_L, 
	MAP_MIDBOSS_KATANA,
	MAP_MIDBOSS_TAEKWONDO,
	MAP_MIDBOSS_KNIFE,
	MAP_MIDBOSS_SCYTHE,
	MAP_VALFIRLE,
	MAP_UNDEF = 0xffffffff,
}MapType;


enum MapCollFlag
{
	MAPCOLL_LEFT	= 0x01,
	MAPCOLL_RIGHT	= 0x02,
	MAPCOLL_UP		= 0x04,
	MAPCOLL_DOWN	= 0x08,
};


class MapManager
{
public:

	/// インスタンスの取得
	static MapManager* getInstance();

private:

    /// コンストラクタ
    MapManager();

    /// デストラクタ
    ~MapManager();

	

public:

	/// 終了処理 (GameManager から呼ばれる)
	void finalize();

    //---------------------------------------------------------------------
    ///**
    //  @brief      マップ (ステージ) の変更
    //
    //  @param[in]  map_id_ : 作成するマップ番号
    //
    //  @par
    //              ストーリーモードで、ステージを切り替えるときに呼び出す。
    //
    //              背景のマップチップの配置を切り替え、必要な GameObject を
    //              すべて new する。
    //
    //              この関数を呼ぶときは、現在のステージで解放する必要があるものは
    //              すべて解放済みであること。
    //*/
    //---------------------------------------------------------------------
    void changeMap( u32 map_id_ );

	u32 collision( LRect rect_, LVector3 velocity_, LVector3* out_pos_ );	// out_pos_は矩形の左上の座標

	bool BulletCollision(LRect rect_);

	LVector3 getStartPosition();

    // タイルマップ解放 (タイトルへ戻るときなど)
    void releaseTilemap();


	int getMapID() { return mMapID; }

private:

	u32                         mMapID;     ///< 現在のマップ番号 (ランダムマップでは常に 0)
	u32                         mWidth;     ///< マップの幅
	u32                         mHeihgt;    ///< マップの高さ

	int							mMapData[100 * 100];

	TileSetPtr					m_tileset;
	TileLayerPtr				m_tileLayer;
	TileMapPtr					mTilemap;



    Ladder* mLadder[250];//はしごクラス
	u32 mLadderCnt;//はしごの数

    LadderTop* mLadderTop[50];//はしごクラス
	u32 mLadderTopCnt;//はしごの数

	Entry* mEntry;

	Exit* mExit;

	Exit_Lock* mExit_Lock;

	Locker* mLocker[30];
	u32 mLockerCnt;

	Manhole* mManhole[30];
	u32 mManholeCnt;

	Window* mWindow[30];
	u32 mWindowCnt;

	Door* mDoor[30];
	u32 mDoorCnt;

	TopWall* mTopWall[30];
	u32 mTopWallCnt;

	BottomWall* mBottomWall[30];
	u32 mBottomWallCnt;

	Vase* mVase[30];//花瓶クラス
	u32 mVaseCnt;//花瓶の数



	Mine* mMine[30];//地雷クラス
	u32 mMineCnt;//地雷の数

	Box* mBox[30];//箱クラス
	u32 mBoxCnt;//箱の数

	Fort* mFort[20];
	u32 mFortCnt;

	GateKey* mKey;//鍵クラス
	
	Cure_S* mCure_S[20];
	u32 mCure_Scnt;

	Cure_M* mCure_M[20];
	u32 mCure_Mcnt;

	Cure_L* mCure_L[20];
	u32 mCure_Lcnt;

	Duct* mDuct[30];
	u32 mDuctCnt;

	UBW * mUBW[10];
	u32 mUBWCnt;

	Enemy* mEnemy;

	MidBoss1* mMidBoss1;

};

//=============================================================================
//								End of File
//=============================================================================
