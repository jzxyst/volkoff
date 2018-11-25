//=============================================================================
//【 GuideNamePlate 】
//-----------------------------------------------------------------------------
///**
//  @file       GuideNamePlate.h
//  @brief      GuideNamePlate.h
//  @author     yama
//*/
//=============================================================================

#pragma once

class GameObject;

//=============================================================================
// ■ GuideNamePlate クラス
//-----------------------------------------------------------------------------
///**
//  @brief      武器、鍵、出口、回復アイテムを指し示すフキダシ
//*/
//=============================================================================
class GuideNamePlate
{
public:

    /// コンストラクタ
    GuideNamePlate();

    /// デストラクタ
    ~GuideNamePlate();

public:

    /// 初期化 (arrow_color_:0から順に、青、緑、橙   ox_ oy_: 座標オフセット(3D空間上))
    void initialize( GameObject* object_, int arrow_color_, float ox_ = 0.0f, float oy_ = 0.0f );

    /*/// フェードイン開始
    void startFadein();

    /// フェードアウト開始
    void startFadeout();*/

    /// フレーム更新
    void update();

private:

    /// 位置の設定 (update() から呼ばれる。吹き出しの先っぽで指定する。)
    void _setPosition( const LVector3& pos_ );

private:

    GameObject*     mGameObject;
    ln::Ref<ln::UISprite>         mFrameSprite;
    ln::Ref<ln::UISprite>         mArrowSprite;
    ln::Ref<ln::UISprite>         mNameTextSprite;
    LTexture        mNameTextTexture;
    LVector3        mOffsetPos;

	EasingValue<float>  mFadeOpacity;
    

    bool            mIsNearPlayer;  /// プレイヤーの近くにあって、表示しているフラグ


    /*
    ln::Ref<ln::UISprite>     mFrameSprite;
    ln::Ref<ln::UISprite>     mHPBarSprite;
    ln::Ref<ln::UISprite>     mDieBarSprite;
    ln::Ref<ln::UISprite>     mNameTextSprite;
    ln::Ref<ln::UISprite>     mBalloonPointSprite;
    LTexture    mNameTextTexture;

    RapidNumber< float >  mHPValue;

    u32         mVisibleFrameCount;

    bool        mVisible;
    */

};

//=============================================================================
//								end of file
//=============================================================================