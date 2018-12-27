//=============================================================================
//�y SceneCredit �z
//=============================================================================

#include "SceneTitle.h"
#include "SceneCredit.h"

//=============================================================================
// �� SceneCredit �N���X
//=============================================================================

// �v���O���}
const char* PROGRAM[] =
{
    "impmlv", "2", "3", "4", NULL
};         

// �O���t�B�b�N
const char* GRAPHICS[] =
{
    "impmlv", "2", "3", "", NULL
};

// ���y�f��
const char* SOUND_MAT[] =
{
    "1", "URL", "", "2", "URL", "", NULL
};

// �X�y�V�����T���N�X
const char* THANKS[] =
{
    "1", "2", "3", "", NULL
};

//---------------------------------------------------------------------
// �� �J�n����
//---------------------------------------------------------------------
void SceneCredit::onStart()
{
    printf( "-------------------------------------------------\n" );
    printf( " �� �X�^�b�t���[��\n" );
    printf( "-------------------------------------------------\n" );

    
    mBGBlackSprite = LSprite::create( ln::Assets::loadTexture( "Data/Graphics/Frontend/Logo_1.png" ) );
    mBGBlackSprite->setSourceRect( 0, 0, 32, 32 );
    mBGBlackSprite->setScale( 20 );

    Accessor::ToneLayer->play(ToneF(0, 0, 0, 0), 1.0f);


    mPhase = 0;
    mFrameCount = 0;
}

//---------------------------------------------------------------------
// �� �t���[���X�V
//---------------------------------------------------------------------
void SceneCredit::onUpdate()
{
    switch ( mPhase )
    {
        /////////////////////// �t�F�[�h�C���t�F�[�Y
        case 0:
        {
            if ( mFrameCount >= 60 )
            {
                mPhase = 1;
                mFrameCount = 0;
            }
            break;
        }

        /////////////////////// ��
        case 1:
        {
            // �I��
            //if ( Input.isOnTrigger( LN_BUTTON_A ) )
            {
                Accessor::ToneLayer->play(ToneF(1, 1, 1, 0), 3.0f);
                mPhase = -1;
                mFrameCount = 0;
                return;
            }
            break;
        }

        /////////////////////// �t�F�[�h�A�E�g�t�F�[�Y
        case -1:
        {
            if ( mFrameCount >= 200 )
            {
                this->changeScene( NEW SceneTitle() );
                return;
            }
            break;
        }
    }

    ++mFrameCount;
}

//---------------------------------------------------------------------
// �� �I������
//---------------------------------------------------------------------
void SceneCredit::onTerminate()
{
}

//=============================================================================
//								end of file
//=============================================================================