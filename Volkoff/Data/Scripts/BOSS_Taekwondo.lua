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

		if frame_count_ == 0 then
			setPuttern( chara_, 72)
		end
		if frame_count_ == 5 then
			setPuttern( chara_, 0 )
		end
		if frame_count_ == 10 then
			setPuttern( chara_, 72 )
		end
		if frame_count_ == 15 then
			setPuttern( chara_, 0 )
		end
		//setPuttern( chara_, 72 )
		//setFrameCount( chara_, -1 )
		if frame_count_ ==26 then
			setPuttern( chara_, 24 )
		end
		if frame_count_ ==28 then
			x, y = getCharaPosition( chara_ )
				PlaySE("./Data/Sound/SE/sfx1.wav",100,180) 	
			CreateEffect(0,x,y)	
			setPosition(chara_,x,y+110,0)
			setVelocity(chara_,15,0)
			CreateEffect(0,x,y+110)
			setCharaState( chara_, CHARASTATE_JUMP )
		end
		if frame_count_ == 30 then
			setVelocity(chara_,15,0)
		end	
		if frame_count_ == 32 then
			setVelocity(chara_,15,0)
		end	
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

		if frame_count_== 1 then		        	
				setVelocity( chara_, 20, 0 )
		end

		if frame_count_ == 0 then
			setPuttern( chara_, 6 )

		elseif frame_count_ == 5 then
			setPuttern( chara_, 7 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  10,   15,      10,    4.0,  2.0,    2 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 7 then
			setPuttern( chara_, 8 )

		elseif frame_count_ == 8 then
			setPuttern( chara_, 9 )
			

		elseif frame_count_ == 13 then
			setPuttern( chara_, 10 )
			setVelocity( chara_, 20, 0 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,    4.0,  2.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// ����j���`�F�b�N
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end


		elseif frame_count_ == 16 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 21 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 32 then

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

		//
		// �摜�\��
		// ������t���[��      : ( ����t���[��*�R�}�� ) -1
		// setPuttern ������ : ����t���[��
		//

        	if frame_count_ == 1 then
			setPuttern( chara_, 36)
		end

        	if frame_count_ == 4 then
			setPuttern( chara_, 42)
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
		end


		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        	list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 4 then	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,    2.0,  10.0,    30 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)
				end
			end
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 30 )
			setVelocity( chara_, 2, 4)
		end
		if frame_count_ == 10 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,40)
		end
		if frame_count_ == 13 then
			setPuttern( chara_, 32 )
		end
		if frame_count_ == 15 then
			setPuttern( chara_, 33 )
		end
		if frame_count_ == 18 then
			setPuttern( chara_, 34 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)
		end
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        	list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 18 then	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,    2.0,  -5.0,   20 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)
				end
			end
		end


		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==20 then	
			setVelocity( chara_, 2, -4)
			AttackUnLock( chara_ )
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
		if frame_count_ == 0 then
			setPuttern( chara_, 18 )
		end

		if frame_count_ == 2 then
			setPuttern( chara_, 19 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,75)
		end   


		if frame_count_ == 7 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ == 11 then
			setPuttern( chara_, 21 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
		end	
/////////////
		if frame_count_ ==14 then
			setPuttern( chara_, 18 )
		end

		if frame_count_ ==16 then
			setPuttern( chara_, 19 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,75)
		end   


		if frame_count_ ==21 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ ==23 then
			setPuttern( chara_, 21 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
		end	
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        	list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 2 or
		   frame_count_== 16 then	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   6,   15,      10,    0.0,  0.0,    8 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)
				end
			end
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        	list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 11 or
		   frame_count_== 23 then		
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   7,   15,      10,    0.0,  0.0,   11 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)
				end
			end
		end


		if frame_count_ == 35 then
			setPuttern( chara_, 10 )
		end
		if frame_count_ == 40 then
			setPuttern( chara_, 11 )
			setVelocity( chara_,35, 2 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
			x, y = getCharaPosition( chara_ )
			CreateEffect(2,x+15 ,y )


		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        	list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 40 then	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   16,   15,      10,    12.0,  8.0,   70 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x ,y )
				end
			end
		end
		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==53 then	
			AttackUnLock( chara_ )
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//

		if frame_count_ == 55 then
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

		if frame_count_== 3 then
				PlaySE("./Data/Sound/SE/don01.wav",100,120) 
				PlaySE("./Data/Sound/SE/sword1.wav",100,80) 	
				setVelocity( chara_, 0, -20 ) 
				setPuttern( chara_, 54 )
				x, y = getCharaPosition( chara_ )
				CreateEffect(0,x,y)

			// �U��
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   2,   15,      10,    2.0,  25.0,    20 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end
		if frame_count_ ==23 then
			setPuttern( chara_, 24 )
		end
		if frame_count_ ==25 then
			x, y = getCharaPosition( chara_ )
				PlaySE("./Data/Sound/SE/sfx1.wav",100,180) 	
			CreateEffect(0,x,y)	
			setPosition(chara_,x,y+80,0)
			CreateEffect(0,x,y+80)
		end
		if frame_count_ ==27 then
			setPuttern( chara_, 20 )
			setVelocity( chara_, 8, 4 ) 
		end
		if frame_count_ ==30 then
			setPuttern( chara_, 21 )
		end
		if frame_count_ ==33 then
			setPuttern( chara_, 22 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        	list = judgeAttackCollision( chara_, target_group )
		if frame_count_== 30 then	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   25,   15,      30,    16.0, -10.0,   70 )
					x, y = getCharaPosition( target )
					CreateEffect(1,x + 10,y + 10)
					PlaySE("./Data/Sound/SE/Explosion01.ogg",50,130)
				end
			end
		end
		//
		// �U���I��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		if frame_count_ == 50 then
			AttackUnLock( chara_ )
		end
		

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂�����W�����v�ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 55 then

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
			setPuttern( chara_, 35 )
		end

		if frame_count_ >=22 and frame_count_ <32 then
			setVelocity( chara_, 40, 0)
		end
		if frame_count_ == 18 then
			setPuttern( chara_, 18 )
		end
		if frame_count_ == 22 then
			setPuttern( chara_, 11 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,40)
		end
		if frame_count_ == 34 then
			setPuttern( chara_, 18 )
			setVelocity( chara_,0,0)
			setDirection(chara_, 1)
		end
		if frame_count_ >=38 and frame_count_ <48 then
			setVelocity( chara_, 40, 0)
		end
		if frame_count_ == 38 then
			setPuttern( chara_, 11 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,40)
		end
		if frame_count_ == 48 then
			setPuttern( chara_, 18 )
			setVelocity( chara_,0,0)
			setDirection(chara_, 0)
		end
		if frame_count_ >=52 and frame_count_ <62 then
			setVelocity( chara_, 40, 0)
		end
		if frame_count_ == 52 then
			setPuttern( chara_, 11 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,40)
		end
		if frame_count_ == 62 then
			setPuttern( chara_, 18 )
			setVelocity( chara_,0,0)
			setDirection(chara_, 1)
		end
		if frame_count_ >=66 and frame_count_ <76 then
			setVelocity( chara_, 40, 0)
		end
		if frame_count_ == 66 then
			setPuttern( chara_, 11 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,40)
		end
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        	list = judgeAttackCollision( chara_, target_group )
		if frame_count_==27 or
		   frame_count_==43 or
		   frame_count_==57 or
		   frame_count_==71 then	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   15,   15,      10,    0.0,  12.0,   50 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)
				end
			end
		end
		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==90 then	
			setVelocity( chara_, 2, -4)
			AttackUnLock( chara_ )
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//

		if frame_count_ == 90 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end
	//-------------------------------------------------------------
    // �� �΋�U��
	elseif state_ == CHARASTATE_ATTACK_ANTIAIR_ATTACK then

		if frame_count_ == 0 then
			setPuttern( chara_, 35 )
		end

		if frame_count_ ==20 then
			setPuttern( chara_, 30 )
			setVelocity( chara_, 7,6)
		end
		if frame_count_ ==23 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,40)
		end
		if frame_count_ ==26 then
			setPuttern( chara_, 32 )
		end
		if frame_count_ ==28 then
			setPuttern( chara_, 33 )
		end
		if frame_count_ == 30 then
			setPuttern( chara_, 34 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)
		end
		if frame_count_ == 32 then
			setPuttern( chara_, 35 )
		end
