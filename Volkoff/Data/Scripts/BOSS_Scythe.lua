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
		wx, wy = getCharaPosition( chara_ )
		if Rand()%100 == 1 then
			SetOpacity( chara_, 1 )
			setInvincibleFrame(chara_,0)
		end
        
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
		if frame_count_ == 1 then
			SetOpacity( chara_, 1 )
		end
		if frame_count_ == 1 and Rand()%10 ==1 then
			PlaySE("./Data/Sound/SE/warp.wav",70,95)
			setPuttern( chara_, 60 )
			SetOpacity( chara_, 0.1 )
			setInvincibleFrame(chara_,250)
			if Rand()%4 == 1 and frame_count_ >=14 then
				x, y = getPlayerPos()
				setPosition(chara_,x,y+40)
			end	
			if Rand()%4 == 1 and frame_count_ >=14 then
				x, y = getPlayerPos()
				setPosition(chara_,wx,wy)
			end	
			if Rand()%4 == 1 and frame_count_ >=14 then
				x, y = getPlayerPos()
				setPosition(chara_,x+150,y+20)
			end	
		end        
	//-------------------------------------------------------------
    // �� �������
    elseif state_ == CHARASTATE_BLOW then

		if frame_count_ == 1 then
			PlaySE("./Data/Sound/SE/warp.wav",70,95)
			setPuttern( chara_, 60 )
			SetOpacity( chara_, 0.9 )
			setInvincibleFrame(chara_,250)
		end
		if frame_count_ == 3 then
			SetOpacity( chara_, 0.7 )
			setPuttern( chara_, 61 )
		end
		if frame_count_ == 5 then 
			SetOpacity( chara_, 0.5 )
			setPuttern( chara_, 62 )
		end
		if frame_count_ == 7 then 
			SetOpacity( chara_, 0.4 )
			setPuttern( chara_, 63 )
		end
		if frame_count_ == 9 then 
			SetOpacity( chara_, 0.3 )
			setPuttern( chara_, 64)
		end
		if frame_count_ == 11 then
			SetOpacity( chara_, 0.1 )
			setPuttern( chara_, 65)
		end
		if frame_count_ == 13 then
			SetOpacity( chara_, 0.1 )
			setPuttern( chara_, 65)
		end

		if Rand()%10 == 1 and frame_count_ >=14 then
			x, y = getPlayerPos()
			setPosition(chara_,x,y+40)
		end	
		if Rand()%10 == 1 and frame_count_ >=14 then
			x, y = getPlayerPos()
			setPosition(chara_,wx,wy)
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
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//
		if frame_count_== 1 then
			//	PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			setPuttern( chara_, 30 )
		end

		if frame_count_ == 5 then
			SetOpacity( chara_, 1 )
			setInvincibleFrame(chara_,0)
			setPuttern( chara_, 31 )
		end
		if frame_count_ ==15 then
			if Rand()%3>=1 then 
				setFrameCount( chara_, 10 )
			end
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
		if frame_count_ ==45 then
			if Rand()%4>=1 then 
				setFrameCount( chara_, 35 )
			end
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
					attackEffect( chara_, target,	 35,   20,      10,    8.0,  7.0,    60 )

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
    // �� �ʏ�U�� 2 �i��
    elseif state_ == CHARASTATE_ATTACK_2 then


	//-------------------------------------------------------------
    // �� �ʏ�U�� 3 �i��
    elseif state_ == CHARASTATE_ATTACK_3 then


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
			setVelocity( chara_,3,-2 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,50)
			SetOpacity( chara_, 1 )
			setInvincibleFrame(chara_,0)
			setPuttern( chara_, 55 )
			wx2, wy2 = getCharaPosition( chara_ )
		end

		if frame_count_ ==6 then
			setPuttern( chara_,56 )
		end
		if frame_count_ >=6 and frame_count_ <=51 then
			setVelocity( chara_,9,0 )
			setAccel( chara_,0,0)
		end
		if frame_count_ ==45 then
			setPuttern( chara_,57 )
		end

		if frame_count_ ==48 then
			setPuttern( chara_, 58 )
		end

		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==51 then
			sa = Rand()%7
			if sa >1 then
				AttackUnLock( chara_ )
			end
			if sa == 1 then
				x, y = getCharaPosition( chara_ )	
				CreateEffect(0,x,y)			
				setPosition(chara_,wx,wy)
				setFrameCount( chara_, 2 )
				PlaySE("./Data/Sound/SE/sfx1.wav",100,180) 	
				CreateEffect(0,wx,wy)	
			end
			if sa == 0 then
				x, y = getCharaPosition( chara_ )	
				CreateEffect(0,x,y)	
				setPosition(chara_,wx2,wy2)
				setFrameCount( chara_, 2 )
				PlaySE("./Data/Sound/SE/sfx1.wav",100,180) 	
				CreateEffect(0,wx2,wy2)
			end
		end

		// �U������t���[��
		if frame_count_ >=6 and frame_count_ <=51 and frame_count_%4 == 1 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 16,   20,      20,   -7.0,  9.0,    50 )

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
        if frame_count_ == 52 then
			if Rand()%3 == 1 then
				setCharaState( chara_, CHARASTATE_ATTACK_ANTIAIR_ATTACK )
				setFrameCount( chara_, -1 )
			else
				setCharaState( chara_, CHARASTATE_JUMP )
				//
				// �W�����v���[�V�����̍ŏ����L�����Z�����邽�߂�
				// �t���[���̓W�����v���[�V�����̏I�����_�Ɏw��
				//
				setFrameCount( chara_, 8 )
			end
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
						PlaySE("./Data/Sound/SE/sword1.wav",100,50)
						SetOpacity( chara_, 1 )
						setInvincibleFrame(chara_,0)
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
						PlaySE("./Data/Sound/SE/Thunder01.wav",60,140)
			if getDirection( chara_ ) == 1 then
				x, y = getPlayerPos()
				SummonSoul( chara_,x+50,y)
						CreateEffect(4,x+50,y)
			else
				x, y = getPlayerPos()
				SummonSoul( chara_,x-50,y)
						CreateEffect(4,x-50,y)
			end
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
		if frame_count_ ==55 then	
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

		if frame_count_ == 60 then
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
			if Rand()%2 == 1 then
				setCharaState( chara_, CHARASTATE_ATTACK_SQUAT_ATTACK )
				setFrameCount( chara_, -1 )
			end
		end
		if frame_count_== 2 then
			if Rand()%3 == 1 then
				setPuttern( chara_, 13 )
			end
			if Rand()%3 == 1 then
				setPuttern( chara_, 66 )
			end
			PlaySE("./Data/Sound/SE/warp.wav",70,95)
			SetOpacity( chara_, 0.9 )
			setInvincibleFrame(chara_,150)
		end

		if frame_count_ ==3 then
			SetOpacity( chara_, 0.8 )
		end
		if frame_count_ ==5 then
			SetOpacity( chara_, 0.7 )
		end
		if frame_count_ ==7 then
			SetOpacity( chara_, 0.6 )
		end
		if frame_count_ ==9 then
			SetOpacity( chara_, 0.5 )
		end
		if frame_count_ ==11 then
			SetOpacity( chara_, 0.4 )
		end
		if frame_count_ ==13 then
			SetOpacity( chara_, 0.3 )
		end
		if frame_count_ ==15 then
			SetOpacity( chara_, 0.2 )
		end
		if frame_count_ ==17 then
			SetOpacity( chara_, 0.1 )
		end
		if frame_count_ ==19 then
			SetOpacity( chara_, 0.1 )
			if Rand()%2 == 1 then
				x, y = getPlayerPos()
				setPosition(chara_,x,y+80)
			end	
			if Rand()%3 == 1 then
				x, y = getPlayerPos()
				setPosition(chara_,wx,wy)
			end	
			if Rand()%4 == 1 then
				x, y = getPlayerPos()
				setPosition(chara_,x+150,y)
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
        if frame_count_ == 23 then

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
