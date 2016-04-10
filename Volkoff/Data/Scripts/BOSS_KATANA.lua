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
    
        setPuttern( chara_, 0)
        
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

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 66 )
		end

       if frame_count_ == 2 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 68 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 69 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 70 )
		end

			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		if frame_count_ == 6 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 3 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  10,   20,      15,    5.0,  5.0,    10 )
				end
			end
		end
		if frame_count_ < 8 then
			//setPuttern( chara_, 36 )
		else
			setPuttern( chara_, 37 )

			// �o�߃t���[������ 3 �ŌŒ�
			// �I�[�o�[�t���[�|����ŁB
           	 setFrameCount( chara_, 8 )
		end


	//-------------------------------------------------------------
    // �� �̂�����
    elseif state_ == CHARASTATE_STUN then

		setPuttern( chara_, 103 )
		setFrameCount( chara_, -1 )
        
	//-------------------------------------------------------------
    // �� �������
    elseif state_ == CHARASTATE_BLOW then

		setPuttern( chara_, 60 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // �� �K�[�h
    elseif state_ == CHARASTATE_GUARD then

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

		if frame_count_ == 3 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 10 )
		end

		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 8 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)			
			AttackUnLock( chara_ )
			//setPuttern( chara_, 11 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �U������t���[��
		if frame_count_ == 5 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 6,   20,      15,    2.0,  2.0,    10 )
				end
			end
		end
        
		if frame_count_ > 8 then
			setPuttern( chara_, 72 )
			//setFrameCount( chara_, -1 )
        	 setFrameCount( chara_, 8 )
		end
	//-------------------------------------------------------------
    // �� ���Ⴊ�݃K�[�h
    elseif state_ == CHARASTATE_SQGUARD then

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setVelocity( chara_, 0, 0 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 19 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 21 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 22 )
		end

		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 7 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
			setPuttern( chara_, 23 )

		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 4 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 6,   20,      2,   10.0,  1.0,    5 )
				end
			end
		end
		if frame_count_ > 8 then
			//setPuttern( chara_, 72 )
			//setFrameCount( chara_, -1 )
        	 setFrameCount( chara_, 1 )
		end
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

		if frame_count_ == 2 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 10 )
		end
		if frame_count_== 6 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 9 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 10 then
			setPuttern( chara_, 10 )
		end
		if frame_count_== 11 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 13 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 14 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 15 then
			setPuttern( chara_, 10 )
		end
		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 16 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)			
			AttackUnLock( chara_ )
			setPuttern( chara_, 11 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �U������t���[��
		if frame_count_ == 3 or
		   frame_count_ == 8 or
		   frame_count_ ==13 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 4,   20,      15,    1.0,  1.0,    10 )
				end
			end
		end
        
		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
		if frame_count_ == 20 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // �� �ʏ�U�� 2 �i��
    elseif state_ == CHARASTATE_ATTACK_2 then


		if frame_count_== 1 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 10 )
		end
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 8 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setVelocity( chara_, 15, 0 )
			 setPuttern( chara_, 18 )
		end

		if frame_count_ == 11 then
			setPuttern( chara_, 19 )
			setVelocity( chara_, 15, 0 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ == 13 then
			setPuttern( chara_, 21 )
		end

		if frame_count_ == 14 then
			setPuttern( chara_, 22 )
		end
////////////////
		if frame_count_== 15 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 17 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 18 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 19 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 20 then
			setPuttern( chara_, 10 )
		end
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 21 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setVelocity( chara_, 15, 0 )
			 setPuttern( chara_, 18 )
		end

		if frame_count_ == 23 then
			setPuttern( chara_, 19 )
			setVelocity( chara_, 15, 0 )
		end

		if frame_count_ == 24 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ == 25 then
			setPuttern( chara_, 21 )
		end

		if frame_count_ == 26 then
			setPuttern( chara_, 22 )
		end
		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 28 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
			setPuttern( chara_, 23 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 5 or
		   frame_count_ == 18 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 4,   20,      15,    2.0,  2.0,    10 )
				end
			end
		end

		if frame_count_ == 12 or
		   frame_count_ == 24 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 6,   20,      15,   3.0,  2.0,    15 )
				end
			end
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
		if frame_count_ == 34 then
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
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 66 )
			 setVelocity( chara_, -5, 0 )
		end

      		 if frame_count_ == 3 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 68 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 69 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 70 )
		end
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

		if frame_count_== 10 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 17,0 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 55 )
			 setVelocity( chara_, 17,0 )
		end

		if frame_count_ == 14 then
			setPuttern( chara_, 56 )
			 setVelocity( chara_, 17,0 )
		end

		if frame_count_ == 16 then
			setPuttern( chara_, 57 )
			setVelocity( chara_, 17,0 )
		end

		if frame_count_ == 18 then
			setPuttern( chara_, 58 )
		end
		
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

		if frame_count_== 19 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,120)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 30 )
		end

		if frame_count_ ==23 then
			setPuttern( chara_, 31 )
		end

		if frame_count_ ==26 then
			setPuttern( chara_, 32 )
		end

		if frame_count_ ==28 then
			setPuttern( chara_, 33 )
		end

		if frame_count_ ==30 then
			setPuttern( chara_, 34 )
		end
		if frame_count_ ==32 then
			setPuttern( chara_,102 )
		end
		if frame_count_ ==43 then
			setPuttern( chara_,103 )
		end
		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 85 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 35 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
