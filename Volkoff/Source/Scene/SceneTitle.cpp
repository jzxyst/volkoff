//=============================================================================
/*! 
    @addtogroup 
    @file       SceneTitle.cpp
    @brief      
    
    タイトルのシーンの実装
    
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

#include "stdafx.h"
#include "../Frontend/PointCursor.h"
#include "SceneTitle.h"
#include "SceneRanking.h"
#include "../Game/GameManager.h"
#include "../Frontend/GameFrontendManager.h"
#include "../Frontend/PointCursor.h"
#include "SceneGame.h"
#include "SceneConnection.h"

static const float COMMAND_POS_X = 420;
static const float COMMAND_POS_Y = 290;
static const int MAX_END_FRAME_COUNT = 120;
static const char* START_DESC_SE = "Data/Sound/SE/cursor21.wav";
static const char* CURSOR_SE = "Data/Sound/SE/kachi38.wav";
static const char* TITLE_BGM = "Data/Sound/BGM/monochrome.ogg";//"H:/DataSource/yumenoato.mp3";//

static const char* gDescContentTitles_1[] =
{
    "GameStart",
    "Ranking",
    "Exit"
};

static const char* gDescContents_1[] =
{
    "ゲームを始めます。\n鍵を探しながらステージを進み、\n最終ステージのボスを倒すと\nゲームクリアです。\n",
    "これまでのランキングを\n確認します。",
    "ゲームを終了します。"
};

static const char* gDescContentTitles_2[] =
{
    "Easy",
    "Normal",
    "Hard",
    "Valfirle"
};

static const char* gDescContents_2[] =
{
    "初心者向けの難易度で始めます。\n敵の攻撃が少し弱くなります。\n",
    "ふつうの難易度で始めます。",
    "上級者向けの難易度で始めます。\n敵の攻撃が激しくなり、\n罠の数も増えます。",
    "神話を体験できます。"

};
//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
SceneTitle::SceneTitle()
    : mStep         ( 0 )
    , mFrameCount   ( 0 )
    , mPointCursor  ( NULL )
{

}


//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneTitle::onStart()
{
    printf( "-------------------------------------------------\n" );
    printf( " ▼ タイトル画面\n" );
    printf( "-------------------------------------------------\n" );
    printf( "Z > ゲーム開始\n" );
    printf( "X > ネット接続\n" );

	// 背景色
	Viewport::GetMainWindowViewport()->SetBackgroundColor(Color::White);
	Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 0.5);

	mRandomSprite = Sprite2D::Create("Data/Graphics/Frontend/Random_1.png");
	mRandomSprite->SetCenter(256, 32);
	mRandomSprite->SetPosition(320, 160);

	LTexture tex = Assets::LoadTexture("Data/Graphics/Frontend/Title_1.png");


	// テキスト下のフレーム
	mTitleFrameSprite = Sprite2D::Create(tex);
	mTitleFrameSprite->SetSrcRect(0, 128, 512, 64);
	mTitleFrameSprite->SetCenter(256, 32);
	mTitleFrameSprite->SetPosition(320, 160);



	// タイトルテキスト
	mTitleTextSprite = Sprite2D::Create(tex);
	mTitleTextSprite->SetCenter(196, 32);
	mTitleTextSprite->SetSrcRect(0, 0, 392, 64);
	mTitleTextSprite->SetPosition(320, 160);

	// フレームしたの文字
	mTitleSubTextSprite = Sprite2D::Create(tex);
	mTitleSubTextSprite->SetCenter(216, 0);
	mTitleSubTextSprite->SetSrcRect(0, 192, 432, 16);
	mTitleSubTextSprite->SetPosition(320, 192);

	// 「PressAnyKey」
	mPressAnyKeySprite = Sprite2D::Create(tex);
	mPressAnyKeySprite->SetSrcRect(0, 224, 176, 32);
	mPressAnyKeySprite->SetCenter(176 / 2, 16);
	mPressAnyKeySprite->SetPosition(320, 350);

	// エフェクト用
	mTitleEffectSprite = Sprite2D::Create(tex);
	mTitleEffectSprite->SetSrcRect(0, 64, 512, 64);
	mTitleEffectSprite->SetCenter(256, 42);
	mTitleEffectSprite->SetPosition(320, 170);
	mTitleEffectSprite->SetOpacity(0);

	// 上下の字幕スーパー
	for (int i = 0; i < 2; ++i)
	{
		mSuperSprite[i] = Sprite2D::Create(tex);
		mSuperSprite[i]->SetSrcRect(128, 496, 256, 16);
		mSuperSprite[i]->SetScale(4, 2);
		mSuperSprite[i]->SetVisible(false);
	}
	// コマンド
	for (int i = 0; i < 4; ++i)
	{
		mCommandSprite[i] = Sprite2D::Create(tex);
		mCommandSprite[i]->SetVisible(false);
	}

	// 説明ウィンドウ
	mDescWindowSprite = Sprite2D::Create(tex);
	mDescWindowSprite->SetPosition(-500, 0);       // 面倒なので画面外で隠す
	mDescWindowSprite->SetSrcRect(272, 224, 240, 144);

	mDescContents = Texture2D::Create(240, 144);
	mDescContentsSprite = Sprite2D::Create(mDescContents);
	mDescContentsSprite->SetPosition(-500, 0);     // 面倒なので画面外で隠す


	mDescTitleFont = Font::Create();
	mDescTitleFont->SetSize(12);
	//mDescTitleFont->SetColor(0, 0, 0, 1);
	mDescTitleFont->SetAntiAlias(true);

	mDescTitleFont = Font::Create();
	mDescTitleFont->SetSize(12);
	//mDescTitleFont->SetColor(0, 0, 0, 1);
	mDescTitleFont->SetAntiAlias(true);

	FontPtr desc_text = Font::Create();
	desc_text->SetSize(15);
	//desc_text->SetColor(0, 0, 0, 1);
	desc_text->SetAntiAlias(true);
	mFormatText.setFont(desc_text);
	mFormatText.setDrawRect(Rect(12, 20, 224, 120));

	// アルファ値用往復値
	mRoundTripValue.AddKeyFrame(0, 0.2f);
	mRoundTripValue.AddKeyFrame(60, 1.0f);
	mRoundTripValue.AddKeyFrame(120, 0.2f);
	mRoundTripValue.SetWrapMode(WrapMode_Loop);
	mRoundTripValue.SetTime(0.0);

	// コマンドのフェードインX座標
	mCommandFadeInX.AddKeyFrame(0, 32, InterpolationMode_CatmullRom);
	mCommandFadeInX.AddKeyFrame(30, 0, InterpolationMode_CatmullRom);
	mCommandFadeInX.SetTime(0.0);
	//mCommandFadeInX.setTimeTickPerSec(1.0f);

	// コマンドのフェードイン不透明度;
	mCommandFadeInOpacity.AddKeyFrame(0, 0.0f);
	mCommandFadeInOpacity.AddKeyFrame(15, 0.5f);
	mCommandFadeInOpacity.AddKeyFrame(30, 1.0f);
	mCommandFadeInOpacity.SetTime(0.0);
	//mCommandFadeInOpacity.setTimeTickPerSec(1.0f);

	mPointCursor = LN_NEW PointCursor();

    mStep = 0;
    mFrameCount = 0;
    mEntryedStep = 0;
    mWindowFadeCount = 0;
    mEndFrameCount = 0;

	GameAudio::PlayBGM(TITLE_BGM, 0.80);
	Engine::ResetFrameDelay();
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneTitle::onUpdate()
{
	mRandomSprite->SetSrcRect(mFrameCount, mFrameCount, 512, 64);

	mPointCursor->update();

	// 終了中？
	if (mEndFrameCount > 0)
	{
		--mEndFrameCount;

		// 字幕のフェードアウト
		int t = MAX_END_FRAME_COUNT - mEndFrameCount;
		mSuperSprite[0]->SetPosition(0, -t * 4);
		mSuperSprite[1]->SetPosition(0, 448 + t * 6);

		// ウィンドウ・コマンドのフェードアウト
		t = mEndFrameCount - (MAX_END_FRAME_COUNT - 20);
		mCommandFadeInOpacity.SetTime(t);

		mDescWindowSprite->SetOpacity(mCommandFadeInOpacity.GetValue());
		mDescContentsSprite->SetOpacity(mCommandFadeInOpacity.GetValue());

		// 拡大エフェクト
		float op = std::min(MAX_END_FRAME_COUNT - mEndFrameCount, 20);
		mTitleEffectSprite->SetOpacity(1.0f - op / 20);
		mTitleEffectSprite->SetScale(op / 100 + 1);

		for (int i = 0; i < 4; ++i)
		{
			mCommandSprite[i]->SetOpacity(mCommandFadeInOpacity.GetValue());
		}

		// 全体フェードアウト
		if (mEndFrameCount == 60)
		{
			Accessor::ToneLayer->ChangeTone(ToneF(1, 1, 1, 0), 1.0);
		}


		if (mEndFrameCount == 0)
		{
			// 親として初期化した後、ゲーム画面に移動する
			GameManager::getInstance()->initializeParent();
			GameManager::getInstance()->setRank(mSelectIndex);
			LGameScene::changeScene(NEW SceneGame());
		}


	}


	switch (mStep)
	{
		/////////////////////// Press Any Key
		case 0:
		{
			mRoundTripValue.SetTime((double)mFrameCount);

			mPressAnyKeySprite->SetOpacity(mRoundTripValue.GetValue());


			if (Input::IsTriggered(InputButtons::Any))
			{
				mStep = 1;
				mFrameCount = 0;
				mEntryedStep = 1;
				_startShowCommand(0);

				mSelectIndex = 0;

				mWindowFadeCount = 40;

				GameAudio::PlaySE("Data/Sound/SE/cursor21.wav", 0.40, 1.00);
			}

			break;
		}
		/////////////////////// モード選択
		case 1:
		{
			if (mFrameCount == 20 && mWindowFadeCount > 10) // mWindowFadeCount > 30 は、step1 0 から来たという意味
			{
				_setPointCursorIndex(mSelectIndex);
			}
			if (mFrameCount >= 20 && mFrameCount <= 60)
			{
				int t = mFrameCount - 20;
				for (int i = 0; i < 3; ++i)
				{
					mCommandFadeInX.SetTime(static_cast< double >(t - 5 * i));
					mCommandSprite[i]->SetPosition(COMMAND_POS_X + mCommandFadeInX.GetValue(), COMMAND_POS_Y + 32 * i);

					mCommandFadeInOpacity.SetTime(static_cast< double >(t - 5 * i));
					mCommandSprite[i]->SetOpacity(mCommandFadeInOpacity.GetValue());
				}
			}

			// 決定ボタン
			if (Input::IsTriggered(LN_BUTTON_A))
			{
				switch (mSelectIndex)
				{
				case 0:
					mSelectIndex = 1;
					break;
				case 1:
					// ランキング
					this->callScene(LN_NEW SceneRanking());
					GameAudio::PlaySE(CURSOR_SE, 0.80);
					return;
				case 2:
					// 終了
					Engine::Exit();
					break;
				}

				mStep = 2;
				mFrameCount = 0;
				_startShowCommand(1);

				_setPointCursorIndex(mSelectIndex);
				GameAudio::PlaySE(CURSOR_SE, 0.80);
				return;
			}

			// ↑
			if (Input::IsRepeated(LN_BUTTON_UP))
			{
				--mSelectIndex;
				if (mSelectIndex < 0)
				{
					mSelectIndex = 2;
				}
				_setPointCursorIndex(mSelectIndex);
				GameAudio::PlaySE(CURSOR_SE, 0.80);
				return;
			}
			// ↓
			if (Input::IsRepeated(LN_BUTTON_DOWN))
			{
				++mSelectIndex;
				if (mSelectIndex > 2)
				{
					mSelectIndex = 0;
				}
				_setPointCursorIndex(mSelectIndex);
				GameAudio::PlaySE(CURSOR_SE, 0.80);
				return;
			}


			break;
		}

		/////////////////////// 難易度選択
		case 2:
		{
			if (mFrameCount <= 50)
			{
				for (int i = 0; i < 4; ++i)
				{
					mCommandFadeInX.SetTime(static_cast< double >(mFrameCount - 5 * i));
					mCommandSprite[i]->SetPosition(COMMAND_POS_X + mCommandFadeInX.GetValue(), COMMAND_POS_Y + 32 * i);

					mCommandFadeInOpacity.SetTime(static_cast< double >(mFrameCount - 5 * i));
					mCommandSprite[i]->SetOpacity(mCommandFadeInOpacity.GetValue());
				}
			}

			// 決定
			if (Input::IsTriggered(LN_BUTTON_A))
			{

				// 終了
				mEndFrameCount = MAX_END_FRAME_COUNT;

				mPointCursor->moveToInit();

				GameAudio::PlaySE("Data/Sound/SE/cursor21.wav", 0.80, 1.20);
				GameAudio::StopBGM(3.0);

				// iss#1 ダミーのステップへ移行して繰り返し決定ボタン押せないようにする
				mStep = 4;
			}

			// キャンセル
			if (Input::IsTriggered(LN_BUTTON_B))
			{
				mStep = 1;
				mFrameCount = 0;
				_startShowCommand(0);
				mSelectIndex = 0;
				_setPointCursorIndex(mSelectIndex);
			}

			// ↑
			if (Input::IsRepeated(LN_BUTTON_UP))
			{
				--mSelectIndex;
				if (mSelectIndex < 0)
				{
					mSelectIndex = 3;
				}
				_setPointCursorIndex(mSelectIndex);
				GameAudio::PlaySE(CURSOR_SE, 0.80);
			}
			// ↓
			if (Input::IsRepeated(LN_BUTTON_DOWN))
			{
				++mSelectIndex;
				if (mSelectIndex > 3)
				{
					mSelectIndex = 0;
				}
				_setPointCursorIndex(mSelectIndex);
				GameAudio::PlaySE(CURSOR_SE, 0.80);
			}
			break;
		}
	};



	if (mEntryedStep == 1)
	{
		if (mPressAnyKeySprite->IsVisible() && mFrameCount <= 10)
		{
			mPressAnyKeySprite->SetScale(mFrameCount / 4.0f + 1.0f, (10.0f - mFrameCount) / 10.0f);
			if (mFrameCount == 10)
			{
				mPressAnyKeySprite->SetVisible(false);
				mEntryedStep = 2;
			}
		}

		if (mFrameCount <= 8)
		{
			mSuperSprite[0]->SetVisible(true);
			mSuperSprite[1]->SetVisible(true);
			mSuperSprite[0]->SetPosition(0, -32.0f + (float)mFrameCount * 4);
			mSuperSprite[1]->SetPosition(0, 480.0f - (float)mFrameCount * 4);
		}
	}

	// ウィンドウのﾌｪｰﾄﾞｲﾝ中
	if (mWindowFadeCount > 0)
	{
		--mWindowFadeCount;

		if (mWindowFadeCount <= 30)
		{
			double t = static_cast< double >(30 - mWindowFadeCount);

			// コマンド用のアニメを使いまわす
			mCommandFadeInX.SetTime(t);
			mCommandFadeInOpacity.SetTime(t);

			mDescWindowSprite->SetPosition(60 - mCommandFadeInX.GetValue(), 280);
			mDescWindowSprite->SetOpacity(mCommandFadeInOpacity.GetValue());

			mDescContentsSprite->SetPosition(60 - mCommandFadeInX.GetValue(), 280);
			mDescContentsSprite->SetOpacity(mCommandFadeInOpacity.GetValue());
		}
	}


	// 説明文描画中
	if (!mFormatText.isFinished())
	{
		mFormatText.update();

		LNFormatTextDrawData data;
		while (mFormatText.getNextDrawData(&data))
		{
			mDescContents->DrawText(StringRef(data.Text, data.Length), data.Rect, data.Font, Color32::Black, Color32::White, 0, TextAlignment::Left);
		}
	}

	/*
	if ( Input.isOnTrigger( LN_BUTTON_A ) )
	{
	// 親として初期化した後、ゲーム画面に移動する
	GameManager::getInstance()->initializeParent();

	LGameScene::changeScene( NEW SceneGame() );
	return;
	}


	if ( Input.isOnTrigger( LN_BUTTON_B ) )
	{
	LGameScene::changeScene( NEW SceneConnection() );
	return;
	}
	*/

	

	++mFrameCount;
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneTitle::onTerminate()
{
	LN_SAFE_DELETE(mPointCursor);
	Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 0.5);
}

