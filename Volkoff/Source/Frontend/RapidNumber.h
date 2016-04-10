
#pragma once


template < typename TYPE_ >
class RapidNumber
{
public:

    /// デフォルトコンストラクタ
    RapidNumber()
        : mNowNumber    ( 0 )
        , mDestNumber   ( 0 )
        , mDivSpeed     ( 1.0f / 10.0f )
    {}

public:

    /// 現在の値の取得
    TYPE_ getValue() const 
    {
        return mNowNumber;
    }

    /// 初期値の設定
    void setInitValue( TYPE_ num_ )
    {
        mNowNumber = num_;
    }

    /// 目標値の設定
    void set( TYPE_ num_ )
    {
        mDestNumber = num_;
    }

    /// 値変化の速さの設定 ( 1より大きい値を設定すること。デフォルトは 10 )
    void setSpeed( int speed_ )
    {
        mDivSpeed = 1.0f / speed_;
    }

    /// 変化終了判定
    bool isFinished() const
    {
        return ( mDestNumber == mNowNumber );
    }

    /// フレーム更新
    void update()
    {
        if ( mNowNumber != mDestNumber )
        {
            if ( abs( mNowNumber - mDestNumber ) < 2.0f )   // 応急処置
            {
                mNowNumber = mDestNumber;
                return;
            }
            int sign = ( mNowNumber > mDestNumber ) ? -1 : 1;
            mNowNumber = mNowNumber + static_cast< TYPE_ >( sign * std::max< TYPE_ >( abs( mDestNumber - mNowNumber ) * mDivSpeed, (TYPE_)1 ) );
        }
    }

private:

    TYPE_   mNowNumber;     ///< 現在の値
    TYPE_   mDestNumber;    ///< 目標値
    float	mDivSpeed;
};