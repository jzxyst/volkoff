//=============================================================================
//【 GameSession 】
//=============================================================================

#include "stdafx.h"
#if MIGRATION
#else
#include "../Object/GameObjectManager.h"
#endif
#include "GameServer.h"
#include "GameSession.h"

//=============================================================================
// ■ GameSession クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
GameSession::GameSession()
    : mGameServer       ( NULL )
    , mServerStream     ( NULL )
    , mEventListener    ( NULL )
{
    memset( &mHostInfo, 0, sizeof( mHostInfo ) );
    memset( &mTempBuffer, 0, sizeof( mTempBuffer ) );
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
GameSession::~GameSession()
{
    SAFE_DELETE( mServerStream );
}

//---------------------------------------------------------------------
// ● 初期化
//---------------------------------------------------------------------
void GameSession::initialize( GameServer* server_ )
{
    mGameServer = server_;
    mHostInfo.IsParent = ( server_ != NULL );
}

//---------------------------------------------------------------------
// ● 子として初期化 (GameManager から呼ばれる)
//---------------------------------------------------------------------
void GameSession::initializeChild( const char* parent_ip_addr_ )
{
    mHostInfo.IsParent = false;

#if MIGRATION
#else
    mServerStream = NEW TcpStream();
    mServerStream->Initialize();
    mServerStream->Connect( "127.0.0.1", GAMEPORT );

    printf("接続しました\n");
#endif
}

//---------------------------------------------------------------------
// ● サーバにデータを送信する
//---------------------------------------------------------------------
void GameSession::sendToServer( u32 event_, void* data_, u32 size_ )
{
    // 自分が親の場合
    if ( mHostInfo.IsParent )
    {
        // すぐに処理
        mGameServer->HandleEvent( event_, data_ );
    }
    // 子の場合
    else
    {
        // ヘッダを作る
        GameSystemEventHeader header;
        header.Type         = event_;
        header.ArgSize      = size_;

        // 一度 mTempBuffer に全て格納
        memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
        if ( data_ )
        {
            memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );
        }

#if MIGRATION
#else
        // サーバに送る
        mServerStream->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
#endif
    }
}

//---------------------------------------------------------------------
// ● オブジェクト作成メッセージ (SYSEV_CREATEED_OBJECT) を送信する
//---------------------------------------------------------------------
void GameSession::sendCreatedObjectEvent( u32 obj_type_, void* data_, u32 size_ )
{
    char temp[ 1024 ];

    u32 all_size = sizeof( CreatedObjectArgs ) + size_;

    CreatedObjectArgs* data = reinterpret_cast< CreatedObjectArgs* >( temp );

    //printf("ホストID受け取る処理ができてない\n");
    data->HostID = 0;
    data->ObjectType = obj_type_;

    memcpy( &data[ 1 ], data_, size_ );

    // サーバに送信。サーバの HandleEvent で、自分以外のホストに送信される。
    // 「自分以外」という判定は HandleEvent 内で行う。
    sendToServer( SYSEV_CREATEED_OBJECT, data, all_size );






    // 自分がサーバの場合
    //if ( mHostInfo.IsParent )
    //{
    //    // すぐに GameSession に送信

    //    //sendEventToExclusionHost

    //}
    //// 自分がクライアントの場合
    //else
    //{
    //    LN_ASSERT( 0, "sendCreatedObjectEvent 未対応" );
    //}
}

//---------------------------------------------------------------------
// ● 同期待機
//---------------------------------------------------------------------
void GameSession::waitSync()
{
}

//---------------------------------------------------------------------
// ● イベント監視
//---------------------------------------------------------------------
void GameSession::polling()
{

#if MIGRATION
#else

    // 子の場合はサーバから送られてきているイベントをチェックする
    if ( mServerStream )
    {
        //mServerStream->getSessionState()
        if ( !mServerStream->getRecvList().empty() )
	    {
            //printf( "data:%s\n", mServerStream->getRecvList().front()->getData() );
            //printf( "size:%d\n", mServerStream->getRecvList().front()->getSize() );

            GameSystemEventHeader* header = reinterpret_cast< GameSystemEventHeader* >( mServerStream->getRecvList().front()->getData() );

            // イベント処理
            HandleEvent( header->Type, &header[ 1 ] );

		    mServerStream->getRecvList().pop_front();
	    }
    }
#endif
}

//---------------------------------------------------------------------
// ● イベント処理
//---------------------------------------------------------------------
int GameSession::HandleEvent( u32 event_, void* args_ )
{
    if ( mEventListener )
    {
        mEventListener->HandleEvent( event_, args_ );
    }

    switch ( event_ )
    {
        

        ///////////////////////////////////////////// オブジェクトを削除する
        case SYSEV_DELETE_GAMEOBJECT:
        {
#if MIGRATION
#else
            GameObjectManager* manager = GameObjectManager::getInstance();
            GameObject* obj = manager->findObject( *static_cast< u32* >( args_ ) );



            if ( obj )
            {
                //printf( "del handle %d\n", *static_cast< u32* >( args_ ) );

                manager->deleteObject( obj );
            }
#endif
            break;
        }
    }

    return 0;
}

//=============================================================================
//								end of file
//=============================================================================