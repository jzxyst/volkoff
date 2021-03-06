//=============================================================================
//【 GameSceneManager 】
//=============================================================================

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
#include "GameScene.h"
//#include <Core/Manager.h>
//#include <Core/Graphics/Manager.h>
//#include <Core/Graphics/Interface.h>
//#include <Core/Scene/Manager.h>
#include "GameSceneManager.h"

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
namespace LNote
{
namespace Utility
{

//=============================================================================
// ■ GameSceneManager クラス
//=============================================================================

    //---------------------------------------------------------------------
    // ● コンストラクタ
    //---------------------------------------------------------------------
    GameSceneManager::GameSceneManager()
        : mScene            ( NULL )
        , mNextScene        ( NULL )
        , mChangeRequested  ( false )
        , mEndRequested     ( false )
        //, mFramework        ( NULL )
        , mShouldAddedScene ( NULL )
    {
    }

	//---------------------------------------------------------------------
    // ● デストラクタ
    //---------------------------------------------------------------------
    GameSceneManager::~GameSceneManager()
    {
        finalize();
    }

    //---------------------------------------------------------------------
    // ● 初期化
    //---------------------------------------------------------------------
    void GameSceneManager::initialize(/* const InitData& data_ */)
    {
        //mFramework = data_.Framework;

        //return LN_OK;
    }

    //---------------------------------------------------------------------
    // ● 終了処理
    //---------------------------------------------------------------------
    void GameSceneManager::finalize()
    {
        _releaseAllScene();
        _releaseAllAddedScene();

        RegistedGameSceneMap::iterator itr = mRegistedGameSceneMap.begin();
        RegistedGameSceneMap::iterator end = mRegistedGameSceneMap.end();
        for ( ; itr != end; ++itr )
        {
            if ( itr->second )
            {
                RefObjectHelper::release(itr->second);
            }
        }
        mRegistedGameSceneMap.clear();
    }


    //---------------------------------------------------------------------
    // ● ゲームシーンのインスタンスを登録する
    //---------------------------------------------------------------------
    bool GameSceneManager::registerSceneInstance( GameScene* scene_ )
    {
        if ( scene_->getSceneName() == NULL )
        {
            // 警告
            return false;
        }

        std::pair< RegistedGameSceneMap::iterator, bool > res;
        mRegistedGameSceneMap.insert( RegistedGameScenePair( scene_->getSceneName(), scene_ ) );
        return res.second;
    }

    //---------------------------------------------------------------------
    // ● 別のゲームシーンに変更する
    //---------------------------------------------------------------------
    void GameSceneManager::changeScene( GameScene* next_ )
    {
        EventMessage ev;
        ev.Command  = SMC_CHANGE;
        ev.Scene    = next_;
        mMessageQueue.push_back( ev );
    }

    //---------------------------------------------------------------------
    // ● 別のゲームシーンに変更する
    //---------------------------------------------------------------------
    void GameSceneManager::changeScene( const TCHAR* scene_name_ )
    {
        RegistedGameSceneMap::iterator itr = mRegistedGameSceneMap.find(scene_name_);
        if ( itr != mRegistedGameSceneMap.end() )
        {
            changeScene( itr->second );
            RefObjectHelper::retain(itr->second);
        }
    }

    //---------------------------------------------------------------------
    // ● 新しいゲームシーンをプッシュする
    //---------------------------------------------------------------------
    void GameSceneManager::pushScene( GameScene* scene_ )
    {
        EventMessage ev;
        ev.Command  = SMC_PUSH;
        ev.Scene    = scene_;
        mMessageQueue.push_back( ev );
    }

    //---------------------------------------------------------------------
    // ● ゲームシーンをプッシュする
    //---------------------------------------------------------------------
    void GameSceneManager::pushScene( const TCHAR* scene_name_ )
    {
        RegistedGameSceneMap::iterator itr = mRegistedGameSceneMap.find(scene_name_);
        if ( itr != mRegistedGameSceneMap.end() )
        {
            pushScene( itr->second );
            RefObjectHelper::retain(itr->second);
        }
    }

