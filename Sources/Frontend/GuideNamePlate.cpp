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

        LTexture tex = Assets::LoadTexture( "Data/Graphics/Frontend/Frontend_1.png" );

        // �t���[��
        mFrameSprite = Sprite2D::Create(  tex);
        mFrameSprite->SetSrcRect( 0, 168 + 16 * arrow_color_, 64, 13 );
        mFrameSprite->SetVisible( false );

        // ���
        mArrowSprite = Sprite2D::Create( tex );
        mArrowSprite->SetSrcRect( 16 * arrow_color_, 128, 16, 8 );
        mArrowSprite->SetCenter( 6, 7 );
        mArrowSprite->SetVisible( false );

        // ���O
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

		float length = (player_pos - object_pos).GetLengthSquared();

		// �v���C���[�Ƌ߂���Ε\��
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
		// �v���C���[���痣��Ă���Δ�\��
		else if (mIsNearPlayer && length >= 60000)
		{
			mIsNearPlayer = false;
			mFadeOpacity.Start(mFadeOpacity.GetValue(), 0.0f, 20);


		}

		float op = GameFrontendManager::getInstance()->getGlobalFadeOpacity() * mFadeOpacity.GetValue();

		mArrowSprite->SetOpacity(mFadeOpacity.GetValue());  // ��󂾂��� Global �������ł��\������
		mFrameSprite->SetOpacity(op);
		mNameTextSprite->SetOpacity(op);




		mFadeOpacity.AdvanceTime(1.0);


		// ���S�Ƀt�F�[�h�A�E�g�����ꍇ�͔�\���ɂ���
		if (mFadeOpacity.IsFinished() && mFadeOpacity.GetValue() == 0.0f)
		{
			mArrowSprite->SetVisible(false);
			mFrameSprite->SetVisible(false);
			mNameTextSprite->SetVisible(false);
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
        mArrowSprite->SetPosition( pos_.x, pos_.y, 100 );
        



        // �t���[���̍���
        float x = pos_.x  - mFrameSprite->GetSrcRect().width / 2;
        
        mFrameSprite->SetPosition( x, pos_.y - 24, 100 );
        

        x = pos_.x  - mNameTextSprite->GetSrcRect().width / 2;
        mNameTextSprite->SetPosition( x, pos_.y - 23, 100 );
        

        
    }


//=============================================================================
//								end of file
//=============================================================================