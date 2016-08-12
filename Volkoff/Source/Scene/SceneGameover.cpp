//=============================================================================
//【 SceneGameover 】
//=============================================================================

#include "stdafx.h"
#include "../Game/GameManager.h"
#include "../Map/MapManager.h"
#include "../Frontend/PointCursor.h"
#include "SceneGameover.h"
#include "SceneGame.h"
#include "SceneTitle.h"

//=============================================================================
// ■ SceneGameover クラス
//=============================================================================


static const int COMMAND_POS_X = 420;
static const int COMMAND_POS_Y = 290;
    
//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneGameover::onStart()
{
    LTexture tex = Texture2D::Create( 32, 32 );
    tex->Clear( Color32( 0, 0, 0 ) );
    mBlindSprite = Sprite2D::Create( tex );
    mBlindSprite->SetScale( 20 );
    mBlindSprite2 = Sprite2D::Create( tex );
    mBlindSprite2->SetScale( 20 );
    mBlindSprite2->SetPosition( 0, 240 );
    mBlindSprite2->SetOpacity( 0 );


    // 説明ウィンドウ
    LTexture fe_tex = Assets::LoadTexture( "Data/Graphics/Frontend/Frontend_1.png" );
    mDescWindowSprite = Sprite2D::Create( fe_tex );
    mDescWindowSprite->SetPosition( 60, 280 );
    mDescWindowSprite->SetSrcRect( 272, 368, 240, 144 );
    mDescWindowSprite->SetOpacity( 0 );
    mDescContents = Texture2D::Create( 240, 144 );
    mDescContentsSprite = Sprite2D::Create( mDescContents );
    mDescContentsSprite->SetPosition( 60, 280 );
    mDescContentsSprite->SetOpacity( 0 );

	mDescTitleFont = Font::Create();
    mDescTitleFont->SetSize( 12 );

    // コマンド
    mCommandSprite[ 0 ] = Sprite2D::Create( fe_tex );
    mCommandSprite[ 0 ]->SetSrcRect( 272, 304, 128, 32 );
    mCommandSprite[ 0 ]->SetPosition( COMMAND_POS_X, COMMAND_POS_Y );
    mCommandSprite[ 0 ]->SetOpacity( 0 );
    mCommandSprite[ 1 ] = Sprite2D::Create( fe_tex );
    mCommandSprite[ 1 ]->SetSrcRect( 272, 336, 128, 32 );
    mCommandSprite[ 1 ]->SetPosition( COMMAND_POS_X, COMMAND_POS_Y + 32 );
    mCommandSprite[ 1 ]->SetOpacity( 0 );

    // 制御文字列描画クラス
    LFont desc_text = Font::Create();
    desc_text->SetSize( 15 );
    mFormatText.setFont( desc_text );
    mFormatText.setDrawRect( LRect( 12, 20, 224, 120 ) );

    // GameOver
    mLogoSprite = Sprite2D::Create( fe_tex );
    mLogoSprite->SetSrcRect( 160, 224, 352, 64 );
    mLogoSprite->SetPosition( 320, 128 );
    mLogoSprite->SetCenter( 352 / 2, 64 / 2 );
    mLogoSprite->SetOpacity( 0 );

    // カーソル
    mPointCursor = NEW PointCursor();

    // BGM フェードアウト
    GameAudio::StopBGM( 5.0f );

    
    mStep = 0;
    mFrameCount = 0;
    mSelectIndex = 0;

    
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneGameover::onUpdate()
{
    mPointCursor->update();

    // 説明文描画中
    if ( !mFormatText.isFinished() )
    {
        mFormatText.update();
        LNFormatTextDrawData data;
        while ( mFormatText.getNextDrawData( &data ) )
        {
			mDescContents->DrawText(StringRef(data.Text, data.Length), data.Rect, data.Font, Color32::White, Color32::Black, 0, TextAlignment::Left);
        }
    }

    switch ( mStep )
    {
        /////////////////////// ブラインド中
        case 0:
        {
            mBlindSprite->SetOpacity( static_cast< float >( mFrameCount ) / 180 );
            ++mFrameCount;
            if ( mFrameCount == 120 )
            {
                mStep = 1;
                mFrameCount = 0;
                mLogoFadeValue.Start( 0.0f, 1.0f, 1.0f );
            }
            break;
        }
        /////////////////////// GameOver フェードイン中
        case 1:
        {
            mLogoFadeValue.AdvanceTime( 0.016f );
            mLogoSprite->SetOpacity( mLogoFadeValue.GetValue() );

            float y = ( 1.0f - mLogoFadeValue.GetValue() ) * 32 + 128;
            mLogoSprite->SetPosition( 320, y );

            
            if ( mFrameCount == 60 )
            {
                mStep = 2;
                mFrameCount = 0;
                mFadeValue.Start( 0.0f, 1.0f, 30.0f );
                _onSelectIndex();
            }
            ++mFrameCount;
            break;
        }
        /////////////////////// コンテンツフェードイン中
        case 2:
        {
            mFadeValue.AdvanceTime( 1.0f );

            float op = mFadeValue.GetValue();
            mDescWindowSprite->SetOpacity( op );
            mDescContentsSprite->SetOpacity( op );
            mCommandSprite[ 0 ]->SetOpacity( op );
            mCommandSprite[ 1 ]->SetOpacity( op );
            mBlindSprite2->SetOpacity( op / 2 );

            ++mFrameCount;
            if ( mFrameCount == 60 )
            {
                mStep = 3;
                mFrameCount = 0;
            }
            break;
        }
        /////////////////////// コンテンツ選択中
        case 3:
        {
            // 決定
            if ( Input::IsTriggered( LN_BUTTON_A ) )
            {
                mPointCursor->moveToInit();
                mStep = 4;
                mFrameCount = 0;
				Accessor::ToneLayer->ChangeTone(ToneF(-1, -1, -1, 0), 1.0f);
            }

            // ↑
            if ( Input::IsRepeated( LN_BUTTON_UP ) )
            {
                --mSelectIndex;
                if ( mSelectIndex < 0 )
                {
                    mSelectIndex = 1;
                }
                _onSelectIndex();
            }
            // ↓
            if ( Input::IsRepeated( LN_BUTTON_DOWN ) )
            {
                ++mSelectIndex;
                if ( mSelectIndex > 1 )
                {
                    mSelectIndex = 0;
                }
                _onSelectIndex();
            }
            break;
        }
        /////////////////////// 終了中
        case 4:
        {
            if ( mFrameCount == 60 )
            {
                if ( mSelectIndex == 0 )
                {

                    // 仮
                    //Audio.playBGM("Data/Sound/BGM/sol_battle014_xp.mid",60);

					if ( MapManager::getInstance()->getMapID() != 7 )
					{

						GameAudio::PlayBGM(MAIN_BGM_NAME,0.60);
					}

                    GameManager::getInstance()->reset();
                    this->returnScene();
                }
                else
                {
                    GameManager::getInstance()->finalize();
                    this->changeScene( NEW SceneTitle() );
                }
            }
            ++mFrameCount;
            break;
        }
    }

	// 以前はこの関数 (SceneGameover::onUpdate()) の先頭で親シーンの onUpdate() を呼び出していた。
	// しかし、コンティニュー時に現在のマップを再構築した後に onUpdate() が呼ばれなかったため、
	// 古いオブジェクトたちの解放が1フレーム遅れていた。(必要なくなったオブジェクトは onUpdate() で開放しているため)
	// 結果、一瞬だけ2倍相当のオブジェクトが出現することになり、描画可能なスプライト数を超えてしまった。
    this->getParentScene()->onUpdate();
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneGameover::onTerminate()
{
	Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 1.0f);

    SAFE_DELETE( mPointCursor );
}

//---------------------------------------------------------------------
// ● 選択している項目を変更した
//---------------------------------------------------------------------
void SceneGameover::_onSelectIndex()
{
    mPointCursor->moveTo( COMMAND_POS_X - 38, COMMAND_POS_Y + mSelectIndex * 32 + 16 );

    mDescContents->Clear( Color32( 0, 0, 0, 0 ) );

    if ( mSelectIndex == 0 )
    {
		mDescContents->DrawText("Continue", LRect(8, 2, 256, 256), mDescTitleFont, Color32::White, Color32::Black, 0, TextAlignment::Left);

        mFormatText.setText( "ステージの最初からやり直します。\n\nスコアが 0 にリセットされます。" );
        mFormatText.build();
    }
    else
    {
		mDescContents->DrawText("End", LRect(8, 2, 256, 256), mDescTitleFont, Color32::White, Color32::Black, 0, TextAlignment::Left);

        mFormatText.setText( "タイトル画面に戻ります。" );
        mFormatText.build();
    }
}



//=============================================================================
//								end of file
//=============================================================================