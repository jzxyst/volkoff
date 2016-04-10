//=============================================================================
/*! 
    @addtogroup 
    @file       EventListener.cpp
    @brief      
    
    EventListenerクラスの実装
    
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
#include "./EventType.h"
#include "./EventManager.h"

#if 0

//---------------------------------------------------------------------------
/*! 
	@brief EventListener::EventListener

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
EventListener::EventListener() : mHandle (0)
{
	this->mHandle = EventManager::getInstance()->AddListener(this);
}


//---------------------------------------------------------------------------
/*! 
	@brief EventListener::~EventListener

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
EventListener::~EventListener()
{
	EventManager::getInstance()->RemoveListener(this);
}

#endif

//=============================================================================
//								End of File
//=============================================================================