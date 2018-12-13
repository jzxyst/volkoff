//=============================================================================
//【 GameManager 】
//-----------------------------------------------------------------------------
///**
//  @file       GameManager.h
//  @brief      GameManager
//  @author     yama
//*/
//=============================================================================

#pragma once

#include <vector>
#include "../Event/EventManager.h"
#include "../Effect/EffectManager.h"
#include "GameServer.h"
#include "GameSession.h"

#define MAIN_BGM_NAME "Data/Sound/BGM/n32.ogg"


typedef enum _ENUM_RANK
{
	RANK_EASY = 0,
	RANK_NOMAL,
	RANK_HARD,
	RANK_VALFIRLE
}Rank;
class Player;
class Character;

//=============================================================================
// ■ GameManager クラス
//-----------------------------------------------------------------------------
///**
//  @brief      ゲーム全体の管理クラス。シングルトン。
//
//  @par
//              ゲーム全体で一元に管理する必要があるデータを扱う。
//              また、
//*/
//=============================================================================
class GameManager
{
public:

    /// インスタンスの取得
    static GameManager* getInstance();

public:

    //---------------------------------------------------------------------
    ///**
    //  @brief      親として初期化する
    //
    //  @par
    //              部屋を作り、このホストをサーバとして動作するようにする。
    //              初期化後、自分の IP アドレスなどを知るためには getHostInfo() を使うこと。
    //              ひとりでプレイするときはこれで初期化。
    //*/
    //---------------------------------------------------------------------
    void initializeParent();

    //---------------------------------------------------------------------
    ///**
    //  @brief      子として初期化する
    //
    //  @retval     true  : 成功
    //  @retval     false : 失敗 (接続できなかった)
    //
    //  @par
    //              接続画面で接続先の IP アドレスを入力した後、
    //              それをこの関数に渡して初期化する。
    //
    //              すぐに処理を返して、接続が完了した場合は
    //              接続完了イベントを自分自身に発行するのがいいと思う。
    //*/
    //---------------------------------------------------------------------
    bool initializeChild( const char* parent_ip_addr_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      ゲームの終了処理
    //
    //  @par
    //              ゲーム画面からタイトル画面に戻るとき等に呼ぶこと。
    //*/
    //---------------------------------------------------------------------
    void finalize();

    //---------------------------------------------------------------------
    ///**
    //  @brief      コンティニューに備えてバックアップを取る
    //*/
    //---------------------------------------------------------------------
    void commit();

    //---------------------------------------------------------------------
    ///**
    //  @brief      コンティニュー時のリセット
    //
    //  @par
    //              ゲームオーバー画面で reset → SceneGame 移動 の順に呼ぶこと。
    //*/
    //---------------------------------------------------------------------
    void reset();

    //---------------------------------------------------------------------
    ///**
    //  @brief      GameSession の取得
    //
    //  @par
    //              サーバとのセッションを表す。
    //              自分自身がサーバ(親)である場合、これは自分自身を指す。
    //              (普通はそんなこと気にしなくてもいいように作ってあるけど)
    //*/
    //---------------------------------------------------------------------
    GameSession* getGameSession() { return mGameSession; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      フレーム更新
    //
    //  @par
    //              毎フレーム呼び出す必要のある更新処理。
    //*/
    //---------------------------------------------------------------------
    void update();

    //---------------------------------------------------------------------
    ///**
    //  @brief      イベント処理
    //
    //  @par
    //              各オブジェクトの HandleEvent の呼び出し元みたいなかんじ…
    //*/
    //---------------------------------------------------------------------
    int HandleEvent( u32 event_, void *args_ );

	void setRank(u32 rank_) { mRank = rank_; }

    /// EffectManager 取得
    EffectManager* getEffectManager() const { return mEffectManager; }

    /// ラスボスを生成した時にコレでセットする
    void setLastBossCharacter( Character* boss_ ) { mLastBoss = boss_; }

    /// (グローバル変数にしてもいいけど、とりあえずシングルトンで徹底)
    Character* getLastBossCharacter() const { return mLastBoss; }



public:

    /// 現在のフロア数の取得
    u32 getFloorNum() const { return mFloorNum; }

    /// 現在のスコアの取得
    u32 getScore() const { return mScore; }
	u8  getRank() const {return mRank;}
	/// Player の取得
	Player* getPlayer() { return mPlayer; }
	u8  getOpenflag() { return mOpenflag;}
	void NextFloor() {++mFloorNum;}

	const u8 getKeyflag() const {return mKeyflag;}

    void setKeyflag(const u8 Keyflag_) {mKeyflag = Keyflag_;}

	void setFloorNum(const u32 FloorNum_){mFloorNum=FloorNum_;}

	void setScore(const u32 Score_){mScore=Score_;}

	void setOpenflag(const u8 open_flag_) {mOpenflag = open_flag_ ;}

	void resetGameTime() { mGameTime = 0; }

	// フレーム数単位
	lnU32 getGameTime() const { return mGameTime; }

	// 現在時間を全体の秒と 時間/分/秒 で取得
	static void splitGameTime( lnU32 frame_count_, u32* h_, u32* m_, u32* s_ )
	{
		//mGameTime;	// フレーム数

		u32 s = frame_count_ / 60;
		*h_ = s / 3600;
		*m_ = (s % 3600) / 60;
		*s_ = (s % 60);
	}

private:
    LN_DISALLOW_COPY_AND_ASSIGN(GameManager);

    /// コンストラクタ
    GameManager();

    /// デストラクタ
    ~GameManager();


private:

    GameServer*     mGameServer;    ///< サーバ。GameManager が親として初期化された場合にのみ作成される
    GameSession*    mGameSession;
    EffectManager*  mEffectManager;

    u32             mFloorNum;      ///< 現在のフロア数
    u32             mScore;         ///< 現在のスコア
	u8              mRank;           ///<　難易度
	Player*			mPlayer;        ///< 自分のホストで操作するキャラクター
	u8             mKeyflag;	//鍵フラグ	
	u8             mOpenflag;
	//u32            mTime;
	lnU32			mGameTime;

    Character*      mLastBoss;

    struct
    {
        u32 Score;
		u32 Time;

    } mBackup;

};

//=============================================================================
//								end of file
//=============================================================================
