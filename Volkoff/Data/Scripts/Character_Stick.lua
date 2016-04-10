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
			// �n��
			setPuttern( chara_, 12 + frame_count_ / 5 )
			if frame_count_ >= 29 then
			    // �o�߃t���[������ 0 �ɖ߂�
			    setFrameCount( chara_, -1 )
			end
		else
			// ��
			if frame_count_  <= 1 then
				setPuttern( chara_, 24 )
			elseif frame_count_ >= 2 then
				setPuttern( chara_, 25 )
				setFrameCount( chara_, 2 )
			end
		end

	//-------------------------------------------------------------
    // �� �W�����v
    elseif state_ == CHARASTATE_JUMP then
		if frame_count_  <= 1 then
			setPuttern( chara_, 24 )
		elseif frame_count_ == 2 then
			setPuttern( chara_, 25 )
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
		setPuttern( chara_, 48 )
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
		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_ <= 19 then
			setPuttern( chara_, 60 + frame_count_ / 4 ) 
			//
			// ����I���A������܂ōŌ�̃R�}��\��
			//
		elseif frame_count_ == 20 then
			setPuttern( chara_, 60 + 4 )
		end

		return	

	//-------------------------------------------------------------
    // �� �ʏ�U�� 1 �i��
    elseif state_ == CHARASTATE_ATTACK_1 then

		if frame_count_== 1 then		        	
				PlaySE("./Data/Sound/SE/sword1.wav",100,80)
				setVelocity( chara_, 20, 0 )
		end

		if frame_count_ == 0 then
			setPuttern( chara_, 6 )

		elseif frame_count_ == 5 then
			setPuttern( chara_, 7 )

		elseif frame_count_ == 7 then
			setPuttern( chara_, 8 )

			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,    3.0,  4.0,    7 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end

		elseif frame_count_ == 9 then
			setPuttern( chara_, 9 )
			

		elseif frame_count_ == 11 then
			setPuttern( chara_, 10 )

		elseif frame_count_ == 13 then
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

		if frame_count_== 1 then		        	
				PlaySE("./Data/Sound/SE/sword1.wav",100,150)
		end

		if frame_count_== 15 then		        	
				PlaySE("./Data/Sound/SE/metal01.wav",150,140)
		end

		if frame_count_ == 0 then
			setPuttern( chara_, 18 )

			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   8,   15,      10,    -4.0,  0.0,    7 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end

		elseif frame_count_ == 3 then
			setPuttern( chara_, 19 )

		elseif frame_count_ == 6 then
			setPuttern( chara_, 20 )

		elseif frame_count_ == 9 then
			setPuttern( chara_, 21 )
			

		elseif frame_count_ == 15 then
			setPuttern( chara_, 22 )

			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,    5.0,  2.0,    45 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end

		elseif frame_count_ == 17 then
			setPuttern( chara_, 23 )

		elseif frame_count_ == 20 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 35 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end

	//-------------------------------------------------------------
    // �� �ʏ�U�� 3 �i��
    elseif state_ == CHARASTATE_ATTACK_3 then

		if frame_count_== 1 then
				PlaySE("./Data/Sound/SE/roll.wav",70,140)
				setVelocity( chara_, 5, 0 )		        	
		end

		if frame_count_== 20 then
				PlaySE("./Data/Sound/SE/stick01.wav",100,120)
				PlaySE("./Data/Sound/SE/don01.wav",80,120)			        	
		end
		
		if frame_count_ == 0 then
			setPuttern( chara_, 30 )

		elseif frame_count_ == 5 then
			setPuttern( chara_, 31 )

		elseif frame_count_ == 10 then
			setPuttern( chara_, 32 )

		elseif frame_count_ == 15 then
			setPuttern( chara_, 33 )
			

		elseif frame_count_ == 20 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 34 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)

			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   20,   15,      10,    27.0,  3.0,   70 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end

		elseif frame_count_ == 25 then
			setPuttern( chara_, 35 )
			AttackUnLock( chara_ )
		elseif frame_count_ == 35 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
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
				PlaySE("./Data/Sound/SE/roll.wav",70,140)
				setVelocity( chara_, 5, 16 ) //5,16
				if CheckWeaponBreak( chara_, 1 ) == 1 then
					setBreakWeapon( chara_, 1 );
				end	        	
		end

		if frame_count_ == 0 then
			setPuttern( chara_, 30 )

		elseif frame_count_ == 5 then
			setPuttern( chara_, 31 )

		elseif frame_count_ == 10 then
			setPuttern( chara_, 32 )

		elseif frame_count_ == 15 then
			setPuttern( chara_, 33 )

		elseif frame_count_ == 17 then
			setPuttern( chara_, 25 )

		end

		//
		// �U���I��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		if frame_count_ == 20 then
			AttackUnLock( chara_ )
		end
		

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����W�����v�ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 20 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 25 )
			end

			setCharaState( chara_, CHARASTATE_JUMP )
			//
			// �W�����v���[�V�����̍ŏ����L�����Z�����邽�߂�
			// �t���[���̓W�����v���[�V�����̏I�����_�Ɏw��
			//
			setFrameCount( chara_, 25 )

        end


	//-------------------------------------------------------------
    // �� ���Ⴊ�ݍU��
	elseif state_ == CHARASTATE_ATTACK_SQUAT_ATTACK then

		if frame_count_== 1 then
				PlaySE("./Data/Sound/SE/roll.wav",70,160)  
		end

		if frame_count_ == 0 then
			setPuttern( chara_, 30 )
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      1,    20.0,  5.0,   40 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end

		elseif frame_count_ == 3 then
			setPuttern( chara_, 31 )

		elseif frame_count_ == 6 then
			setPuttern( chara_, 32 )
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      1,    20.0,  5.0,   40 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end

		elseif frame_count_ == 9 then
			setPuttern( chara_, 33 )

		elseif frame_count_ == 12 then
			setPuttern( chara_, 36 )

		end

		//
		// �U���I��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		if frame_count_ == 17 then
			AttackUnLock( chara_ )
		end
		
		if frame_count_ == 22 then

			// �j�����Ă��ꍇ
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
			
		end

	//-------------------------------------------------------------
    // �� �΋�U��
	elseif state_ == CHARASTATE_ATTACK_ANTIAIR_ATTACK then

		if frame_count_== 1 then		        	
				PlaySE("./Data/Sound/SE/sword1.wav",100,60)
		end

		setVelocity( chara_, 0, 0 )

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
        if frame_count_ <= 25 then
			setPuttern( chara_, 66 + frame_count_ / 4 )
			//
			// �U���I��
			// frame_count_    : ����t���[��*�R�}��
			// �s�������̃��b�N���������A
			// �摜���t�H���[�X���[�̂��̂ɕύX�B
			//
		elseif frame_count_ == 24 then
			setPuttern( chara_, 66 + 3 )
			AttackUnLock( chara_ )
		end

		if frame_count_ == 10 then
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

			// �Ƃ肠�����G�ɍU��
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   32,   15,      10,    0.0,  -7.0,    20 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
							setBreakWeapon( chara_, 1 );
					end
				end
			end
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 30 then

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