//
		if frame_count_ == 5 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  9,   20,      15,    8.0,  4.0,    10 )
				end
			end
		end

		if frame_count_ == 12 or
			frame_count_ == 14 or
			frame_count_ == 16 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  7,   30,      15,    5.0,  .0,    10 )
				end
			end
		end
//
		if frame_count_ == 26 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  15,   20,      15,   18.0,  2.0,    60 )
				end
			end
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 88 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
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

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 58 )
		end
		if frame_count_== 7 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 9 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 10 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 11 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 58 )
		end
		if frame_count_== 13 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 15 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 16 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 17 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 18 then
			setPuttern( chara_, 58 )
		end

		if frame_count_== 19 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 21 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 22 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 23 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 24 then
			setPuttern( chara_, 58 )
		end
		if frame_count_== 25 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 27 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 28 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 29 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 30 then
			setPuttern( chara_, 58 )
		end
		if frame_count_== 31 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 33 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 34 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 35 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 36 then
			setPuttern( chara_, 58 )
		end

		//3�����
		if frame_count_== 37 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,120)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)
			 PlaySE("./Data/Sound/SE/don01.wav",100,120)		
			 setPuttern( chara_, 30 )
		end

		if frame_count_ == 38 then
			setPuttern( chara_, 31 )
		end

		if frame_count_ == 39 then
			setPuttern( chara_, 32 )
		end

		if frame_count_ == 40 then
			setPuttern( chara_, 33 )
		end

		if frame_count_ == 41 then
			setPuttern( chara_, 34 )
		end

		if frame_count_ == 50 then
			setPuttern( chara_, 48 )
		end
		if frame_count_ == 60 then
			setPuttern( chara_, 102 )
		end
		if frame_count_ == 70 then
			setPuttern( chara_, 103 )
		end

			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		if frame_count_ == 95 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)

			//setPuttern( chara_, 0 )
			setPuttern( chara_, 27 )
			AttackUnLock( chara_ )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 4 or
			frame_count_ == 10 or
			frame_count_ == 16 or
			frame_count_ == 22 or
			frame_count  == 28 or
			frame_count_ == 34 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  6,   30,      20,    0,  0,    17 )
				end
			end
		end
		if frame_count_ == 39 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  15,   20,      15,   14.0,  2.0,    60 )
				end
			end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 100 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
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
		if frame_count_ == 10 then
			setPuttern( chara_, 35 )
		end
		if frame_count_ == 35 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			setPuttern( chara_, 0 )
		end
		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 50 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 0 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 6 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  20,   20,      15,   15.0,  2.0,    60 )
				end
			end
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 45 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
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
			 setVelocity( chara_, -5, 0 )
		end

      		 if frame_count_ == 3 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 68 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 69 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 70 )
		end
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

		if frame_count_== 10 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 13,13 )
		end

		if frame_count_ == 13 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 16 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 17 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 20 then
			setPuttern( chara_, 58 )
		end
		if frame_count_ == 25 then
			setPuttern( chara_, 102)
			 setVelocity( chara_, 0, 0 )
		end

			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		if frame_count_ == 45 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)

			//setPuttern( chara_, 0 )
			setPuttern( chara_, 27 )
			AttackUnLock( chara_ )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
		if frame_count_ == 5 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					DecrementUseCount(1)
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  10,   20,      15,    8.0,  8.0,    20 )
				end
			end
		end

		if frame_count_ == 13 or
			frame_count_ == 16 or
			frame_count_ == 17 then
			// �G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  7,   30,      30,    3.0,  -5.0,    30 )
				end
			end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 48 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end
	end
end

//=============================================================================
//                              end of file
//=============================================================================
