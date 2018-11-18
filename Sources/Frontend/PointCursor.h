//=============================================================================
//�y PointCursor �z
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
// �� PointCursor �N���X
//-----------------------------------------------------------------------------
///**
//  @brief     ���ڑI���Ŏg�����J�[�\��
//*/
//=============================================================================
class PointCursor
{
public:

    /// �R���X�g���N�^
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

    /// �f�X�g���N�^
    ~PointCursor() {}

public:

    /// �ړ���w��
    void moveTo( int x_, int y_ )
    {
        mXPos.set( x_ );
        mYPos.set( y_ );
        mFadeValue.Start( mFadeValue.GetValue(), 1.0f, 10 );
    }

    /// �����ʒu�ւ��ǂ��Ȃ���t�F�[�h�A�E�g
    void moveToInit()
    {
        mFadeValue.Start( mFadeValue.GetValue(), 0.0f, 10 );
    }

    /// �t���[���X�V
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