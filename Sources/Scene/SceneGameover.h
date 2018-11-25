//=============================================================================
//�y SceneGameover �z
//-----------------------------------------------------------------------------
///**
//  @file       SceneGameover.h
//  @brief      SceneGameover
//  @author     yama
//*/
//=============================================================================

#pragma once
#include "../Utility/FormatText.h"

class PointCursor;

//=============================================================================
// �� SceneGameover �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�Q�[���I�[�o�[���
//*/
//=============================================================================
class SceneGameover
    : public LGameScene
{
public:

    /// �V�[����
    virtual const char* getSceneName() { return "SceneGameover"; }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

private:

    /// �I�����Ă��鍀�ڂ�ύX����
    void _onSelectIndex();

private:

    ln::Ref<ln::UISprite>     mBlindSprite;
    ln::Ref<ln::UISprite>     mBlindSprite2;

    int         mStep;
    int         mFrameCount;
    int         mGotoScene;
    int         mSelectIndex;

	EasingValue<float>	mLogoFadeValue;
	EasingValue<float>	mFadeValue;

    ln::Ref<ln::UISprite>     mLogoSprite;

    ln::Ref<ln::UISprite>     mDescWindowSprite;      // �����E�B���h�E�̘g
    ln::Ref<ln::UISprite>     mDescContentsSprite;
    LTexture    mDescContents;          // �����E�B���h�E�̓��e
    Ref<LFont>       mDescTitleFont;
    int         mWindowFadeCount;
    Utility::FormatText mFormatText;

    ln::Ref<ln::UISprite>     mCommandSprite[ 2 ];

    PointCursor*    mPointCursor;

};

//=============================================================================
//								end of file
//=============================================================================