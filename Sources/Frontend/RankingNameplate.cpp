//=============================================================================
//y RankingNameplate z
//=============================================================================

#include "../Game/GameManager.h"
#include "RankingNameplate.h"

//=============================================================================
// ¡ RankingNameplate
//=============================================================================

    //---------------------------------------------------------------------
    //
    //---------------------------------------------------------------------
    RankingNameplate::RankingNameplate()
	{
		mInited = false;
	}

	//---------------------------------------------------------------------
    //
    //---------------------------------------------------------------------
	void RankingNameplate::initialize(int no_, const char* name_, int rank_, lnU32 time_, lnU32 score_ )
	{
		mRankingTexture = LTexture::create("Data/Graphics/Frontend/Ranking_1.png");

		mFrameSprite = LSprite::create(mRankingTexture);
		mFrameSprite->setSourceRect(0, 0, 320, 47);

		mNumberSprite = LSprite::create(LTexture::create("Data/Graphics/Frontend/Number_2.png"));
		mNumberSprite->setSourceRect(7 * no_, 0, 7, 11);

		mRankSprite = LSprite::create(mRankingTexture);
		mRankSprite->setSourceRect(0, rank_ * 16 + 96, 48, 12);

        Ref<LFont> name_font = LFont::createDefaultFont();
		name_font.setColor(LColor(0, 0, 0));

		mNameTexture = LTexture::create(128, 32);
		mNameTexture.setFont(name_font);
		mNameTexture.drawText(name_, LRect(0, 0, 0, 0));

		mNameSprite = LSprite::create(mNameTexture);


        Ref<LFont> time_font = LFont::createDefaultFont();
		time_font.setColor(LColor(0, 0, 0));
		time_font.setSize(15);

		mTextTexture = LTexture::create(128, 48);
		
		// ŽžŠÔ
		lnU32 h, m, s;
		//Base::Time::splitMillisecond(time_ms_, &h, &m, &s, NULL);
		GameManager::getInstance()->splitGameTime(
			GameManager::getInstance()->getGameTime(),
			&h, &m, &s );
		LRefTString tm;
		tm.format("Time %02d:%02d:%02d", h, m, s);
		mTextTexture.setFont(time_font);
		mTextTexture.drawText(tm.c_str(), LRect(0, 0, 110, 32), LN_TEXTALIGN_RIGHT);

		// ƒXƒRƒA
		LRefTString sc;
		sc.format("%d", score_);
		mTextTexture.setFont(name_font);
		mTextTexture.drawText(sc.c_str(), LRect(0, 16, 110, 32), LN_TEXTALIGN_RIGHT);

		mTextSprite = LSprite::create(mTextTexture);


		mCaretSprite = LSprite::create(mRankingTexture);
		mCaretSprite->setSourceRect(64, 96, 1, 18);
		mCaretSprite->setVisible(false);
		mCaretCount = 0;
		mCaretX = 0;

		mInited = true;
	}

	//---------------------------------------------------------------------
    //
    //---------------------------------------------------------------------
    void RankingNameplate::setPosition( int x_, int y_ )
	{
		if (mInited)
		{
			mPosition.set(x_, y_, 0);
			mFrameSprite->setPosition(x_, y_);
			mNumberSprite->setPosition(x_ + 6, y_ + 3);
			mRankSprite->setPosition(x_ + 32, y_ + 3);
			mNameSprite->setPosition(x_ + 16, y_ + 20);
			mTextSprite->setPosition(x_ + 128, y_ + 4);
			mCaretSprite->setPosition(mPosition.x + 16 + mCaretX, mPosition.y + 23);
		}
	}

	//---------------------------------------------------------------------
    //
    //---------------------------------------------------------------------
    void RankingNameplate::setOpacity(float op_)
	{
		if (mInited)
		{
			mFrameSprite->setOpacity(op_);
			mNumberSprite->setOpacity(op_);
			mRankSprite->setOpacity(op_);
			mNameSprite->setOpacity(op_);
			mTextSprite->setOpacity(op_);
		}
	}

	//---------------------------------------------------------------------
    //
    //---------------------------------------------------------------------
	void RankingNameplate::setName(const char* name_)
	{
		if (mInited)
		{
			mNameTexture->clear(LColor::TRANSPARENCY_WHITE);
			mNameTexture->drawText(name_, LRect(0, 0, 0, 0));

			LRect r;
			mNameTexture->getFont().getTextSize(name_, strlen(name_), &r);
			mCaretX = r.w;
			mCaretSprite->setPosition(mPosition.x + 16 + mCaretX, mPosition.y + 23);
		}
	}

	//---------------------------------------------------------------------
    //
    //---------------------------------------------------------------------
	void RankingNameplate::updateCaret()
	{
		if (mInited)
		{
			if (mCaretCount < 30)
			{
				mCaretSprite->setVisible(false);
			}
			else
			{
				mCaretSprite->setVisible(true);
			}

			++mCaretCount;
			if (mCaretCount > 60) mCaretCount = 0;
		}
	}


//=============================================================================
//								end of file
//=============================================================================