//---------------------------------------------------------------------
// ● コマンド項目の表示開始
//---------------------------------------------------------------------
void SceneTitle::_startShowCommand( int type_ )
{
    if ( type_ == 0 )
    {
        for ( int i = 0; i < 3; ++i )
        {
            mCommandSprite[ i ]->SetSrcRect( 0, 256 + i * 32, 128, 32 );
            mCommandSprite[ i ]->SetVisible( true );
            mCommandSprite[ i ]->SetOpacity( 0.0f );
        }
        mCommandSprite[ 3 ]->SetVisible( false );
    }
    else
    {
        for ( int i = 0; i < 4; ++i )
        {
            mCommandSprite[ i ]->SetSrcRect( 128, 256 + i * 32, 128, 32 );
            mCommandSprite[ i ]->SetVisible( true );
            mCommandSprite[ i ]->SetOpacity( 0.0f );
        }
    }
}

//---------------------------------------------------------------------
// ● 矢印の位置設定
//---------------------------------------------------------------------
void SceneTitle::_setPointCursorIndex( int index_ )
{
	//mSelectIndex = index_;
	mPointCursor->moveTo((int)COMMAND_POS_X - 38, (int)COMMAND_POS_Y + mSelectIndex * 32 + 16);

	mDescContents->Clear(Color32(0, 0, 0, 0));

	// モード選択中
	if (mStep == 1)
	{
		mDescContents->DrawText(gDescContentTitles_1[mSelectIndex], Rect(8, 2, 256, 256), mDescTitleFont, Color32::Black, Color32::White, 0, TextAlignment::Left);
		mFormatText.setText(gDescContents_1[mSelectIndex]);
		mFormatText.build();
	}
	// 難易度選択中
	else if (mStep == 2)
	{
		mDescContents->DrawText(gDescContentTitles_2[mSelectIndex], Rect(8, 2, 256, 256), mDescTitleFont, Color32::Black, Color32::White, 0, TextAlignment::Left);
		mFormatText.setText(gDescContents_2[mSelectIndex]);
		mFormatText.build();
	}
}

//=============================================================================
//								End of File
//=============================================================================