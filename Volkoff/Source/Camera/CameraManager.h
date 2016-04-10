//=============================================================================
/*! 
    @addtogroup 
    @file       CameraManager.h
    @brief      カメラの管理
    
    CameraManagerの定義
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/12/12
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/12/12 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_CAMERAMANAGER_H__
#define __INCLUDE_CAMERAMANAGER_H__


/*! @par include */
#include "./../Utility/Singleton.h"
#include "./../Object/GameObject.h"


/*! @enum CameraMode */
typedef enum _ENUM_CAMERA_MODE
{
	CAMERA_UNDEF = 0,
	CAMERA_ZOOM_IN,
	CAMERA_ZOOM_OUT,
	CAMERA_MOVE,
	CAMERA_LOOK_OBJECT,
	CAMERA_LOOK_PLAYER,
}CameraMode;


/*! @class GameObjectManager */
class CameraManager : public Singleton<CameraManager>
{
	friend Singleton<CameraManager>;

private:
	/*! @par privateメンバ変数 */
	CameraMode m_eMode;
	GameObject *m_pCLookObj;
	LVector3 m_CVector;

private:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::CameraManager

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	CameraManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::~CameraManager

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~CameraManager();

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
	void setMode(CameraMode eMode_) {this->m_eMode = eMode_;}

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::Initialize

		初期化処理

		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize();

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::Release

		終了処理

		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::Update

		フレーム更新処理
        
		@param[in]      void
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::Move

		指定された位置から動き続ける
        
		@param[in]      LVector3 pos_    - 始点
		@param[in]      LVector3 vector_ - ベクトル
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void Move(LVector3 pos_,LVector3 vector_);

	//---------------------------------------------------------------------------
	/*! 
		@brief CameraManager::ChaseObject

		指定されたオブジェクトを追尾する
        
		@param[in]      GameObject *pObj_ - オブジェクトポインタ
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void ChaseObject(GameObject *pObj_);
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================
