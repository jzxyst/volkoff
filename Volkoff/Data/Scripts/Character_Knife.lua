//=============================================================================
//�y Character_BareHands �z
//-----------------------------------------------------------------------------
//  ����u�_�v�̓���̒�`
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
			setPuttern( chara_, 12 + frame_count_ / 5 )
        
			if frame_count_ >= 29 then
				// �o�߃t���[������ 0 �ɖ߂�
				setFrameCount( chara_, -1 )
			end
		else
			if frame_count_  <= 1 then
				setPuttern( chara_, 13 )
				setFrameCount( chara_, 1 )
			end
		end

	//-------------------------------------------------------------
    // �� �W�����v
    elseif state_ == CHARASTATE_JUMP then
		if frame_count_  == 1 then
			setPuttern( chara_, 24 )
		end
		if frame_count_  == 2 then
			setPuttern( chara_, 25 )
		end
		if frame_count_  == 3 then
			setPuttern( chara_, 26 )
		end
		if frame_count_  >= 5 then
			setPuttern( chara_, 27 )
		end
	//-------------------------------------------------------------
    // �� ���Ⴊ��
    elseif state_ == CHARASTATE_SQUAT then
		if frame_count_  == 0 then
			setPuttern( chara_, 37 )
		end

	//-------------------------------------------------------------
    // �� �̂�����
    elseif state_ == CHARASTATE_STUN then
		if frame_count_  == 1 then
			setPuttern( chara_, 48 )
		end
		if frame_count_  == 2 then
			setPuttern( chara_, 49 )
		end
		if frame_count_  == 3 then
			setPuttern( chara_, 50 )
		end
        
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

		setPuttern( chara_, 84 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // �� ���Ⴊ�݃K�[�h
    elseif state_ == CHARASTATE_SQGUARD then
		setPuttern( chara_, 74 )
		setFrameCount( chara_, -1 )
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

	

	//-------------------------------------------------------------
    // �� �ʏ�U�� 1 �i��
    elseif state_ == CHARASTATE_ATTACK_1 then
		
		if frame_count_ == 0 then
			setPuttern( chara_, 6 )
			setVelocity( chara_, 20, 1 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,200)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   8,   15,      10,    2.0,  2.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 2 then
			setPuttern( chara_, 7 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 8 )

		elseif frame_count_ == 12 then
			setPuttern( chara_, 9 )
			setVelocity( chara_, 10, 2 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,170)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   13,   15,      10,    10.0,  3.0,    15 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 14 then
			setPuttern( chara_, 10 )

		elseif frame_count_ == 16 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 18 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 30 then

			// �j�����Ă��ꍇ
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
			
		end
	//-------------------------------------------------------------
    // �� �ʏ�U�� 2 �i��
    elseif state_ == CHARASTATE_ATTACK_2 then

		if frame_count_ == 0 then
			setPuttern( chara_, 18 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 19 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			setVelocity( chara_, 4, 10 )
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    1,  0,    6 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 8 then
			setPuttern( chara_, 20 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    1,  0,    6 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 12 then
			setPuttern( chara_, 21 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    1,  0.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 16 then
			setPuttern( chara_, 22 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    1.0,  0.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 20 then
			setPuttern( chara_, 23 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    7.0,  4.0,    20 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 24 then
			setPuttern( chara_, 35 )
			AttackUnLock( chara_ )

		elseif frame_count_ == 28 then
			setPuttern( chara_, 34 )

		elseif frame_count_ == 40 then
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end

	//-------------------------------------------------------------
    // �� �ʏ�U�� 3 �i��
    elseif state_ == CHARASTATE_ATTACK_3 then
		
		if frame_count_ == 0 then
			setPuttern( chara_, 30 )
			setVelocity( chara_, 2, 5 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   20,   15,      10,    4.0,  4.0,    35 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 6 then
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)

		elseif frame_count_ == 8 then
			setPuttern( chara_, 32 )

		elseif frame_count_ == 10 then
			setPuttern( chara_, 33 )

		elseif frame_count_ == 20 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 30 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end

	//-------------------------------------------------------------
    // �� �W�����v�U��
	elseif state_ == CHARASTATE_ATTACK_JUMP_ATTACK then
		
		if frame_count_ == 0 then
			setPuttern( chara_, 54 )
			//setVelocity( chara_, 2, 5 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 55 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   10,   15,      10,    4.0,  4.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 5 then
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)

		elseif frame_count_ == 8 then
			setPuttern( chara_, 56 )

		elseif frame_count_ == 12 then
			setPuttern( chara_, 57 )

		elseif frame_count_ == 16 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 20 then
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 24 )
			end

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
        if frame_count_ == 0 then
			setPuttern( chara_, 42)

		elseif frame_count_ == 1 then
			setPuttern( chara_, 43)

		elseif frame_count_ == 2 then
			setPuttern( chara_, 44)
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,    6.0,  2.0,    30 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 6 then
			setPuttern( chara_, 45)

		elseif frame_count_ == 8 then
			setPuttern( chara_, 46)

		elseif frame_count_ == 10 then
			setPuttern( chara_, 47)
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,    6.0,  2.0,    30 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 12 then
			setPuttern( chara_, 59)

		elseif frame_count_ == 14 then
			setPuttern( chara_, 37)

		elseif frame_count_ == 18 then
			AttackUnLock( chara_ )
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂����炵�Ⴊ�݂ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 20 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 37 )
			end

			setCharaState( chara_, CHARASTATE_SQUAT )
			//
			// ���Ⴊ�݃��[�V�����̂��Ⴊ�ݎn�߂��L�����Z�����邽�߂�
			// �t���[���͂��Ⴊ�݃��[�V�����̏I�����_����J�n
			//
			setFrameCount( chara_, 37 )
        end

	//-------------------------------------------------------------
    // �� �΋�U��
	elseif state_ == CHARASTATE_ATTACK_ANTIAIR_ATTACK then

		if frame_count_ == 0 then
			setPuttern( chara_, 66 )
			setVelocity( chara_, 1, 15)

		elseif frame_count_ == 2 then
			setPuttern( chara_, 67 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)

		elseif frame_count_ == 4 then
			setPuttern( chara_, 68 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)

		elseif frame_count_ == 6 then
			setPuttern( chara_, 69 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)

		elseif frame_count_ == 8 then
			setPuttern( chara_, 70 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)

			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   10,   15,      10,    3.0,  16.0,   15 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 10 then
			setPuttern( chara_, 71 )

		elseif frame_count_ == 12 then
			setPuttern( chara_, 83 )

		elseif frame_count_ == 14 then
			setPuttern( chara_, 27 )

		elseif frame_count_ == 25 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 30 then

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
