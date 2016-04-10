//=============================================================================
/*! 
    @addtogroup 
    @file       Main.cpp
    @brief      プログラムメイン処理
    
    プログラムメイン処理
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/05
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/05 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================

/*! @par include */
//インクルードファイルは、不必要になり次第逐次消すこと
#include "stdafx.h"
#include <crtdbg.h>
#include <time.h>
#if MIGRATION
#include "Scene/SceneTitle.h"
#include "Scene/SceneGame.h"
#include "Game/GameManager.h"
#else
#include <Core/System/Win32/Win32WindowManager.h>
#include "Object/GameObject.h"
#include "Scene/SceneTitle.h"
#include "Scene/SceneGame.h"
#include "Scene/SceneConnection.h"
#include "Scene/SceneNetRoom.h"
#include "Network/WinSock/SocketManager.h"

#endif
#include "Object/CharacterScriptInterface.h"
#include "Game/GameManager.h"
#include "Game/RankingManager.h"
#include "Scene/SceneResult.h"
#include "Scene/SceneStartup.h"

//---------------------------------------------------------------------
// 設定関数
//---------------------------------------------------------------------
void lnConfig(EngineSettings* settings)
{
	//Base::Error::setProcessMode(LN_ERROR_PROC_IMMABORT);
	//
    //config.setEnableConsole( true );
    //config.Framework.setProcessMode( LN_SYSPROCMODE_ALWAYS );

	settings->GraphicsAPI = GraphicsAPI::DirectX9;
	settings->RenderingType = RenderingType::Immediate;
	settings->fpuPreserveEnabled = true;
	settings->mainWindowTitle = _T("Last Valfirle Ver1.0.1");
	settings->mainWindowSize = Size(640, 480);
	settings->backBufferSize = Size(640, 480);
	settings->directMusicMode = DirectMusicMode::ThreadWait;
	settings->soundCacheCapacity.objectCount = 32;


#if MIGRATION
#else
	config._c->EnableShowFPS = true;
#endif
}

#if MIGRATION
#else
// ウィンドウメッセージのリスナークラス
class RelayWndProc
	: public LNote::Core::System::IWin32MessageListener
	//: public LNote::Core::System::IEventListener
{
	
	//virtual bool onEvent( const LNote::Core::System::Event& event_ )
	//{ 
	//	if ( event_.Type == LNEV_KEY_CHAR )
	//	{
	//		const Core::System::KeyEvent& key_args = (const Core::System::KeyEvent&)event_;
	//	}
	//	return false;
	//}
	

    virtual LRESULT WndProc( HWND hwnd_, UINT msg_, WPARAM wparam_, LPARAM lparam_, bool* handled_ )
    {
        /*
        

        if ( msg_ == WM_DESTROY )
        {
            printf( "WM_DESTROY\n" );
        }
        if ( msg_ == WM_CLOSE )
        {
            printf( "WM_CLOSE\n" );
        }
        if ( msg_ == WM_SOCKET )
        {
            printf( "WM_SOCKET\n" );
        }
        */

        if ( msg_ != WM_DESTROY )
        {
            SocketManager::getInstance()->Proc(hwnd_,msg_,wparam_,lparam_);
        }

		if ( msg_ == WM_CHAR )
		{
			// 文字
			if ( 0x20 <= wparam_ && wparam_ <= 0x7E )
			{
				char code = wparam_;
				if ( ::GetKeyState( VK_SHIFT ) < 0 )
				{
					code = toupper( code );
				}
				if (gSceneResult)
				{
					gSceneResult->onkeyEvent( code );
				}
			}
			// Enter  BackSpace
			if (( wparam_ == VK_RETURN ) || ( wparam_ == VK_BACK ))
			{
				if (gSceneResult)
				{
					gSceneResult->onkeyEvent( wparam_ );
				}
			}
		}

        return 0;
    }
};

static RelayWndProc gRelayWndProc;

#endif

