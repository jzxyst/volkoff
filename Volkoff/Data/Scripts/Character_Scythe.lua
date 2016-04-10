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
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 1 then
				PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			setPuttern( chara_, 6 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ ==9 then
			setPuttern( chara_,8 )
			setVelocity( chara_,16,1.5 )
			PlaySE("./Data/Sound/SE/metal01.wav",150,140)
		end
		if frame_count_ ==15 then
			setPuttern( chara_, 7 )
		end

		if frame_count_== 9 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun

					attackEffect( chara_, target,	  10,   10,      5,    1.0,  1.0,    25 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end	    

				end
			end
		end
		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==11 then	
			AttackUnLock( chara_ )
		end
		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
		if frame_count_ == 32 then

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
						PlaySE("./Data/Sound/SE/sword1.wav",100,50)
			setPuttern( chara_, 18 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 19 )
		end

		if frame_count_ ==8 then
			setPuttern( chara_,20 )
		end

		if frame_count_ ==11 then
			setPuttern( chara_,21 )
		end

		if frame_count_ ==13 then
			setPuttern( chara_, 22 )
		end

		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==19 then	
			AttackUnLock( chara_ )
		end

		// �U������t���[��
		if frame_count_== 11 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 15,   20,      20,    2.0,  7.0,    25 )

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

		if frame_count_ == 37 then
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
			//	PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			setPuttern( chara_, 30 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 31 )
		end

		if frame_count_ ==20 then
			setPuttern( chara_,32 )
			setVelocity( chara_,17,2 )
			PlaySE("./Data/Sound/SE/Swordhit3.wav",100,100)
		end

		if frame_count_ ==22 then
			setPuttern( chara_,33 )
		end

		if frame_count_ ==24 then
			setPuttern( chara_, 34 )
		end
		if frame_count_ ==26 then
			setPuttern( chara_, 35 )
		end
		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==50 then	
			AttackUnLock( chara_ )
		end

		// �U������t���[��
		if frame_count_== 22 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 37,   20,      30,    8.0,  7.0,    60 )

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

		if frame_count_ == 50 then
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

			setPuttern( chara_, 54 )

		end

		if frame_count_ == 3 then
			setVelocity( chara_,3,11 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,50)
			setPuttern( chara_, 55 )
		end

		if frame_count_ ==6 then
			setPuttern( chara_,56 )
		end

		if frame_count_ ==9 then
			setPuttern( chara_,57 )
		end

		if frame_count_ ==18 then
			setPuttern( chara_, 58 )
		end

		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==25 then	
			AttackUnLock( chara_ )
		end

		// �U������t���[��
		if frame_count_== 4 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 13,   20,      20,   12.0,  4.0,    20 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end	    

				end
			end
		end  
		if frame_count_== 12 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 13,   20,      20,    2.0,  12.0,    20 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end	    

				end
			end
		end  
		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����W�����v�ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 28 then
			setCharaState( chara_, CHARASTATE_JUMP )
			//
			// �W�����v���[�V�����̍ŏ����L�����Z�����邽�߂�
			// �t���[���̓W�����v���[�V�����̏I�����_�Ɏw��
			//
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
			//	PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			 setPuttern( chara_, 42 )
		end

		if frame_count_ ==20 then
			PlaySE("./Data/Sound/SE/Swordhit3.wav",100,100)
			setPuttern( chara_, 43 )
		end

		if frame_count_ == 21 then
			setPuttern( chara_, 44 )
		end

		if frame_count_ ==23 then
			setPuttern( chara_, 45 )
		end
		if frame_count_ ==25 then
			setPuttern( chara_, 46 )
		end

			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		if frame_count_ == 36 then
			AttackUnLock( chara_ )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 21 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  24,   20,      30,    3.0, 16.0,    50 )

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
        if frame_count_ == 37 then

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
				PlaySE("./Data/Sound/SE/sword1.wav",100,60)
			 setPuttern( chara_, 66 )
		end

		if frame_count_ ==7 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 10 then
				PlaySE("./Data/Sound/SE/sword1.wav",100,70)
			setPuttern( chara_, 68 )
		end

		if frame_count_ ==13 then
			setPuttern( chara_, 69 )
		end
		if frame_count_ ==16 then
			setPuttern( chara_, 70 )
		end
		if frame_count_ ==19 then
			setPuttern( chara_, 71 )
		end
			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		if frame_count_ == 33 then
			AttackUnLock( chara_ )
		end



		if frame_count_ == 10 then
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  10,   20,      20,   10.0, 3.0,    10 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end
		if frame_count_ == 13 then
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  18,   20,      20,    -10.0, 8.0,    25 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end
		if frame_count_ == 16 then
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  10,   20,      20,    2.0, -7.0,    10 )

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
        if frame_count_ == 34 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 47 )
			end

			setCharaState( chara_, CHARASTATE_SQUAT )
			setFrameCount( chara_, 5 )
        end
	end
end

//=============================================================================
//                              end of file
//=============================================================================
