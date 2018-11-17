//=============================================================================
//【 GameScene 】
//=============================================================================

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
#include "GameScene.h"

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
namespace LNote
{
namespace Utility
{

//=============================================================================
// ■ GameScene クラス
//=============================================================================

    //---------------------------------------------------------------------
    // ● コンストラクタ
    //---------------------------------------------------------------------
    GameScene::GameScene( GameSceneManager* manager_ )
    {
        _lngs.mManager  = manager_;
        _lngs.mParent   = NULL;
        _lngs.mIsActive = false;
    }

    //---------------------------------------------------------------------
    // ● 親シーンがある場合は親の onUpdate() を呼ぶ
    //---------------------------------------------------------------------
    //void GameScene::updateParentScene()
    //{
    //    if ( _lngs.mParent )
    //    {
    //        _lngs.mParent->onUpdate();
    //    }
    //}

    //---------------------------------------------------------------------
    // ● シーンの変更
    //---------------------------------------------------------------------
    void GameScene::changeScene( const TCHAR* scene_name_ )
    {
        if ( isActiveScene() )
        {
            _lngs.mManager->changeScene( scene_name_ );
        }
    }
    void GameScene::changeScene( GameScene* next_scene_ )
    {
        if ( isActiveScene() )
        {
            _lngs.mManager->changeScene( next_scene_ );
        }
    }

    //---------------------------------------------------------------------
    // ● シーンの呼び出し
    //---------------------------------------------------------------------
    void GameScene::callScene( const TCHAR* scene_name_ )
    {
        if ( isActiveScene() )
        {
            _lngs.mManager->pushScene( scene_name_ );
        }
    }
    void GameScene::callScene( GameScene* next_scene_ )
    {
        if ( isActiveScene() )
        {
            _lngs.mManager->pushScene( next_scene_ );
        }
    }

    //---------------------------------------------------------------------
    // ● 呼び出し元のシーン (親シーン) へ戻る
    //---------------------------------------------------------------------
    void GameScene::returnScene( const TCHAR* parent_name_ )
    {
        if ( _lngs.mParent && _lngs.mManager->getActiveGameScene() == this )
        {
            _lngs.mManager->returnScene( parent_name_ );
        }
    }

    //---------------------------------------------------------------------
    // ● アクティブなシーンかを判定する
    //---------------------------------------------------------------------
    bool GameScene::isActiveScene() const
    {
        return ( _lngs.mManager->getActiveGameScene() == this );
    }

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

} // namespace Utility
} // namespace LNote

//=============================================================================
//                              end of file
//=============================================================================