/////////////1
		if frame_count_ == 34 then
			setPuttern( chara_, 30 )
			setVelocity( chara_, 7,6)
		end
		if frame_count_ == 36 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,60)
		end
		if frame_count_ == 38 then
			setPuttern( chara_, 32 )
		end
		if frame_count_ == 40 then
			setPuttern( chara_, 33 )
		end
		if frame_count_ == 42 then
			setPuttern( chara_, 34 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)
		end
		if frame_count_ == 44 then
			setPuttern( chara_, 35 )
		end
/////////////2
		if frame_count_ == 46 then
			setPuttern( chara_, 30 )
			setVelocity( chara_, 7,6)
		end
		if frame_count_ == 48 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,60)
		end
		if frame_count_ == 50 then
			setPuttern( chara_, 32 )
		end
		if frame_count_ == 52 then
			setPuttern( chara_, 33 )
		end
		if frame_count_ == 54 then
			setPuttern( chara_, 34 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)
		end
		if frame_count_ == 56 then
			setPuttern( chara_, 35 )
		end
/////////////3
		if frame_count_ == 57 then
			setPuttern( chara_, 30 )
			//setVelocity( chara_, 5,11)
		end
		if frame_count_ == 58 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,90)
		end
		if frame_count_ == 59 then
			setPuttern( chara_, 32 )
		end
		if frame_count_ == 60 then
			setPuttern( chara_, 33 )
		end
		if frame_count_ == 61 then
			setPuttern( chara_, 34 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)
		end
		if frame_count_ == 62 then
			setPuttern( chara_, 35 )
		end
