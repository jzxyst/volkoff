//=============================================================================
//�y SceneGameover �z
//=============================================================================

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
    LTexture tex = Texture2D::create( 32, 32 );
    tex->clear( Color32( 0, 0, 0 ) );
    mBlindSprite = ln::UISprite::create( tex );
    mBlindSprite->setScale( 20 );
    mBlindSprite2 = ln::UISprite::create( tex );
    mBlindSprite2->setScale( 20 );
    mBlindSprite2->setPosition( 0, 240 );
    mBlindSprite2->setOpacity( 0 );


    // �����E�B���h�E
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

    // �R�}���h
    mCommandSprite[ 0 ] = ln::UISprite::create( fe_tex );
    mCommandSprite[ 0 ]->setSourceRect( 272, 304, 128, 32 );
    mCommandSprite[ 0 ]->setPosition( COMMAND_POS_X, COMMAND_POS_Y );
    mCommandSprite[ 0 ]->setOpacity( 0 );
    mCommandSprite[ 1 ] = ln::UISprite::create( fe_tex );
    mCommandSprite[ 1 ]->setSourceRect( 272, 336, 128, 32 );
    mCommandSprite[ 1 ]->setPosition( COMMAND_POS_X, COMMAND_POS_Y + 32 );
    mCommandSprite[ 1 ]->setOpacity( 0 );

    // ���䕶����`��N���X
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

    // �J�[�\��
    mPointCursor = NEW PointCursor();

    // BGM �t�F�[�h�A�E�g
    GameAudio::stopBGM( 5.0f );

    
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
			mDescContents->drawText(StringRef(data.Text, data.Length), data.Rect, data.Font, Color::White, TextAlignment::Left);
        }
    }

    switch ( mStep )
    {
        /////////////////////// �u���C���h��
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
        /////////////////////// GameOver �t�F�[�h�C����
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
        /////////////////////// �R���e���c�t�F�[�h�C����
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
        /////////////////////// �R���e���c�I��
        case 3:
        {
            // ����
            if ( Input::isTriggered( LN_BUTTON_A ) )
            {
                mPointCursor->moveToInit();
                mStep = 4;
                mFrameCount = 0;
				Accessor::ToneLayer->play(ToneF(-1, -1, -1, 0), 1.0f);
            }

            // ��
            if ( Input::isRepeated( LN_BUTTON_UP ) )
            {
                --mSelectIndex;
                if ( mSelectIndex < 0 )
                {
                    mSelectIndex = 1;
                }
                _onSelectIndex();
            }
            // ��
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
	Accessor::ToneLayer->play(ToneF(0, 0, 0, 0), 1.0f);

    SAFE_DELETE( mPointCursor );
}

//---------------------------------------------------------------------
// �� �I�����Ă��鍀�ڂ�ύX����
//---------------------------------------------------------------------
void SceneGameover::_onSelectIndex()
{
    mPointCursor->moveTo( COMMAND_POS_X - 38, COMMAND_POS_Y + mSelectIndex * 32 + 16 );

    mDescContents->clear( Color( 0, 0, 0, 0 ) );

    if ( mSelectIndex == 0 )
    {
		mDescContents->drawText("Continue", LRect(8, 2, 256, 256), mDescTitleFont, Color::White, TextAlignment::Left);

        mFormatText.setText( "�X�e�[�W�̍ŏ������蒼���܂��B\n\n�X�R�A�� 0 �Ƀ��Z�b�g����܂��B" );
        mFormatText.build();
    }
    else
    {
		mDescContents->drawText("End", LRect(8, 2, 256, 256), mDescTitleFont, Color::White, TextAlignment::Left);

        mFormatText.setText( "�^�C�g����ʂɖ߂�܂��B" );
        mFormatText.build();
    }
}



//=============================================================================
//								end of file
//=============================================================================