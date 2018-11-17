//=============================================================================
//【 GameServer 】
//=============================================================================

#include "../Event/EventType.h"
#include "../Object/GameObjectManager.h"
#include "../Object/Weapon.h"
#include "GameManager.h"
#include "GameSession.h"
#include "GameServer.h"

//=============================================================================
// ■ GameServer クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
GameServer::GameServer()
    : mMyGameSession    ( NULL )
    , mListen           ( NULL )
{
    
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
GameServer::~GameServer()
{
    SAFE_DELETE( mListen );


    TcpStreamArray::iterator itr = mConnectedStreamArray.begin();
    TcpStreamArray::iterator end = mConnectedStreamArray.end();
    for ( ;itr != end; ++itr )
    {
        SAFE_DELETE( (*itr) );
    }
}

//---------------------------------------------------------------------
// ● 初期化
//---------------------------------------------------------------------
void GameServer::initialize( GameSession* sesson_ )
{
    mMyGameSession = sesson_;

#if MIGRATION
#else
    mListen = NEW TcpStream();
    mListen->Initialize();
    mListen->Bind( GAMEPORT );
    mListen->Listen( 5 );
#endif
}

//---------------------------------------------------------------------
// ● 接続を監視する (1フレームに1度呼び出す)
//---------------------------------------------------------------------
void GameServer::polling()
{
#if MIGRATION
#else
    if ( mListen->getAcceptDemandNum() > 0 )
    {
        TcpStream* tcp_stream;
        mListen->Accept( &tcp_stream );

        mConnectedStreamArray.push_back( tcp_stream );

        printf("接続してきました\n");

        tcp_stream->Send( "fせつぞくできた", strlen( "fせつぞくできた" ) + 1 );
    }
#endif
}

//---------------------------------------------------------------------
// ● 全てのクライアントにイベントを送信する
//---------------------------------------------------------------------
void GameServer::sendEventToAllHost( u32 event_, void* data_, u32 size_ )
{
    // 自分自身にはすぐに送信
    mMyGameSession->HandleEvent( event_, data_ );

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

    // 接続済みのものに全て送信
    TcpStreamArray::iterator itr = mConnectedStreamArray.begin();
    TcpStreamArray::iterator end = mConnectedStreamArray.end();
    for ( ;itr != end; ++itr )
    {
#if MIGRATION
#else
        (*itr)->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
#endif
    }
}

//---------------------------------------------------------------------
// ● 指定したホスト以外の全てのホストの GameSession にイベントを送信する
//---------------------------------------------------------------------
void GameServer::sendEventToExclusionHost( u32 exc_host_id_, u32 event_, void* data_, u32 size_ )
{
    if ( exc_host_id_ != 0 )
    {
        // 自分自身にはすぐに送信
        mMyGameSession->HandleEvent( event_, data_ );
    }

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

    // 指定以外の接続済みのものに全て送信
    u32 n = mConnectedStreamArray.size();
    u32 exc = exc_host_id_ - 1;
    for ( u32 i = 0; i < n; ++i )
    {
        if ( i != exc )
        {
#if MIGRATION
#else
            mConnectedStreamArray[ i ]->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
#endif
        }
    }
}

//---------------------------------------------------------------------
// ● イベント処理
//---------------------------------------------------------------------
int GameServer::HandleEvent( u32 event_, void* args_ )
{
    switch ( event_ )
    {
        ///////////////////////////////////////////// SceneGame に移動する
        case SYSEV_GOTO_SCENEGAME:
        {
            sendEventToAllHost( SYSEV_GOTO_SCENEGAME, NULL, 0 );
            break;
        }

        ///////////////////////////////////////////// アイテム(武器含む)を拾いたいときの要求 (各ホストからサーバに送られてくる)
        case SYSEV_ITEM_REQUEST:
        {
			ItemRequestArgs* args = static_cast< ItemRequestArgs* >(args_);
			GameObjectManager* manager = GameObjectManager::getInstance();

			// アイテムオブジェクトを探す
			GameObject* obj = manager->findObject(args->ItemObjHandle);

			if (obj)
			{
				// 武器の場合
				if (obj->getObjType() == OBJ_WEAPON)
				{
					// 取得するキャラクターに対してオブジェクトの持つ武器データを送信する
					WeaponData data = (static_cast< Weapon* >(obj))->getWeaponData();
					manager->postEvent(args->GetterHandle, EV_GET_WEAPON, &data, sizeof(WeaponData));

					u32 handle = obj->getHandle();

					// 武器オブジェクトを削除する
					sendEventToAllHost(SYSEV_DELETE_GAMEOBJECT, &handle, sizeof(u32));
				}
			}
        }
    }

    return 0;
}



//=============================================================================
//								End of File
//=============================================================================