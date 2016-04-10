//=============================================================================
// �� Arrange_Ring
// 2011/1/21 Keisuke Hosoda
//
// ����F
//  2�����ɂ����钆�S�_����̉~����̍��W��Ԃ�
//=============================================================================
#include "stdafx.h"
#include "Arrange_Ring.h"
#include <d3dx9math.h>
#include <windows.h>

// �R���X�g���N�^
Ring::Ring()
{
	ZeroMemory( &mStdCir, sizeof( StandardCircle ) );
	ZeroMemory( &mSData, sizeof( StarData ) );
	ZeroMemory( &mTData, sizeof( TurnData ) );
}

// �f�X�g���N�^
Ring::~Ring()
{
}

//---------------------------------------------------------------------
// < 2011/1/21 Keisuke_Hosoda >
//
// �֐����F Initialize
//
//  ���� �F < void >
// �߂�l�F < void >
//  ���� �F �������B�g�p�O�Ɉ�x�����ĂԂ���
//---------------------------------------------------------------------
void Ring::Initialize()
{
	mTData.InputLock = false;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F Process
//
//  ���� �F < void >
// �߂�l�F < void >
//  ���� �F ���[�v�̒��ŌĂԂ���
//---------------------------------------------------------------------
void Ring::Process()
{
	mTData.OldTurnVec = mTData.TurnVec;

	// ��]���Ă��邩�ǂ���
	if ( mTData.TurnVec != 0 )
	{
		float ditect = 1;

		// ��]���͓��͂��󂯕t���Ȃ�
		mTData.InputLock = true;

		// ��]����
		if ( mTData.TurnVec > 0 ) ditect = -1;

		mTData.Deg += mTData.TurnSpeed * ditect;
		mTData.TurnLimit += mTData.TurnSpeed;
	}

	// ��]�p�x��͈͓��Ɏ��߂�
	if ( mTData.Deg < 0 )
		mTData.Deg += 360;
	
	if ( mTData.Deg >= 360 )
		mTData.Deg -= 360;

	// ��]��̊���W�ɂ���Star�̓Y����
	if ( mSData.Angle <= mTData.TurnLimit )
	{
		mTData.TurnVec   = 0;
		mTData.TurnLimit = 0;
		mTData.InputLock = false;

		if ( mTData.OldTurnVec > 0 )
		{
			if ( mSData.Target < ( mSData.setNum-1 ) )
				++mSData.Target;
			else
				mSData.Target = 0;
		}
		else
		{
			if ( mSData.Target > 0 )
				--mSData.Target;
			else
				mSData.Target = ( mSData.setNum-1 );
		}

		ResetDeg( &mSData.Target );
	}

	// �p�x����~����̍��W���擾
	for ( unsigned int i = 0; i < mSData.setNum; ++i )
	{
		mTData.Rad = D3DXToRadian( mTData.Deg + ( mSData.Angle * i ) + mSData.OriginDeg );
		mSData.Pos[ i ].x = mStdCir.Origin.x + mStdCir.Radius.x * cos( mTData.Rad );
		mSData.Pos[ i ].y = mStdCir.Origin.y - mStdCir.Radius.y * sin( mTData.Rad );
	}
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F Release
//
//  ���� �F < void >
// �߂�l�F < void >
//  ���� �F ��������B�K�������I�ɌĂԂ���
//---------------------------------------------------------------------
void Ring::Release()
{
}

// �ȉ��Z�b�^���Q�b�^

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setCircleOrigin
//
//  ���� �F < const int x, const int y >
// �߂�l�F < void >
//  ���� �F �����w��̏ꏊ���~�̌��_�Ƃ���
//---------------------------------------------------------------------
void Ring::setCircleOrigin( const int x, const int y )
{
	mStdCir.Origin.x = static_cast< float >( x );
	mStdCir.Origin.y = static_cast< float >( y );
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setCircleSize
//
//  ���� �F < const float width, const float height >
// �߂�l�F < void >
//  ���� �F �~�̑傫���������Ŏw�肷��
//---------------------------------------------------------------------
void Ring::setCircleSize( const float width, const float height )
{
	mStdCir.Radius.x = width;
	mStdCir.Radius.y = height;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setCircle
//
//  ���� �F < const int x, const int y, 
//            const float width, const float height >
// �߂�l�F < void >
//  ���� �F �~�̃f�[�^�������Ŏw�肷��
//---------------------------------------------------------------------
void Ring::setCircle( const int x, const int y, const float width, const float height )
{
	mStdCir.Origin.x = static_cast< float >( x );
	mStdCir.Origin.y = static_cast< float >( y );
	mStdCir.Radius.x = width;
	mStdCir.Radius.y = height;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setStarNum
//
//  ���� �F < const unsigned int number >
// �߂�l�F < void >
//  ���� �F �~����ɕ��ԍ��W( Star )�̐���ݒ�
//---------------------------------------------------------------------
void Ring::setStarNum( const unsigned int number )
{
	mSData.setNum = number;

	for ( unsigned int i = 0; i < number; ++i )
	{
		HVector2 star;
		ZeroMemory( &star, sizeof( HVector2 ) );
		mSData.Pos.push_back( star );
	}
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setOriginDeg
//
//  ���� �F < const float degree >
// �߂�l�F < void >
//  ���� �F Star�̊�p�x�������w��
//---------------------------------------------------------------------
void Ring::setOriginDeg( const float degree )
{
	mSData.OriginDeg = degree;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setTarget
//
//  ���� �F < const unsigned int idx >
// �߂�l�F < void >
//  ���� �F ��ʒu�Ɉ����w���Star��z�u
//---------------------------------------------------------------------
void Ring::setTarget( const unsigned int idx )
{
	mSData.Target = idx;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setTurnDirection
//
//  ���� �F < const int direct >
// �߂�l�F < void >
//  ���� �F ��]�����A-1, 0, 1�Ŏw��
//---------------------------------------------------------------------
void Ring::setTurnDirection( const int direct )
{
	mTData.TurnVec = direct;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F setTurnSpeed
//
//  ���� �F < const float speed >
// �߂�l�F < void >
//  ���� �F ��ʒu�Ɉ����w���Star��z�u
//---------------------------------------------------------------------
void Ring::setTurnSpeed( const float speed )
{
	mTData.TurnSpeed = speed;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F ResetDeg
//
//  ���� �F < const int target >
// �߂�l�F < void >
//  ���� �F ����W�Ɉ����w���Star���Z�b�g����
//---------------------------------------------------------------------
void Ring::ResetDeg( const unsigned int *target )
{
	calcAngle();
	mTData.Deg = 360 - ( mSData.Angle * static_cast< float >( *target ) );
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// �֐����F calcAngle
//
//  ���� �F < void >
// �߂�l�F < void >
//  ���� �F �~����̓_�𓙊Ԋu�ɕ��ׂ邽�߂̊p�x���v�Z�B
//    ��_���猩�čœK�Ȋp�x�ɒ�������B
//    ���������邽�тɈ�x�����ĂԁB
//---------------------------------------------------------------------
void Ring::calcAngle()
{
	if ( mSData.setNum != 0 )
		mSData.Angle = 360 / static_cast< float >( mSData.setNum );
	else
		mSData.Angle = 0;
}

//=============================================================================
//								End of File
//=============================================================================