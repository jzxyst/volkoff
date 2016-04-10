//=============================================================================
//�y GameManager �z
//=============================================================================

#include "stdafx.h"
#include "../Object/Player.h"
#include "GameManager.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Map/MapManager.h"

//=============================================================================
// �� GameManager �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �C���X�^���X�̎擾
//---------------------------------------------------------------------
GameManager* GameManager::getInstance()
{
    static GameManager instance;
    return &instance;
}

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
GameManager::GameManager()
    : mGameServer       ( NULL )
    , mGameSession      ( NULL )
    , mEffectManager    ( NULL )
    , mFloorNum         ( 0 )
    , mScore            ( 0 )
	, mRank             ( 1 )
	, mOpenflag         ( 0 )
	//, mTime             ( 0 )
	, mGameTime			(3660)	// ��
    , mLastBoss         ( NULL )
{
    
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
GameManager::~GameManager()
{
    finalize();
}

//---------------------------------------------------------------------
// �� �e�Ƃ��ď���������
//---------------------------------------------------------------------
void GameManager::initializeParent()
{
    //SAFE_DELETE( mGameSession );

    mGameServer = NEW GameServer();
    mGameSession = NEW GameSession();

    mGameServer->initialize( mGameSession );
    mGameSession->initialize( mGameServer );

	//mTime = 0;
    mLastBoss = NULL;
    
    mEffectManager = NEW EffectManager();

	GameObjectManager::getInstance()->Initialize();
    mPlayer = NEW Player();
    mPlayer->Initialize();
    mPlayer->setPosition( LVector3( 80.0f, 50.0f, -1.0f ) );    // ���̏����ʒu

    GameFrontendManager::getInstance()->initialize( mPlayer );
	return;
    
}

//---------------------------------------------------------------------
// �� �q�Ƃ��ď���������
//---------------------------------------------------------------------
bool GameManager::initializeChild( const char* parent_ip_addr_ )
{
    //SAFE_DELETE( mGameSession );

    mGameSession = NEW GameSession();
    mGameSession->initializeChild( parent_ip_addr_ );

	//mTime = 0;
    mLastBoss = NULL;

    GameObjectManager::getInstance()->Initialize();
    mEffectManager = NEW EffectManager();
    mPlayer = NEW Player();
    mPlayer->Initialize();
    //mPlayer->setPosition( LVector3( 80.0f, 50.0f, -1.0f ) );
  
    GameFrontendManager::getInstance()->initialize( mPlayer );
    return true;
}

//---------------------------------------------------------------------
// �� �Q�[���̏I������
//---------------------------------------------------------------------
void GameManager::finalize()
{
    //SAFE_DELETE( mPlayer );   // GameObjectManager ��������Ă����̂ŕK�v�Ȃ�
    SAFE_DELETE( mEffectManager );

    GameObjectManager::getInstance()->Release();
    
	MapManager::getInstance()->finalize();
    GameFrontendManager::getInstance()->finalize();

    SAFE_DELETE( mGameServer );
    SAFE_DELETE( mGameSession );
    
    mLastBoss = NULL;
}

//---------------------------------------------------------------------
// �� �R���e�B�j���[�ɔ����ăo�b�N�A�b�v�����
//---------------------------------------------------------------------
void GameManager::commit()
{
    mPlayer->commit();

    mBackup.Score = mScore;
	//mBackup.Time= mTime;
}

//---------------------------------------------------------------------
// �� �R���e�B�j���[���̃��Z�b�g
//---------------------------------------------------------------------
void GameManager::reset()
{
    printf( "�� reset\n" );

    //GameObjectManager::getInstance()->Release();
    setOpenflag(0);
    setKeyflag(0);

    GameObjectManager::getInstance()->deleteStageObject();
    
    mPlayer->reset();

    //mScore = mBackup.Score;
    mScore = 0;
	//mTime = 0;
    mLastBoss = NULL;


    MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());

    
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void GameManager::update()
{
    if ( mGameServer )
    {
        mGameServer->polling();
    }

    if ( mGameSession )
    {
        mGameSession->polling();
    }

//++mTime;
	++mGameTime;
    mEffectManager->update();
}

//---------------------------------------------------------------------
// �� �C�x���g����
//---------------------------------------------------------------------
int GameManager::HandleEvent( u32 event_, void *args_ )
{

    
         
    return 0;
}

//=============================================================================
//								End of File
//=============================================================================