//---------------------------------------------------------------------
// エントリーポイント
//---------------------------------------------------------------------
int lnMain()
{
	// キーコンフィグ
	Input::GetController(0)->AddBinding(InputBinding::Create(LN_BUTTON_C, Key::C));
	Input::GetController(0)->AddBinding(InputBinding::Create(LN_BUTTON_X, Key::A));

	Camera::GetDefault3DCamera()->SetFarClip(10000);

#if MIGRATION
	//---------------------------------------------------------
	// 初期化処理
	//Debug
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	::SetConsoleTitle(TEXT("Volkoff Debug System[Ver.1.0.1]"));
	::printf("Volkoff Debug System[Ver.0.9.0]\n");
	::printf("Copyright (c) 2011 Valfirle Developer. All Rights Reserved.\n\n");
	//::SetWindowText(Engine::Framework::getInstance()->getSystemManager()->getMainWindow()->getWindowHandle(),TEXT("Last Valfirle Ver1.0.1"));


	CharacterScriptInterface::getInstance();
#else
//    LNote::Base::Error::setProcessMode( LN_ERROR_PROC_IMMABORT );

	Core::Scene::SceneGraph* scene = static_cast< Core::Scene::SceneGraph* >(
        LNote::gFramework->getSceneManager()->getDefaultSceneGraph() );

	scene->getDefaultNode( LN_DEFAULT_SCENENODE_3D )->getSpriteRenderer()->setSortMode(
		LN_SPRITESORT_NONE, false );

	//scene->getDefaultNode( LN_DEFAULT_SCENENODE_3D )->getSpriteRenderer()->setCullingMode( LN_CULL_DOUBLE );

	//LRenderState state;
	//state.Culling = LN_CULL_DOUBLE;
	//scene->setNodeDefaultRenderState( state );

#if 0
    {
        Engine::Input::JoypadConfig joy_cfg;
        joy_cfg.setButton( LN_BUTTON_A, 4 );
        joy_cfg.setButton( LN_BUTTON_B, 3 );
        joy_cfg.setButton( LN_BUTTON_C, 1 );//5
        joy_cfg.setButton( LN_BUTTON_X, 2 );


        LKeyConfigData data = Input.getConfigData();
        data.setJoypadConfig( joy_cfg );
        Input.setConfigData( data );
    }
#endif


    //---------------------------------------------------------
	// 初期化処理
	//Debug
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	::SetConsoleTitle(TEXT("Volkoff Debug System[Ver.1.0.1]"));
	::printf("Volkoff Debug System[Ver.0.9.0]\n");
	::printf("Copyright (c) 2011 Valfirle Developer. All Rights Reserved.\n\n");
	//::SetWindowText(Engine::Framework::getInstance()->getSystemManager()->getMainWindow()->getWindowHandle(),TEXT("Last Valfirle Ver1.0.1"));

	::srand(static_cast<unsigned int>(::time(NULL)));

	LNote::Core::System::Win32WindowManager* window_manager =
		(LNote::Core::System::Win32WindowManager*)Framework.getInterface()->getSystemManager()->getWindowManager();

    // ネットワーク
	HWND hwnd = Core::System::Environment::getWindowHandle( Framework.getInterface()->getSystemManager()->getMainWindow() );
	SocketManager::getInstance()->Initialize( hwnd ); 

	window_manager->attachWin32MessageListener( &gRelayWndProc, 0 );

    // 背景色
    Graphics.setBGColor( 0.0f, 0.0f, 0.0f );
	Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setFarClip( 5000.f );

    // カメラをマウスで操作可能
	//Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setType( LN_CAMERA_MOUSE_MOVE );
	//Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setPosition(LVector3(0.0f,0.0f,-500.0f));
    
    CharacterScriptInterface::getInstance();

	RankingManager::getInstance()->Initialize();


    
    
    


    //LTexture t = Texture2D::Create("test");

    // 開始時、GUI は非アクティブ
    //Framework->getInterface()->getGUIManager()->setActive( false );

#endif

	//---------------------------------------------------------
	// ゲームループ開始

#if 0  // デバッグのため、すぐにゲーム開始する場合は 1

    GameManager::getInstance()->initializeParent();
	LFramework::run( NEW SceneGame() );

#else

	//::MessageBoxA(0, "", "", 0);

	LFramework::run( LN_NEW SceneStartup() );
	//Framework.run( NEW SceneResult( 1 ) );

#endif


    //---------------------------------------------------------
	// 終了処理
#if MIGRATION
#else

	RankingManager::getInstance()->Release();
	GameManager::getInstance()->finalize();

	window_manager->detachWin32MessageListener( &gRelayWndProc );

#endif

    return 0;
}

