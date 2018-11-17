//=============================================================================
//�y SceneNetRoom �z
//=============================================================================

#include "../Game/GameManager.h"
#include "SceneGame.h"
#include "SceneConnection.h"
#include "SceneNetRoom.h"

//=============================================================================
// �� SceneNetRoom �N���X
//=============================================================================


//---------------------------------------------------------------------
// �� �J�n����
//---------------------------------------------------------------------
void SceneNetRoom::onStart()
{
    printf( "-------------------------------------------------\n" );
    printf( " �� ���[�����\n" );
    printf( "-------------------------------------------------\n" );

    if ( GameManager::getInstance()->getGameSession()->isParent() )
    {
        printf( "Z > �Q�[����ʂ�\n" );
    }
    else
    {
        printf( "�J�n�҂�...\n" );
    }

    GameManager::getInstance()->getGameSession()->setEventListener( this );
}

//---------------------------------------------------------------------
// �� �t���[���X�V
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
// �� �I������
//---------------------------------------------------------------------
void SceneNetRoom::onTerminate()
{
    GameManager::getInstance()->getGameSession()->setEventListener( NULL );
}

//---------------------------------------------------------------------
// �� �C�x���g�����R�[���o�b�N
//---------------------------------------------------------------------
int SceneNetRoom::HandleEvent( u32 event_, void* args_ )
{
    switch ( event_ )
    {
        ///////////////////////////////////////////// SceneGame �Ɉړ�����
        case SYSEV_GOTO_SCENEGAME:
        {
            printf( "���[�ނ��ǂ�\n" );
            LGameScene::changeScene( NEW SceneGame() );
            break;
        }
    }
    return 0;
}

//=============================================================================
//								end of file
//=============================================================================