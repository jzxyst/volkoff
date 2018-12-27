//=============================================================================
//【 SceneCredit 】
//=============================================================================

#include "SceneTitle.h"
#include "SceneCredit.h"

//=============================================================================
// ■ SceneCredit クラス
//=============================================================================

// プログラマ
const char* PROGRAM[] =
{
    "impmlv", "2", "3", "4", NULL
};         

// グラフィック
const char* GRAPHICS[] =
{
    "impmlv", "2", "3", "", NULL
};

// 音楽素材
const char* SOUND_MAT[] =
{
    "1", "URL", "", "2", "URL", "", NULL
};

// スペシャルサンクス
const char* THANKS[] =
{
    "1", "2", "3", "", NULL
};

//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneCredit::onStart()
{
    printf( "-------------------------------------------------\n" );
    printf( " ▼ スタッフロール\n" );
    printf( "-------------------------------------------------\n" );

    
    mBGBlackSprite = LSprite::create( ln::Assets::loadTexture( "Data/Graphics/Frontend/Logo_1.png" ) );
    mBGBlackSprite->setSourceRect( 0, 0, 32, 32 );
    mBGBlackSprite->setScale( 20 );

    Accessor::ToneLayer->play(ToneF(0, 0, 0, 0), 1.0f);


    mPhase = 0;
    mFrameCount = 0;
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneCredit::onUpdate()
{
    switch ( mPhase )
    {
        /////////////////////// フェードインフェーズ
        case 0:
        {
            if ( mFrameCount >= 60 )
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
            //if ( Input.isOnTrigger( LN_BUTTON_A ) )
            {
                Accessor::ToneLayer->play(ToneF(1, 1, 1, 0), 3.0f);
                mPhase = -1;
                mFrameCount = 0;
                return;
            }
            break;
        }

        /////////////////////// フェードアウトフェーズ
        case -1:
        {
            if ( mFrameCount >= 200 )
            {
                this->changeScene( NEW SceneTitle() );
                return;
            }
            break;
        }
    }

    ++mFrameCount;
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneCredit::onTerminate()
{
}

//=============================================================================
//								end of file
//=============================================================================