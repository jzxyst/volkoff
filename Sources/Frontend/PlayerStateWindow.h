//=============================================================================
//【 PlayerStateWindow 】
//-----------------------------------------------------------------------------
///**
//  @file       PlayerStateWindow.h
//  @brief      PlayerStateWindow
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "RapidNumber.h"

class Player;


//=============================================================================
// ■ PlayerStateWindow クラス
//-----------------------------------------------------------------------------
///**
//  @brief      プレイヤーの状態を表示するウィンドウ (ゲーム画面の左上の)
//*/
//=============================================================================
class PlayerStateWindow
{
public:

    /// コンストラクタ
    PlayerStateWindow( Player* player_ );

    /// デストラクタ
    ~PlayerStateWindow();

public:

    /// 位置の設定
    void setPosition( float x_, float y_ );

    /// 不透明度の設定
    void setOpacity( float op_ );

    /// リフレッシュ (とりあえず今は空。リアルタイムに更新できない処理があったら使うようにする)
    void refresh();

    /// フレーム更新
    void update();

private:

    enum ProcStep
    {
        PSW_PTEP_SETUP = 0,     ///< 開始状態。バーを増やす。
        PSW_PTEP_IDLE,          ///< 普通の監視状態
    };

private:

    LVector3    mPosition;

    Player*     mPlayer;
    ProcStep    mStep;

    LTexture    mFrontendTexture;           ///< Frontend_1.png
    LTexture    mNumberTextureS;            ///< 小さい数字テクスチャ
    LTexture    mNumberTextureL;            ///< 大きい数字テクスチャ

    ln::Ref<ln::UISprite>     mFrameWindow;               ///< 枠
    ln::Ref<ln::UISprite>     mFloorNumSprite[ 2 ];       ///< フロア数
    ln::Ref<ln::UISprite>     mScoreNumSprite[ 10 ];      ///< スコア
    ln::Ref<ln::UISprite>     mHPBarSprite;               ///< HP バー
    ln::Ref<ln::UISprite>     mHPDieBarSprite;            ///< HP バーの、ダメージを受けて削られた部分
    ln::Ref<ln::UISprite>     mWeaponIconSprite;          ///< 武器アイコン
    ln::Ref<ln::UISprite>     mWeaponLevelSprite;         ///< 武器レベル
    ln::Ref<ln::UISprite>     mWeaponEXPBar;              ///< 武器経験値バー
    ln::Ref<ln::UISprite>     mWeaponCountSprite[ 3 ];    ///< 武器使用回数
    ln::Ref<ln::UISprite>     mKeySprite;                 ///< 鍵
    ln::Ref<ln::UISprite>     mKeyEffectSprite[ 2 ];      ///< 鍵入手時エフェクト


    u32         mLastWeaponCount;           ///< 使用回数の警告開始の判定に使う
    ln::Ref<ln::UISprite>     mWeaponCountWarningSprite[ 3 ];    ///< 武器使用回数
    u32         mWarningFrameCount;
    u8          mWarningShowedFlag;         ///< 30%以下になった瞬間を表示した場合は 1、15%以下を表示した場合は2

    u32         mPlayerHP;
    u32         mHPDieWidth;                ///< HP の無くなった部分の幅

    RapidNumber<int>    mHPNumber;
    u32                 mDieWaitFrameCount; ///< 無くなった黒部分の減少開始までの待ちフレーム数

    u32         mEXPBarFrameCount;

    u8          mHasKey;    ///< 鍵を表示しているフラグ
    u32         mKeyEffectFrameCount;


};

//=============================================================================
//								end of file
//=============================================================================