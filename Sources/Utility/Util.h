//=============================================================================
//�y Util �z
//-----------------------------------------------------------------------------
///**
//  @file       Util.h
//  @brief      Util
//  @author     yama
//  @par
//              ���ɕ��ނł��Ȃ����̂Ƃ��A�ȒP�Ȋ֐��Ƃ��������Ă����Ƃ���B
//*/
//=============================================================================

#pragma once

//=============================================================================
// �� Util �N���X
//-----------------------------------------------------------------------------
///**
//  @brief      ���[�e�B���e�B�֐��B�Ƃ肠�������m�X�e�C�g�B
//*/
//=============================================================================
class Util
{
public:

    //---------------------------------------------------------------------
    ///**
    //  @brief      ��`���m���d�Ȃ��Ă��邩�𔻒肷��
    //
    //  @param[in]  rect0_        : ���[���h���W��̋�`
    //  @param[in]  rect1_        : ���[���h���W��̋�`
    //
    //  @return     �d�Ȃ��Ă����ꍇ true
    //*/
    //---------------------------------------------------------------------
    static bool judgeCollitionRect( const LRect& rect0_, const LRect& rect1_ )
    {
        /*
        int l0, t0, r0, b0;
        int l1, t1, r1, b1;

        l0 = rect0_.X;
        t0 = rect0_.Y - rect0_.height;
        b0 = rect0_.Y;
        r0 = rect0_.X + rect0_.width;

        l1 = rect1_.X;
        t1 = rect1_.Y - rect1_.height;
        b1 = rect1_.Y;
        r1 = rect1_.X + rect1_.width;

        if ( l0 <= r1 && r0 >= l1 && t0 <= b1 && b0 >= t1 )
        {
            return true;
        }

        return false;
        */

        if ( rect0_.x                       <= ( rect1_.x + rect1_.width ) &&
             ( rect0_.x + rect0_.width )    >= rect1_.x &&
             ( rect0_.y - rect0_.height )   <= rect1_.y &&
             rect0_.y                       >= ( rect1_.y - rect1_.height ) )
        {
            return true;
        }

        return false;
    }

    //---------------------------------------------------------------------
    ///**
    //  @brief      ���l�̊e���̒l��z��Ɋi�[����
    //
    //  @param[in]  num_        : ���l (�����Ȃ�)
    //  @param[in]  max_digits_ : �ő包�� (�����ɖ����Ȃ��ꍇ�� 0 ���i�[����)
	//  @param[in]  result_     : ���ʂ��i�[����z��(��̌����珇)
    //*/
    //---------------------------------------------------------------------
    static void numberToArray( u32 num_, u32 max_digits_, u32* result_ )
    {
        int div = 10 * max_digits_;
        int idx = max_digits_ - 1;  // �z��ւ̏������݈ʒu

        for ( ; idx >= 0; --idx )
        {
            result_[ idx ] = num_ % 10;
            num_ /= 10;
        }
    }

	/// numberToArray() �ɂ����āA��̌��� 0 �̏ꍇ�� ������ -1 ���i�[����
	static void numberToArray2( u32 num_, u32 max_digits_, int* result_ )
    {
        u32 result[ 64 ];
		numberToArray( num_, max_digits_, result );
		u32 i = 0;
		for ( ; i < max_digits_; ++i )
		{
			if ( result[ i ] == 0 )
			{
				result_[ i ] = -1;
			}
			else
			{
				break;
			}
		}
		for ( ; i < max_digits_; ++i )
		{
			result_[ i ] = result[ i ];
		}
    }


	/// �����̌����𒲂ׂ�
	static inline int getNumberDigits(int x_) { int i = 0; while (x_ != 0) { ++i; x_ /= 10; } return i; }

	/// �����̌����𒲂ׂ�
	static inline int getNumberDigits(lnU32 x_) { int i = 0; while (x_  > 0) { ++i; x_ /= 10; } return i; }
};

//=============================================================================
//								end of file
//=============================================================================