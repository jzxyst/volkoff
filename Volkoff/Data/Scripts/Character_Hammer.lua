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
				setPuttern( chara_, 24 )
				setFrameCount( chara_, 1 )
			end
		end

	//-------------------------------------------------------------
    // �� �W�����v
    elseif state_ == CHARASTATE_JUMP then
		if frame_count_  <= 1 then
			setPuttern( chara_, 24 )
		end
	//-------------------------------------------------------------
    // �� ���Ⴊ��
    elseif state_ == CHARASTATE_SQUAT then
			setPuttern( chara_, 36 )

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
			PlaySE("./Data/Sound/SE/sword1.wav",100,50)

		elseif frame_count_ == 4 then
			setPuttern( chara_, 7 )

		elseif frame_count_ == 8 then
			setPuttern( chara_, 8 )

		elseif frame_count_ == 14 then
			setPuttern( chara_, 9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,60)

		elseif frame_count_ == 16 then
			setPuttern( chara_, 10 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)

		elseif frame_count_ == 18 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 20 then
			setPuttern( chara_, 18 )
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   25,   10,      15,    2.0,  15.0,    30 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 22 then
			setPuttern( chara_, 19 )

		elseif frame_count_ == 24 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 40 then

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
			setPuttern( chara_, 20 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 21 )

		elseif frame_count_ == 7 then
			setPuttern( chara_, 22 )

		elseif frame_count_ == 17 then
			setPuttern( chara_, 23 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)

		elseif frame_count_ == 19 then
			setPuttern( chara_, 30 )
			setVelocity( chara_, -2, 16 ) 
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)
			PlaySE("./Data/Sound/SE/don01.wav",80,80)
			PlaySE("./Data/Sound/SE/don01.wav",80,100) 

			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   45,   10,      20,    7.0,  8.0,    40 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 21 then
			setPuttern( chara_, 31 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)

		elseif frame_count_ == 40 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 50 then

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
			AttackUnLock( chara_ )

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
			setPuttern( chara_, 6 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,50)

		elseif frame_count_ == 2 then
			setPuttern( chara_, 7 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 8 )

		elseif frame_count_ == 8 then
			setPuttern( chara_, 9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,60)

		elseif frame_count_ == 10 then
			setPuttern( chara_, 10 )

		elseif frame_count_ == 12 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 14 then
			setPuttern( chara_, 18 )

			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   13,   10,      5,    16.0,  6.0,    10 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 16 then
			setPuttern( chara_, 19 )

		elseif frame_count_ == 18 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 25 then

			// �j�����Ă��ꍇ
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 24 )
			end

			setCharaState( chara_, CHARASTATE_JUMP )
			setFrameCount( chara_, 8 )
			
		end


	//-------------------------------------------------------------
    // �� ���Ⴊ�ݍU��
	elseif state_ == CHARASTATE_ATTACK_SQUAT_ATTACK then

		if frame_count_ == 1 then
			AttackUnLock( chara_ )
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂����炵�Ⴊ�݂ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 1 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 42 )
			end

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

		if frame_count_ == 1 then
			AttackUnLock( chara_ )
		end

		if frame_count_ == 1 then

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
