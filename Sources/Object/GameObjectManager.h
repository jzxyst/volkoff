//=============================================================================
/*! 
    @addtogroup 
    @file       GameObjectManager.h
    @brief      GameObjectの管理
    
    GameObjectManagerの定義
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_GAMEOBJECTMANAGER_H__
#define __INCLUDE_GAMEOBJECTMANAGER_H__


/*! @par include */
#include "./../Utility/Singleton.h"
#include "./../Utility/NodeList.h"
#include "./../Utility/MessageQueue.h"
#include "./../Event/EventType.h"
#include <list>
#include <map>


class GameObject;
class AttackedObject;

typedef std::list<GameObject*>                  GameObjectList;
typedef std::map<u32,GameObject*>               GameObjectMap;
typedef std::pair<u32,GameObject*>              GameObjectPair;
typedef std::list< AttackedObject* >            AttackedObjectList;
typedef Core::Base::NodeList< AttackedObject >  HitObjectList;

/*! @enum ObjectType */
typedef enum _ENUM_OBJECT_TYPE
{
	OBJ_UNDEF = 0,
	OBJ_CHARACTER, //一時的
	OBJ_LADDER,    // はしご           … static オブジェクト。 以下は動的。
	OBJ_LADDERTOP,
	OBJ_BOX,       // 木箱

    OBJ_ITEM_BEGIN, // ▼ ここからアイテム
	OBJ_CURE_S,    // 回復アイテム小
	OBJ_CURE_M,    // 回復アイテム中       
	OBJ_CURE_L,    // 回復アイテム大
	OBJ_KEY,       // 鍵
    OBJ_ITEM_END,   // ▲ ここまでアイテム
	OBJ_EXIT,     //出口
	OBJ_EXIT_LOCK,//鍵付き出口
    OBJ_WEAPON,     ///< 武器
	OBJ_DOOR,		///< ドア	[山本]とりあえず用意
	OBJ_ENTRY,		///< 入口　とりあえず
	OBJ_FORT,		///< 自動機銃
	OBJ_LOCKER,		///< ロッカー
	OBJ_MANHOLE,	///< マンホール
	OBJ_MINE,		///< 地雷
	OBJ_VASE,		///< 花瓶
	OBJ_WINDOW,		///< 窓
	OBJ_ENEMY,
	OBJ_UBW,        ///UBW
	OBJ_BULLET,
	OBJ_GRENADE,

}ObjectType;


/*! @class GameObjectManager */
class GameObjectManager : public Singleton<GameObjectManager>
{
	friend Singleton<GameObjectManager>;

private:
	/*! @par privateメンバ変数 */
	GameObjectList  m_dqObjectList;     ///< すべての GameObject を格納するリスト
	GameObjectList  m_dqTempList;       ///< Update中にnewされたオブジェクトを格納するリスト
    GameObjectMap   m_mObjectMap;       ///< GameObject とハンドルの対応表

    u32             m_unNextHandle;     ///< 次に作成されるオブジェクトに割り当てるハンドル (※ハンドルはサーバからもらう必要がある。後で直しておく)

private:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::GameObjectManager

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	GameObjectManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::~GameObjectManager

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~GameObjectManager();

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::Initialize

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
		@brief GameObjectManager::Release

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
		@brief GameObjectManager::Update

		フレーム更新処理
        
		@param[in]      void
		@return         void
		@exception      none
        @par
                        [yama]
                        キューにたまっているイベントも合わせて処理する。
                        関数の実行順序は、
                        
                            HandleEvent() → Update() → UpdateSelf() → 削除する必要があれば削除
	*/
	//---------------------------------------------------------------------------
	void Update();



    //---------------------------------------------------------------------------
	/*! 
		@brief GameObjectManager::AddObject

		リスナーをリストに追加する

		@param[in]      GameObject *pCObj 追加するオブジェクトポインタ
		@return         追加されたオブジェクトに割り当てられたハンドル (gatHandle() で得られるものと同じ)
		@exception      none
	*/
	//---------------------------------------------------------------------------
	u32 AddObject(GameObject *pCObj);

    /// オブジェクトを削除する
    void deleteObject( GameObject* obj_ );


    /// 攻撃の関係するオブジェクトを追加する (AttackedObject のコンストラクタから呼ばれる)
    void addAttackedObject( AttackedObject* obj_ );

