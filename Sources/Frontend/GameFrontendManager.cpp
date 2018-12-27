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
    : mPlayerStateWindow    ( nullptr )
    , mStep                 ( GFM_PTEP_SETUP )
    , mFrameCount           ( 0 )
    , mNamePlateFont        ( nullptr )
    , mDamagePop            ( nullptr )
    , mGuidNamePlateFont    ( nullptr )
    , mPointCursor          ( nullptr )
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

	mNumberTexture1 = Assets::loadTexture("Data/Graphics/Frontend/Number_1.png");


	mPlayerStateWindow = NEW PlayerStateWindow(player_);

	mNamePlateFont = Font::create();
	mNamePlateFont->setFamily(u"МＳ Ｐゴシック");
	mNamePlateFont->setSize(10);
	//mNamePlateFont->SetColor( LColor( 1, 1, 1 ) );
	mNamePlateFont->setAntiAlias(false);


	mGuidNamePlateFont = Font::create();
	mGuidNamePlateFont->setFamily(u"МＳ Ｐゴシック");
	mGuidNamePlateFont->setSize(10);
	//mGuidNamePlateFont->SetColor( LColor( 1, 1, 1 ) );
	//mGuidNamePlateFont->setEdgeSize( 1 );
	//mGuidNamePlateFont->setEdgeColor( LColor( 0.25f, 0.25f, 0.25f ) );
	mGuidNamePlateFont->setAntiAlias(false);

	mDamagePop = NEW DamagePop();




	mShowCharacterNamePlateCount = 0;
	mGlobalFadeOpacity.start(1.0f, 1.0f, 0.1f);

	mLevelupFrameCount = 0;

	LTexture tex = Assets::loadTexture("Data/Graphics/Frontend/Frontend_1.png");
	mLevelupSprites[0] = ln::UISprite::create(tex);//return;
	mLevelupSprites[0]->setSourceRect(0, 480, 256, 16);
	mLevelupSprites[0]->setCenterPoint(128, 8);
	mLevelupSprites[0]->setVisible(false);
	mLevelupSprites[1] = ln::UISprite::create(tex);
	mLevelupSprites[1]->setSourceRect(0, 496, 256, 16);
	mLevelupSprites[1]->setCenterPoint(128, 8);
	mLevelupSprites[1]->setVisible(false);
	mLevelEffectSprite = ln::UISprite::create(tex);
	mLevelEffectSprite->setSourceRect(0, 416, 64, 64);
	mLevelEffectSprite->setPosition(320, 200);
	mLevelEffectSprite->setCenterPoint(32, 32);
	mLevelEffectSprite->setVisible(false);

	mLevelupSprites[0]->setPosition(320, 200 - 8);
	mLevelupSprites[1]->setPosition(320, 200 + 8);

	mPointCursor = NEW PointCursor();



    auto curve1 = KeyFrameAnimationCurve::create();
    curve1->addKeyFrame(0, 0.0f, TangentMode::Auto);
    curve1->addKeyFrame(30, 1.0f, TangentMode::Linear);
    curve1->addKeyFrame(90, 1.0f, TangentMode::Auto);
    curve1->addKeyFrame(120, 2.0f, TangentMode::Auto);
    mFloorNumAnim = ScalarAnimationTrack::create();
    mFloorNumAnim->setCurve(curve1);

    auto curve2 = KeyFrameAnimationCurve::create();
    curve2->addKeyFrame(0, 0.0f, TangentMode::Auto);
    curve2->addKeyFrame(30, 1.0f, TangentMode::Auto);
    curve2->addKeyFrame(90, 1.0f, TangentMode::Auto);
    curve2->addKeyFrame(120, 0.0f, TangentMode::Auto);
    mFloorNumAnimAlpha = ScalarAnimationTrack::create();
    mFloorNumAnimAlpha->setCurve(curve2);

	mFloorInfoTexture = Assets::loadTexture("Data/Graphics/Frontend/FloorInfo_1.png");
	for (int i = 0; i < 3; ++i)
	{
		mFloorInfoSprite[i] = ln::UISprite::create(mFloorInfoTexture);
		mFloorInfoSprite[i]->setVisible(false);
	}
	mFloorInfoSprite[0]->setSourceRect(0, 0, 512, 32); // 下線
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void GameFrontendManager::finalize()
{
    SAFE_DELETE( mPlayerStateWindow );
    mNamePlateFont = nullptr;
	mGuidNamePlateFont = nullptr;
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
			mGlobalFadeOpacity.start(mGlobalFadeOpacity.getValue(), 1.0f, 20.0);
		}
	}

	// GuidNamePlate 全体の透明度
	if (!mGlobalFadeOpacity.isFinished())
	{
		mGlobalFadeOpacity.advanceTime(1.0);
	}


	//---------------------------------------------------------
	// レベルアップ関係
	if (mLevelupFrameCount > 0)
	{
		// 閃光
		if (mLevelupFrameCount >= 50)
		{
			float c = static_cast< float >(mLevelupFrameCount - 50);

			mLevelEffectSprite->setScale(
				7.0f * (10.0f - c) + 1.0f,
				0.8f * c);

			mLevelEffectSprite->setOpacity(0.05f + c / 10.0f);

			if (mLevelupFrameCount == 50)
			{
				mLevelEffectSprite->setVisible(false);
			}
		}

		// 文字フェードイン
		if (mLevelupFrameCount >= 50)
		{
			float c = static_cast< float >(10 - (mLevelupFrameCount - 50));
			mLevelupSprites[0]->setOpacity(c / 10.0f);
			mLevelupSprites[1]->setOpacity(c / 10.0f);
		}

		// 文字フェードアウト
		if (mLevelupFrameCount < 10)
		{
			float c = static_cast< float >(mLevelupFrameCount - 1);
			float rate = c / 10.0f;

			mLevelupSprites[0]->setOpacity(rate);
			mLevelupSprites[1]->setOpacity(rate);

			mLevelupSprites[0]->setScale(1.0f + (10.0f - c), rate);
			mLevelupSprites[1]->setScale(1.0f + (10.0f - c), rate);
		}


		--mLevelupFrameCount;

		if (mLevelupFrameCount == 0)
		{
			mLevelupSprites[0]->setVisible(false);
			mLevelupSprites[1]->setVisible(false);
			mLevelEffectSprite->setVisible(false);
		}
	}

	//---------------------------------------------------------
	// フロア数
	if (mFloorNumAnimTime < mFloorNumAnim->lastFrameTime())
	{
		float v = mFloorNumAnim->evaluate(mFloorNumAnimTime);

		mFloorInfoSprite[0]->setPosition(300 - v * 32, 448);
		mFloorInfoSprite[1]->setPosition(mFloorInfoOffset + 320 + v * 32, 400);
		mFloorInfoSprite[2]->setPosition(520, 320 + v * 48);

		float a = mFloorNumAnimAlpha->evaluate(mFloorNumAnimTime);
		for (int i = 0; i < 3; ++i)
		{
			mFloorInfoSprite[i]->setOpacity(a);
		}

		mFloorNumAnimTime += 1.0f;

		// finished
		if (mFloorNumAnimTime >= mFloorNumAnim->lastFrameTime())
		{
			for (int i = 0; i < 3; ++i)
			{
				mFloorInfoSprite[i]->setVisible(false);
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

    

    mLevelupSprites[ 0 ]->setOpacity( 0 );
    mLevelupSprites[ 1 ]->setOpacity( 0 );

    mLevelupSprites[ 0 ]->setScale( 1 );
    mLevelupSprites[ 1 ]->setScale( 1 );

    mLevelupSprites[ 0 ]->setVisible( true );
    mLevelupSprites[ 1 ]->setVisible( true );
    mLevelEffectSprite->setVisible( true );
}

//---------------------------------------------------------------------
// ● フロア変更時のフロア数表示エフェクトの表示開始
//---------------------------------------------------------------------
void GameFrontendManager::showFloorNum( int num_ )
{
    for ( int i = 0; i < 3; ++i )
    {
        mFloorInfoSprite[ i ]->setVisible( true );
        mFloorInfoSprite[ i ]->setOpacity( 0 );
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

    mFloorNumAnimTime = 0;
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

    mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 0.0f, 20.0 );
}


//=============================================================================
//								end of file
//=============================================================================