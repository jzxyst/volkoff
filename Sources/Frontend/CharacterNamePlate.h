//=============================================================================
//【 CharacterNamePlate 】
//-----------------------------------------------------------------------------
///**
//  @file       CharacterNamePlate.h
//  @brief      CharacterNamePlate
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "RapidNumber.h"

class Character;

//=============================================================================
// ■ CharacterNamePlate クラス
//-----------------------------------------------------------------------------
///**
//  @brief      キャラクターの頭の上あたりに表示する、名前と HP バー
//
//  @par
//              とりあえずキャラクターのメンバとして持っておく。
//*/
//=============================================================================
class CharacterNamePlate
{
public:

    /// コンストラクタ
    CharacterNamePlate();

    /// デストラクタ
    ~CharacterNamePlate();

public:

    /// 初期化
    void initialize( Character* character_ );

    /// 可視状態の設定 (false にすると、startShow() が呼ばれても表示しない)
    void setVisible( bool flag_ );

    /// 表示開始 (攻撃か当たった場合など、表示する場合にこれだけ呼ぶ。あとは勝手にﾌｪｰﾄﾞｱｳﾄする)
    void startShow();

    /// フレーム更新
    void update();

private:

    /// 位置の設定 (update() から呼ばれる。吹き出しの先っぽで指定する。)
    void _setPosition( float x_, float y_, const LVector3& screen_pos_ );

private:

    Character*  mCharacter;
    LSprite     mFrameSprite;
    LSprite     mHPBarSprite;
    LSprite     mDieBarSprite;
    LSprite     mNameTextSprite;
    LSprite     mBalloonPointSprite;
    LTexture    mNameTextTexture;

    RapidNumber< float >  mHPValue;

    u32         mVisibleFrameCount;

    int         mFrameWidth;        ///< ウィンドウの幅 (通常72、文字が多い場合は96)
    int         mSrcRectOY;
    float       mHPBarMaxWidth;

    bool        mVisible;

};

//=============================================================================
//								end of file
//=============================================================================