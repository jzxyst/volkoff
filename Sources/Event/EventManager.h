//=============================================================================
/*! 
    @addtogroup 
    @file       EventManager.h
    @brief      EventListenerの管理
    
    EventManagerの定義
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/17
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/17 Hi-ra Mizuo
      -# 作成

    - 2011/10/21 yama
      -# 廃止
*/
//=============================================================================

#if 0

//Include Guard
#ifndef __INCLUDE_EVENTMANAGER_H__
#define __INCLUDE_EVENTMANAGER_H__


/*! @par include */
#include "./../Utility/Singleton.h"
#include "./EventType.h"
#include <deque>
#include <map>


/*! @class EventManager */
class EventManager : public Singleton<EventManager>
{
	friend Singleton<EventManager>;

private:
	/*! @par privateメンバ変数 */
	std::deque<EventListener*> m_dqListenerList;
	std::map<unsigned int,EventListener*> m_mListenerMap;

	unsigned int m_unNextHandle;

private:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::EventManager

		デフォルトコンストラクタ

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	EventManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::~EventManager

		デストラクタ

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~EventManager();

public:
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::Initialize

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
		@brief EventManager::Release

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
		@brief EventManager::Update

		フレーム更新処理

		@param[in]      void
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::AddListener

		リスナーをリストに追加する

		@param[in]      EventListener *pCListener 追加するリスナーポインタ
		@return         unsigned int リスナーハンドル
		@exception      none
	*/
	//---------------------------------------------------------------------------
	unsigned int AddListener(EventListener *pCListener);

	//---------------------------------------------------------------------------
	/*! 
		@brief EventManager::RemoveListener

		リスナーをリストから削除する

		@param[in]      EventListener *pCListener 削除するリスナーポインタ
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	void RemoveListener(EventListener *pCListener);
};


//End of Include Guard
#endif

#endif

//=============================================================================
//								End of File
//=============================================================================