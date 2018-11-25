//=============================================================================
//【 SceneRanking 】
//=============================================================================

#include "SceneTitle.h"
#include "SceneRanking.h"
#if MIGRATION
#else
#include "../Game/RankingManager.h"
#endif

//=============================================================================
// ■ SceneRanking クラス
//=============================================================================

//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneRanking::onStart()
{
#if MIGRATION
#else
    printf( "-------------------------------------------------\n" );
    printf( " ▼ ランキング\n" );
    printf( "-------------------------------------------------\n" );

	mRankingTexture = Assets::LoadTexture( "Data/Graphics/Frontend/Ranking_1.png" );
    
    mBGWhiteSprite = LSprite::create( mRankingTexture );
    mBGWhiteSprite->setSourceRect( 320, 0, 32, 32 );
    mBGWhiteSprite->setScale( 20 );
	mBGWhiteSprite->setOpacity( 1.0 );


	//RankingManager::getInstance()->PostLocalStoryScore( "Tom", 31200971, 5, 71000 * 60 * 2, 0 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Jason", 51050986, 5, 13000 * 60 * 2, 1 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Freddy", 73027916, 5, 11000 * 60 * 2, 2 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Predator", 31050981, 5, 104500 * 60 * 2, 3 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Lee", 63020186, 5, 1000 * 60 * 2, 2 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Jack", 31438678, 5, 12000 * 60 * 2, 2 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Vito", 41000986, 5, 10500 * 60 * 2, 3 );
	//RankingManager::getInstance()->PostLocalStoryScore( "Jimmy", 36021786, 5, 10600 * 60 * 2, 0 );
	//RankingManager::getInstance()->PostLocalStoryScore( "James", 61006569, 5, 341000 * 60 * 2, 1 );

	std::list<ScoreData> score_list = RankingManager::getInstance()->GetLocalStoryRanking( 10 );

	int i = 0;
	std::list<ScoreData>::iterator itr = score_list.begin();
	std::list<ScoreData>::iterator end = score_list.end();
	for (; itr != end && (i < MAX_RANKING_NUM); ++itr, ++i)
	{
		mRankingNameplate[i].initialize(i + 1, (*itr).szName, (*itr).nRank, (*itr).unTime, (*itr).unScore);
		mRankingNameplate[i].setPosition(44, 52 * i + 35);
	}
    
    mPhase = 0;
    mFrameCount = 0;
	Framework.getInterface()->resetDelayTime();
#endif
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneRanking::onUpdate()
{
#if MIGRATION
#else
    switch ( mPhase )
    {
        /////////////////////// フェードインフェーズ
        case 0:
        {
			mBGWhiteSprite.setOpacity( ( mFrameCount / 30.0 ) * 0.8 );

			for (int i = 0; i < MAX_RANKING_NUM; ++i)
			{
				float op = ( (mFrameCount - i * 2) / 15.0 );
				mRankingNameplate[i].setOpacity(LMath::limit<float>(op, 0, 1));
			}

            if ( mFrameCount >= 30 )
            {
                mPhase = 1;
                mFrameCount = 0;
            }
            break;
        }

        /////////////////////// 仮
        case 1:
        {
            // 終了
            if ( Input.isOnTrigger( LN_BUTTON_A ) || Input.isOnTrigger( LN_BUTTON_B ) )
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
			mBGWhiteSprite.setOpacity( 0.8 - ( mFrameCount / 30.0 ) * 0.8 );
			for (int i = 0; i < MAX_RANKING_NUM; ++i)
			{
				float op = ( (mFrameCount - i * 2) / 15.0 );
				mRankingNameplate[i].setOpacity(1.0 - LMath::limit<float>(op, 0, 1));
			}

            if ( mFrameCount >= 30 )
            {
                this->returnScene();
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
void SceneRanking::onTerminate()
{
}

//=============================================================================
//								end of file
//=============================================================================