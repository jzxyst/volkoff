//=============================================================================
//�y Character_BareHands �z
//-----------------------------------------------------------------------------
//  �f���Ԃ̓���̒�`
//=============================================================================

//---------------------------------------------------------------------
// �� �t���[���X�V
//      chara_       : Character �̃|�C���^
//      state_       : �L�����N�^�[�̏�� (enum CharaState �̒l)
//      frame_count_ : �A�j���t���[���� (���̊֐����I�������� +1 �����)
//---------------------------------------------------------------------
function update( chara_, state_, frame_count_ )

    //-------------------------------------------------------------
    // �� �ҋ@���
    if state_ == CHARASTATE_WAIT then
    
        setPuttern( chara_, 0 )
		setFrameCount( chara_, -1 )
        
	//-------------------------------------------------------------
    // �� ������
    elseif state_ == CHARASTATE_RUN then

		if getOnGround( chara_ ) then
			// �n��ł͕��s���[�V����
			if frame_count_ < 23 then
				setPuttern( chara_, 12 + frame_count_ / 4 )
			else
				// �o�߃t���[������ 0 �ɖ߂�
				setFrameCount( chara_, -1 )
			end
		else
			// �󒆂ł̓W�����v���[�V����
			if frame_count_  <= 7 then
				setPuttern( chara_, 24 + frame_count_ / 2 )
			elseif frame_count_ >= 8 then
				setPuttern( chara_, 27 )
				setFrameCount( chara_, 8 )
			end
		end

	//-------------------------------------------------------------
    // �� �W�����v
    elseif state_ == CHARASTATE_JUMP then

		if frame_count_  <= 7 then
			setPuttern( chara_, 24 + frame_count_ / 2 )
		elseif frame_count_ == 8 then
			setPuttern( chara_, 27 )
		end

	//-------------------------------------------------------------
    // �� ���Ⴊ��
    elseif state_ == CHARASTATE_SQUAT then

		if frame_count_ < 2 then
			setPuttern( chara_, 36 )
		else
			setPuttern( chara_, 37 )
            setFrameCount( chara_, 3 )
		end

	//-------------------------------------------------------------
    // �� �̂�����
    elseif state_ == CHARASTATE_STUN then

		setPuttern( chara_, 48 )
        
	//-------------------------------------------------------------
    // �� �������
    elseif state_ == CHARASTATE_BLOW then

		if frame_count_ == 1 then
			setPuttern( chara_, 60 )
		end
		if frame_count_ == 3 then
			setPuttern( chara_, 61 )
		end
		if frame_count_ == 5 then 
			setPuttern( chara_, 62 )
		end
		if frame_count_ == 7 then 
			setPuttern( chara_, 63 )
		end
		if frame_count_ == 9 then 
			setPuttern( chara_, 64)
		end
		if frame_count_ == 11 then
			setPuttern( chara_, 65)
		end
		//setFrameCount( chara_, -1 )

    // �� �K�[�h
    elseif state_ == CHARASTATE_GUARD then

		setPuttern( chara_, 86 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // �� ���Ⴊ�݃K�[�h
    elseif state_ == CHARASTATE_SQGUARD then
		setPuttern( chara_, 74 )
		setFrameCount( chara_, 3 )

	//-------------------------------------------------------------
    // �� �͂����ҋ@
    elseif state_ == CHARASTATE_LADDER_WAIT then
		// �Ȃɂ����Ȃ��B���~���[�V�����~�߂�΂���

	//-------------------------------------------------------------
    // �� �͂������/�~�� �������[�V�����Ȃ̂œ���
    elseif state_ == CHARASTATE_LADDER_UP or
		state_ == CHARASTATE_LADDER_DOWN or
		state_ == CHARASTATE_LADDER_WAIT then

		setPuttern( chara_, 96 + frame_count_ / 10 )

		if frame_count_ == 19 then
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // �� �A�C�e���E��
    elseif state_ == CHARASTATE_ITENGET then

	//-------------------------------------------------------------
    // �� ���S
    elseif state_ == CHARASTATE_DEAD then

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_ <= 19 then
			setPuttern( chara_, 102 + frame_count_ / 4 ) 
			//
			// ����I���A������܂ōŌ�̃R�}��\��
			//
		elseif frame_count_ == 20 then
			setPuttern( chara_, 102 + 4 )
		end

		return
	

	//-------------------------------------------------------------
    // �� �ʏ�U�� 1 �i��
    elseif state_ == CHARASTATE_ATTACK_1 then

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 1 then		        	
			PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			setPuttern( chara_, 6)
			x, y = getCharaPosition( chara_ )
			GrenadeGenerate(chara_,x,y+40,4,6,0.3,110,50,1,-20,5,100,30,10,10)
			if CheckWeaponBreak( chara_, 1 ) == 1 then
				setBreakWeapon( chara_ );
			end
		end
		if frame_count_== 3 then		        	
			setPuttern( chara_, 7)
		end
		if frame_count_== 5 then		        	
			setPuttern( chara_, 8)
		end
		if frame_count_== 7 then		        	
			setPuttern( chara_, 9)
		end
		if frame_count_== 9 then		        	
			setPuttern( chara_, 10)
		end
		if frame_count_==11 then		        	
			setPuttern( chara_, 11)
			AttackUnLock( chara_ )
		end


		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
		if frame_count_ == 11 then

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // �� �ʏ�U�� 2 �i��
    elseif state_ == CHARASTATE_ATTACK_2 then
				setCharaState( chara_, CHARASTATE_WAIT )
			AttackUnLock( chara_ )
	//-------------------------------------------------------------
    // �� �ʏ�U�� 3 �i��
    elseif state_ == CHARASTATE_ATTACK_3 then
				setCharaState( chara_, CHARASTATE_WAIT )
				AttackUnLock( chara_ )	

	//-------------------------------------------------------------
    // �� �W�����v�U��
	elseif state_ == CHARASTATE_ATTACK_JUMP_ATTACK then
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 1 then		        	
			PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			x, y = getCharaPosition( chara_ )
			GrenadeGenerate(chara_,x,y+40,4,7.5,0.3,110,50,1,-20,5,100,30,10,10)
			if CheckWeaponBreak( chara_, 1 ) == 1 then
				setBreakWeapon( chara_ );
			end
			setPuttern( chara_, 6)
		end
		if frame_count_== 3 then		        	
			setPuttern( chara_, 7)
		end
		if frame_count_== 5 then		        	
			setPuttern( chara_, 8)
		end
		if frame_count_== 7 then		        	
			setPuttern( chara_, 9)
		end
		if frame_count_== 9 then		        	
			setPuttern( chara_, 10)
		end
		if frame_count_==11 then		        	
			setPuttern( chara_, 11)
			AttackUnLock( chara_ )
		end


		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
		if frame_count_ == 11 then

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end
	//-------------------------------------------------------------
    // �� ���Ⴊ�ݍU��
	elseif state_ == CHARASTATE_ATTACK_SQUAT_ATTACK then
				setCharaState( chara_, CHARASTATE_WAIT )
			AttackUnLock( chara_ )

	//-------------------------------------------------------------
    // �� �΋�U��
	elseif state_ == CHARASTATE_ATTACK_ANTIAIR_ATTACK then
				setCharaState( chara_, CHARASTATE_WAIT )
			AttackUnLock( chara_ )
	end
end

//=============================================================================
//                              end of file
//=============================================================================
