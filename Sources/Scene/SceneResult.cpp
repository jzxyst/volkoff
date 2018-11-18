//=============================================================================
//【 SceneResult 】
//=============================================================================

#include "../Utility/Util.h"
#include "../Game/GameManager.h"
#if MIGRATION
#else
#include "../Game/RankingManager.h"
#endif
#include "SceneTitle.h"
#include "SceneCredit.h"
#include "SceneResult.h"

//=============================================================================
// ■ SceneResult クラス
//=============================================================================

SceneResult* gSceneResult = NULL;

//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneResult::onStart()
{
#if MIGRATION
#else
    printf( "-------------------------------------------------\n" );
    printf( " ▼ リザルト\n" );
    printf( "       スコア:%d\n", GameManager::getInstance()->getScore() );
    printf( "       難易度:%d\n", GameManager::getInstance()->getRank() );
    printf( "-------------------------------------------------\n" );

	// 各スコア値
	mScore = std::max<lnU32>( 10, GameManager::getInstance()->getScore());
	mTime = std::max<lnU32>( 0, ( 1800 * 60 ) - GameManager::getInstance()->getGameTime() );	// 30 分から減算
	mRank = GameManager::getInstance()->getRank() * 1000000;
	mTotalScore = mScore + mTime + mRank;


	// ランクインのチェック
	mIsNewRecord = false;
	mRankingNo = 0;
	std::list<ScoreData> score_list = RankingManager::getInstance()->GetLocalStoryRanking( 10 );
	if (score_list.size() < MAX_RANKING_NUM)
	{
		mIsNewRecord = true;
		std::list<ScoreData>::iterator itr = score_list.begin();
		std::list<ScoreData>::iterator end = score_list.end();
		for (int i = 0; (itr != end) && (i < MAX_RANKING_NUM); ++itr, ++i)
		{
			if (mTotalScore > (*itr).unScore)
			{
				mRankingNo = i;
				break;
			}
		}
	}
	else
	{
		std::list<ScoreData>::iterator itr = score_list.begin();
		std::list<ScoreData>::iterator end = score_list.end();
		for (int i = 0; i < MAX_RANKING_NUM; ++itr, ++i)
		{
			if (mTotalScore > (*itr).unScore)
			{
				mIsNewRecord = true;
				mRankingNo = i;
				break;
			}
		}
	}

	

	
	mScoreRapid.set(mScore);
	mTimeRapid.set(mTime);
	mRankRapid.set(mRank);
	mTotalRapid.set(mTotalScore);


    // 背景色
    Graphics.setBGColor( 1.0f, 1.0f, 1.0f );

    mCharacterSprite = Sprite2D::Create(Assets::LoadTexture( "Data/Graphics/Character/Char_Knife.png" ) );
    mCharacterSprite->setSourceRect( 0, 1760, 160, 160 );
    mCharacterSprite->SetPosition( 160, 320, 0 );
    mWeaponSprite = Sprite2D::Create(Assets::LoadTexture( "Data/Graphics/Object/Weapons.png" ) );
    mWeaponSprite->setSourceRect( mWeaponNo * 80, 0, 80, 80 );
    mWeaponSprite->SetPosition( 100, 400, 0 );

	//------------------------------------------------------------
	//
	mResultTexture = Assets::LoadTexture( "Data/Graphics/Frontend/Result_1.png" );
	
	for ( int i = 0; i < 3; ++i )
	{
		mScoreLineSprites[ i ] = Sprite2D::Create( mResultTexture );
		mScoreLineSprites[ i ]->setSourceRect( 0, 96 + 32 * i, 352, 32 );
		mScoreLineSprites[ i ]->SetPosition( 0, LINE_MARGIN_Y - 4 + 48 * i );
		mScoreLineSprites[ i ]->SetOpacity( 0 );
	}

	mTotalLineSprite = Sprite2D::Create( mResultTexture );
	mTotalLineSprite->setSourceRect( 0, 192, 608, 32 );
	mTotalLineSprite->SetPosition( LINE_MARGIN_X, 256 );
	mTotalLineSprite->SetOpacity( 0 );

	// 時間
	for ( int i = 0; i < 6; ++i )
	{
		mTimeSprite[ i ] = Sprite2D::Create( mResultTexture );
		mTimeSprite[ i ]->setSourceRect( 0, 0, 11, 16 );
		mTimeSprite[ i ]->SetPosition(
			LINE_MARGIN_X + 108 + 11 * i + (i / 2 * 8), LINE_MARGIN_Y + 2 + 48 );
		mTimeSprite[ i ]->SetOpacity( 0 );
	}
	u32 h, m, s;
	GameManager::getInstance()->splitGameTime(
		GameManager::getInstance()->getGameTime(),
		&h, &m, &s );

	// h
	u32 buf[2];
	Util::numberToArray(h, 2, buf);
	mTimeSprite[ 0 ]->setSourceRect( 11 * buf[0], 0, 11, 16 );
	mTimeSprite[ 1 ]->setSourceRect( 11 * buf[1], 0, 11, 16 );

	// m
	Util::numberToArray(m, 2, buf);
	mTimeSprite[ 2 ]->setSourceRect( 11 * buf[0], 0, 11, 16 );
	mTimeSprite[ 3 ]->setSourceRect( 11 * buf[1], 0, 11, 16 );

	// s
	Util::numberToArray(s, 2, buf);
	mTimeSprite[ 4 ]->setSourceRect( 11 * buf[0], 0, 11, 16 );
	mTimeSprite[ 5 ]->setSourceRect( 11 * buf[1], 0, 11, 16 );

	// ランク
	mRankSprite = Sprite2D::Create( mResultTexture );
	mRankSprite->setSourceRect( 272, 20 * GameManager::getInstance()->getRank(), 92, 20 );
	mRankSprite->SetPosition( LINE_MARGIN_X + 110, LINE_MARGIN_Y - 2 + 96 );
	mRankSprite->SetOpacity( 0 );

	// Score 数値
	for ( int i = 0; i < 10; ++i )
	{
		mScoreNumberSprites[ i ] = Sprite2D::Create( mResultTexture );
		mScoreNumberSprites[ i ]->setSourceRect( 0, 0, 11, 16 );
		mScoreNumberSprites[ i ]->SetPosition( LINE_MARGIN_X + 234 + 11 * i - 32, LINE_MARGIN_Y + 2 );
		mScoreNumberSprites[ i ]->SetOpacity( 0 );
	}

	// Time 数値
	for ( int i = 0; i < 10; ++i )
	{
		mTimeNumberSprites[ i ] = Sprite2D::Create( mResultTexture );
		mTimeNumberSprites[ i ]->setSourceRect( 0, 0, 11, 16 );
		mTimeNumberSprites[ i ]->SetPosition( LINE_MARGIN_X + 234 + 11 * i - 32, LINE_MARGIN_Y + 2 + 48 );
		mTimeNumberSprites[ i ]->SetOpacity( 0 );
	}

	// Rank 数値
	for ( int i = 0; i < 10; ++i )
	{
		mRankNumberSprites[ i ] = Sprite2D::Create( mResultTexture );
		mRankNumberSprites[ i ]->setSourceRect( 0, 0, 11, 16 );
		mRankNumberSprites[ i ]->SetPosition( LINE_MARGIN_X + 234 + 11 * i - 32, LINE_MARGIN_Y + 2 + 96 );
		mRankNumberSprites[ i ]->SetOpacity( 0 );
	}

	// Total 数値
	for ( int i = 0; i < 10; ++i )
	{
		mTotalNumberSprites[ i ] = Sprite2D::Create( mResultTexture );
		mTotalNumberSprites[ i ]->setSourceRect( 0, 16, 18, 24 );
		mTotalNumberSprites[ i ]->SetPosition( LINE_MARGIN_X + 368 + 18 * i, LINE_MARGIN_Y + 206 );
		mTotalNumberSprites[ i ]->SetOpacity( 0 );
	}

	// New Record
	mNewRecordSprite = Sprite2D::Create( mResultTexture );
	mNewRecordSprite->setSourceRect( 384, 0, 160, 32 );
	mNewRecordSprite->SetPosition( 452, 340 );
	mNewRecordSprite->SetOpacity( 0 );

	mNewRecordBGSprite = Sprite2D::Create( mResultTexture );
	mNewRecordBGSprite->setSourceRect( 0, 224, 32, 32 );
	mNewRecordBGSprite->SetScale(20);
	mNewRecordBGSprite->SetPosition(0, 0);
	mNewRecordBGSprite->SetOpacity( 0 );

	mRankingFrameSprite = Sprite2D::Create(
		Assets::LoadTexture( "Data/Graphics/Frontend/Ranking_1.png" ));
	mRankingFrameSprite->SetPosition(320, 200 + 48 / 2);
	mRankingFrameSprite->SetCenter(256 / 2, 48 / 2);
	mRankingFrameSprite->setSourceRect(0, 0, 256, 48);
	mRankingFrameSprite->SetOpacity(0);
	//mRankingFrameSprite->SetScale(2);


	// コマンドのフェードインX座標
    mCommandFadeInX.setCapacity( 2 );
    mCommandFadeInX.addKeyFrame( 0, 0 );
    mCommandFadeInX.addKeyFrame( 30, 32 );
    mCommandFadeInX[ 0 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mCommandFadeInX[ 1 ].InterMode = LN_ANIM_INTER_CATMULLROM;
    mCommandFadeInX.setTime( 0.0 );
    mCommandFadeInX.setTimeTickPerSec( 1.0f );

    // コマンドのフェードイン不透明度
    mCommandFadeInOpacity.setCapacity( 3 );
    mCommandFadeInOpacity.addKeyFrame( 0,  0.0f );
    mCommandFadeInOpacity.addKeyFrame( 15, 0.5f );
    mCommandFadeInOpacity.addKeyFrame( 30, 1.0f );
    mCommandFadeInOpacity.setTime( 0.0 );
    mCommandFadeInOpacity.setTimeTickPerSec( 1.0f );





	Accessor::ToneLayer->ChangeTone( LTone( 0, 0, 0 ), 2.0f );
	


	LTexture tex = Texture2D::Create( 640, 96 );
	tex.drawText(
		"",
		LRect( 0, 0, 512, 96 ) );
	mMessageSprite = Sprite2D::Create( tex );
	mMessageSprite->SetPosition( 100, 100 );
	mMessageSprite->SetVisible(false);


    mPhase = 0;
    mFrameCount = 0;

	gSceneResult = this;
#endif
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneResult::onUpdate()
{
#if MIGRATION
#else
    switch ( mPhase )
    {
        /////////////////////// ウェイト
        case 0:
        {
            if ( mFrameCount >= 30 )
            {
                mPhase = 1;
                mFrameCount = 0;
            }
            break;
        }

        /////////////////////// フェードインフェーズ
        case 1:
        {
			// アンダーラインのフェードイン
			if ( mFrameCount >= 20 && mFrameCount <= 60 )
            {
				int t = mFrameCount - 20;
				for ( int i = 0; i < 3; ++i )
				{
					mCommandFadeInX.setTime( static_cast< double >( t - 5 * i ) );
					mScoreLineSprites[ i ]->SetPosition(
						LINE_MARGIN_X + mCommandFadeInX.getValue() - 32, LINE_MARGIN_Y + 48 * i );

					mCommandFadeInOpacity->SetTime( static_cast< double >( t - 5 * i ) );
					mScoreLineSprites[ i ]->SetOpacity( mCommandFadeInOpacity.getValue() );
				}

				// 時間
				mCommandFadeInX.setTime( static_cast< double >( t - 5 ) );
				mCommandFadeInOpacity.setTime( t - 5 );
				for ( int i = 0; i < 6; ++i )
				{
					mTimeSprite[ i ]->SetPosition(
						LINE_MARGIN_X + 108 + 11 * i + (i / 2 * 8) + mCommandFadeInX.getValue() - 32 - 32, LINE_MARGIN_Y + 2 + 48 );
					mTimeSprite[ i ]->SetOpacity( mCommandFadeInOpacity.getValue() );
				}

				// ランク
				mCommandFadeInX.setTime( static_cast< double >( t - 10 ) );
				mCommandFadeInOpacity.setTime( t - 10 );
				mRankSprite->SetPosition(
						LINE_MARGIN_X + 110 + mCommandFadeInX.getValue() - 32 - 32, LINE_MARGIN_Y - 2 + 96 );
				mRankSprite->SetOpacity( mCommandFadeInOpacity.getValue() );
			}


			// Score 数値のフェードイン
			if ( mFrameCount >= 50 )// && mFrameCount <= 80 + 160 )
            {
				mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 50 ) );
				for ( int i = 0; i < 10; ++i )
				{
					mScoreNumberSprites[ i ]->SetOpacity( mCommandFadeInOpacity.getValue() );
				}

				mScoreRapid.update();
			}

			// Time 数値のフェードイン
			if ( mFrameCount >= 60 )// && mFrameCount <= 90 + 160 )
            {
				mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 60 ) );
				for ( int i = 0; i < 10; ++i )
				{
					mTimeNumberSprites[ i ]->SetOpacity( mCommandFadeInOpacity.getValue() );
				}

				mTimeRapid.update();
			}

			// Rank 数値のフェードイン
			if ( mFrameCount >= 70 )// && mFrameCount <= 100 + 160 )
            {
				mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 70 ) );
				for ( int i = 0; i < 10; ++i )
				{
					mRankNumberSprites[ i ]->SetOpacity( mCommandFadeInOpacity.getValue() );
				}
				
				mRankRapid.update();
			}


			


			//----------------------------------------------------------
			// 数値更新
			int value[10];

			// Score
			Util::numberToArray2( mScoreRapid.getValue(), 10, value );
			for ( int i = 0; i < 10; ++i )
			{
				if ( value[i] == -1 )
					mScoreNumberSprites[ i ]->SetVisible(false);
				else
				{
					mScoreNumberSprites[ i ]->SetVisible(true);
					mScoreNumberSprites[ i ]->setSourceRect( value[i] * 11, 0, 11, 16 );
				}
			}

			// Time
			Util::numberToArray2( mTimeRapid.getValue(), 10, value );
			for ( int i = 0; i < 10; ++i )
			{
				if ( value[i] == -1 )
					mTimeNumberSprites[ i ]->SetVisible(false);
				else
				{
					mTimeNumberSprites[ i ]->SetVisible(true);
					mTimeNumberSprites[ i ]->setSourceRect( value[i] * 11, 0, 11, 16 );
				}
			}

			// Rank
			Util::numberToArray2( mRankRapid.getValue(), 10, value );
			for ( int i = 0; i < 10; ++i )
			{
				if ( value[i] == -1 )
					mRankNumberSprites[ i ]->SetVisible(false);
				else
				{
					mRankNumberSprites[ i ]->SetVisible(true);
					mRankNumberSprites[ i ]->setSourceRect( value[i] * 11, 0, 11, 16 );
				}
			}

			


			if ( mScoreRapid.isFinished() && mTimeRapid.isFinished() && mRankRapid.isFinished() )//mFrameCount >= 260 )
            {
                mPhase = 2;
                mFrameCount = 0;
            }
            break;
        }

        /////////////////////// 仮
        case 2:
        {
			// Total Line
			if ( mFrameCount >= 0 && mFrameCount <= 60 )
			{
				float t = mFrameCount - 0;
				mCommandFadeInX.setTime( t / 2 );
				mCommandFadeInOpacity.setTime( t / 2  );
				mTotalLineSprite->setSourceRect( 0, 192, 608.0 * mCommandFadeInX.getValue() / 32, 32 );
				mTotalLineSprite->SetOpacity( mCommandFadeInOpacity.getValue() );
			}

			// Total 数値のフェードイン
			if ( mFrameCount >= 60 )// && mFrameCount <= 250 + 160 )
            {
				mCommandFadeInOpacity.setTime( static_cast< double >( mFrameCount - 60 ) );
				for ( int i = 0; i < 10; ++i )
				{
					mTotalNumberSprites[ i ]->SetOpacity( mCommandFadeInOpacity.getValue() );
				}
				
				mTotalRapid.update();
			}

			// Total 数値更新
			int value[10];
			Util::numberToArray2( mTotalRapid.getValue(), 10, value );
			for ( int i = 0; i < 10; ++i )
			{
				if ( value[i] == -1 )
					mTotalNumberSprites[ i ]->SetVisible(false);
				else
				{
					mTotalNumberSprites[ i ]->SetVisible(true);
					mTotalNumberSprites[ i ]->setSourceRect( value[i] * 18, 16, 18, 24 );
				}
			}


			if ( mTotalRapid.isFinished() )
			{
				mPhase = 3;
                mFrameCount = 0;
				return;
			}
            break;
        }

		/////////////////////// 決定ボタン待ちフェーズ
        case 3:
        {
			if ( mIsNewRecord )
			{
				if ( mFrameCount == 0 )
				{
					mNewRecordOpacity.start(0.5, 1.0, 20);
				}

				mNewRecordSprite->SetOpacity( mNewRecordOpacity.getValue() );
				mNewRecordOpacity.advanceTime( 1 );
			}


			if ( Input.isOnTrigger( LN_BUTTON_A ) )
            {
				if (mIsNewRecord)
				{
					mPhase = 4;
				}
				else
				{
					mPhase = -1;
				}
                mFrameCount = 0;
                return;
            }
            break;
		}

		/////////////////////// 名前入力開始フェーズ
        case 4:
        {
			if (mFrameCount == 0)
			{
				mRankingNameplate.initialize(
					mRankingNo + 1, "",
					GameManager::getInstance()->getRank(),
					GameManager::getInstance()->getGameTime(),
					mTotalScore );
				mRankingNameplate->SetOpacity(0);
				mRankingNameplate->SetPosition( 320 - 128, 200 );
				mNameplateOpacity.start(0, 1, 30);
			}

			mNameplateOpacity.advanceTime(1);
			mRankingNameplate->SetOpacity(mNameplateOpacity.getValue());
			mNewRecordBGSprite->SetOpacity(mNameplateOpacity.getValue() * 0.75);
			
			if (mFrameCount >= 30)
			{
				mPhase = 5;
				mFrameCount = 0;
				return;
			}
			break;
		}

		/////////////////////// 名前入力フェーズ
        case 5:
        {
			mRankingNameplate.updateCaret();
			//{
			//	mPhase = 6;
			//	mFrameCount = 0;
			//	return;
			//}
			break;
		}

		/////////////////////// 名前入力終了フェーズ
        case 6:
        {
			if (mFrameCount == 0)
			{
				mNameplateOpacity.start(1, 0, 30);
			}
			mNameplateOpacity.advanceTime(1);
			mRankingNameplate->SetOpacity(mNameplateOpacity.getValue());
			mNewRecordBGSprite->SetOpacity(mNameplateOpacity.getValue() * 0.75);

			if (mFrameCount <= 8)
			{
				float rate = LMath::min<float>(((float)mFrameCount) / 8.f, 1.f);
				mRankingFrameSprite->SetOpacity(1.0f - rate);
				mRankingFrameSprite->SetScale(rate * 0.5f + 1.f);
			}
			

			if (mFrameCount >= 30)
			{
				mPhase = -1;
				mFrameCount = 0;
				return;
			}
			break;
		}

        /////////////////////// フェードアウトフェーズ
        case -1:
        {
            if ( mFrameCount <= 120 )
            {
				float op = 0.008f * ( 120 - mFrameCount );

                mCharacterSprite->SetOpacity( op );

				for ( int i = 0; i < 3; ++i ) mScoreLineSprites[i]->SetOpacity( op );
				mTotalLineSprite->SetOpacity( op );
				for ( int i = 0; i < 6; ++i ) mTimeSprite[i]->SetOpacity( op );
				mRankSprite->SetOpacity( op );
				for ( int i = 0; i < 10; ++i ) 
				{
					mScoreNumberSprites[i]->SetOpacity( op );
					mTimeNumberSprites[i]->SetOpacity( op );
	 				mRankNumberSprites[i]->SetOpacity( op );
					mTotalNumberSprites[i]->SetOpacity( op );
				}

				if (mIsNewRecord)
				{
					mNewRecordSprite->SetOpacity( op );
				}
            }

			if ( mFrameCount == 120 )
            {
				Accessor::ToneLayer->ChangeTone( LTone( 1, 1, 1 ), 2.0f );
			}

            if ( mFrameCount >= 300 )
            {
                this->changeScene( NEW SceneCredit() );
                return;
            }
            break;
        }
    }
