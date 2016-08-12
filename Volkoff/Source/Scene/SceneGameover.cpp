//=============================================================================
//�y SceneGameover �z
//=============================================================================

#include "stdafx.h"
#include "../Game/GameManager.h"
#include "../Map/MapManager.h"
#include "../Frontend/PointCursor.h"
#include "SceneGameover.h"
#include "SceneGame.h"
#include "SceneTitle.h"

//=============================================================================
// �� SceneGameover �N���X
//=============================================================================


static const int COMMAND_POS_X = 420;
static const int COMMAND_POS_Y = 290;
    
//---------------------------------------------------------------------
// �� �J�n����
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


    // �����E�B���h�E
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

    // �R�}���h
    mCommandSprite[ 0 ] = Sprite2D::Create( fe_tex );
    mCommandSprite[ 0 ]->SetSrcRect( 272, 304, 128, 32 );
    mCommandSprite[ 0 ]->SetPosition( COMMAND_POS_X, COMMAND_POS_Y );
    mCommandSprite[ 0 ]->SetOpacity( 0 );
    mCommandSprite[ 1 ] = Sprite2D::Create( fe_tex );
    mCommandSprite[ 1 ]->SetSrcRect( 272, 336, 128, 32 );
    mCommandSprite[ 1 ]->SetPosition( COMMAND_POS_X, COMMAND_POS_Y + 32 );
    mCommandSprite[ 1 ]->SetOpacity( 0 );

    // ���䕶����`��N���X
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

    // �J�[�\��
    mPointCursor = NEW PointCursor();

    // BGM �t�F�[�h�A�E�g
    GameAudio::StopBGM( 5.0f );

    
    mStep = 0;
    mFrameCount = 0;
    mSelectIndex = 0;

    
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneGameover::onUpdate()
{
    mPointCursor->update();

    // �������`�撆
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
        /////////////////////// �u���C���h��
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
        /////////////////////// GameOver �t�F�[�h�C����
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
        /////////////////////// �R���e���c�t�F�[�h�C����
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
        /////////////////////// �R���e���c�I��
        case 3:
        {
            // ����
            if ( Input::IsTriggered( LN_BUTTON_A ) )
            {
                mPointCursor->moveToInit();
                mStep = 4;
                mFrameCount = 0;
				Accessor::ToneLayer->ChangeTone(ToneF(-1, -1, -1, 0), 1.0f);
            }

            // ��
            if ( Input::IsRepeated( LN_BUTTON_UP ) )
            {
                --mSelectIndex;
                if ( mSelectIndex < 0 )
                {
                    mSelectIndex = 1;
                }
                _onSelectIndex();
            }
            // ��
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
        /////////////////////// �I����
        case 4:
        {
            if ( mFrameCount == 60 )
            {
                if ( mSelectIndex == 0 )
                {

                    // ��
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

	// �ȑO�͂��̊֐� (SceneGameover::onUpdate()) �̐擪�Őe�V�[���� onUpdate() ���Ăяo���Ă����B
	// �������A�R���e�B�j���[���Ɍ��݂̃}�b�v���č\�z������� onUpdate() ���Ă΂�Ȃ��������߁A
	// �Â��I�u�W�F�N�g�����̉����1�t���[���x��Ă����B(�K�v�Ȃ��Ȃ����I�u�W�F�N�g�� onUpdate() �ŊJ�����Ă��邽��)
	// ���ʁA��u����2�{�����̃I�u�W�F�N�g���o�����邱�ƂɂȂ�A�`��\�ȃX�v���C�g���𒴂��Ă��܂����B
    this->getParentScene()->onUpdate();
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneGameover::onTerminate()
{
	Accessor::ToneLayer->ChangeTone(ToneF(0, 0, 0, 0), 1.0f);

    SAFE_DELETE( mPointCursor );
}

//---------------------------------------------------------------------
// �� �I�����Ă��鍀�ڂ�ύX����
//---------------------------------------------------------------------
void SceneGameover::_onSelectIndex()
{
    mPointCursor->moveTo( COMMAND_POS_X - 38, COMMAND_POS_Y + mSelectIndex * 32 + 16 );

    mDescContents->Clear( Color32( 0, 0, 0, 0 ) );

    if ( mSelectIndex == 0 )
    {
		mDescContents->DrawText("Continue", LRect(8, 2, 256, 256), mDescTitleFont, Color32::White, Color32::Black, 0, TextAlignment::Left);

        mFormatText.setText( "�X�e�[�W�̍ŏ������蒼���܂��B\n\n�X�R�A�� 0 �Ƀ��Z�b�g����܂��B" );
        mFormatText.build();
    }
    else
    {
		mDescContents->DrawText("End", LRect(8, 2, 256, 256), mDescTitleFont, Color32::White, Color32::Black, 0, TextAlignment::Left);

        mFormatText.setText( "�^�C�g����ʂɖ߂�܂��B" );
        mFormatText.build();
    }
}



//=============================================================================
//								end of file
//=============================================================================