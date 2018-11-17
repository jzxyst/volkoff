//=============================================================================
//�y CharacterNamePlate �z
//=============================================================================

#include "../Object/Character.h"
#include "GameFrontendManager.h"
#include "CharacterNamePlate.h"

//=============================================================================
// �� CharacterNamePlate �N���X
//=============================================================================

    //---------------------------------------------------------------------
    // �� �R���X�g���N�^
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
    // �� �f�X�g���N�^
    //---------------------------------------------------------------------
    CharacterNamePlate::~CharacterNamePlate()
    {
    }

    //---------------------------------------------------------------------
    // �� ������
    //---------------------------------------------------------------------
    void CharacterNamePlate::initialize( Character* character_ )
    {
        mCharacter = character_;

        // �`�悷�閼�O
        const char* name = ( mCharacter->getName() ) ? mCharacter->getName() : "����������I";

        LTexture tex = Assets::LoadTexture( "Data/Graphics/Frontend/Frontend_1.png" );
        FontPtr font = GameFrontendManager::getInstance()->getNamePlateFont();

        if ( !font )
        {
            setVisible( false );
            mFrameWidth = 72;
            mSrcRectOY = 0;
            mHPBarMaxWidth = 64;
        }
        else
        {
            // ���O��`�悵�����̕��ɂ���āA�E�B���h�E�T�C�Y�����߂�
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



        // �g
        mFrameSprite = Sprite2D::Create( tex );
        mFrameSprite->SetSrcRect( 0, mSrcRectOY, mFrameWidth, 18 );

        // �o�[
        mHPBarSprite  = Sprite2D::Create( tex );
        mHPBarSprite->SetSrcRect( 8, mSrcRectOY + 24, 8, 8 );
        mDieBarSprite = Sprite2D::Create( tex );
        mDieBarSprite->SetSrcRect( 8, mSrcRectOY + 24, 8, 8 );

        // �����o��
        mBalloonPointSprite = Sprite2D::Create( tex );
        mBalloonPointSprite->SetSrcRect( 0, mSrcRectOY + 25, 5, 4 );

        // ���O��`�悷��e�N�X�`��
        mNameTextTexture = Texture2D::Create( mFrameWidth - 8, 16 );
		mNameTextTexture->DrawText(name, LRect(0, 0, mFrameWidth - 8, 16), font, Color32::White, Color32::White, 0, TextAlignment::Center);
       
        // ���O�X�v���C�g
        mNameTextSprite = Sprite2D::Create( mNameTextTexture );
        
        //mNameTextSprite->setSrcRect( 0, 48, 40, 16 );   // ��

        mHPValue.setInitValue( mCharacter->getLife() );


        // �ŏ��͑S����\��
        mFrameSprite->SetVisible( false );
        mBalloonPointSprite->SetVisible( false );
        mHPBarSprite->SetVisible( false );
        mDieBarSprite->SetVisible( false );
        mNameTextSprite->SetVisible( false );

        mVisibleFrameCount = 0;
    }

    //---------------------------------------------------------------------
    // �� ����Ԃ̐ݒ� (false �ɂ���ƁAstartShow() ���Ă΂�Ă��\�����Ȃ�)
    //---------------------------------------------------------------------
    void CharacterNamePlate::setVisible( bool flag_ )
    {
        mVisible = flag_;
    }

    //---------------------------------------------------------------------
    // �� �\���J�n (�U�������������ꍇ�ȂǁA�\������ꍇ�ɂ��ꂾ���ĂԁB���Ƃ͏����̪��ޱ�Ă���)
    //---------------------------------------------------------------------
    void CharacterNamePlate::startShow()
    {
        if ( mVisible )
        {
            mVisibleFrameCount = 210;
            mFrameSprite->SetOpacity( 1.0f );
            mBalloonPointSprite->SetOpacity( 1.0f );
            mHPBarSprite->SetOpacity( 1.0f );
            mDieBarSprite->SetOpacity( 1.0f );
            mNameTextSprite->SetOpacity( 1.0f );

            mFrameSprite->SetVisible( true );
            mBalloonPointSprite->SetVisible( true );
            mHPBarSprite->SetVisible( true );
            mDieBarSprite->SetVisible( true );
            mNameTextSprite->SetVisible( true );

            mHPValue.set( mCharacter->getLife() );

            GameFrontendManager::getInstance()->onShowCharacterNamePlate();

            update();
        }
    }

    //---------------------------------------------------------------------
    // �� �t���[���X�V
    //---------------------------------------------------------------------
    void CharacterNamePlate::update()
    {
        if ( mVisible && mVisibleFrameCount > 0 )
        {
            

            //-------------------------------------------------
            // HP�o�[
            if ( !mHPValue.isFinished() )
            {
                mHPValue.update();

                float rate = static_cast< float >( mHPValue.getValue() ) / mCharacter->getMaxLife();
                float w = rate * mHPBarMaxWidth;
                float lv = 0;

                // �c�� HP �ɂ���ăo�[�̐F��ς���
                if ( rate <= 0.15f )
                {
                    lv = 2;
                }
                else if ( rate <= 0.50f )
                {
                    lv = 1;
                }

                mHPBarSprite->SetSrcRect(  0, mSrcRectOY + 32 + lv * 4, w, 4 );
                mDieBarSprite->SetSrcRect( w, mSrcRectOY + 44, mHPBarMaxWidth - w, 4 );
            }




            //-------------------------------------------------
            // �ʒu
            const LMatrix& vp_mat = Camera::GetMain3DCamera()->GetViewProjectionMatrix();
			LVector3 sc_pos = LVector3::TransformCoord(mCharacter->getPosition(), vp_mat);
			
            sc_pos.y *= -1.0f;  // y �͉��� + �Ȃ̂ŏ㉺���]
            sc_pos += 1.0f;     // 0.0�`2.0 �ɂ���
            sc_pos *= 0.5f;     // 0.0�`1.0 �ɂ���


            // _setPosition �ɓn���p�Ɉꎞ�ޔ�
            LVector3 tpos = sc_pos;

            auto size = Engine::GetMainViewport()->GetSize();
            sc_pos.x *= size.width;
            sc_pos.y *= size.height;

            // �ʒu���L�����̑����Ȃ̂ŁA��̕��Ɉړ�
            sc_pos.y -= 90.0f;
        

            _setPosition( sc_pos.x, sc_pos.y, tpos );

            

            

            
            


            
            --mVisibleFrameCount;

            // �t�F�[�h�A�E�g
            if ( mVisibleFrameCount <= 30 )
            {
                float op = 0.033f * mVisibleFrameCount;    // 0.033 = 1/30
                mFrameSprite->SetOpacity( op );
                mBalloonPointSprite->SetOpacity( op );
                mHPBarSprite->SetOpacity( op );
                mDieBarSprite->SetOpacity( op );
                mNameTextSprite->SetOpacity( op );
            }

            
           
        }
        else
        {
            mFrameSprite->SetVisible( false );
            mBalloonPointSprite->SetVisible( false );
            mHPBarSprite->SetVisible( false );
            mDieBarSprite->SetVisible( false );
            mNameTextSprite->SetVisible( false );
        }
    }

    //---------------------------------------------------------------------
    // �� �ʒu�̐ݒ� (update() ����Ă΂��)
    //---------------------------------------------------------------------
    void CharacterNamePlate::_setPosition( float x_, float y_, const LVector3& screen_pos_ )
    {
        mBalloonPointSprite->SetPosition( x_ - 1, y_ - 3 );


        float ox = 62.0f * screen_pos_.x;

        // �t���[���̍���
        float x = x_ - 1 - ox;
        float y = y_ - 20;

        mFrameSprite->SetPosition( x, y );
        mNameTextSprite->SetPosition( x + 4, y + 1 );
        mHPBarSprite->SetPosition( x + 4, y + 12 );
        mDieBarSprite->SetPosition( x + 4 + mHPBarSprite->GetSrcRect().width, y + 12 );
    }

//=============================================================================
//								end of file
//=============================================================================