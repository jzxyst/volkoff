//=============================================================================
//【 GuideNamePlate 】
//=============================================================================

#include "GameFrontendManager.h"
#include "GuideNamePlate.h"
#include "../Game/GameManager.h"
#include "../Object/GameObject.h"
#include "../Object/Player.h"


//=============================================================================
// ■ GuideNamePlate クラス
//=============================================================================

//#define GUIDE_UNDER

    //---------------------------------------------------------------------
    // ● コンストラクタ
    //---------------------------------------------------------------------
    GuideNamePlate::GuideNamePlate()
        : mIsNearPlayer ( false )
    {
        GameFrontendManager::getInstance()->addGuidNamePlate( this );
    }

    //---------------------------------------------------------------------
    // ● デストラクタ
    //---------------------------------------------------------------------
    GuideNamePlate::~GuideNamePlate()
    {
        GameFrontendManager::getInstance()->removeGuidNamePlate( this );
    }

    //---------------------------------------------------------------------
    // ● 初期化
    //---------------------------------------------------------------------
    void GuideNamePlate::initialize( GameObject* object_, int arrow_color_, float ox_, float oy_ )
    {
        mGameObject = object_;

        LTexture tex = Assets::LoadTexture( "Data/Graphics/Frontend/Frontend_1.png" );

        // フレーム
        mFrameSprite = Sprite2D::Create(  tex);
        mFrameSprite->SetSrcRect( 0, 168 + 16 * arrow_color_, 64, 13 );
        mFrameSprite->SetVisible( false );

        // 矢印
        mArrowSprite = Sprite2D::Create( tex );
        mArrowSprite->SetSrcRect( 16 * arrow_color_, 128, 16, 8 );
        mArrowSprite->SetCenter( 6, 7 );
        mArrowSprite->SetVisible( false );

        // 名前
        LFont font = GameFrontendManager::getInstance()->getGuidNamePlateFont();
		
        Size size = font->MeasureRenderSize( mGameObject->getName() );

        mNameTextTexture = Texture2D::Create( size.width , 20 );
		mNameTextTexture->DrawText(mGameObject->getName(), Rect(0, 0, size.width, size.height), font, Color32::White, Color32::Black, 0, TextAlignment::Left);

        mNameTextSprite = Sprite2D::Create( mNameTextTexture );
        mNameTextSprite->SetVisible( false );
		mNameTextSprite->SetSrcRect(0, 0, size.width, size.height);

        mOffsetPos.Set( ox_, oy_, 0 );
        


#ifdef GUIDE_UNDER

        mArrowSprite->SetSrcRect( 32 * arrow_color_, 128 + 16, 16, 8 );
        mOffsetPos->Set( ox_, -96, 0 );
#endif
    }

    /*
    //---------------------------------------------------------------------
    // ● フェードイン開始
    //---------------------------------------------------------------------
    void GuideNamePlate::startFadein()
    {
        mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 1.0f, 20.0 );
    }

    //---------------------------------------------------------------------
    // ● フェードアウト開始
    //---------------------------------------------------------------------
    void GuideNamePlate::startFadeout()
    {
        mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 0.0f, 20.0 );
    }
    */

    //---------------------------------------------------------------------
    // ● フレーム更新
    //---------------------------------------------------------------------
    void GuideNamePlate::update()
    {
		const LVector3& player_pos = GameManager::getInstance()->getPlayer()->getPosition();
		const LVector3& object_pos = mGameObject->getPosition();

		//if ( ( player_pos - object_pos ).getLength() < 200 )

		float length = (player_pos - object_pos).GetLengthSquared();

		// プレイヤーと近ければ表示
		if (!mIsNearPlayer && length < 60000)
		{
			mIsNearPlayer = true;

			mFadeOpacity.Start(mFadeOpacity.GetValue(), 1.0f, 20);

			mArrowSprite->SetVisible(true);
			mFrameSprite->SetVisible(true);
			mNameTextSprite->SetVisible(true);

#ifdef GUIDE_UNDER

			mNameTextSprite->SetPosition(pos_2d.x, pos_2d.y + 10);
#endif

		}
		// プレイヤーから離れていれば非表示
		else if (mIsNearPlayer && length >= 60000)
		{
			mIsNearPlayer = false;
			mFadeOpacity.Start(mFadeOpacity.GetValue(), 0.0f, 20);


		}

		float op = GameFrontendManager::getInstance()->getGlobalFadeOpacity() * mFadeOpacity.GetValue();

		mArrowSprite->SetOpacity(mFadeOpacity.GetValue());  // 矢印だけは Global が透明でも表示する
		mFrameSprite->SetOpacity(op);
		mNameTextSprite->SetOpacity(op);




		mFadeOpacity.AdvanceTime(1.0);


		// 完全にフェードアウトした場合は非表示にする
		if (mFadeOpacity.IsFinished() && mFadeOpacity.GetValue() == 0.0f)
		{
			mArrowSprite->SetVisible(false);
			mFrameSprite->SetVisible(false);
			mNameTextSprite->SetVisible(false);
		}
		else
		{


			// オブジェクトの座標をスクリーン座標に変換
			LVector3 pos_2d = Accessor::Main3Camera->WorldToViewportPoint((object_pos + mOffsetPos));

			_setPosition(pos_2d);
		}
    }

    //---------------------------------------------------------------------
    // ● 位置の設定 (update() から呼ばれる。吹き出しの先っぽで指定する。)
    //---------------------------------------------------------------------
    void GuideNamePlate::_setPosition( const LVector3& pos_ )
    {
        mArrowSprite->SetPosition( pos_.x, pos_.y, 100 );
        



        // フレームの左上
        float x = pos_.x  - mFrameSprite->GetSrcRect().width / 2;
        
        mFrameSprite->SetPosition( x, pos_.y - 24, 100 );
        

        x = pos_.x  - mNameTextSprite->GetSrcRect().width / 2;
        mNameTextSprite->SetPosition( x, pos_.y - 23, 100 );
        

        
    }


//=============================================================================
//								end of file
//=============================================================================