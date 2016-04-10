//=============================================================================
/*! 
    @addtogroup 
    @file       EventType.h
    @brief      イベント周りの定義
    
    イベント周りの定義
    
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


//Include Guard
#ifndef __INCLUDE_EVENT_TYPE_H__
#define __INCLUDE_EVENT_TYPE_H__


/*! @enum EventType */
typedef enum _ENUM_EVENT_TYPE
{
	EV_UNDEF = 0,
	EV_INPUT,


    // ▼ 行動関係 ////////////////////////////////////////////
    //      行動関係のイベントは、送られてきたときに直ちにその行動をとるようにする。
    //      これは、ネットワーク実装時に回線速度とかの問題でのけぞり時間が長引いてしまった場合、
    //      その間攻撃開始メッセージが送られてきてもその動作をしないということを防ぐために必要。

    EV_ACTION_WAIT,                     ///< [ 引数なし ] 待機開始
    EV_ACTION_RUN,                      ///< [ enum CharaDir ] 走り開始 

    EV_ACTION_STUN,                     ///< [ u32 フレーム数 ] のけぞり開始
	EV_ACTION_BLOW,						// [ u32 フレーム数 ] ふっとび時間

	EV_ACTION_JUMP,			            // [ 引数なし ]ジャンプ開始
	EV_ACTION_SQUAT,					// [ 引数なし ]しゃがみ開始
	EV_ACTION_LADDER_WAIT,              // [ 引数なし ]はしご待機開始
	EV_ACTION_LADDER_UP,                // [ 引数なし ]はしご登り開始
	EV_ACTION_LADDER_DOWN,              // [ 引数なし ]はしご降り開始
	EV_ACTION_GUARD,					// [ 引数なし ]ガード開始
	EV_ACTION_SQUAT_GUARD,				// [ 引数なし ]しゃがみガード開始

    EV_ACTION_ITEM_GET,                 ///< アイテム取得のためのしゃがみ

    EV_ACTION_ATTACK_1,                 ///< 通常攻撃1
	EV_ACTION_ATTACK_2,                 ///< 通常攻撃2
	EV_ACTION_ATTACK_3,                 ///< 通常攻撃3
	EV_ACTION_ATTACK_SQUAT_ATTACK,      ///< しゃがみ攻撃
	EV_ACTION_ATTACK_JUMP_ATTACK,       ///< ジャンプ攻撃
	EV_ACTION_ATTACK_ANTIAIR_ATTACK,    ///< 対空攻撃
	EV_ACTION_ATTACK_DUSH_ATTACK,       ///< ダッシュ攻撃

    EV_ACTION_START_DEAD,               ///< [ 引数なし ] 戦闘不能開始 (モーション開始とか)
    // ▼  ////////////////////////////////////////////
    EV_APPLY_DAMAGE,        ///< [ AttackEventArg ] ダメージを与える

    EV_GET_ITEM,            ///< [ u32 アイテム番号 ] アイテムを拾うことができた
    EV_GET_WEAPON,          ///< [ WeaponData ] 武器を拾うことができた
    

    // ▼ システム系イベント ////////////////////////////////////////////
    //      GameSession::send で使う。GameObjectでは基本的に使わない。
    SYSEV_BEGIN,

    SYSEV_GOTO_SCENEGAME,       ///< SceneGame に移動する (親ホストからサーバ(自分自身)に送られた後、サーバから全てのホストに送られる)


    SYSEV_GAMEOBJECT,           ///< ゲームオブジェクト関係のデータ。(LNote::Utility::MessageQueue のシリアライズデータ)
    SYSEV_ITEM_REQUEST,         ///< [ ItemRequestArgs ] アイテム(武器含む)を拾いたいときの要求 (各ホストからサーバへ。サーバは EV_GET_ITEM または EV_GET_WEAPON を返す)

    SYSEV_DELETE_GAMEOBJECT,    ///< [ u32 オブジェクトハンドル ] ゲームオブジェクトを削除する (実際には削除フラグを立てる。GameObject が isEntity() == true の場合、デストラクタで送信する。または、アイテム取得等の削除。)
                                //                                デストラクタ以外から削除する場合、送信側はかならず削除するオブジェクトを削除した後でこのイベントを送信すること。

    SYSEV_CREATEED_OBJECT,      ///< [ CreatedObjectArgs ]各ホスト内でオブジェクトを作成した時(create() で is_entity_ = true にしたとき)、サーバ経由で、作成したホスト以外のホストに生成したことを伝える

    SYSEV_END,

}EventType;


/*! @enum InputType */
typedef enum _ENUM_INPUT_TYPE
{
	INPUT_UNDEF = 0,
	INPUT_ON_ATTACK,
}InputType;


/// イベントのヘッダデータ (このデータは postEvent 時、自動的に付加される。特に気にする必要は無し)
struct EventHeader
{
    u32         Type;           ///< イベントの種類
    u32         ObjectHandle;   ///< 送信対象のオブジェクト (0xffffffff で全てに送信する)
    u32         ArgSize;        ///< 以降に続く引数データのサイズ
};

/// ゲーム全体に関係するイベントのヘッダ (GameSession::send() で自動的に不可される。ゲームオブジェクト用のもの (EventHeader) とは別)
struct GameSystemEventHeader
{
    u32         Type;           ///< イベントの種類
    u32         ArgSize;        ///< 以降に続く引数データのサイズ
};

/// 攻撃イベントの引数データ
struct AttackEventArg
{
    s32         Damage;         ///< ダメージ量
	u32         AttackerHandle; //
    LVector3    BrowVector;     ///< ふっ飛ばしベクトル
	u8          Criticalflag;    ///< クリティカルのフラグ
	u8			Guardflag;       ///<ガードのフラグ
};

struct ItemRequestArgs
{
    u32         GetterHandle;   ///< 拾おうとしているキャラクターのハンドル
    u32         ItemObjHandle;  ///< アイテムまたは武器オブジェクトのハンドル
};

/// オブジェクト生成時、他のホストに伝えるときのデータ
struct CreatedObjectArgs
{
    u32         HostID;         ///< 自ホストに割り当てられているホストID。サーバに送られた後、これ以外のホストに送信される。GameSession から取得する。
    u32         ObjectType;     ///< ObjectType の値
    //void*       ArgData;        ///< 以降に続く引数データ。このデータは各オブジェクトの create() に渡される
};

/// サーバにオブジェクトの作成を要求するときの引数データ
//struct CreateObjectArgs
//{
 //   u32         
//};


#if 0

class EventListener
{
private:
	unsigned int mHandle;

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
	const unsigned int& getHandle() const {return mHandle;}

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	void setHandle(unsigned int unHandle_) {mHandle = unHandle_;}

	EventListener();
	virtual ~EventListener();
	virtual int HandleEvent(u32 event_,void *args_) = 0;
};

#endif


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
