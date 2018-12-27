//=============================================================================
//【 PointCursor 】
//-----------------------------------------------------------------------------
///**
//  @file       PointCursor.h
//  @brief      PointCursor
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "RapidNumber.h"

//=============================================================================
// ■ PointCursor クラス
//-----------------------------------------------------------------------------
///**
//  @brief     項目選択で使う矢印カーソル
//*/
//=============================================================================
class PointCursor
{
public:

    /// コンストラクタ
    PointCursor()
    {
        mXPos.setInitValue( 0 );
        mXPos.setSpeed( 5 );
        mYPos.setInitValue( 0 );
        mYPos.setSpeed( 5 );
        mCursorSprite = ln::UISprite::create(Assets::loadTexture( "Data/Graphics/Frontend/Cursor_1.png" ) );
        mCursorSprite->setSourceRect( 0, 0, 32, 32 );
        mCursorSprite->setOpacity( 0 );
        mFrameCount = 0;
    }

    /// デストラクタ
    ~PointCursor() {}

public:

    /// 移動先指定
    void moveTo( int x_, int y_ )
    {
        mXPos.set( x_ );
        mYPos.set( y_ );
        mFadeValue.start( mFadeValue.getValue(), 1.0f, 10 );
    }

    /// 初期位置へもどしながらフェードアウト
    void moveToInit()
    {
        mFadeValue.start( mFadeValue.getValue(), 0.0f, 10 );
    }

    /// フレーム更新
    void update()
    {
        mFadeValue.advanceTime( 1.0f );
        mXPos.update();
        mYPos.update();

        mCursorSprite->setPosition( (float)mXPos.getValue(), (float)mYPos.getValue() );
        mCursorSprite->setOpacity( mFadeValue.getValue() );

        mCursorSprite->setSourceRect( ( mFrameCount / 10 ) * 32, 0, 32, 32 );
        if ( mFrameCount >= 59 )
        {
            mFrameCount = 0;
        }
        
        ++mFrameCount;
    }


private:

    RapidNumber< int > mXPos;
    RapidNumber< int > mYPos;
	EasingValue< float >   mFadeValue;

    ln::Ref<UISprite> mCursorSprite;
    int     mFrameCount;
    
};

//=============================================================================
//								end of file
//=============================================================================