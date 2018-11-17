//=============================================================================
/*! 
    @addtogroup 
    @file       SceneTitle.h
    @brief      
    
    タイトルのシーン
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/13
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/13 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================

#include "../Utility/FormatText.h"

class PointCursor;

class SceneTitle : public LGameScene
{
public:

    /// コンストラクタ
    SceneTitle();

public:

    /// シーン名
    virtual const char* getSceneName() { return "SceneTitle"; }

	/// 開始処理
	virtual void onStart();

    /// フレーム更新
	virtual void onUpdate();

    /// 終了処理
	virtual void onTerminate();

    // This tale is the last message we present to everyone.

private:

    /// コマンド項目の表示開始
    void _startShowCommand( int type_ );


    /// 矢印の位置設定
    void _setPointCursorIndex( int index_ );

private:

    

    int     mStep;
    int     mFrameCount;

    

    LSprite     mRandomSprite;
    LSprite     mTitleFrameSprite;
    LSprite     mTitleTextSprite;
    LSprite     mTitleSubTextSprite;
    LSprite     mPressAnyKeySprite;

    LSprite     mTitleEffectSprite;

    LSprite     mSuperSprite[ 2 ];  // 上下の字幕スーパー
    LSprite     mCommandSprite[ 4 ];

    LSprite     mDescWindowSprite;      // 説明ウィンドウの枠
    LSprite     mDescContentsSprite;
    LTexture    mDescContents;          // 説明ウィンドウの内容
    LFont       mDescTitleFont;
    int         mWindowFadeCount;

	FloatAnimationCurve  mRoundTripValue;        ///< 0.2 ～1.0 を往復する値。アルファ値用

	FloatAnimationCurve  mCommandFadeInX;
	FloatAnimationCurve  mCommandFadeInOpacity;

    Utility::FormatText mFormatText;


    int         mEntryedStep;
    int         mSelectIndex;
 
    PointCursor*    mPointCursor;

    int         mEndFrameCount;
};

//=============================================================================
//								End of File
//=============================================================================