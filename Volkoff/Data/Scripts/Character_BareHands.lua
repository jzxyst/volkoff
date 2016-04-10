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
				setVelocity( chara_, 12, 0 )
		end
        if frame_count_ <= 9 then
			setPuttern( chara_, 6 + frame_count_ / 5 )
			//
			// �U���I���A���i�󂯕t��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//

		elseif frame_count_ == 10 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 6 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 9 then	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun

					attackEffect( chara_, target,	  10,   20,      5,    1.0,  1.0,    5 )

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
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 1 then		        	
				PlaySE("./Data/Sound/SE/sword1.wav",100,90)
				setVelocity( chara_, 12, 0 )
		end
        if frame_count_ <= 14 then
			setPuttern( chara_, 18 + frame_count_ / 5 )
			//
			// �U���I���A���i�󂯕t��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		elseif frame_count_ == 15 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 18 + 1 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 14 then		
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  12,   20,      5,    2.0,  2.0,    10 )
				end
			end
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
		if frame_count_ == 30 then
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
				PlaySE("./Data/Sound/SE/sword1.wav",100,200)
				setVelocity( chara_, 12, 0 )
		end
        if frame_count_ <= 19 then
			setPuttern( chara_, 30 + frame_count_ / 5 )
			//
			// �U���I���A���i�󂯕t��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		elseif frame_count_ == 20 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 30 + 3 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 12 then
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  15,   20,      5,    2.0,  2.0,    15 )
				end
			end
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
        if frame_count_ == 30 then
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
		PlaySE("./Data/Sound/SE/sword1.wav",100,90)
		setVelocity( chara_, 2, 10 )
		end
        if frame_count_ <= 11 then
			setPuttern( chara_, 54 + frame_count_ / 4 )
			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		elseif frame_count_ == 15 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 54 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 11 then
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  14,   20,      5,    2.0,  5.0,   10 )
				end
			end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����W�����v�ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 23 then
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
		PlaySE("./Data/Sound/SE/sword1.wav",100,130)
		end
        if frame_count_ <= 7 then
			setPuttern( chara_, 42 + frame_count_ / 4 )
			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		elseif frame_count_ == 8 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 42 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 7 then
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  10,   20,      10,    1.0,  1.0,    5 )
				end
			end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂����炵�Ⴊ�݂ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 12 then
			setCharaState( chara_, CHARASTATE_SQUAT )
			//
			// ���Ⴊ�݃��[�V�����̂��Ⴊ�ݎn�߂��L�����Z�����邽�߂�
			// �t���[���͂��Ⴊ�݃��[�V�����̏I�����_����J�n
			//
			setFrameCount( chara_, 3 )
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
		PlaySE("./Data/Sound/SE/sword1.wav",100,70)
		end
        if frame_count_ <= 15 then
			setPuttern( chara_, 66 + frame_count_ / 4 )
			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		elseif frame_count_ == 16 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 66 + 3 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 8 then
		if not ( list == nil ) then
			for i, target in ipairs( list ) do
				// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
				attackEffect( chara_, target,	  16,   20,      5,    5.0,  5.0,    25 )
			end
		end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 24 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end
	end
end

//=============================================================================
//                              end of file
//=============================================================================