    /// 攻撃の関係するオブジェクトを外す (AttackedObject のデストラクタから呼ばれる)
    void removeAttackedObject( AttackedObject* obj_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      オブジェクトを検索する
    //
    //  @param[in]  handle_ : 対象オブジェクトのハンドル
    //
    //  @par
    //              存在しない場合は NULL を返す。
    //*/
    //---------------------------------------------------------------------
    GameObject* findObject( u32 handle_ );
	



    //---------------------------------------------------------------------
    ///**
    //  @brief      指定したハンドルを持つオブジェクトにイベントを送信する (キューイング無し)
    //
    //  @param[in]  handle_ : 対象オブジェクトのハンドル (0xffffffff ですべてのオブジェクトに送信する)
    //  @param[in]  event_  : イベントの種類
    //  @param[in]  data_   : イベントの引数データ)
    //  @param[in]  size_   : data_ のサイズ (バイト単位)
    //
    //  @par
    //              イベントをキューにためず、直ちにオブジェクトに送信する。
    //              ネットワーク越しには使えないので注意。
    //              主にコントローラからの入力を Player に伝えるために使う。
    //*/
    //---------------------------------------------------------------------
    void sendEvent( u32 handle_, u32 event_, void* data_, u32 size_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      指定したハンドルを持つオブジェクトにイベントを送信する (キューイングあり)
    //
    //  @param[in]  handle_ : 対象オブジェクトのハンドル (0xffffffff ですべてのオブジェクトに送信する)
    //  @param[in]  event_  : イベントの種類
    //  @param[in]  data_   : イベントの引数データ)
    //  @param[in]  size_   : data_ のサイズ (バイト単位)
    //
    //  @par
    //              イベントを一度キューにため、次の GameObjectManager::Update() が
    //              呼ばれたときにすべて処理する。
    //              ネットワーク越しに使うイベントはこちら。
    //*/
    //---------------------------------------------------------------------
    void postEvent( u32 handle_, u32 event_, void* data_, u32 size_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      AttackedObject ととの当たり判定を行う
    //
    //  @param[in]  rect_         : ワールド座標上の矩形
    //  @param[in]  target_group_ : 対象のグループ (AttackedGroup の組み合わせ)
    //
    //  @return     当たったオブジェクトのリスト
    //*/
    //---------------------------------------------------------------------
    HitObjectList* judgeCollitionToAttackedObject( const LRect& rect_, u32 target_group_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      指定した種類のオブジェクトと当たり判定を行う
    //
    //  @param[in]  rect_             : ワールド座標上の矩形
    //  @param[in]  target_type_      : 対象の種類
    //  @param[in]  target_type_end_  : 対象の種類
    //
    //  @return     当たったオブジェクトのハンドル
    //
    //  @par
    //              target_type_end_ は範囲指定する場合に値を渡す。
    //              指定した場合、target_type_ 以上、target_type_end_ 以下の
    //              種類のオブジェクトと判定を行う。
    //*/
    //---------------------------------------------------------------------
    u32 judgeCollitionTypeSpecified( const LRect& rect_, ObjectType target_type_, ObjectType target_type_end_ = OBJ_UNDEF );

	//---------------------------------------------------------------------
    ///**
    //  @brief      指定した種類のオブジェクトと当たり判定を行ったのちに消去する
    //
    //  @param[in]  rect_             : ワールド座標上の矩形
    //  @param[in]  target_type_      : 対象の種類
    //  @param[in]  target_type_end_  : 対象の種類
    //
    //  @return     当たったオブジェクトのハンドル
    //
    //  @par
    //              target_type_end_ は範囲指定する場合に値を渡す。
    //              指定した場合、target_type_ 以上、target_type_end_ 以下の
    //              種類のオブジェクトと判定を行う。
    //*/
    //---------------------------------------------------------------------
    u32 judgeCollitionTypeSpecifiedAndDelete( const LRect& rect_, ObjectType target_type_, ObjectType target_type_end_ = OBJ_UNDEF );


    

	//
	// GameObjectManager::CollisionToObject
	//
	// @param[u32]  obj_type_ : 対象のオブジェクトタイプ
	// @param[LRect]    rect_ : 対象の矩形
	// @param[LVector2] dist_ : オブジェクトと対象矩形の中心座標の距離
	// @param[LVector2] over_ : オブジェクトとのめり込み量
	// @return[u32]           : リストの中の当たっていたオブジェクトの種類
	//
	//    渡された矩形とリスト内の矩形を比較
	//    当たっていた場合ObjectTypeを返す
	//
	u32 CollisionToObject( const u32 obj_type_, LRect rect_, LVector2* dist_, LVector2* over_ );


    //---------------------------------------------------------------------
    ///**
    //  @brief      指定した種類のオブジェクトを削除する
    //
    //  @param[in]  target_type_  : 対象の種類
    //
    //  @return     当たったオブジェクトのハンドル
    //*/
    //---------------------------------------------------------------------
    u32 removeObject( ObjectType target_type_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      プレイヤー以外のオブジェクトを削除する
    //
    //  @return     
    //*/
    //---------------------------------------------------------------------
    void deleteStageObject();


    GameObjectList& getGameObjectList() { return m_dqObjectList; }


private:

    static const int MSGQUEUE_SIZE = 16384;	///< メッセージキュー一つ分のサイズ (バイト数)
    static const int TEMPBUFFER_SIZE = 256;
    static const int MAX_MSG_QUEUES = 64;	///< メッセージキューの数

    LNote::Utility::MessageQueue    mEventQueueArray[ MAX_MSG_QUEUES ];

    u32                             mUsingEventQueueIndex;
    u8                              mTempBuffer[ TEMPBUFFER_SIZE ];
    AttackedObjectList              mAttackedObjectList;                ///< 攻撃をする・攻撃を受けるオブジェクトのリスト
    HitObjectList                   mHitObjectList;                     ///< judgeCollitionToAttackedObject() 用の一時リスト
};


//End of Include Guard
#endif

#include "AttackedObject.h"

//=============================================================================
//								End of File
//=============================================================================
