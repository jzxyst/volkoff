//=============================================================================
//�y SceneStartup �z
//-----------------------------------------------------------------------------
///**
//  @file       SceneStartup.h
//  @brief      SceneStartup
//  @author     yama
//  @par
//              �N����A��ԍŏ��Ɏ��s�����V�[���B
//              �O�܂� SceneLogo �Ƃ����O�����Ă����́B
//*/
//=============================================================================

#pragma once

//=============================================================================
// �� SceneStartup �N���X
//-----------------------------------------------------------------------------
///**
//  @brief		�N����A��ԍŏ��Ɏ��s�����V�[��
//*/
//=============================================================================
class SceneStartup : public LGameScene
{
public:

    /// �V�[����
    virtual const TCHAR* getSceneName() { return _T("SceneStartup"); }

	/// �J�n����
	virtual void onStart();

    /// �t���[���X�V
	virtual void onUpdate();

    /// �I������
	virtual void onTerminate();

private:
	Sprite2DPtr			mLogoSprite;
	Sprite2DPtr			mFlashSprite;
	Sprite2DPtr			mTitleSubTextSprite;
	EasingValue<float>	mFlashScale;
	int         mStep;
	int         mFrameCount;
};

//=============================================================================
//								end of file
//=============================================================================