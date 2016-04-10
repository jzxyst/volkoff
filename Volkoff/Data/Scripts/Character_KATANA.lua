//=============================================================================
//�y Character_KATANA �z
//-----------------------------------------------------------------------------
//  ��������Ԃ̓���̒�`
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
        
	//-------------------------------------------------------------
    // �� ������
    elseif state_ == CHARASTATE_RUN then

		if getOnGround( chara_ ) then
			// �n��ł͕��s���[�V����
			if frame_count_ < 29 then
				setPuttern( chara_, 12 + frame_count_ / 5 )
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

			// �o�߃t���[������ 3 �ŌŒ�
			// �I�[�o�[�t���[�|����ŁB
            setFrameCount( chara_, 3 )
		end

	//-------------------------------------------------------------
    // �� �̂�����
    elseif state_ == CHARASTATE_STUN then

		setPuttern( chara_, 48 )
		setFrameCount( chara_, -1 )
        
	//-------------------------------------------------------------
    // �� �������
    elseif state_ == CHARASTATE_BLOW then

		setPuttern( chara_, 60 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // �� �K�[�h
    elseif state_ == CHARASTATE_GUARD then

		setPuttern( chara_, 72 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // �� ���Ⴊ�݃K�[�h
    elseif state_ == CHARASTATE_SQGUARD then
		setPuttern( chara_, 84 )
		setFrameCount( chara_, 3 )

	//-------------------------------------------------------------
    // �� �͂����ҋ@
    elseif state_ == CHARASTATE_LADDER_WAIT then
		// �Ȃɂ����Ȃ��B���~���[�V�����~�߂�΂���

		setFrameCount( chara_, frame_count_ - 1  )

	//-------------------------------------------------------------
    // �� �͂������/�~�� �������[�V�����Ȃ̂œ���
    elseif state_ == CHARASTATE_LADDER_UP or
		state_ == CHARASTATE_LADDER_DOWN then

		if frame_count_ == 0 then
			setPuttern( chara_, 96 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 97 )
		end

		if frame_count_ == 14 then
			setPuttern( chara_, 98 )
		end

		if frame_count_ == 21 then
			setPuttern( chara_, 97 )
		end

		if frame_count_ == 28 then
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
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 10 )
		end

		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 9 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)		
			AttackUnLock( chara_ )

			if getBreakWeapon( chara_ ) == 1 then
				PlaySE("./Data/Sound/SE/WEAPON_BREAK.wav",50,120)
				setPuttern( chara_, 0 )
			else
				setPuttern( chara_, 11 )
			end
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �U������t���[��
		if frame_count_ == 6 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 15,   20,      15,    2.0,  2.0,    10 )
					
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end
        
		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//

		if frame_count_ == 18 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // �� �ʏ�U�� 2 �i��
    elseif state_ == CHARASTATE_ATTACK_2 then

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setVelocity( chara_, 20, 0 )
			 setPuttern( chara_, 18 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 19 )
			setVelocity( chara_, 20, 0 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 21 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 22 )
		end

		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 9 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )

			if getBreakWeapon( chara_ ) == 1 then
				PlaySE("./Data/Sound/SE/WEAPON_BREAK.wav",50,120)
				setPuttern( chara_, 0 )
			else
				setPuttern( chara_, 23 )
			end
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 6 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 19,   20,      15,   10.0,  2.0,    15 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
		if frame_count_ == 18 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end

	//-------------------------------------------------------------
    // �� �ʏ�U�� 3 �i��
    elseif state_ == CHARASTATE_ATTACK_3 then
		
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,120)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 30 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 31 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 32 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 33 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 34 )
		end

		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 10 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 35 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 6 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  35,   20,      15,   12.0,  2.0,    60 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 30 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			else
				PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end

	//-------------------------------------------------------------
    // �� �W�����v�U��
	elseif state_ == CHARASTATE_ATTACK_JUMP_ATTACK then

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 9 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 58 )
		end

			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		if frame_count_ == 16 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
			setPuttern( chara_, 27 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 5 or
			frame_count_ == 8 or
			frame_count_ == 9 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  16,   30,      30,    3.0,  -5.0,    30 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 18 then

			if getBreakWeapon( chara_ ) == 1 then
				PlaySE("./Data/Sound/SE/WEAPON_BREAK.wav",50,120)
				setPuttern( chara_, 27 )
			end

			setCharaState( chara_, CHARASTATE_JUMP )
			setFrameCount( chara_, 8 )
        end

	//-------------------------------------------------------------
    // �� ���Ⴊ�ݍU��
	elseif state_ == CHARASTATE_ATTACK_SQUAT_ATTACK then

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 42 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 43 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 44 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 45 )
		end

		if frame_count_ == 9 then
			setPuttern( chara_, 46 )
		end

			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		if frame_count_ == 12 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
			setPuttern( chara_, 47 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 6 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  15,   20,      15,    2.0,  2.0,    10 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 18 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 47 )
			end

			setCharaState( chara_, CHARASTATE_SQUAT )
			setFrameCount( chara_, 5 )
        end

	//-------------------------------------------------------------
    // �� �΋�U��
	elseif state_ == CHARASTATE_ATTACK_ANTIAIR_ATTACK then

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 66 )
			 setVelocity( chara_, -10, 0 )
		end

       if frame_count_ == 4 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 68 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 69 )
		end

		if frame_count_ == 9 then
			setPuttern( chara_, 70 )
		end

			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		if frame_count_ == 12 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
			setPuttern( chara_, 71 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 6 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  16,   20,      15,    8.0,  10.0,    20 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 18 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end
	end
end

//=============================================================================
//                              end of file
//=============================================================================
