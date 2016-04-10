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
    : public ln::NonCopyable
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
	LFont getNamePlateFont() const { return mNamePlateFont; }

    /// ダメージポップ管理クラスの取得
    DamagePop* getDamagePopManager() const { return mDamagePop; }

    /// 画面中央に「LevelUp」表示
    void showLevelUp();

    /// フロア変更時のフロア数表示エフェクトの表示開始
    void showFloorNum( int num_ );



	LFont getGuidNamePlateFont() const { return mGuidNamePlateFont; }
 
    /// (GuidNamePlate のコンストラクタから呼ばれる)
    void addGuidNamePlate( GuideNamePlate* plate_ );

    /// (GuidNamePlate のデストラクタから呼ばれる)
    void removeGuidNamePlate( GuideNamePlate* plate_ );

    /// CharacterNamePlate::show が呼ばれた時のコールバック
    void onShowCharacterNamePlate();

    float getGlobalFadeOpacity() { return mGlobalFadeOpacity.GetValue(); }

    PointCursor* getPointCursor() const { return mPointCursor; }

private:

    /// コンストラクタ
    GameFrontendManager();

    /// デストラクタ
    ~GameFrontendManager();

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
	LFont					mNamePlateFont;

    RapidNumber<int>        mFrameXPos;

    DamagePop*              mDamagePop;


    GuideNamePlateList      mGuideNamePlateList;
	LFont					mGuidNamePlateFont;     ///< ガイド用の縁取りフォント

    u32                     mShowCharacterNamePlateCount;
	EasingValue<float>		mGlobalFadeOpacity;

    u32                     mLevelupFrameCount;
    LSprite                 mLevelupSprites[ 2 ];
    LSprite                 mLevelEffectSprite;

    PointCursor*            mPointCursor;


	FloatAnimationCurve     mFloorNumAnim;
	FloatAnimationCurve     mFloorNumAnimAlpha;
	double					mFloorNumAnimTime;
    LTexture                mFloorInfoTexture;
    LSprite                 mFloorInfoSprite[ 3 ];
    float                   mFloorInfoOffset;
};

//=============================================================================
//								end of file
//=============================================================================