//---------------------------------------------------------------------
// ネットワーク実装について
/*

    ◆ 接続の流れ

        ― 共通 ―

        ・タイトル画面で、「ネットワーク」項目を選択
        ・接続画面で、「部屋を作る」「部屋をに入る」いずれかを選択


        ― 親 ―

        ・接続画面開始時、GameServer クラスを作る。(GameManager?)
        ・子からの接続があった場合は、プレイヤー番号を決めて(連番)、子の情報をキューに入れる。
          番号を決めた後はすぐに
          キューの情報は、メインループで新しい接続を判定して画面に表示するために使う。

        ・受付を締め切ってゲームに進むかを選択
        　


        ― 子 ―

        ・自分の名前と親の IP アドレスを入力して、親に接続


    ◆ 

*/


/*
// ゲーム中、ずっと存在するシングルトン。親ホスト内でのみ存在する
class GameServer
    : public ServerEventListener
{
public:
    
    // すべてのクライアントに、ゲームシーンに移動するメッセージを送信する (何かと一緒にできるかも)
    void send_GotoGameScene()
    {
    }
    
    
    
private:
    
    std::vector< IClientOfServer* >     mClients;
};



    ◆ 基本移動

        -------------------------------------------------------
        ● ゲーム開始 (オブジェクト生成ともちょっとかぶる)

            SceneGame::onStart()


            ０．[全] GameManager::initialize()
                        以下の一連の処理が終わるまで制御を返さない。
                        同期等もすべてこの中で行う。


            １．[P1] GameServer::changeMap()
                        //マップを構築 (まだ GameObject は作らない)
                        mMapManager->makeRandomMap();
                        
                        //クライアントの GameClient にマップデータを送信する
                        PacketMapData data;
                        memcpy( data.MapData, mMapManager->getMapData(), sizeof());
                        foreach ( crient in mClients )
                        {
                            crient->send( data, sizeof( MapData ) );
                        }

                        // マップデータから必要なオブジェクトを作成する
                        mMapManager->createGameObject();

            ２．[P1] MapManager::createGameObject()
                        マップをすべて走査して、GameObject を作成する。
                        なお、ここで作成される GameObject はすべて親ホスト(サーバ)で作成されたものとして扱う。
                        

                 GameServer と GameClient は GameManager に統合でいいかも。

            -- 生成 --

            ３．[P1] GameManager::createGameObjectEntity( u32 obj_key_, void* args_ )
                        あらかじめ登録しておいた obj_key_ に対応する create 関数を呼び出す。
                        WoodBox::create( args_, true ) みたいに、is_entity_ は true で作成。
                        生成できたら、自分以外のすべてのホストに EV_CREATE_GAME_OBJECT を送信する。

                        EV_CREATE_GAME_OBJECT
                            obj_key_
                            args_
                            割り当てられたオブジェクトハンドル


            ４．[P2] GameManager::HandleEvent()
                        EV_CREATE_GAME_OBJECT の処理。
                        引数から取り出したオブジェクトの種類に対応する create 関数で、
                        オブジェクトを作成する。
                        WoodBox::create( args_, false ) みたいに、is_entity_ は false で作成。

            -- 生成 ここまで --


            ５．[全] GameManager::createPlayer(引数なし) 戻り値無し
                        各ホストで、自分が操作する Player を作成する。作成できる Player は各ホスト 1 つまで。
                        作成は createGameObjectEntity() で行い、戻り値は mPlayer に保持する。
                        この Player は GameManager::getPlayer() で取得可能。


                        プレイヤーの生成前に一度同期取った方がいいかも？
                        同期が簡単に取れるシステムがほしい。
                        メニュー画面とかも含めて。

                        プレイヤーは、ステージごとに作り直すとかは無し。
                        ゲーム中は常に存在する。

            ６．[全] GameManager::
                        すべてのホストが準備完了をサーバに伝える。
                        サーバは、準備ができたらゲーム開始を伝える。


        -------------------------------------------------------
        ● GameObject の削除

            例 WoodBox (WoodBoxCommon ではない)

            １．update() HandleEvent()
                    時間経過や被ダメージ判定でオブジェクトを削除する場合、
                    GameObjectManager->deleteObject( this ); で削除する。
                    this が、他の Object によって保持されている場合は考えない。
                    そのようなオブジェクトが必要な場合、this を持っている側が
                    参照を外した後に deleteObject() を呼ぶ。

            ２．[P1] GameObjectManager->deleteObject( GameObject* obj_ )
                    とりあえず、自分を含むすべてのホストに送信する。
                    EventManager->sendToAllHost( EV_DELETE_OBJECT, args_(obj_->Handle) );
                    自分へ送る分は一度キューにためられるので、実際に削除されるのは
                    ちょっとだけ後。


            ３．[全] GameObjectManager::HandleEvent()
                    EV_DELETE_OBJECT の処理。
                    単純にマップを検索して、キーに一致するオブジェクトをすべて delete する。
                    ギミックなどで、「●●が削除された場合」を検出したい場合は、
                    P1 から「ハンドル x のオブジェクトが削除されようとしている」イベントをすべてに送信する。

                    





            ※削除イベントを発行するのは、常に Entity 側。
              他のホストがすることは、ダメージをあたえるとかだけ。

        -------------------------------------------------------
        ● プレイヤーの死亡

            いずれかの Player の HP が 0 になった場合、
            各ホストから EV_DEAD みたいなイベントを
            自分以外のすべてのホストに送信する。
            
            複数の Player が同時に死亡した場合、
            どの Player が原因でゲームオーバーになったのかわからなくなる。
            今のままの仕様でいくなら問題ないけど、
            厳密に判定するなら一度サーバに死亡イベントを送ってから、
            改めて全ホストに EV_GAMEORVER を送る。


        -------------------------------------------------------
        ● ゲームオーバー

            各ホストは EV_GAMEORVER を受け取った場合、
            問答無用でゲームオーバーの情報を表示する。

            プレイヤーが二人以上同時に死亡した場合、
            EV_GAMEORVER は複数回来る可能性があるため、
            その辺の対応が必要。
            (既にゲームオーバーであれば EV_GAMEORVER はスルーする等)

            １．[全] GameManager::HandleEvent()
                        EV_GAMEORVER の処理。
                        現在のゲームシーン (SceneGame) の startGameOver() を呼び出す。
                        Framework->getActiveScene()->startGameOver()。

            or１．[全] SceneGame::HandleEvent()
                        EV_GAMEORVER の処理。
                        startGameOver() を呼ぶ。

            ２．[全] SceneGame::startGameOver()
                        SceneGameover に移動。
                        現在の SceneGame をスタックしていきたいところ。

            ３．[全] SceneGameover::update()
                        親がコンテニュー or ゲーム終了を選択する。
                        子はとりあえずそれをみてるだけ。

                        コンテニューが選択された場合は、
                        ステージの開始位置から再開する。





            ▼ コンテニューのために覚えておく情報

                サーバ
                    ・ランダムマップの状態 (または乱数シード)

                全ホスト
                    ・ステージ開始時のステータス (シリアライズ？)

        -------------------------------------------------------
        ● ゲームクリア

            ボスに最後の一撃を入れたところまではゲームとして同期をとっていく。
            ボス撃破～リザルト画面で決定ボタンを押すまでは各ホストで進行。
            ボス撃破時にサーバが成績とかのデータを作成して各ホストに送信し、
            リザルト画面で決定ボタンが押されるまで待つ。

            終了したら接続待ち画面へ。部屋を作って、みんな参加してる状態。
            参加も受け付ける。


            

        -------------------------------------------------------
        ● 敵の攻撃の当たり判定は各ホストで行いたい
            
        -------------------------------------------------------
        ● ダメージを与えた時などのスコアの加算

            完全な同期は不可能。
            敵の HP が 1 の状態で P1 と P2 が同時に攻撃したら、
            どっちに点が入るかを正しく判定するのはちょっと手間。
            それに、「当てゲー」ってことなら、この場合は両方に
            スコアを入れてあげるがベストかと。

            倒した時にだけ入る得点はちょっと別かなと思うけど。 

        -------------------------------------------------------
        ● アイテムの取得

            一度サーバに要求して、返答が来るまで
            しゃがみ状態を続ける。
            タイムアウトが必要かも。

            １．[2P] Player::updateSelf();
                        アイテムを拾うべきフレームになったので、
                        「アイテムを取得したい」というメッセージを送る
                        EV_GET_ITEM_REQUEST
                            取得要求した GameObject のハンドル
                            アイテムのオブジェクトハンドル (ちゃんと送信側でアイテムかどうかチェックしておく)

            ２．[1P] GameManager::HandleEvent(  )        //onReceive( void*  )
                        






    
        -------------------------------------------------------
        ● 左右移動開始
            
            １．[P1] 右ボタンを押す
            ２．[P1] Controller クラスから、自分のホストに関連付けられている Player に「右押した」を送信する
                    サーバは介さない。ホスト内の EventManager から直に Player に送信する。
                    EventManager->sendToSelf( mPlayer, EV_INPUT );
                    
            ３．[P1] EventManager::SendToSelf( GameObject* recver_obj_, u32 event_, void* args_ )
                        recver_obj_ の持つハンドルをキーにして、EventManager が管理している
                        Listener オブジェクトを検索。
                        見つかった Listener に event_ をすぐに送信する。

            ４．[P1] Player::HandleEvent()
                        EV_INPUT の処理。
                        自分のホスト内で、現在の状態を元に移動開始できるかどうかを判定する。
                        (敵の攻撃に当たってのけぞり中ではない等)
                        移動開始できる場合、EV_ACTION_MOVE を自分含むすべてのホストに送信する。

            ５．[P1] EventManager::sendToAllHost( GameObject* recver_obj_, u32 event_, void* args_ )
                        自分への送信は SendToSelf() で即送信。
                        他ホストへの送信は、送信用のキューに詰める。
                        次の EventManager::process() で、他ホストに送信する。

            ６．[P1 P2] Player::HandleEvent()
                        EV_ACTION_MOVE の処理。
                        引数で受け取った移動速度(今回は移動速度固定になるかも)によって
                        mVelocity に速度を設定し「走り状態」になる。

            ７．[P1 P2] Player::update()
                        if (走り状態の場合)
                        {
                            アニメーション
                            座標更新
                        }

            ▼ 必要なもの

                ・EV_INPUT
                    ボタン番号
                    押し下状態

                ・EV_ACTION_START_RUN
                    方向

                ・EventManager::sendToSelf( GameObject* recver_obj_, u32 event_, void* args_, u32 size_ );
                ・EventManager::sendToAllHost( GameObject* recver_obj_, u32 event_, void* args_, u32 size_ );

                ・Player Enemy::isIdle()
                    走り ジャンプ しゃがみ ガード 攻撃等の各基本アクションが開始できるかを判定する

                ※ isIdle() で動作開始可能判定をするのは INPUT 系イベントの中のみ。
                   ACTION 系イベントの中で行うと、各ホスト内で判定が行われるため、動作の不整合が発生する。
                   自分以外のキャラの動きが、ジャンプ中で空中にいるのに走りアニメーションになるとか
                   不自然なことはあるけど、これは今は目をつむっておく。


        ● 左右移動終了

            手順は 「左右移動開始」とほぼ同じ。
            INPUT で、現在「走り状態」であれば
            すべてのホストに EV_ACTION_STOP_RUN を送る。

            受け取った側では速度を 0 にする。あるいは、「待機状態」にする。
            


        ● 敵から攻撃を受ける

            ※すべての敵の動作を管理するのはサーバ

                        
                    
                        
                        
        
    
        
        
        
        
        

    ・攻撃を当てました
        クライアント    → サーバ
        サーバ          → サーバ


    -------------------------------------------------------
    ◆ 各 GameObject の ::create( void* args_, bool is_entity_ )

        実装例

        class WoodBoxCommon : public GameObject
        {
            struct CreateArgs
            {
                LVector3    Pos;
            };

            // コンストラクタ
            WoodBoxCommon( CreateArgs* args_ )
            {
                
            }

            
        };

        class WoodBox : public WoodBoxCommon
        {
            // args_ は、CreateArgs へのポインタ
            static void* create( void* args_, bool is_entity_ = true )
            {
                if ( is_entity_ )
                {
                    return NEW WoodBox( (CreateArgs*)args_ );
                }
                else
                {
                    return NEW WoodBoxCommon( (CreateArgs*)args_ );
                }
            }

            // コンストラクタ
            WoodBox( CreateArgs* args_ )
                : WoodBoxCommon( args_ )
            {
                // 生成と同時に他のオブジェクトを作成する必要がある場合などはここに書く
            }

            
        };


        徹底することは、GameObject 内で create を呼ぶ必要があるときは
        サブクラス側でのみ呼ぶようにすること。


*/

//=============================================================================
//								End of File
//=============================================================================
