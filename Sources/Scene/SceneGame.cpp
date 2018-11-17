//=============================================================================
/*! 
    @addtogroup 
    @file       SceneGame.cpp
    @brief      
    
    ゲームのメインとなるシーンの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "./../Event/EventManager.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Game/GameManager.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "../Object/Character.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Object/MidBoss1.h"
#include "../Object/Weapon.h"
#include "./../Object/GameObjectManager.h"
#include "./../Camera/CameraManager.h"
#include "./../Object/MidBoss1.h"
#include "./../Object/Bullet.h"
#include "SceneGameover.h"
#include "SceneResult.h"

#include "./../Effect/Effect_1.h"
#include "./../Effect/Effect_2.h"

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
SceneGame::SceneGame()
    : mMapManager           ( NULL )
	, mFrameCount           ( 0 )
	, mBeginScene           ( false )
    , mBossCollapseCount         ( 0 ) 
{
}

//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneGame::onStart()
{
	// 背景色
	Engine::GetMainViewport()->SetBackgroundColor(Color::Gray);



	//BGM
	GameAudio::PlayBGM(MAIN_BGM_NAME, 0.60);



	// 
	//Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->setType( LN_CAMERA_MOUSE_MOVE );

	// 難易度の設定
	//GameManager::getInstance()->setRank(2);


    // GameManager に移動
	//GameFrontendManager::getInstance()->initialize( GameManager::getInstance()->getPlayer() );
	GameFrontendManager::getInstance()->getPlayerStateWindow()->setOpacity(0);

    // 最初のマップの設定
	
	GameManager::getInstance()->setFloorNum(0);
	MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());



	//カメラの設定
	CameraManager::getInstance()->Initialize();
	//CameraManager::getInstance()->ChaseObject(GameManager::getInstance()->getPlayer());

    // 武器
    /*
    Weapon::CreateData wdata2;
    wdata2.Data.WeaponType  = WEAPON_SHOTGUN;
    wdata2.Data.UseCount    = 1000;//gWeaponBaseData[WEAPON_SHOTGUN].UseCount;
    wdata2.Position         = LVector3( 150.0f, 200.0f, -1.0f );
    Weapon* test_weapon2 = Weapon::create( &wdata2 );
    */

	

    GameManager::getInstance()->commit();
	GameManager::getInstance()->resetGameTime();

	//debug
	mUBW = 0;

	//初期演出用
	GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
	GameManager::getInstance()->getPlayer()->setVisible(false);
	//GameManager::getInstance()->getPlayer()->setLevel( 7 );

    mBossCollapseCount = 0;
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneGame::onUpdate()
{
	++mFrameCount;

	//---------------------------------------------------------
    // 演出用
	if(this->mBeginScene)
	{
		GameFrontendManager::getInstance()->update();
	}


	//---------------------------------------------------------
	// ボス撃破エフェクト
	if (mBossCollapseCount > 0)
	{
		GameManager::getInstance()->getEffectManager()->update();
		CameraManager::getInstance()->Update();
		GameFrontendManager::getInstance()->update();
		--mBossCollapseCount;
		if (mBossCollapseCount == 0)
		{
			this->changeScene(NEW SceneResult(GameManager::getInstance()->getPlayer()->getWeaponData().WeaponType));
		}
		return;
	}

	GameObjectManager::getInstance()->Update();
	GameManager::getInstance()->update();
	CameraManager::getInstance()->Update();



	/* _p( Framework.getFrameCount() );
	_p( GameObjectManager::getInstance()->findObject( 124 ) );*/

	// 以下はシーンがアクティブな場合にのみ呼ぶ
	if (!this->isActiveScene())
	{
		return;
	}

    

    // プレイヤーが亡くなってる場合は子シーンとしてゲームオーバーを呼ぶ
    if ( GameManager::getInstance()->getPlayer()->isDead() )
    {
        this->callScene( NEW SceneGameover() );
    }

    // ボスがいて倒れている場合は撃破エフェクトへ
    Character* boss = GameManager::getInstance()->getLastBossCharacter();
    if ( boss && boss->isDead() )
    {
        mBossCollapseCount = 300;
        NEW Effect_ValfirleDead( boss->getPosition() + LVector3( 0, 15, 0 ) );
		Accessor::ToneLayer->ChangeTone(ToneF(1, 1, 1, 0), 0.5); // 画面フェードアウト
        GameAudio::StopBGM( 5.0f );                                  // 5秒かけてBGMをフェードアウト
        return;
    }

#if 0

	static int a;
	a++;


	//Debug
	//エネミーをすべて削除する開発用コマンド
	if(::GetKeyState(VK_F1) & 0x8000)
	{
		printf("%d\n",GameObjectManager::getInstance()->removeObject(OBJ_ENEMY));
	}
	//Debug 回復アイテムを頭上に出現させる
	if(::GetKeyState(VK_F2) & 0x8000)
	{
		Cure_L *pCure = new Cure_L();
		pCure->Initialize();

		LVector3 v =  GameManager::getInstance()->getPlayer()->getPosition();
		v.y += 100;

		pCure->setPosition(v);
	}
	//Debug 鍵取得
	if(::GetKeyState(VK_F3) & 0x8000)
	{
		printf("鍵取得（Debug）\n");
		GameManager::getInstance()->setKeyflag(1);
	//	GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+1);


	}
	//Debug 難易度変更
	if((::GetKeyState(VK_F4) & 0x8000)&&(a%50==0))
	{
		if(	GameManager::getInstance()->getRank()!=3)
			GameManager::getInstance()->setRank(GameManager::getInstance()->getRank()+1);
		else
			GameManager::getInstance()->setRank(0);
		switch(GameManager::getInstance()->getRank())
		{
		case 0:
			printf("イージー\n");
			break;
		case 1:
			printf("ノーマル\n");
			break;
		case 2:
			printf("ハード\n");
			break;
		case 3:
			printf("ヴァルファーレ\n");
			break;
		}
	}
	//Debug 次のステージへ移動する
	if((::GetKeyState(VK_F5) & 0x8000)&&(a%50==0))
	{
		GameManager::getInstance()->setKeyflag(0);
		GameObjectManager::getInstance()->deleteStageObject();
		GameManager::getInstance()->NextFloor();
		MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());
		printf("ステージ%d\n",GameManager::getInstance()->getFloorNum()+1);
	}
	//Debug 前のステージへ移動する
	if((::GetKeyState(VK_F6) & 0x8000)&&(a%50==0))
	{
		GameManager::getInstance()->setKeyflag(0);
		GameObjectManager::getInstance()->deleteStageObject();
		GameManager::getInstance()->setFloorNum(GameManager::getInstance()->getFloorNum()-2);
		GameManager::getInstance()->NextFloor();
		MapManager::getInstance()->changeMap(GameManager::getInstance()->getFloorNum());
		printf("ステージ%d\n",GameManager::getInstance()->getFloorNum()+1);
	}
	//Debug 武器の使用回数を増やす
	if(::GetKeyState(VK_F7) & 0x8000)
	{
		GameManager::getInstance()->getPlayer()->setLife(100);
		GameManager::getInstance()->getPlayer()->setOpacity(1);
	}
	//Debug 武器を出現させる
    if ( Input.isOnTrigger( LN_BUTTON_R ) )
    {
		mUBW = 10;
		GameAudio::PlaySE("./Data/Sound/SE/UBW.wav");
		//Audio.playBGM("d:\\Users\\GamePG\\Desktop\\bgm\\【Fate／unlimited codes】EMIYA【BGM】.mp3",60);
    }

	//Debug 武器を出現させる
    if ( Input.isOnTrigger( LN_BUTTON_L ) )
    {
		mUBW = 10;
		GameAudio::PlaySE("./Data/Sound/SE/I_am_the_bone.wav");
		//Audio.playBGM("d:\\Users\\GamePG\\Desktop\\The Pink Panther Theme Song.mp3",100,100);
    }

	/*
	Animation::FixedLengthScalar anim( 32 );
	anim.addKeyFrame( 0, 10 );
	anim.addKeyFrame( 20, 100 );
	anim.addKeyFrame( 30, 50 );

	anim[0].InterMode = LN_ANIM_INTER_CATMULLROM;
	anim[1].InterMode = LN_ANIM_INTER_CATMULLROM;
	anim[2].InterMode = LN_ANIM_INTER_CATMULLROM;



















	while()
	{
		anim.advanceTime(0.016f);
		int x = anim.getValue();
	}
	*/




	//Debug UBW
	if(this->mUBW && !(this->mFrameCount % 2))
	{
		Weapon::CreateData wdata;

		wdata.Data.WeaponType  = static_cast<WeaponType>(::rand() % (WEAPON_NORMAL_MAX_NUM ) + 1);
		//wdata.Data.WeaponType = WEAPON_STICK;
		wdata.Data.UseCount    = 1000;//gWeaponBaseData[wdata.Data.WeaponType].UseCount;

		LVector3 v = GameManager::getInstance()->getPlayer()->getPosition();
		v.x += ::rand() % 300 - 150;
		v.y += 210;
		wdata.Position = v;
		Weapon::create( &wdata );

		mUBW--;
	}

