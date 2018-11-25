//=============================================================================
/*! 
    @addtogroup 
    @file       SceneTitle.h
    @brief      
    
    �^�C�g���̃V�[��
    
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
      -# �쐬
*/
//=============================================================================

#include "../Utility/FormatText.h"

class PointCursor;

class SceneTitle : public LGameScene
{
public:

    /// �R���X�g���N�^
    SceneTitle();

public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneTitle"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

    // This tale is the last message we present to everyone.

private:

    /// �R�}���h���ڂ̕\���J�n
    void _startShowCommand( int type_ );


    /// ���̈ʒu�ݒ�
    void _setPointCursorIndex( int index_ );

private:

    

    int     mStep;
    int     mFrameCount;

    

    ln::Ref<ln::UISprite>     mRandomSprite;
    ln::Ref<ln::UISprite>     mTitleFrameSprite;
    ln::Ref<ln::UISprite>     mTitleTextSprite;
    ln::Ref<ln::UISprite>     mTitleSubTextSprite;
    ln::Ref<ln::UISprite>     mPressAnyKeySprite;

    ln::Ref<ln::UISprite>     mTitleEffectSprite;

    ln::Ref<ln::UISprite>     mSuperSprite[ 2 ];  // �㉺�̎����X�[�p�[
    ln::Ref<ln::UISprite>     mCommandSprite[ 4 ];

    ln::Ref<ln::UISprite>     mDescWindowSprite;      // �����E�B���h�E�̘g
    ln::Ref<ln::UISprite>     mDescContentsSprite;
    LTexture    mDescContents;          // �����E�B���h�E�̓��e
    Ref<LFont>       mDescTitleFont;
    int         mWindowFadeCount;

	FloatAnimationCurve  mRoundTripValue;        ///< 0.2 �`1.0 ����������l�B�A���t�@�l�p

	FloatAnimationCurve  mCommandFadeInX;
	FloatAnimationCurve  mCommandFadeInOpacity;

    Utility::FormatText mFormatText;


    int         mEntryedStep;
    int         mSelectIndex;
 
    PointCursor*    mPointCursor;

    int         mEndFrameCount;
};

//=============================================================================
//								End of File
//=============================================================================