//=============================================================================
//【 CharacterNamePlate 】
//=============================================================================

#include "../Object/Character.h"
#include "GameFrontendManager.h"
#include "CharacterNamePlate.h"

//=============================================================================
// ■ CharacterNamePlate クラス
//=============================================================================

    //---------------------------------------------------------------------
    // ● コンストラクタ
    //---------------------------------------------------------------------
    CharacterNamePlate::CharacterNamePlate()
        : mCharacter            ( NULL )
        , mVisibleFrameCount    ( 0 )
        , mFrameWidth           ( 72 )
        , mSrcRectOY            ( 0 )
        , mHPBarMaxWidth        ( 64 )
        , mVisible              ( true )
    {
    }

    //---------------------------------------------------------------------
    // ● デストラクタ
    //---------------------------------------------------------------------
    CharacterNamePlate::~CharacterNamePlate()
    {
    }

    //---------------------------------------------------------------------
    // ● 初期化
    //---------------------------------------------------------------------
    void CharacterNamePlate::initialize( Character* character_ )
    {
        mCharacter = character_;

        // 描画する名前
        const char* name = ( mCharacter->getName() ) ? mCharacter->getName() : "名無しさん！";

        LTexture tex = Assets::loadTexture( "Data/Graphics/Frontend/Frontend_1.png" );
        Ref<LFont> font = GameFrontendManager::getInstance()->getNamePlateFont();

        if ( !font )
        {
            setVisible( false );
            mFrameWidth = 72;
            mSrcRectOY = 0;
            mHPBarMaxWidth = 64;
        }
        else
        {
            // 名前を描画した時の幅によって、ウィンドウサイズを決める
            Size rc = font->MeasureRenderSize(name);
            if ( rc.width > 64 )
            {
                mFrameWidth = 96;
                mSrcRectOY = 48;
                mHPBarMaxWidth = 88;
            }
            else
            {
                mFrameWidth = 72;
                mSrcRectOY = 0;
                mHPBarMaxWidth = 64;
            }
        }



        // 枠
        mFrameSprite = ln::UISprite::create( tex );
        mFrameSprite->setSourceRect( 0, mSrcRectOY, mFrameWidth, 18 );

        // バー
        mHPBarSprite  = ln::UISprite::create( tex );
        mHPBarSprite->setSourceRect( 8, mSrcRectOY + 24, 8, 8 );
        mDieBarSprite = ln::UISprite::create( tex );
        mDieBarSprite->setSourceRect( 8, mSrcRectOY + 24, 8, 8 );

        // 吹き出し
        mBalloonPointSprite = ln::UISprite::create( tex );
        mBalloonPointSprite->setSourceRect( 0, mSrcRectOY + 25, 5, 4 );

        // 名前を描画するテクスチャ
        mNameTextTexture = Texture2D::create( mFrameWidth - 8, 16 );
		mNameTextTexture->DrawText(name, LRect(0, 0, mFrameWidth - 8, 16), font, Color32::White, Color32::White, 0, TextAlignment::Center);
       
        // 名前スプライト
        mNameTextSprite = ln::UISprite::create( mNameTextTexture );
        
        //mNameTextSprite->setSourceRect( 0, 48, 40, 16 );   // 仮

        mHPValue.setInitValue( mCharacter->getLife() );


        // 最初は全部非表示
        mFrameSprite->setVisible( false );
        mBalloonPointSprite->setVisible( false );
        mHPBarSprite->setVisible( false );
        mDieBarSprite->setVisible( false );
        mNameTextSprite->setVisible( false );

        mVisibleFrameCount = 0;
    }

    //---------------------------------------------------------------------
    // ● 可視状態の設定 (false にすると、startShow() が呼ばれても表示しない)
    //---------------------------------------------------------------------
    void CharacterNamePlate::setVisible( bool flag_ )
    {
        mVisible = flag_;
    }

    //---------------------------------------------------------------------
    // ● 表示開始 (攻撃か当たった場合など、表示する場合にこれだけ呼ぶ。あとは勝手にﾌｪｰﾄﾞｱｳﾄする)
    //---------------------------------------------------------------------
    void CharacterNamePlate::startShow()
    {
        if ( mVisible )
        {
            mVisibleFrameCount = 210;
            mFrameSprite->setOpacity( 1.0f );
            mBalloonPointSprite->setOpacity( 1.0f );
            mHPBarSprite->setOpacity( 1.0f );
            mDieBarSprite->setOpacity( 1.0f );
            mNameTextSprite->setOpacity( 1.0f );

            mFrameSprite->setVisible( true );
            mBalloonPointSprite->setVisible( true );
            mHPBarSprite->setVisible( true );
            mDieBarSprite->setVisible( true );
            mNameTextSprite->setVisible( true );

            mHPValue.set( mCharacter->getLife() );

            GameFrontendManager::getInstance()->onShowCharacterNamePlate();

            update();
        }
    }

    //---------------------------------------------------------------------
    // ● フレーム更新
    //---------------------------------------------------------------------
    void CharacterNamePlate::update()
    {
        if ( mVisible && mVisibleFrameCount > 0 )
        {
            

            //-------------------------------------------------
            // HPバー
            if ( !mHPValue.isFinished() )
            {
                mHPValue.update();

                float rate = static_cast< float >( mHPValue.getValue() ) / mCharacter->getMaxLife();
                float w = rate * mHPBarMaxWidth;
                float lv = 0;

                // 残り HP によってバーの色を変える
                if ( rate <= 0.15f )
                {
                    lv = 2;
                }
                else if ( rate <= 0.50f )
                {
                    lv = 1;
                }

                mHPBarSprite->setSourceRect(  0, mSrcRectOY + 32 + lv * 4, w, 4 );
                mDieBarSprite->setSourceRect( w, mSrcRectOY + 44, mHPBarMaxWidth - w, 4 );
            }




            //-------------------------------------------------
            // 位置
            const LMatrix& vp_mat = Accessor::Main3Camera->viewProjectionMatrix();
			LVector3 sc_pos = LVector3::transformCoord(mCharacter->getPosition(), vp_mat);
			
            sc_pos.y *= -1.0f;  // y は下が + なので上下反転
            sc_pos += 1.0f;     // 0.0～2.0 にする
            sc_pos *= 0.5f;     // 0.0～1.0 にする


            // _setPosition に渡す用に一時退避
            LVector3 tpos = sc_pos;

            auto size = Engine::mainViewport()->GetSize();
            sc_pos.x *= size.width;
            sc_pos.y *= size.height;

            // 位置がキャラの足元なので、上の方に移動
            sc_pos.y -= 90.0f;
        

            _setPosition( sc_pos.x, sc_pos.y, tpos );

            

            

            
            


            
            --mVisibleFrameCount;

            // フェードアウト
            if ( mVisibleFrameCount <= 30 )
            {
                float op = 0.033f * mVisibleFrameCount;    // 0.033 = 1/30
                mFrameSprite->setOpacity( op );
                mBalloonPointSprite->setOpacity( op );
                mHPBarSprite->setOpacity( op );
                mDieBarSprite->setOpacity( op );
                mNameTextSprite->setOpacity( op );
            }

            
           
        }
        else
        {
            mFrameSprite->setVisible( false );
            mBalloonPointSprite->setVisible( false );
            mHPBarSprite->setVisible( false );
            mDieBarSprite->setVisible( false );
            mNameTextSprite->setVisible( false );
        }
    }

    //---------------------------------------------------------------------
    // ● 位置の設定 (update() から呼ばれる)
    //---------------------------------------------------------------------
    void CharacterNamePlate::_setPosition( float x_, float y_, const LVector3& screen_pos_ )
    {
        mBalloonPointSprite->setPosition( x_ - 1, y_ - 3 );


        float ox = 62.0f * screen_pos_.x;

        // フレームの左上
        float x = x_ - 1 - ox;
        float y = y_ - 20;

        mFrameSprite->setPosition( x, y );
        mNameTextSprite->setPosition( x + 4, y + 1 );
        mHPBarSprite->setPosition( x + 4, y + 12 );
        mDieBarSprite->setPosition( x + 4 + mHPBarSprite->sourceRect().width, y + 12 );
    }

//=============================================================================
//								end of file
//=============================================================================