#endif

    ++mFrameCount;
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneResult::onTerminate()
{
	gSceneResult = NULL;
}

//---------------------------------------------------------------------
// ● 文字入力イベント処理
//---------------------------------------------------------------------
void SceneResult::onkeyEvent( char code_ )
{
#if MIGRATION
#else
	if (mPhase == 5)
	{
		if (code_ == VK_RETURN)
		{
			if (strlen(mRankingName) > 0)
			{
				RankingManager::getInstance()->PostLocalStoryScore(
					mRankingName,
					mTotalScore, 
					0,
					GameManager::getInstance()->getGameTime(),
					GameManager::getInstance()->getRank() );

				mRankingNameplate.setVisibleCaret(false);
				mPhase = 6;
				mFrameCount = 0;
			}
		}
		else if (code_ == VK_BACK)
		{
			int last = strlen(mRankingName);
			if (last > 0)
			{
				mRankingName[last - 1] = '\0';
			}
		}
		else
		{
			int last = strlen(mRankingName);
			if (last < MAX_RANKING_NAME_LEN)
			{
				mRankingName[last] = code_;
				mRankingName[last + 1] = '\0';
			}
		}

		mRankingNameplate.setName(mRankingName);
	}
#endif
}

//=============================================================================
//								end of file
//=============================================================================