/////////////4
		if frame_count_ == 63 then
			setPuttern( chara_, 30 )
			//setVelocity( chara_, 5,11)
		end
		if frame_count_ == 64 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,110)
		end
		if frame_count_ == 65 then
			setPuttern( chara_, 32 )
		end
		if frame_count_ == 66 then
			setPuttern( chara_, 33 )
		end
		if frame_count_ == 67 then
			setPuttern( chara_, 34 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)
		end
		if frame_count_ == 68 then
			setPuttern( chara_, 35 )
		end
/////////////5
		if frame_count_ == 70 then
			setPuttern( chara_, 0)
		end
		if frame_count_ == 75 then
			setPuttern( chara_, 72)
		end
		if frame_count_ == 80 then
			setPuttern( chara_, 0 )
		end
		if frame_count_ == 85 then
			setPuttern( chara_, 72)
		end
		//if frame_count_ == 90 then
		//	setPuttern( chara_, 0 )
		//end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// �Ƃ肠�����G�ɍU��
        	list = judgeAttackCollision( chara_, target_group )
		if frame_count_==30 or
		   frame_count_==42 or
		   frame_count_==54 or
		   frame_count_==61 or
		   frame_count_==67 then	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target ���U������		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,   12.0,  3.0,   22 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)
				end
			end
		end



		//
		// �U���I���A���i�󂯕t��
		// frame_count_    : ����t���[��*�R�}��
		// �s�������̃��b�N���������A
		// �摜���t�H���[�X���[�̂��̂ɕύX�B
		//
		if frame_count_ ==91 then	
			setVelocity( chara_, 2, -4)
			AttackUnLock( chara_ )
		end

		//
		// �󂯕t�����ԏI��
		// ���̒i�ւ̎󂯕t�����Ԃ𒴂�����ҋ@�ɂ���
		// �󂯕t���F�w��t���[����2�{
		//

		if frame_count_ == 92 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end
        end
	//end
end

//=============================================================================
//                              end of file
//=============================================================================
