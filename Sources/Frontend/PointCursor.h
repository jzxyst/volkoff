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
        mCursorSprite = Sprite2D::Create(Assets::LoadTexture( "Data/Graphics/Frontend/Cursor_1.png" ) );
        mCursorSprite->setSourceRect( 0, 0, 32, 32 );
        mCursorSprite->SetOpacity( 0 );
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
        mFadeValue.Start( mFadeValue.GetValue(), 1.0f, 10 );
    }

    /// 初期位置へもどしながらフェードアウト
    void moveToInit()
    {
        mFadeValue.Start( mFadeValue.GetValue(), 0.0f, 10 );
    }

    /// フレーム更新
    void update()
    {
        mFadeValue.AdvanceTime( 1.0f );
        mXPos.update();
        mYPos.update();

        mCursorSprite->SetPosition( (float)mXPos.getValue(), (float)mYPos.getValue() );
        mCursorSprite->SetOpacity( mFadeValue.GetValue() );

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

    Sprite2DPtr mCursorSprite;
    int     mFrameCount;
    
};

//=============================================================================
//								end of file
//=============================================================================