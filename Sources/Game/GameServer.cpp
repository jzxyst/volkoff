//=============================================================================
//�y GameServer �z
//=============================================================================

#include "../Event/EventType.h"
#include "../Object/GameObjectManager.h"
#include "../Object/Weapon.h"
#include "GameManager.h"
#include "GameSession.h"
#include "GameServer.h"

//=============================================================================
// �� GameServer �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
GameServer::GameServer()
    : mMyGameSession    ( NULL )
    , mListen           ( NULL )
{
    
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
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
// �� ������
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
// �� �ڑ����Ď����� (1�t���[����1�x�Ăяo��)
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

        printf("�ڑ����Ă��܂���\n");

        tcp_stream->Send( "f�������ł���", strlen( "f�������ł���" ) + 1 );
    }
#endif
}

//---------------------------------------------------------------------
// �� �S�ẴN���C�A���g�ɃC�x���g�𑗐M����
//---------------------------------------------------------------------
void GameServer::sendEventToAllHost( u32 event_, void* data_, u32 size_ )
{
    // �������g�ɂ͂����ɑ��M
    mMyGameSession->HandleEvent( event_, data_ );

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

    // �ڑ��ς݂̂��̂ɑS�đ��M
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
// �� �w�肵���z�X�g�ȊO�̑S�Ẵz�X�g�� GameSession �ɃC�x���g�𑗐M����
//---------------------------------------------------------------------
void GameServer::sendEventToExclusionHost( u32 exc_host_id_, u32 event_, void* data_, u32 size_ )
{
    if ( exc_host_id_ != 0 )
    {
        // �������g�ɂ͂����ɑ��M
        mMyGameSession->HandleEvent( event_, data_ );
    }

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

    // �w��ȊO�̐ڑ��ς݂̂��̂ɑS�đ��M
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
// �� �C�x���g����
//---------------------------------------------------------------------
int GameServer::HandleEvent( u32 event_, void* args_ )
{
    switch ( event_ )
    {
        ///////////////////////////////////////////// SceneGame �Ɉړ�����
        case SYSEV_GOTO_SCENEGAME:
        {
            sendEventToAllHost( SYSEV_GOTO_SCENEGAME, NULL, 0 );
            break;
        }

        ///////////////////////////////////////////// �A�C�e��(����܂�)���E�������Ƃ��̗v�� (�e�z�X�g����T�[�o�ɑ����Ă���)
        case SYSEV_ITEM_REQUEST:
        {
			ItemRequestArgs* args = static_cast< ItemRequestArgs* >(args_);
			GameObjectManager* manager = GameObjectManager::getInstance();

			// �A�C�e���I�u�W�F�N�g��T��
			GameObject* obj = manager->findObject(args->ItemObjHandle);

			if (obj)
			{
				// ����̏ꍇ
				if (obj->getObjType() == OBJ_WEAPON)
				{
					// �擾����L�����N�^�[�ɑ΂��ăI�u�W�F�N�g�̎�����f�[�^�𑗐M����
					WeaponData data = (static_cast< Weapon* >(obj))->getWeaponData();
					manager->postEvent(args->GetterHandle, EV_GET_WEAPON, &data, sizeof(WeaponData));

					u32 handle = obj->getHandle();

					// ����I�u�W�F�N�g���폜����
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