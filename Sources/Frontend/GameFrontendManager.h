//=============================================================================
//【 GameFrontendManager 】
//-----------------------------------------------------------------------------
///**
//  @file       GameFrontendManager.h
//  @brief      GameFrontendManager
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "PlayerStateWindow.h"
#include "DamagePop.h"

class Player;
//class PlayerStateWindow;
class GuideNamePlate;
class PointCursor;

//=============================================================================
// ■ GameFrontendManager クラス
//-----------------------------------------------------------------------------
///**
//  @brief      ゲーム中のフロントエンドの管理クラス (シングルトン)
//*/
//=============================================================================
class GameFrontendManager
{
public:

    /// インスタンスの取得
    static GameFrontendManager* getInstance();

    /// 初期化
    void initialize( Player* player_ );

    /// 終了処理
    void finalize();

    /// フレーム更新
    void update();

    /// PlayerStateWindow の取得
    PlayerStateWindow* getPlayerStateWindow() const { return mPlayerStateWindow; }

    /// ネームプレートの文字描画に使うフォントの取得
	Ref<LFont> getNamePlateFont() const { return mNamePlateFont; }

    /// ダメージポップ管理クラスの取得
    DamagePop* getDamagePopManager() const { return mDamagePop; }

    /// 画面中央に「LevelUp」表示
    void showLevelUp();

    /// フロア変更時のフロア数表示エフェクトの表示開始
    void showFloorNum( int num_ );



    Ref<LFont> getGuidNamePlateFont() const { return mGuidNamePlateFont; }
 
    /// (GuidNamePlate のコンストラクタから呼ばれる)
    void addGuidNamePlate( GuideNamePlate* plate_ );

    /// (GuidNamePlate のデストラクタから呼ばれる)
    void removeGuidNamePlate( GuideNamePlate* plate_ );

    /// CharacterNamePlate::show が呼ばれた時のコールバック
    void onShowCharacterNamePlate();

    float getGlobalFadeOpacity() { return mGlobalFadeOpacity.getValue(); }

    PointCursor* getPointCursor() const { return mPointCursor; }

private:

    /// コンストラクタ
    GameFrontendManager();

    /// デストラクタ
    ~GameFrontendManager();

    LN_DISALLOW_COPY_AND_ASSIGN(GameFrontendManager);

private:

    enum ProcStep
    {
        GFM_PTEP_SETUP = 0,     ///< 開始状態
        GFM_PTEP_IDLE,          ///< 普通の監視状態
    };

    typedef std::list< GuideNamePlate* >    GuideNamePlateList;

private:

    ProcStep            mStep;
    u32                 mFrameCount;
    

    LTexture                mNumberTexture1;    ///< 数字テクスチャ
    PlayerStateWindow*      mPlayerStateWindow;
    Ref<LFont>					mNamePlateFont;

    RapidNumber<int>        mFrameXPos;

    DamagePop*              mDamagePop;


    GuideNamePlateList      mGuideNamePlateList;
    Ref<LFont>					mGuidNamePlateFont;     ///< ガイド用の縁取りフォント

    u32                     mShowCharacterNamePlateCount;
	EasingValue<float>		mGlobalFadeOpacity;

    u32                     mLevelupFrameCount;
    ln::Ref<ln::UISprite>                 mLevelupSprites[ 2 ];
    ln::Ref<ln::UISprite>                 mLevelEffectSprite;

    PointCursor*            mPointCursor;

    ln::Ref<ln::ScalarAnimationTrack> mFloorNumAnim;
    ln::Ref<ln::ScalarAnimationTrack> mFloorNumAnimAlpha;

	double					mFloorNumAnimTime;
    LTexture                mFloorInfoTexture;
    ln::Ref<ln::UISprite>                 mFloorInfoSprite[ 3 ];
    float                   mFloorInfoOffset;
};

//=============================================================================
//								end of file
//=============================================================================