#endif

	// 演出用
	if(!this->mBeginScene)
	{
		if (Input::IsTriggered(LN_BUTTON_A))
		{
			Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 0.0);
			CameraManager::getInstance()->ChaseObject(GameManager::getInstance()->getPlayer());
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(MapManager::getInstance()->getStartPosition().x,MapManager::getInstance()->getStartPosition().y + 40,MapManager::getInstance()->getStartPosition().z));
			GameManager::getInstance()->getPlayer()->setDefPosition(MapManager::getInstance()->getStartPosition());
			GameManager::getInstance()->getPlayer()->setVelocity(LVector3(20,5,0));
			GameManager::getInstance()->getPlayer()->setVisible(true);

			this->mBeginScene = true;
			return;
		}

		LVector3 v;

		switch(this->mFrameCount)
		{
		case 1:
			Accessor::ToneLayer->ChangeTone(ToneF(-1, -1, -1, 0), 0.0);
			Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 1.5);
			v = LVector3(600,200,-400);
			CameraManager::getInstance()->Move(v,LVector3(0,0,-3));

			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 180:
			Accessor::ToneLayer->ChangeTone(ToneF(-1, -1, -1, 0), 0.4);
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 200:
			Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 0.4);
			v = LVector3(1000,180,-1000);
			CameraManager::getInstance()->Move(v,LVector3(0,2.5,0));

			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 370:
			Accessor::ToneLayer->ChangeTone(ToneF(-1, -1, -1, 0), 0.4);
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 390:
			Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 0.4);
			v = LVector3(1200,650,-400);
			CameraManager::getInstance()->Move(v,LVector3(4,0,0));

			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 570:
			Accessor::ToneLayer->ChangeTone(ToneF(-1, -1, -1, 0), 0.4);
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 600:
			Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 0.6);
			v = LVector3(1000,300,-1300);
			CameraManager::getInstance()->Move(v,LVector3(0,0,-15));

			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 720:
			CameraManager::getInstance()->Move(Accessor::Main3Camera->position(),LVector3(-9.8888888889,-2.66666667,20.0));
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 810:
			CameraManager::getInstance()->Move(LVector3(MapManager::getInstance()->getStartPosition().x,MapManager::getInstance()->getStartPosition().y + 40,-1300),LVector3(0,0,0));
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;

		case 820:
			CameraManager::getInstance()->ChaseObject(GameManager::getInstance()->getPlayer());
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(MapManager::getInstance()->getStartPosition().x,MapManager::getInstance()->getStartPosition().y + 40,MapManager::getInstance()->getStartPosition().z));
			GameManager::getInstance()->getPlayer()->setDefPosition(MapManager::getInstance()->getStartPosition());
			GameManager::getInstance()->getPlayer()->setVelocity(LVector3(20,5,0));
			GameManager::getInstance()->getPlayer()->setVisible(true);

			this->mBeginScene = true;
			break;

		default:
			GameManager::getInstance()->getPlayer()->setPosition(LVector3(1999.0f,1999.0f,1999.0f));
			break;
		}
	}


    
  //  //Debug Dキー
  //  if ( Input.isOnTrigger( LN_BUTTON_Z ) )
  //  {
  //      //GameFrontendManager::getInstance()->showLevelUp();
  //      //GameFrontendManager::getInstance()->showFloorNum( 5 );
  //      //NEW Effect_ValfirleDead( GameManager::getInstance()->getPlayer()->getPosition() );
		////NEW Effect_Thunder( GameManager::getInstance()->getPlayer()->getPosition() );
  //  }
  //  
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneGame::onTerminate()
{
    MapManager::getInstance()->releaseTilemap();

    GameManager::getInstance()->finalize();
	
    //GameFrontendManager::getInstance()->finalize();
}


//=============================================================================
//								End of File
//=============================================================================
