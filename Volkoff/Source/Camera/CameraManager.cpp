//=============================================================================
/*! 
    @addtogroup 
    @file       CameraManager.cpp
    @brief      �J�����̊Ǘ�
    
    CameraManager�w�b�_�̎���
    
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
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "stdafx.h"
#include "./CameraManager.h"
#include "./../Game/GameManager.h"
#include "./../Object/Player.h"


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::CameraManager

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
CameraManager::CameraManager()
{
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::~CameraManager

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
CameraManager::~CameraManager()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool CameraManager::Initialize()
{
	//�J�����̏����ʒu
	//LVector3 v(GameManager::getInstance()->getPlayer()->getPosition().x,(GameManager::getInstance()->getPlayer())->getPosition().y + 80,-1200.0f);
	//LVector3 look(v);

	//Camera::GetMain3DCamera()->setPosition(v);
 //   v.z = 0;
	//Camera::GetMain3DCamera()->setLookAt(v);

	this->m_eMode = CAMERA_UNDEF;
	this->m_pCLookObj = NULL;

	Camera::GetMain3DCamera()->SetFovY(Math::PI * 0.125);

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool CameraManager::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::Update

	�t���[���X�V����
        
	@param[in]      void
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void CameraManager::Update()
{
	LVector3 v;

	switch(this->m_eMode)
	{
	case CAMERA_UNDEF:
		break;

	case CAMERA_MOVE:
		v = Camera::GetMain3DCamera()->GetPosition();
		v += this->m_CVector;
		Camera::GetMain3DCamera()->SetPosition(v);
		v.z = 0;
		Camera::GetMain3DCamera()->SetLookAt(v);
		break;

	case CAMERA_LOOK_OBJECT:
		v = this->m_pCLookObj->getPosition();
		v.y += 80;
		v.z = -1200.0f;
		Camera::GetMain3DCamera()->SetPosition(v);
		v.z = 0;
		Camera::GetMain3DCamera()->SetLookAt(v);
		break;

	case CAMERA_LOOK_PLAYER:
		v = GameManager::getInstance()->getPlayer()->getPosition();
		v.y += 80;
		v.z = -1200.0f;
		Camera::GetMain3DCamera()->SetPosition(v);
		v.z = 0;
		Camera::GetMain3DCamera()->SetLookAt(v);
		break;

	default:
		break;
	}

	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::Move

	�w�肳�ꂽ�ʒu���瓮��������
        
	@param[in]      LVector3 pos_    - �n�_
	@param[in]      LVector3 vector_ - �x�N�g��
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void CameraManager::Move(LVector3 pos_,LVector3 vector_)
{
	this->m_CVector = vector_;
	Camera::GetMain3DCamera()->SetPosition(pos_);
	this->m_eMode = CAMERA_MOVE;

	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief CameraManager::ChaseObject

	�w�肳�ꂽ�I�u�W�F�N�g��ǔ�����
        
	@param[in]      GameObject *pObj_ - �I�u�W�F�N�g�|�C���^
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void CameraManager::ChaseObject(GameObject *pObj_)
{
	this->m_pCLookObj = pObj_;
	this->m_eMode = CAMERA_LOOK_OBJECT;

	return;
}


//=============================================================================
//								End of File
//=============================================================================
