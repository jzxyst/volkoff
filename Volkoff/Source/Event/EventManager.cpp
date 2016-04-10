//=============================================================================
/*! 
    @addtogroup 
    @file       EventManager.cpp
    @brief      
    
    EventManager�N���X�̎���
    
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
      -# �쐬
*/
//=============================================================================



/*! @par include */
#include "stdafx.h"
#include "./EventManager.h"

#if 0

//---------------------------------------------------------------------------
/*! 
	@brief EventManager::EventManager

	�f�t�H���g�R���X�g���N�^

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

	�f�X�g���N�^

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

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
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

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
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

	�t���[���X�V����

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

	���X�i�[�����X�g�ɒǉ�����

	@param[in]      EventListener *pCListener �ǉ����郊�X�i�[�|�C���^
	@return         unsigned int ���X�i�[�n���h��
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

	���X�i�[�����X�g����폜����

	@param[in]      EventListener *pCListener �폜���郊�X�i�[�|�C���^
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