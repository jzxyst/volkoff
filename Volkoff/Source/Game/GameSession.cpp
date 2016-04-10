//=============================================================================
//�y GameSession �z
//=============================================================================

#include "stdafx.h"
#if MIGRATION
#else
#include "../Object/GameObjectManager.h"
#endif
#include "GameServer.h"
#include "GameSession.h"

//=============================================================================
// �� GameSession �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
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
// �� �f�X�g���N�^
//---------------------------------------------------------------------
GameSession::~GameSession()
{
    SAFE_DELETE( mServerStream );
}

//---------------------------------------------------------------------
// �� ������
//---------------------------------------------------------------------
void GameSession::initialize( GameServer* server_ )
{
    mGameServer = server_;
    mHostInfo.IsParent = ( server_ != NULL );
}

//---------------------------------------------------------------------
// �� �q�Ƃ��ď����� (GameManager ����Ă΂��)
//---------------------------------------------------------------------
void GameSession::initializeChild( const char* parent_ip_addr_ )
{
    mHostInfo.IsParent = false;

#if MIGRATION
#else
    mServerStream = NEW TcpStream();
    mServerStream->Initialize();
    mServerStream->Connect( "127.0.0.1", GAMEPORT );

    printf("�ڑ����܂���\n");
#endif
}

//---------------------------------------------------------------------
// �� �T�[�o�Ƀf�[�^�𑗐M����
//---------------------------------------------------------------------
void GameSession::sendToServer( u32 event_, void* data_, u32 size_ )
{
    // �������e�̏ꍇ
    if ( mHostInfo.IsParent )
    {
        // �����ɏ���
        mGameServer->HandleEvent( event_, data_ );
    }
    // �q�̏ꍇ
    else
    {
        // �w�b�_�����
        GameSystemEventHeader header;
        header.Type         = event_;
        header.ArgSize      = size_;

        // ��x mTempBuffer �ɑS�Ċi�[
        memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
        if ( data_ )
        {
            memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );
        }

#if MIGRATION
#else
        // �T�[�o�ɑ���
        mServerStream->Send( mTempBuffer, sizeof( EventHeader ) + size_ );
#endif
    }
}

//---------------------------------------------------------------------
// �� �I�u�W�F�N�g�쐬���b�Z�[�W (SYSEV_CREATEED_OBJECT) �𑗐M����
//---------------------------------------------------------------------
void GameSession::sendCreatedObjectEvent( u32 obj_type_, void* data_, u32 size_ )
{
    char temp[ 1024 ];

    u32 all_size = sizeof( CreatedObjectArgs ) + size_;

    CreatedObjectArgs* data = reinterpret_cast< CreatedObjectArgs* >( temp );

    //printf("�z�X�gID�󂯎�鏈�����ł��ĂȂ�\n");
    data->HostID = 0;
    data->ObjectType = obj_type_;

    memcpy( &data[ 1 ], data_, size_ );

    // �T�[�o�ɑ��M�B�T�[�o�� HandleEvent �ŁA�����ȊO�̃z�X�g�ɑ��M�����B
    // �u�����ȊO�v�Ƃ�������� HandleEvent ���ōs���B
    sendToServer( SYSEV_CREATEED_OBJECT, data, all_size );






    // �������T�[�o�̏ꍇ
    //if ( mHostInfo.IsParent )
    //{
    //    // ������ GameSession �ɑ��M

    //    //sendEventToExclusionHost

    //}
    //// �������N���C�A���g�̏ꍇ
    //else
    //{
    //    LN_ASSERT( 0, "sendCreatedObjectEvent ���Ή�" );
    //}
}

//---------------------------------------------------------------------
// �� �����ҋ@
//---------------------------------------------------------------------
void GameSession::waitSync()
{
}

//---------------------------------------------------------------------
// �� �C�x���g�Ď�
//---------------------------------------------------------------------
void GameSession::polling()
{

#if MIGRATION
#else

    // �q�̏ꍇ�̓T�[�o���瑗���Ă��Ă���C�x���g���`�F�b�N����
    if ( mServerStream )
    {
        //mServerStream->getSessionState()
        if ( !mServerStream->getRecvList().empty() )
	    {
            //printf( "data:%s\n", mServerStream->getRecvList().front()->getData() );
            //printf( "size:%d\n", mServerStream->getRecvList().front()->getSize() );

            GameSystemEventHeader* header = reinterpret_cast< GameSystemEventHeader* >( mServerStream->getRecvList().front()->getData() );

            // �C�x���g����
            HandleEvent( header->Type, &header[ 1 ] );

		    mServerStream->getRecvList().pop_front();
	    }
    }
#endif
}

//---------------------------------------------------------------------
// �� �C�x���g����
//---------------------------------------------------------------------
int GameSession::HandleEvent( u32 event_, void* args_ )
{
    if ( mEventListener )
    {
        mEventListener->HandleEvent( event_, args_ );
    }

    switch ( event_ )
    {
        

        ///////////////////////////////////////////// �I�u�W�F�N�g���폜����
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