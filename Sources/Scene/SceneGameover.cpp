//=============================================================================
//【 SceneGameover 】
//=============================================================================

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
    LTexture tex = Texture2D::create( 32, 32 );
    tex->clear( Color32( 0, 0, 0 ) );
    mBlindSprite = ln::UISprite::create( tex );
    mBlindSprite->setScale( 20 );
    mBlindSprite2 = ln::UISprite::create( tex );
    mBlindSprite2->setScale( 20 );
    mBlindSprite2->setPosition( 0, 240 );
    mBlindSprite2->setOpacity( 0 );


    // 説明ウィンドウ
    LTexture fe_tex = Assets::loadTexture( "Data/Graphics/Frontend/Frontend_1.png" );
    mDescWindowSprite = ln::UISprite::create( fe_tex );
    mDescWindowSprite->setPosition( 60, 280 );
    mDescWindowSprite->setSourceRect( 272, 368, 240, 144 );
    mDescWindowSprite->setOpacity( 0 );
    mDescContents = Texture2D::create( 240, 144 );
    mDescContentsSprite = ln::UISprite::create( mDescContents );
    mDescContentsSprite->setPosition( 60, 280 );
    mDescContentsSprite->setOpacity( 0 );

	mDescTitleFont = Font::create();
    mDescTitleFont->setSize( 12 );

    // コマンド
    mCommandSprite[ 0 ] = ln::UISprite::create( fe_tex );
    mCommandSprite[ 0 ]->setSourceRect( 272, 304, 128, 32 );
    mCommandSprite[ 0 ]->setPosition( COMMAND_POS_X, COMMAND_POS_Y );
    mCommandSprite[ 0 ]->setOpacity( 0 );
    mCommandSprite[ 1 ] = ln::UISprite::create( fe_tex );
    mCommandSprite[ 1 ]->setSourceRect( 272, 336, 128, 32 );
    mCommandSprite[ 1 ]->setPosition( COMMAND_POS_X, COMMAND_POS_Y + 32 );
    mCommandSprite[ 1 ]->setOpacity( 0 );

    // 制御文字列描画クラス
    Ref<LFont> desc_text = Font::create();
    desc_text->setSize( 15 );
    mFormatText.setFont( desc_text );
    mFormatText.setDrawRect( LRect( 12, 20, 224, 120 ) );

    // GameOver
    mLogoSprite = ln::UISprite::create( fe_tex );
    mLogoSprite->setSourceRect( 160, 224, 352, 64 );
    mLogoSprite->setPosition( 320, 128 );
    mLogoSprite->setCenterPoint( 352 / 2, 64 / 2 );
    mLogoSprite->setOpacity( 0 );

    // カーソル
    mPointCursor = NEW PointCursor();

    // BGM フェードアウト
    GameAudio::stopBGM( 5.0f );

    
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
			mDescContents->drawText(StringRef(data.Text, data.Length), data.Rect, data.Font, Color::White, TextAlignment::Left);
        }
    }

    switch ( mStep )
    {
        /////////////////////// ブラインド中
        case 0:
        {
            mBlindSprite->setOpacity( static_cast< float >( mFrameCount ) / 180 );
            ++mFrameCount;
            if ( mFrameCount == 120 )
            {
                mStep = 1;
                mFrameCount = 0;
                mLogoFadeValue.start( 0.0f, 1.0f, 1.0f );
            }
            break;
        }
        /////////////////////// GameOver フェードイン中
        case 1:
        {
            mLogoFadeValue.advanceTime( 0.016f );
            mLogoSprite->setOpacity( mLogoFadeValue.getValue() );

            float y = ( 1.0f - mLogoFadeValue.getValue() ) * 32 + 128;
            mLogoSprite->setPosition( 320, y );

            
            if ( mFrameCount == 60 )
            {
                mStep = 2;
                mFrameCount = 0;
                mFadeValue.start( 0.0f, 1.0f, 30.0f );
                _onSelectIndex();
            }
            ++mFrameCount;
            break;
        }
        /////////////////////// コンテンツフェードイン中
        case 2:
        {
            mFadeValue.advanceTime( 1.0f );

            float op = mFadeValue.getValue();
            mDescWindowSprite->setOpacity( op );
            mDescContentsSprite->setOpacity( op );
            mCommandSprite[ 0 ]->setOpacity( op );
            mCommandSprite[ 1 ]->setOpacity( op );
            mBlindSprite2->setOpacity( op / 2 );

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
            if ( Input::isTriggered( LN_BUTTON_A ) )
            {
                mPointCursor->moveToInit();
                mStep = 4;
                mFrameCount = 0;
				Accessor::ToneLayer->play(ToneF(-1, -1, -1, 0), 1.0f);
            }

            // ↑
            if ( Input::isRepeated( LN_BUTTON_UP ) )
            {
                --mSelectIndex;
                if ( mSelectIndex < 0 )
                {
                    mSelectIndex = 1;
                }
                _onSelectIndex();
            }
            // ↓
            if ( Input::isRepeated( LN_BUTTON_DOWN ) )
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

						GameAudio::playBGM(MAIN_BGM_NAME,0.60);
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
	Accessor::ToneLayer->play(ToneF(0, 0, 0, 0), 1.0f);

    SAFE_DELETE( mPointCursor );
}

//---------------------------------------------------------------------
// ● 選択している項目を変更した
//---------------------------------------------------------------------
void SceneGameover::_onSelectIndex()
{
    mPointCursor->moveTo( COMMAND_POS_X - 38, COMMAND_POS_Y + mSelectIndex * 32 + 16 );

    mDescContents->clear( Color( 0, 0, 0, 0 ) );

    if ( mSelectIndex == 0 )
    {
		mDescContents->drawText("Continue", LRect(8, 2, 256, 256), mDescTitleFont, Color::White, TextAlignment::Left);

        mFormatText.setText( "ステージの最初からやり直します。\n\nスコアが 0 にリセットされます。" );
        mFormatText.build();
    }
    else
    {
		mDescContents->drawText("End", LRect(8, 2, 256, 256), mDescTitleFont, Color::White, TextAlignment::Left);

        mFormatText.setText( "タイトル画面に戻ります。" );
        mFormatText.build();
    }
}



//=============================================================================
//								end of file
//=============================================================================