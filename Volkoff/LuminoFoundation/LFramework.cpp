//=============================================================================
//【 LFramework 】
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
// ■ LFramework クラス
//=============================================================================


    // フレーム更新回数の取得
    //u32 LFramework::getFrameCount() const
    //{
    //    return _impl->getGameTime().getTotalFrameCount();
    //}


    // フレーム更新
	bool LFramework::update()
	{
        if ( gGameSceneManager->getActiveGameScene() != NULL ) { return true; }
		return Engine::UpdateFrame();
	}

    //// 登録されているゲームシーンを指定して実行開始
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

    // ゲームシーンを与えて実行開始
    void LFramework::run( LGameScene* scene_ )
    {
        gGameSceneManager->changeScene( scene_ );

        do
        {
            gGameSceneManager->update();

        } while (Engine::UpdateFrame());
    } 

    // ゲームシーンを実行中かどうかを判定する
    //bool LFramework::isRunning() const
    //{
    //    return ( gGameSceneManager->getActiveGameScene() != NULL );
    //}

    //// ライブラリに終了を要求する
    //void LFramework::exit()
    //{
    //    _impl->exit();
    //}

    //// ゲームシーンのインスタンスを登録する
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