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
			x, y = getCharaPosition( chara_ )
			GrenadeGenerate(chara_,x,y+40,1.5,7,0.3,55,30,1,15,10,60,-30,10,30)
			setPuttern( chara_, 65)
		end
		//setFrameCount( chara_, -1 )
    // �� �K�[�h
    elseif state_ == CHARASTATE_GUARD then
		if frame_count_ == 0 then
			setPuttern( chara_, 30 )
			setVelocity( chara_,40, 2 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/Swordhit3.wav",100,120)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   14,   15,      20,    -14.0,  5.0,    65 )
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
		end
		if frame_count_ >=11 then
			setPuttern( chara_, 84 )
			//setFrameCount( chara_, -1 )
		end

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
					attackEffect( chara_, target,	   6,   15,      10,    2.0,  2.0,    5 )
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

		elseif frame_count_ == 8 then
			setPuttern( chara_, 9 )
			setVelocity( chara_, 10, 2 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,170)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   8,   15,      10,    6.0,  3.0,    15 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 10 then
			setPuttern( chara_, 10 )

		elseif frame_count_ == 12 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 14 then
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
			 setPuttern( chara_, 66 )
			 setVelocity( chara_,30,0 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 4 then
			 setPuttern( chara_, 67 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 7 then
			 setPuttern( chara_, 68 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_==10 then
			 setPuttern( chara_, 69 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_==16 then
			 setPuttern( chara_, 68 )
			 setVelocity( chara_,40,0 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_==20 then
			 setPuttern( chara_, 67 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_==22 then
			 setPuttern( chara_, 66 )
		end
		// �U������t���[��
		if frame_count_ == 4 or
		   frame_count_ == 7 or
		   frame_count_ == 10 or
		   frame_count_ == 16 or
		   frame_count_ == 20 then

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 4,   20,      15,    7.0,  1.0,    3 )	
					x, y = getCharaPosition( chara_ )
					setPosition(target,x,y,0)
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end

		//
		// �U���I��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 21 then
			AttackUnLock( chara_ )
		end
		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
       		 if frame_count_ >= 35 then
	
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
			 setPuttern( chara_, 66 )
			 setVelocity( chara_,20,0 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 4 then
			 setPuttern( chara_, 67 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 7 then
			 setPuttern( chara_, 68 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_==10 then
			 setPuttern( chara_, 69 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_==13 then
			 setPuttern( chara_, 70 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end

		if frame_count_ ==16 then
			setPuttern( chara_, 30 )
			setVelocity( chara_,20, 0 )
		end
		if frame_count_ ==19 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/Swordhit3.wav",100,120)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   17,   15,      20,     10.0,  10.0,    65 )
					x, y = getCharaPosition( chara_ )
					setPosition(target,x,y,0)
					x, y = getCharaPosition( target )

					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end
		if frame_count_ ==21 then
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_ == 22 then
			setPuttern( chara_, 32 )
		end
		if frame_count_ == 24 then
			setPuttern( chara_, 33 )
		end

		// �U������t���[��
		if frame_count_ == 4 or
		   frame_count_ == 7 or
		   frame_count_ == 10 or
		   frame_count_ == 13 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 3,   20,      15,    3.0,  1.0,    3 )	
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end

		//
		// �U���I��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 32 then
			AttackUnLock( chara_ )
		end
		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
       		 if frame_count_ >= 43 then
	
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

		if frame_count_ == 0 then
			setPuttern( chara_, 30 )
			setVelocity( chara_,39, 0 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/Swordhit3.wav",100,120)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   17,   15,      20,    -14.0,  5.0,    65 )
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

		elseif frame_count_ == 45 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 46 then

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
			 setPuttern( chara_, 66 )
			 setVelocity( chara_,0,9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 4 then
			 setPuttern( chara_, 67 )
			 setVelocity( chara_,0,9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 7 then
			 setPuttern( chara_, 68 )
			setVelocity( chara_,0,9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 10 then
			 setPuttern( chara_, 69 )
			 setVelocity( chara_,0,9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 13 then
			 setPuttern( chara_, 70 )
			 setVelocity( chara_,0,9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 16 then
			 setPuttern( chara_, 71 )
			 setVelocity( chara_,0,9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end
		if frame_count_== 19 then
			 setPuttern( chara_, 83 )
			setVelocity( chara_,0,9 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
		end

		if frame_count_== 25 then
			setVelocity( chara_,0,0 )
			 setPuttern( chara_, 54 )

		end
		if frame_count_== 27 then
			PlaySE("./Data/Sound/SE/sword1.wav",100,70)
			 setPuttern( chara_, 55 )
		end
		if frame_count_== 29 then
			 setPuttern( chara_, 56 )
		end
		if frame_count_== 31 then
			 setPuttern( chara_, 57 )
		end


		// �U������t���[��
		if frame_count_ == 1 or
		   frame_count_ == 4 or
		   frame_count_ == 7 or
		   frame_count_ == 10 or
		   frame_count_ == 13 or
		   frame_count_ == 16 or
		   frame_count_ == 19 then

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 3,   20,      10,    0.0,  9.0,    2 )	
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end

		// �U������t���[��
		if frame_count_ == 27 then

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	13,   20,      10,   10.0,  -25.0,    60 )	
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end
		//
		// �U���I��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ == 32 then
			AttackUnLock( chara_ )
		end
		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//
       		 if frame_count_ >= 33 then
	
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
