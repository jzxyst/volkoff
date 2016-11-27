//=============================================================================
//【 SceneStartup 】
//=============================================================================

#include "stdafx.h"
#include "SceneTitle.h"
#include "SceneStartup.h"


//=============================================================================
// ■ SceneStartup クラス
//=============================================================================

//---------------------------------------------------------------------
// ● 開始処理
//---------------------------------------------------------------------
void SceneStartup::onStart()
{
	// 背景色
	Engine::GetMainViewport()->SetBackgroundColor(Color::Black);

	mLogoSprite = Sprite2D::Create(_T("Data/Graphics/Frontend/Logo_1.png"));

	Texture2DPtr tex = Assets::LoadTexture(_T("Data/Graphics/Frontend/Title_1.png"));

	//mFlashSprite = Sprite2D::Create(tex);
	//mFlashSprite->SetCenter(64, 8, 0);
	//mFlashSprite->SetPosition(Viewport::GetMainWindowViewport()->GetSize().Width, Viewport::GetMainWindowViewport()->GetSize().Height / 2, 0);
	//mFlashSprite->SetSrcRect(0, 496, 128, 16);

	// 文字用
	mTitleSubTextSprite = Sprite2D::Create(Assets::LoadTexture(_T("Data/Graphics/Frontend/Title_1.png")));
	mTitleSubTextSprite->SetPosition(108, 192, 0);
	mTitleSubTextSprite->SetSrcRect(0, 192 + 16, 424, 16);
	mTitleSubTextSprite->SetVisible(false);

	mFlashScale.Start(0, 60, 5);

    mStep = 0;
    mFrameCount = 0;
}

//---------------------------------------------------------------------
// ● フレーム更新
//---------------------------------------------------------------------
void SceneStartup::onUpdate()
{
	switch (mStep)
	{
		/////////////////////// ロゴ表示ステップ
		case 0:
		{
			// 閃光
			//mFlashScale.SetTime(mFrameCount);
			//mFlashSprite->SetScale(mFlashScale.GetValue());

			if (mFrameCount < 20)
			{
				Accessor::BlurLayer->SetBlurStatus(0.9f, Vector2((20 - mFrameCount) * 0.1 - 1.0, 0.0), 1.02);
			}
			else if (mFrameCount == 20)
			{
				Accessor::BlurLayer->SetBlurStatus(0.9f, Vector2((20 - mFrameCount) * 0.1 - 1.0, 0.0), 1.02, 0.2);
			}

			// ボタンが押された場合、150 フレーム目まで飛ばす
			if (Input::IsTriggered(InputButtons::Any) && mFrameCount < 150)
			{
				mFrameCount = 150;
			}
			
			// フェードアウト開始
			if (mFrameCount == 150)
			{
				Accessor::ToneLayer->ChangeTone(ToneF(-1, -1, -1, 0), 0.5);
			}

			// 文字表示へ
			if (mFrameCount >= 200)
			{
				// フェードイン
				Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 0.5);

				Accessor::BlurLayer->SetAmount(0);
				//LLayer::getBGLayer()->blur(0, 0, 1.00, LVector3(0, 0, 0), false);

				mLogoSprite->SetVisible(false);
				mStep = 1;
				mFrameCount = 0;
			}
			break;
		}
		/////////////////////// 文字表示ステップ
		case 1:
		{
			if (mFrameCount >= 50 && mFrameCount <= (50 + 53 * 2)) // 53 文字
			{
				int count = mFrameCount - 50;
				mTitleSubTextSprite->SetVisible(true);
				mTitleSubTextSprite->SetSrcRect(0, 192 + 16, count / 2 * 8, 16);
			}

			// ボタン五された場合、220 フレーム目まで飛ばす
			if (Input::IsTriggered(InputButtons::Any) && mFrameCount < 220)
			{
				mFrameCount = 220;
			}

			// フェードアウト開始
			if (mFrameCount == 220)
			{
				Accessor::ToneLayer->ChangeTone(ToneF(1, 1, 1, 0), 0.4);
			}

			// タイトル画面へ
			if (mFrameCount >= 280)
			{
				LGameScene::changeScene(LN_NEW SceneTitle());
			}
			break;
		}
	}
    
    ++mFrameCount;
}

//---------------------------------------------------------------------
// ● 終了処理
//---------------------------------------------------------------------
void SceneStartup::onTerminate()
{

}



//=============================================================================
//								end of file
//=============================================================================