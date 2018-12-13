//
// Collision.cpp
// Dat�t�@�C������f�[�^�𕜌����A
// �����蔻�������N���X
//

#include "Collision.h"

// �R���X�g���N�^
Collision::Collision()
{
    mReadFP = NULL;
}

// �f�X�g���N�^
Collision::~Collision()
{
}

// ������
void Collision::Initialize()
{
	for ( int i = 0; i < SET_H_NUM*SET_V_NUM; ++i )
		ZeroMemory( &mLoadData[ i ], sizeof( Data ) );
}

//
// LoadFile
// ���@�� const char* fileName_
// �߂�l void
//
// �����Ŏw�肳�ꂽ
// �����蔻��f�[�^�̓ǂݍ���
//
void Collision::LoadFile( const char* fileName_ )
{
    if ( mReadFP )
    {
        fclose( mReadFP );
        mReadFP = NULL;
    }

	// �ǂݍ���--------------------------
	fopen_s( &mReadFP, fileName_, "rb" );
	if ( mReadFP == NULL )
	{
		printf( "Error:dat�t�@�C���I�[�v���Ɏ��s\n" );
		printf( "�t�@�C�������݂��Ȃ����A�p�X���Ⴄ�\��������܂��B\n" );
		printf( "File< %s >\n", fileName_ );
		fclose( mReadFP );
		exit( 1 );
	}
	fread( &mLoadData, sizeof( Data ), SET_H_NUM*SET_V_NUM, mReadFP );
}

//
// getAtkCollision
// ���@�� const unsigned int ActionIdx, const unsigned int Frames
// �߂�l LRect
//
// �A�N�V�����ԍ��ƃR�}�ԍ���n����
// �@���̓���̍U���̓����蔻�肪�Ԃ�( x, y, width, height )
//
LRect* Collision::getAtkCollision( const unsigned int ActionIdx, const unsigned int Frames )
{
	int idx   = ActionIdx;
	int frame = Frames;

	// idx��2���
	if ( ActionIdx >= 6 )
	{
		idx   -= 6;
		frame += 6;
	}

	mAtkArea.set(
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.V );

	// ���ׂĂO(=�f�[�^�Ȃ�)�̏ꍇnull���^�[��
	if ( mAtkArea.x == 0
		&& mAtkArea.y == 0
		&& mAtkArea.width == 0
		&& mAtkArea.height == 0 )
	{
		//printf( "�擾�ʒu Idx %d, Frame %d �Y���f�[�^�Ȃ�\n", ActionIdx, Frames );
		return NULL;
	}

    /*
	printf( "�����蔻��擾:�w��ʒu%d,%d/�擾�ʒu%d,%d\n  �U�� ����:x %d, y %d, width %d, height %d\n",
		ActionIdx,
		Frames,
		idx,
		frame,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.V );
        */

	return &mAtkArea;
}

//
// getDmgCollision
// ���@�� const unsigned int ActionIdx, const unsigned int Frames
// �߂�l LRect
//
// �A�N�V�����ԍ��ƃR�}�ԍ���n����
// �@���̓���̃_���[�W�̓����蔻�肪�Ԃ�( x, y, width, height )
//
LRect* Collision::getDmgCollision( const unsigned int ActionIdx, const unsigned int Frames )
{
	int idx   = ActionIdx;
	int frame = Frames;

	// idx��2���
	if ( ActionIdx >= 6 )
	{
		idx   -= 6;
		frame += 6;
	}

	mDmgArea.set(
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_size.V );

	// ���ׂĂO(=�f�[�^�Ȃ�)�̏ꍇnull���^�[��
	if ( mDmgArea.x == 0
		&& mDmgArea.y == 0
		&& mDmgArea.width == 0
		&& mDmgArea.height == 0 )
	{
		printf( "�擾�ʒu Idx %d, Frame %d �Y���f�[�^�Ȃ�\n", ActionIdx, Frames );
		return NULL;
	}

	return &mDmgArea;
}