    //---------------------------------------------------------------------
    // ● 実行中のシーンを終了して親シーンへ戻る
    //---------------------------------------------------------------------
	void GameSceneManager::returnScene( const TCHAR* scene_name_ )
    {
        if ( scene_name_ )
        {
            // 名前の一致するシーンまでの階層数を調べる
            int  level = 1;
            bool found = false;
            GameScene* scene = mScene->_lngs.mParent;
            while ( scene )
            {
                if ( _tcscmp( scene->getSceneName(), scene_name_ ) != 0 )
                {
                    ++level;
                    found = true;
                }
                scene = scene->_lngs.mParent;
            }
            // 見つかったら調べた階層分 return
            if ( found )
            {
                EventMessage ev;
                ev.Command  = SMC_RETURN;
                ev.Scene    = NULL;
                for ( int i = 0; i < level; ++i )
                {
                    mMessageQueue.push_back( ev );
                }
            }
        }
        else
        {
            EventMessage ev;
            ev.Command  = SMC_RETURN;
            ev.Scene    = NULL;
            mMessageQueue.push_back( ev );
        }
    }

    //---------------------------------------------------------------------
    // ● 次のゲームシーンがあるか調べる
    //---------------------------------------------------------------------
	bool GameSceneManager::isNextScene() const
    {
        // 次のシーンがあり、さらにそれが現在のシーンとは違う場合は true を返す
		return ( mNextScene != NULL  &&  mNextScene != mScene );
    }

    //---------------------------------------------------------------------
    // ● フレーム更新
    //---------------------------------------------------------------------
	bool GameSceneManager::update()
    {
        while ( !mMessageQueue.empty() )
        {
            const EventMessage& ev = mMessageQueue.front();

            switch ( ev.Command )
            {
                /////////////// 直接遷移
                case SMC_CHANGE:
                {
                    // 現在の全てのシーンを解放 (onTerminate() 呼び出し)
                    _releaseAllScene();

                    mScene = ev.Scene;
                    if ( mScene )
                    {
                        mScene->_lngs.mParent = NULL;
                        mScene->onStart();
                    }
                    break;
                }
                /////////////// 呼び出し
                case SMC_PUSH:
                {
                    // アクティブなシーンの子として追加する
                    ev.Scene->_lngs.mParent = mScene;
                    mScene = ev.Scene;
                    mScene->onStart();
                    break;
                }
                /////////////// 呼び出し元へ戻る
                case SMC_RETURN:
                {
                    GameScene* old = mScene;
                    mScene = mScene->_lngs.mParent;
                    old->onTerminate();
                    RefObjectHelper::release(old);
                    break;
                }
            }

            mMessageQueue.pop_front();
        }
            
        // この時点でシーンがなければ終了
        if ( mScene == NULL )
        {
            return false;
        }

        mScene->onUpdate();
        return true;
    }

    //---------------------------------------------------------------------
    // ● 終了する
    //---------------------------------------------------------------------
	void GameSceneManager::end()
    {
        mNextScene = NULL;
		mEndRequested = true;
    }

    //---------------------------------------------------------------------
    // ● 実行中のシーンを階層構造も含めて release する
    //---------------------------------------------------------------------
    void GameSceneManager::_releaseAllScene()
    {
        GameScene* scene = mScene;
        GameScene* tmp;
        while ( scene )
        {
            scene->onTerminate();

            tmp = scene;
            scene = scene->_lngs.mParent;
            RefObjectHelper::release(tmp);
        }
        mScene = NULL;
    }

    //---------------------------------------------------------------------
    // ● 追加待ち子ツリーを全て release() する
    //---------------------------------------------------------------------
    void GameSceneManager::_releaseAllAddedScene()
    {
        GameScene* scene = mShouldAddedScene;
        GameScene* tmp;
        while ( scene )
        {
            tmp = scene;
            scene = scene->_lngs.mParent;
            RefObjectHelper::release(tmp);
        }
        mShouldAddedScene = NULL;  
    }


//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

} // namespace Utility
} // namespace LNote

//=============================================================================
//                              end of file
//=============================================================================