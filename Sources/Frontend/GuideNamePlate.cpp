//=============================================================================
//�y GuideNamePlate �z
//=============================================================================

#include "GameFrontendManager.h"
#include "GuideNamePlate.h"
#include "../Game/GameManager.h"
#include "../Object/GameObject.h"
#include "../Object/Player.h"


//=============================================================================
// �� GuideNamePlate �N���X
//=============================================================================

//#define GUIDE_UNDER

    //---------------------------------------------------------------------
    // �� �R���X�g���N�^
    //---------------------------------------------------------------------
    GuideNamePlate::GuideNamePlate()
        : mIsNearPlayer ( false )
    {
        GameFrontendManager::getInstance()->addGuidNamePlate( this );
    }

    //---------------------------------------------------------------------
    // �� �f�X�g���N�^
    //---------------------------------------------------------------------
    GuideNamePlate::~GuideNamePlate()
    {
        GameFrontendManager::getInstance()->removeGuidNamePlate( this );
    }

    //---------------------------------------------------------------------
    // �� ������
    //---------------------------------------------------------------------
    void GuideNamePlate::initialize( GameObject* object_, int arrow_color_, float ox_, float oy_ )
    {
        mGameObject = object_;

        LTexture tex = Assets::loadTexture( "Data/Graphics/Frontend/Frontend_1.png" );

        // �t���[��
        mFrameSprite = ln::UISprite::create(  tex);
        mFrameSprite->setSourceRect( 0, 168 + 16 * arrow_color_, 64, 13 );
        mFrameSprite->setVisible( false );

        // ���
        mArrowSprite = ln::UISprite::create( tex );
        mArrowSprite->setSourceRect( 16 * arrow_color_, 128, 16, 8 );
        mArrowSprite->setCenterPoint( 6, 7 );
        mArrowSprite->setVisible( false );

        // ���O
        Ref<LFont> font = GameFrontendManager::getInstance()->getGuidNamePlateFont();
		
        Size size = font->MeasureRenderSize( mGameObject->getName() );

        mNameTextTexture = Texture2D::create( size.width , 20 );
		mNameTextTexture->DrawText(mGameObject->getName(), Rect(0, 0, size.width, size.height), font, Color32::White, Color32::Black, 0, TextAlignment::Left);

        mNameTextSprite = ln::UISprite::create( mNameTextTexture );
        mNameTextSprite->setVisible( false );
		mNameTextSprite->setSourceRect(0, 0, size.width, size.height);

        mOffsetPos.set( ox_, oy_, 0 );
        


#ifdef GUIDE_UNDER

        mArrowSprite->setSourceRect( 32 * arrow_color_, 128 + 16, 16, 8 );
        mOffsetPos->Set( ox_, -96, 0 );
#endif
    }

    /*
    //---------------------------------------------------------------------
    // �� �t�F�[�h�C���J�n
    //---------------------------------------------------------------------
    void GuideNamePlate::startFadein()
    {
        mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 1.0f, 20.0 );
    }

    //---------------------------------------------------------------------
    // �� �t�F�[�h�A�E�g�J�n
    //---------------------------------------------------------------------
    void GuideNamePlate::startFadeout()
    {
        mGlobalFadeOpacity.start( mGlobalFadeOpacity.getValue(), 0.0f, 20.0 );
    }
    */

    //---------------------------------------------------------------------
    // �� �t���[���X�V
    //---------------------------------------------------------------------
    void GuideNamePlate::update()
    {
		const LVector3& player_pos = GameManager::getInstance()->getPlayer()->getPosition();
		const LVector3& object_pos = mGameObject->getPosition();

		//if ( ( player_pos - object_pos ).getLength() < 200 )

		float length = (player_pos - object_pos).lengthSquared();

		// �v���C���[�Ƌ߂���Ε\��
		if (!mIsNearPlayer && length < 60000)
		{
			mIsNearPlayer = true;

			mFadeOpacity.Start(mFadeOpacity.GetValue(), 1.0f, 20);

			mArrowSprite->setVisible(true);
			mFrameSprite->setVisible(true);
			mNameTextSprite->setVisible(true);

#ifdef GUIDE_UNDER

			mNameTextSprite->SetPosition(pos_2d.x, pos_2d.y + 10);
#endif

		}
		// �v���C���[���痣��Ă���Δ�\��
		else if (mIsNearPlayer && length >= 60000)
		{
			mIsNearPlayer = false;
			mFadeOpacity.Start(mFadeOpacity.GetValue(), 0.0f, 20);


		}

		float op = GameFrontendManager::getInstance()->getGlobalFadeOpacity() * mFadeOpacity.GetValue();

		mArrowSprite->setOpacity(mFadeOpacity.GetValue());  // ��󂾂��� Global �������ł��\������
		mFrameSprite->setOpacity(op);
		mNameTextSprite->setOpacity(op);




		mFadeOpacity.AdvanceTime(1.0);


		// ���S�Ƀt�F�[�h�A�E�g�����ꍇ�͔�\���ɂ���
		if (mFadeOpacity.IsFinished() && mFadeOpacity.GetValue() == 0.0f)
		{
			mArrowSprite->setVisible(false);
			mFrameSprite->setVisible(false);
			mNameTextSprite->setVisible(false);
		}
		else
		{


			// �I�u�W�F�N�g�̍��W���X�N���[�����W�ɕϊ�
			LVector3 pos_2d = Accessor::Main3Camera->WorldToViewportPoint((object_pos + mOffsetPos));

			_setPosition(pos_2d);
		}
    }

    //---------------------------------------------------------------------
    // �� �ʒu�̐ݒ� (update() ����Ă΂��B�����o���̐���ۂŎw�肷��B)
    //---------------------------------------------------------------------
    void GuideNamePlate::_setPosition( const LVector3& pos_ )
    {
        mArrowSprite->setPosition( pos_.x, pos_.y, 100 );
        



        // �t���[���̍���
        float x = pos_.x  - mFrameSprite->sourceRect().width / 2;
        
        mFrameSprite->setPosition( x, pos_.y - 24, 100 );
        

        x = pos_.x  - mNameTextSprite->sourceRect().width / 2;
        mNameTextSprite->setPosition( x, pos_.y - 23, 100 );
        

        
    }


//=============================================================================
//								end of file
//=============================================================================