//
// getOrigin
// ���@�� const unsigned int ActionIdx, const unsigned int Frames
// �߂�l LVector2
//
// �A�N�V�����ԍ��ƃR�}�ԍ���n����
// �@���̓���̊�_���Ԃ�( x, y )
//
LVector2 Collision::getOrigin( const unsigned int ActionIdx, const unsigned int Frames )
{
	LVector2    Origin;
	int idx   = ActionIdx;
	int frame = Frames;

	// idx��2���
	if ( ActionIdx >= 6 )
	{
		idx   -= 6;
		frame += 6;
	}

	Origin.x = static_cast< float >( mLoadData[ idx*SET_H_NUM + frame ].origin.H );
	Origin.y = static_cast< float >( mLoadData[ idx*SET_H_NUM + frame ].origin.V );

	return Origin;
}

// [�R�{] �U���p�����蔻����R�}�ԍ�����擾���� (�R�}�ԍ��͍��ォ��E�ɂ����� +1�A���ɍs���ɂ�� +12)
LRect* Collision::getAtkCollisionByIndex( const unsigned int index_ )
{
    mAtkArea.set(
		mLoadData[ index_ ].Atk_pos.H,
		mLoadData[ index_ ].Atk_pos.V,
		mLoadData[ index_ ].Atk_size.H,
		mLoadData[ index_ ].Atk_size.V );

	if ( mAtkArea.x == 0
		&& mAtkArea.y == 0
		&& mAtkArea.width == 0
		&& mAtkArea.height == 0 )
	{
		return NULL;
	}

    return &mAtkArea;
}

// [�R�{] �_���[�W�p�����蔻����R�}�ԍ�����擾����
LRect* Collision::getDmgCollisionByIndex( const unsigned int index_ )
{
    mDmgArea.set(
		mLoadData[ index_ ].Dmg_pos.H,
		mLoadData[ index_ ].Dmg_pos.V,
		mLoadData[ index_ ].Dmg_size.H,
		mLoadData[ index_ ].Dmg_size.V );

	if ( mDmgArea.x == 0
		&& mDmgArea.y == 0
		&& mDmgArea.width == 0
		&& mDmgArea.height == 0 )
	{
		return NULL;
	}

	return &mDmgArea;
}

// [�R�{] ���_���R�}�ԍ�����擾����
LVector2 Collision::getOriginByIndex( const unsigned int index_ )
{
    return LVector2( 
        static_cast< float >( mLoadData[ index_ ].origin.H ),
        static_cast< float >( mLoadData[ index_ ].origin.V ) );
}

//
// checkHit
// ���@�� const LVector3 alphaPos, const LRect* alpha,
//        const LVector3 betaPos,  const LRect* beta
// �߂�l bool
//
// �����蔻���Rect��n����
// �@�������Ă��邩�ǂ�����bool�ŕԂ�
//
bool Collision::checkHit( const LVector3 alphaPos, const LRect* alpha, const LVector3 betaPos, const LRect* beta )
{
	LRect L = *alpha;
	LRect R = *beta;

	L.x      += static_cast< int >( alphaPos.x );
	L.y      += static_cast< int >( alphaPos.y );
	L.width  += static_cast< int >( alphaPos.x );
	L.height += static_cast< int >( alphaPos.y );

	R.x      += static_cast< int >( betaPos.x );
	R.y      += static_cast< int >( betaPos.y );
	R.width  += static_cast< int >( betaPos.x );
	R.height += static_cast< int >( betaPos.y );

	// �����������ق�����
	if ( L.x > R.x )
	{
		LRect temp;

		temp = L;
		L = R;
		R = temp;		
	}

	// L�̉E�[��R�̍��[�ȏ�
	if ( L.width >= R.x )
	{
		if ( L.height >= R.y )
		{
			return true;
		}
		else if ( L.y <= R.height )
		{
			return true;
		}
	}

	return false;
}

// ���
void Collision::Release()
{
	fclose( mReadFP );
}
// EOF