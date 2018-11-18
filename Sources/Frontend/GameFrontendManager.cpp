//=============================================================================
//【 GameFrontendManager 】
//=============================================================================

#include "GameFrontendManager.h"
#include "PlayerStateWindow.h"
#include "GuideNamePlate.h"
#include "PointCursor.h"

//=============================================================================
// ■ GameFrontendManager クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
GameFrontendManager::GameFrontendManager()
    : mPlayerStateWindow    ( NULL )
    , mStep                 ( GFM_PTEP_SETUP )
    , mFrameCount           ( 0 )
    , mNamePlateFont        ( NULL )
    , mDamagePop            ( NULL )
    , mGuidNamePlateFont    ( NULL )
    , mPointCursor          ( NULL )
    , mFloorInfoOffset      ( 0.0f )
{
    mFrameXPos.setInitValue( -32 );
    mFrameXPos.set( 12 );
    mFrameXPos.setSpeed( 6 );
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
GameFrontendManager::~GameFrontendManager()
{
    finalize();
    
}

//---------------------------------------------------------------------
// ● インスタンスの取得
//---------------------------------------------------------------------
GameFrontendManager* GameFrontendManager::getInstance()
{
    static GameFrontendManager instance;
    return &instance;
}

//---------------------------------------------------------------------
// ● 初期化
//---------------------------------------------------------------------
void GameFrontendManager::initialize( Player* player_ )
{
	mStep = GFM_PTEP_SETUP;
	mFrameCount = 0;
	mFloorInfoOffset = 0;
	mFloorNumAnimTime = 0;

	mNumberTexture1 = Assets::LoadTexture("Data/Graphics/Frontend/Number_1.png");


	mPlayerStateWindow = NEW PlayerStateWindow(player_);

	mNamePlateFont = Font::Create();
	mNamePlateFont->SetFamily("МＳ Ｐゴシック");
	mNamePlateFont->SetSize(10);
	//mNamePlateFont->SetColor( LColor( 1, 1, 1 ) );
	mNamePlateFont->SetAntiAlias(false);


	mGuidNamePlateFont = Font::Create();
	mGuidNamePlateFont->SetFamily("МＳ Ｐゴシック");
	mGuidNamePlateFont->SetSize(10);
	//mGuidNamePlateFont->SetColor( LColor( 1, 1, 1 ) );
	//mGuidNamePlateFont->setEdgeSize( 1 );
	//mGuidNamePlateFont->setEdgeColor( LColor( 0.25f, 0.25f, 0.25f ) );
	mGuidNamePlateFont->SetAntiAlias(false);

	mDamagePop = NEW DamagePop();




	mShowCharacterNamePlateCount = 0;
	mGlobalFadeOpacity.Start(1.0f, 1.0f, 0.1f);

	mLevelupFrameCount = 0;

	LTexture tex = Assets::LoadTexture("Data/Graphics/Frontend/Frontend_1.png");
	mLevelupSprites[0] = Sprite2D::Create(tex);//return;
	mLevelupSprites[0]->setSourceRect(0, 480, 256, 16);
	mLevelupSprites[0]->SetCenter(128, 8);
	mLevelupSprites[0]->SetVisible(false);
	mLevelupSprites[1] = Sprite2D::Create(tex);
	mLevelupSprites[1]->setSourceRect(0, 496, 256, 16);
	mLevelupSprites[1]->SetCenter(128, 8);
	mLevelupSprites[1]->SetVisible(false);
	mLevelEffectSprite = Sprite2D::Create(tex);
	mLevelEffectSprite->setSourceRect(0, 416, 64, 64);
	mLevelEffectSprite->SetPosition(320, 200);
	mLevelEffectSprite->SetCenter(32, 32);
	mLevelEffectSprite->SetVisible(false);

	mLevelupSprites[0]->SetPosition(320, 200 - 8);
	mLevelupSprites[1]->SetPosition(320, 200 + 8);

	mPointCursor = NEW PointCursor();



	mFloorNumAnim.AddKeyFrame(0, 0.0f, InterpolationMode_CatmullRom);
	mFloorNumAnim.AddKeyFrame(30, 1.0f, InterpolationMode_Linear);
	mFloorNumAnim.AddKeyFrame(90, 1.0f, InterpolationMode_CatmullRom);
	mFloorNumAnim.AddKeyFrame(120, 2.0f, InterpolationMode_CatmullRom);
	mFloorNumAnim.SetTime(1000);

	mFloorNumAnimAlpha.AddKeyFrame(0, 0.0f, InterpolationMode_CatmullRom);
	mFloorNumAnimAlpha.AddKeyFrame(30, 1.0f, InterpolationMode_CatmullRom);
	mFloorNumAnimAlpha.AddKeyFrame(90, 1.0f, InterpolationMode_CatmullRom);
	mFloorNumAnimAlpha.AddKeyFrame(120, 0.0f, InterpolationMode_CatmullRom);
	mFloorNumAnimAlpha.SetTime(1000);

	mFloorInfoTexture = Assets::LoadTexture("Data/Graphics/Frontend/FloorInfo_1.png");
	for (int i = 0; i < 3; ++i)
	{
		mFloorInfoSprite[i] = Sprite2D::Create(mFloorInfoTexture);
		mFloorInfoSprite[i]->SetVisible(false);
	}
	mFloorInfoSprite[0]->setSourceRect(0, 0, 512, 32); // 下線
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void GameFrontendManager::finalize()
{
    SAFE_DELETE( mPlayerStateWindow );
	mNamePlateFont.SafeRelease();
	mGuidNamePlateFont.SafeRelease();
    SAFE_DELETE( mDamagePop );
    SAFE_DELETE( mPointCursor );

	mNumberTexture1 = nil;
	mLevelupSprites[ 0 ] = nil;
	mLevelupSprites[ 1 ] = nil;
	mLevelEffectSprite = nil;
	mFloorInfoTexture = nil;
	mFloorInfoSprite[ 0 ] = nil;
	mFloorInfoSprite[ 1 ] = nil;
	mFloorInfoSprite[ 2 ] = nil;
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void GameFrontendManager::update()
{
    mPlayerStateWindow->update();
    mDamagePop->update();
    mPointCursor->update();

    {
        GuideNamePlateList::iterator itr = mGuideNamePlateList.begin();
        GuideNamePlateList::iterator end = mGuideNamePlateList.end();
        for ( ; itr != end; ++itr )
        {
            (*itr)->update();
        }
    }

	switch (mStep)
	{
		///////////////////////////////////////// 開始状態
		case GFM_PTEP_SETUP:
		{
			mPlayerStateWindow->setPosition(mFrameXPos.getValue(), 12);
			mPlayerStateWindow->setOpacity(static_cast< float >(mFrameCount) / 20.0f);

			++mFrameCount;
			if (mFrameCount == 20)
			{
				mStep = GFM_PTEP_IDLE;
			}
			mFrameXPos.update();
			break;
		}
		///////////////////////////////////////// 待機状態
		case GFM_PTEP_IDLE:
		{
			break;
		}
	};

	if (mShowCharacterNamePlateCount > 0)
	{
		--mShowCharacterNamePlateCount;
		if (mShowCharacterNamePlateCount == 0)
		{
			mGlobalFadeOpacity.Start(mGlobalFadeOpacity.GetValue(), 1.0f, 20.0);
		}
	}

	// GuidNamePlate 全体の透明度
	if (!mGlobalFadeOpacity.IsFinished())
	{
		mGlobalFadeOpacity.AdvanceTime(1.0);
	}


	//---------------------------------------------------------
	// レベルアップ関係
	if (mLevelupFrameCount > 0)
	{
		// 閃光
		if (mLevelupFrameCount >= 50)
		{
			float c = static_cast< float >(mLevelupFrameCount - 50);

			mLevelEffectSprite->SetScale(
				7.0f * (10.0f - c) + 1.0f,
				0.8f * c);

			mLevelEffectSprite->SetOpacity(0.05f + c / 10.0f);

			if (mLevelupFrameCount == 50)
			{
				mLevelEffectSprite->SetVisible(false);
			}
		}

		// 文字フェードイン
		if (mLevelupFrameCount >= 50)
		{
			float c = static_cast< float >(10 - (mLevelupFrameCount - 50));
			mLevelupSprites[0]->SetOpacity(c / 10.0f);
			mLevelupSprites[1]->SetOpacity(c / 10.0f);
		}

		// 文字フェードアウト
		if (mLevelupFrameCount < 10)
		{
			float c = static_cast< float >(mLevelupFrameCount - 1);
			float rate = c / 10.0f;

			mLevelupSprites[0]->SetOpacity(rate);
			mLevelupSprites[1]->SetOpacity(rate);

			mLevelupSprites[0]->SetScale(1.0f + (10.0f - c), rate);
			mLevelupSprites[1]->SetScale(1.0f + (10.0f - c), rate);
		}


		--mLevelupFrameCount;

		if (mLevelupFrameCount == 0)
		{
			mLevelupSprites[0]->SetVisible(false);
			mLevelupSprites[1]->SetVisible(false);
			mLevelEffectSprite->SetVisible(false);
		}
	}

	//---------------------------------------------------------
	// フロア数
	if (mFloorNumAnimTime < mFloorNumAnim.GetLastFrameTime())
	{
		float v = mFloorNumAnim.GetValue();

		mFloorInfoSprite[0]->SetPosition(300 - v * 32, 448);
		mFloorInfoSprite[1]->SetPosition(mFloorInfoOffset + 320 + v * 32, 400);
		mFloorInfoSprite[2]->SetPosition(520, 320 + v * 48);

		float a = mFloorNumAnimAlpha.GetValue();
		for (int i = 0; i < 3; ++i)
		{
			mFloorInfoSprite[i]->SetOpacity(a);
		}

		mFloorNumAnimTime += 1.0f;
		mFloorNumAnim.SetTime(mFloorNumAnimTime);
		mFloorNumAnimAlpha.SetTime(mFloorNumAnimTime);

		// finished
		if (mFloorNumAnimTime >= mFloorNumAnim.GetLastFrameTime())
		{
			for (int i = 0; i < 3; ++i)
			{
				mFloorInfoSprite[i]->SetVisible(false);
			}
		}
	}
}

//---------------------------------------------------------------------
// ● 画面中央に「LevelUp」表示
//---------------------------------------------------------------------
void GameFrontendManager::showLevelUp()
{
    mLevelupFrameCount = 60;

    

    mLevelupSprites[ 0 ]->SetOpacity( 0 );
    mLevelupSprites[ 1 ]->SetOpacity( 0 );

    mLevelupSprites[ 0 ]->SetScale( 1 );
    mLevelupSprites[ 1 ]->SetScale( 1 );

    mLevelupSprites[ 0 ]->SetVisible( true );
    mLevelupSprites[ 1 ]->SetVisible( true );
    mLevelEffectSprite->SetVisible( true );
}

//---------------------------------------------------------------------
// ● フロア変更時のフロア数表示エフェクトの表示開始
//---------------------------------------------------------------------
void GameFrontendManager::showFloorNum( int num_ )
{
    for ( int i = 0; i < 3; ++i )
    {
        mFloorInfoSprite[ i ]->SetVisible( true );
        mFloorInfoSprite[ i ]->SetOpacity( 0 );
    }

    if ( num_ < 8 )
    {
        mFloorInfoSprite[ 1 ]->setSourceRect( 0, 32, 160, 64 );

        int x = num_ % 5;
        int y = num_ / 5;
        mFloorInfoSprite[ 2 ]->setSourceRect( x * 96, 128 + y * 96, 96, 96 );
    }
    // ラストフロア
    else
    {
        mFloorInfoSprite[ 1 ]->setSourceRect( 160, 32, 352, 64 );
        mFloorInfoSprite[ 2 ]->setSourceRect( 0, 96, 8, 8 );    // 透明
        mFloorInfoOffset = -50.0;
    }


    mFloorNumAnim.SetTime( 0.0f );
    mFloorNumAnimAlpha.SetTime( 0.0f );
}

//---------------------------------------------------------------------
// ● (GuidNamePlate のコンストラクタから呼ばれる)
//---------------------------------------------------------------------
void GameFrontendManager::addGuidNamePlate( GuideNamePlate* plate_ )
{
    mGuideNamePlateList.push_back( plate_ );
}

//---------------------------------------------------------------------
// ● (GuidNamePlate のデストラクタから呼ばれる)
//---------------------------------------------------------------------
void GameFrontendManager::removeGuidNamePlate( GuideNamePlate* plate_ )
{
    if ( !mGuideNamePlateList.empty() )
    {
        mGuideNamePlateList.remove( plate_ );
    }
}


//---------------------------------------------------------------------
// ● CharacterNamePlate::show が呼ばれた時のコールバック
//---------------------------------------------------------------------
void GameFrontendManager::onShowCharacterNamePlate()
{ 
    mShowCharacterNamePlateCount = 100; 

    mGlobalFadeOpacity.Start( mGlobalFadeOpacity.GetValue(), 0.0f, 20.0 );
}


//=============================================================================
//								end of file
//=============================================================================