//=============================================================================
//【 SceneNetRoom 】
//=============================================================================

#include "../Game/GameManager.h"
#include "SceneGame.h"
#include "SceneConnection.h"
#include "SceneNetRoom.h"

//=============================================================================
// ■ SceneNetRoom クラス
//=============================================================================


//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneNetRoom::onStart()
{
    printf( "-------------------------------------------------\n" );
    printf( " ▼ ルーム画面\n" );
    printf( "-------------------------------------------------\n" );

    if ( GameManager::getInstance()->getGameSession()->isParent() )
    {
        printf( "Z > ゲーム画面へ\n" );
    }
    else
    {
        printf( "開始待ち...\n" );
    }

    GameManager::getInstance()->getGameSession()->setEventListener( this );
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneNetRoom::onUpdate()
{
    GameManager::getInstance()->update();



    GameSession* session = GameManager::getInstance()->getGameSession();

    if ( session->isParent() )
    {
        if ( Input.isOnTrigger( LN_BUTTON_A ) )
        {
            session->sendToServer( SYSEV_GOTO_SCENEGAME, NULL, 0 );

            //LGameScene::changeScene( NEW SceneGame() );
        }
    }

}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneNetRoom::onTerminate()
{
    GameManager::getInstance()->getGameSession()->setEventListener( NULL );
}

//---------------------------------------------------------------------
// ● イベント処理コールバック
//---------------------------------------------------------------------
int SceneNetRoom::HandleEvent( u32 event_, void* args_ )
{
    switch ( event_ )
    {
        ///////////////////////////////////////////// SceneGame に移動する
        case SYSEV_GOTO_SCENEGAME:
        {
            printf( "げーむいどう\n" );
            LGameScene::changeScene( NEW SceneGame() );
            break;
        }
    }
    return 0;
}

//=============================================================================
//								end of file
//=============================================================================