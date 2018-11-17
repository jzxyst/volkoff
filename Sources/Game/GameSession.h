//=============================================================================
//【 GameSession 】
//-----------------------------------------------------------------------------
///**
//  @file       GameSession.h
//  @brief      GameSession
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "../Event/EventType.h"

#define GAMEPORT (29796)

/// 親・子にかかわらず必ず持っているホスト情報
struct HostInfo
{
    char    IPAddress[ 32 ];    ///< IP アドレス
    char    Name[ 32 ];         ///< ユーザー名 (とりあえず接続画面で入力)
    bool    IsParent;           ///< 親 (サーバ) の場合は true
};



class GameServer;
class TcpStream;

//=============================================================================
// ■ GameSession クラス
//-----------------------------------------------------------------------------
///**
//  @brief      サーバとのセッションを管理するクラス
//
//  @par
//              親・子関係なく、サーバとの通信はこのクラスを使って行う。
//              親ホストの場合、このクラスは自分自身と通信することになる。
//
//              このクラスは GameManager 内にひとつだけ存在する。
//
//              今のところソケットによるのデータ受信処理は、クライアントは
//              GameSession で行い、サーバの場合は GameServer から直接
//              GameSession の HandleEvent を呼んでいる。
//*/
//=============================================================================
class GameSession
{
public:

    class EventListener
    {
    public:
        
        virtual ~EventListener() {}

        /// イベント処理コールバック
        virtual int HandleEvent( u32 event_, void* args_ ) = 0;
    };

public:

    /// コンストラクタ
    GameSession();

    /// デストラクタ
    ~GameSession();

public:

    /// 親として初期化 (GameManager から呼ばれる)
    void initialize( GameServer* server_ );

    /// 子として初期化 (GameManager から呼ばれる)
    void initializeChild( const char* parent_ip_addr_ );

    /// 自分自身のホストを表す情報を取得する
    const HostInfo& getHostInfo() const { return mHostInfo; }

    /// 親かを判定する
    bool isParent() const { return mHostInfo.IsParent; }

    /// イベントリスナーをセットする (外す時は自分で NULL を入れること)
    void setEventListener( EventListener* listener_ ) { mEventListener = listener_; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      サーバにデータを送信する (GameSession へ)
    //
    //  @par
    //              自分自身が親(サーバ)の場合はネットワークを使わず、
    //              直接 GameServer クラスに送信する。
    //*/
    //---------------------------------------------------------------------
    void sendToServer( u32 event_, void* data_, u32 size_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      オブジェクト作成メッセージ (SYSEV_CREATEED_OBJECT) をサーバに送信する
    //
    //  @param[in]  obj_type_ : enum ObjectType の値
    //
    //  @par
    //              SYSEV_CREATEED_OBJECT を送信するためのユーティリティ関数。
    //              各 GameObject の create() 内から呼ぶ。
    //*/
    //---------------------------------------------------------------------
    void sendCreatedObjectEvent( u32 obj_type_, void* data_, u32 size_ );

    

    //---------------------------------------------------------------------
    ///**
    //  @brief      同期待機
    //
    //  @par
    //              サーバに接続している全てのホストがこの関数を呼ぶまで
    //              待機する。その間、この関数は制御を返さない。
    //             
    //              (タイムアウトを入れておけるとベスト)
    //*/
    //---------------------------------------------------------------------
    void waitSync();

    //---------------------------------------------------------------------
    ///**
    //  @brief      イベント監視
    //
    //  @par
    //              サーバからホスト宛てに送られてきたデータを監視して
    //              HandleEvent に送る。
    //
    //              親の場合は GameServer から直接 HandleEvent 呼ばれるので
    //              この関数はなにもしない。
    //*/
    //---------------------------------------------------------------------
    void polling();

    //---------------------------------------------------------------------
    ///**
    //  @brief      イベント処理
    //
    //  @par
    //              GameObject のとは違い、SYSEV_～系のシステムイベントの処理関数。
    //*/
    //---------------------------------------------------------------------
    int HandleEvent( u32 event_, void* args_ );

private:

    static const int TEMP_BUFFER_SIZE = 2048;

    GameServer*     mGameServer;
    HostInfo        mHostInfo;      ///< 自分自身のホスト情報 (initiaze() で作成する)
    TcpStream*      mServerStream;  ///< サーバを示すストリーム (子として初期化した場合にのみ作成される)
    char            mTempBuffer[ TEMP_BUFFER_SIZE ];    ///< 一時バッファ
    EventListener*  mEventListener;

};

//=============================================================================
//								end of file
//=============================================================================