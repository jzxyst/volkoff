//=============================================================================
//�y LFramework �z
//=============================================================================

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
#include "stdafx.h"
#include "GameSceneManager.h"
#include "Accessor.h"
#include "LFramework.h"

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
namespace LNote
{

//=============================================================================
// �� LFramework �N���X
//=============================================================================


    // �t���[���X�V�񐔂̎擾
    //u32 LFramework::getFrameCount() const
    //{
    //    return _impl->getGameTime().getTotalFrameCount();
    //}


    // �t���[���X�V
	bool LFramework::update()
	{
        if ( gGameSceneManager->getActiveGameScene() != NULL ) { return true; }
		return Engine::UpdateFrame();
	}

    //// �o�^����Ă���Q�[���V�[�����w�肵�Ď��s�J�n
    //void LFramework::run( const lnChar* scene_name_ )
    //{
    //    gGameSceneManager->changeScene( scene_name_ );

    //    do
    //    {
    //        gGameSceneManager->update();
    //        //_preUpdate();

    //        //mGameManager->update();

    //        //if ( !_postUpdate() )
    //        //{
    //        //    return;
    //        //}
    //    } while ( _impl->update() );

    //    /*
    //    _impl->run( "Scene_Test" );
    //    */
    //}

    // �Q�[���V�[����^���Ď��s�J�n
    void LFramework::run( LGameScene* scene_ )
    {
        gGameSceneManager->changeScene( scene_ );

        do
        {
            gGameSceneManager->update();

        } while (Engine::UpdateFrame());
    } 

    // �Q�[���V�[�������s�����ǂ����𔻒肷��
    //bool LFramework::isRunning() const
    //{
    //    return ( gGameSceneManager->getActiveGameScene() != NULL );
    //}

    //// ���C�u�����ɏI����v������
    //void LFramework::exit()
    //{
    //    _impl->exit();
    //}

    //// �Q�[���V�[���̃C���X�^���X��o�^����
    //void LFramework::registerSceneInstance( LGameScene* scene_ )
    //{
    //    gGameSceneManager->registerSceneInstance( scene_ );
    //}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

} // namespace LNote

//=============================================================================
//								end of file
//=============================================================================