//=============================================================================
/*! 
    @addtogroup 
    @file       Box.h
    @brief      ���I�u�W�F�N�g
    
    Box�N���X�̒�`
    
    @attention  -
    @note       -
    @author     matui
    @date       2011/10/26
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/26 matsui
      -# �쐬
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_BOX_H__
#define __INCLUDE_BOX_H__


/*! @par include */
#include "./../GameObject.h"


/*! @par global */
static const char g_szBoxFilePath[] = "./Data/Graphics/Object/Box.png";


/*! @class Ladder */
class Box : public AttackedObject
{
private:
	LBatchPanel mPanel;
	int m_nAnime;
	int m_nFrame;
	bool m_bCreate;
public:
	//---------------------------------------------------------------------------
	/*! @brief �����o�Q�b�^�[ */
	//---------------------------------------------------------------------------
	virtual ObjectType getObjType() const { return OBJ_BOX; }

	//---------------------------------------------------------------------------
	/*! @brief �����o�Z�b�^�[ */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::Box

		�f�t�H���g�R���X�g���N�^

		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	Box();

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::~Box

		�f�X�g���N�^

		@param[in]      none
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~Box();

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::Initialize

		����������

		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize();

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::Release

		�I������

		@param[in]      void
		@return         bool
		- true  ����
		- false ���s
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::Update

		�t���[���X�V����

		@param[in]      void
		@return         bool
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Update();

	//---------------------------------------------------------------------------
	/*! 
		@brief Box::HandleEvent

		�C�x���g����

		@param[in]      EventType event_ �C�x���g�^�C�v
		@param[in]      void      *args_ �f�[�^(�K���ɃL���X�g����)
		@return         void
		@exception      none
	*/
	//---------------------------------------------------------------------------
	int HandleEvent(u32 event_,void *args_);

	//
	// Box::getBoundingRect
	//
	// �דc�ǉ��E�����蔻���Ԃ�
	//
	const LRect* Box::getBoundingRect();
};


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================