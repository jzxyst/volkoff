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

		elseif frame_count_ == 2 then
			setPuttern( chara_, 10 )

		elseif frame_count_ == 4 then
			setVelocity( chara_, -4, 2 )
			PlaySE("./Data/Sound/SE/shotgun.wav",40,110)
			x, y = getCharaPosition( chara_ )

			if getDirection( chara_ ) == 1 then
				BulletGenerate(chara_,x,y + 50,8,4,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,8,2,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,8,0,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,8,-2,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,8,-4,21,1,1,2,2,20,60,7)
			else
				BulletGenerate(chara_,x,y + 50,-8,4,21,1,5,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,-8,2,21,1,5,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,-8,0,21,1,5,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,-8,-2,21,1,5,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,-8,-4,21,1,5,2,2,20,60,7)
			end
			if CheckWeaponBreak( chara_, 1 ) == 1 then
				setBreakWeapon( chara_ );
			end

		elseif frame_count_ == 6 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 14 then
			setPuttern( chara_, 6 )

		elseif frame_count_ == 17 then
			setPuttern( chara_, 7 )

		elseif frame_count_ == 20 then
			setPuttern( chara_, 8 )

		elseif frame_count_ == 23 then
			setPuttern( chara_, 9 )

		elseif frame_count_ == 26 then
			setPuttern( chara_, 10 )
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
			AttackUnLock( chara_ )

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

		elseif frame_count_ == 2 then
			setPuttern( chara_, 10 )

		elseif frame_count_ == 4 then
			setVelocity( chara_, -4, 2 )
			PlaySE("./Data/Sound/SE/shotgun.wav",40,110)
			x, y = getCharaPosition( chara_ )

			if getDirection( chara_ ) == 1 then
				BulletGenerate(chara_,x,y + 50,8,4,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,8,2,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,8,0,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,8,-2,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,8,-4,21,1,1,2,2,20,60,7)
			else
				BulletGenerate(chara_,x,y + 50,-8,4,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,-8,2,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,-8,0,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,-8,-2,21,1,1,2,2,20,60,7)
				BulletGenerate(chara_,x,y + 50,-8,-4,21,1,1,2,2,20,60,7)
			end
			if CheckWeaponBreak( chara_, 1 ) == 1 then
				setBreakWeapon( chara_ );
			end

		elseif frame_count_ == 6 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 14 then
			setPuttern( chara_, 6 )

		elseif frame_count_ == 17 then
			setPuttern( chara_, 7 )

		elseif frame_count_ == 20 then
			setPuttern( chara_, 8 )

		elseif frame_count_ == 23 then
			setPuttern( chara_, 9 )

		elseif frame_count_ == 26 then
			setPuttern( chara_, 10 )
			AttackUnLock( chara_ )

		elseif frame_count_ == 30 then

			// �j�����Ă��ꍇ
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_JUMP )
			setFrameCount( chara_, 8 )
			
		end


	//-------------------------------------------------------------
    // �� ���Ⴊ�ݍU��
	elseif state_ == CHARASTATE_ATTACK_SQUAT_ATTACK then

		if frame_count_ == 0 then
			AttackUnLock( chara_ )
		end

		//
		// �d�����ԏI��
		// �d�����Ԃ��o�߂����炵�Ⴊ�݂ɂ���
		// �d�����ԁF�w��t���[����1.5�{
		//
        if frame_count_ == 0 then

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

		if frame_count_ == 0 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 1 then

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
