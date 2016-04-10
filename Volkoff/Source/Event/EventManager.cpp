//=============================================================================
/*! 
    @addtogroup 
    @file       EventManager.cpp
    @brief      
    
    EventManagerクラスの実装
    
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
*/
//=============================================================================



/*! @par include */
#include "stdafx.h"
#include "./EventManager.h"

#if 0

//---------------------------------------------------------------------------
/*! 
	@brief EventManager::EventManager

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
EventManager::EventManager()
{
	this->m_unNextHandle = 1;
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::~EventManager

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
EventManager::~EventManager()
{
	this->Release();
}


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
bool EventManager::Initialize()
{
	this->Release();

	this->m_unNextHandle = 1;

	return true;
}


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
bool EventManager::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::Update

	フレーム更新処理

	@param[in]      void
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void EventManager::Update()
{
	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::AddListener

	リスナーをリストに追加する

	@param[in]      EventListener *pCListener 追加するリスナーポインタ
	@return         unsigned int リスナーハンドル
	@exception      none
*/
//---------------------------------------------------------------------------
unsigned int EventManager::AddListener(EventListener *pCListener)
{
	pCListener->setHandle(this->m_unNextHandle);
	this->m_dqListenerList.push_back(pCListener);
	this->m_mListenerMap.insert(std::pair<unsigned int,EventListener*>(this->m_unNextHandle,pCListener));

	return (m_unNextHandle++);
}


//---------------------------------------------------------------------------
/*! 
	@brief EventManager::RemoveListener

	リスナーをリストから削除する

	@param[in]      EventListener *pCListener 削除するリスナーポインタ
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
void EventManager::RemoveListener(EventListener *pCListener)
{
	for(std::deque<EventListener*>::iterator itr = this->m_dqListenerList.begin();itr != this->m_dqListenerList.end();++itr)
	{
		if((*itr) == pCListener)
		{
			this->m_dqListenerList.erase(itr);
			break;
		}
	}

	for(std::map<unsigned int,EventListener*>::iterator itr = this->m_mListenerMap.begin();itr != this->m_mListenerMap.end();++itr)
	{
		if((*itr).second == pCListener)
		{
			this->m_mListenerMap.erase(itr);
			break;
		}
	}

	return;
}

#endif

//=============================================================================
//								End of File
//=============================================================================