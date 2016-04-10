//=============================================================================
/*! 
    @addtogroup 
    @file       SceneGame.h
    @brief      
    
    ゲームのメインとなるシーンの定義
    
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


/*! @par include */
#include "../Map/MapManager.h"
#include "../Object/Player.h"


/*! @par global */
static const int scg_nCameraSceneFrame[] = {1,180,360,540};


/*! @class SceneGame
	@brief SceneGameクラス

	ゲームのメインとなるシーン
*/
class SceneGame : public LGameScene
{
public:

    /// コンストラクタ
    SceneGame();

public:

    /// シーン名
    virtual const char* getSceneName() { return "SceneGame"; }

	/// 開始処理
	virtual void onStart();

    /// フレーム更新
	virtual void onUpdate();

    /// 終了処理
	virtual void onTerminate();

private:

    MapManager*     mMapManager;

	//Debug
	int mFrameCount;
	int mUBW;
	bool mBeginScene;
    int mBossCollapseCount;
	
};

//=============================================================================
//								End of File
//=============================================================================
