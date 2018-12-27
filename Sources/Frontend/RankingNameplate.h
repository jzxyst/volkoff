//=============================================================================
//【 RankingNameplate 】
//-----------------------------------------------------------------------------
///**
//  @file       RankingNameplate.h
//  @brief      RankingNameplate
//  @author     yama
//*/
//=============================================================================

#pragma once

//=============================================================================
// ■ RankingNameplate
//-----------------------------------------------------------------------------
///**
//  @brief     
//*/
//=============================================================================
class RankingNameplate
{
public:

    /// コンストラクタ
    RankingNameplate();

public:

	// 名前が NULL の場合は何も表示しない
	void initialize(int no_, const char* name_, int rank_, lnU32 frame_count_, lnU32 score_ );

    void setPosition(int x_, int y_);

	void setOpacity(float op_);

	void setName(const char* name_);

	void updateCaret();

	void setVisibleCaret(bool f_) { if (mInited) mCaretSprite->setVisible(f_); }

private:

	LVector3 mPosition;

    LTexture mRankingTexture;
    ln::Ref<ln::UISprite> mFrameSprite;
    ln::Ref<ln::UISprite> mNumberSprite;
    ln::Ref<ln::UISprite> mRankSprite;
    Ref<LFont> mNameFont;
	LTexture mNameTexture;
    ln::Ref<ln::UISprite> mNameSprite;

	LTexture mTextTexture;
    ln::Ref<ln::UISprite> mTextSprite;

    ln::Ref<ln::UISprite>	mCaretSprite;
	int mCaretCount;
	int mCaretX;

	bool mInited;
};

//=============================================================================
//								end of file
//=============================================================================