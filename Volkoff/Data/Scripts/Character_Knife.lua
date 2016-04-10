//=============================================================================
//【 Character_BareHands 】
//-----------------------------------------------------------------------------
//  武器「棒」の動作の定義
//=============================================================================

//---------------------------------------------------------------------
// ● フレーム更新
//      chara_       : Character のポインタ
//      state_       : キャラクターの状態 (enum CharaState の値)
//      frame_count_ : アニメフレーム数 (この関数が終了した後 +1 される)
//---------------------------------------------------------------------
function update( chara_, state_, frame_count_ )
	
	//-------------------------------------------------------------
    // ▼ 待機状態
    if state_ == CHARASTATE_WAIT then
    
        setPuttern( chara_, 0 )
        
	//-------------------------------------------------------------
    // ▼ 走り状態
    elseif state_ == CHARASTATE_RUN then
    
		if getOnGround( chara_ ) then
			setPuttern( chara_, 12 + frame_count_ / 5 )
        
			if frame_count_ >= 29 then
				// 経過フレーム数を 0 に戻す
				setFrameCount( chara_, -1 )
			end
		else
			if frame_count_  <= 1 then
				setPuttern( chara_, 13 )
				setFrameCount( chara_, 1 )
			end
		end

	//-------------------------------------------------------------
    // ▼ ジャンプ
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
    // ▼ しゃがみ
    elseif state_ == CHARASTATE_SQUAT then
		if frame_count_  == 0 then
			setPuttern( chara_, 37 )
		end

	//-------------------------------------------------------------
    // ▼ のけぞり
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
    // ▼ 吹っ飛び
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
    // ▼ ガード
    elseif state_ == CHARASTATE_GUARD then

		setPuttern( chara_, 84 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // ▼ しゃがみガード
    elseif state_ == CHARASTATE_SQGUARD then
		setPuttern( chara_, 74 )
		setFrameCount( chara_, -1 )
	//-------------------------------------------------------------
    // ▼ はしご待機
    elseif state_ == CHARASTATE_LADDER_WAIT then
		// なにもしない。昇降モーション止めればいい

	//-------------------------------------------------------------
    // ▼ はしご上り/降り 同じモーションなので統合
    elseif state_ == CHARASTATE_LADDER_UP or
		state_ == CHARASTATE_LADDER_DOWN or
		state_ == CHARASTATE_LADDER_WAIT then

		setPuttern( chara_, 96 + frame_count_ / 10 )

		if frame_count_ == 19 then
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // ▼ アイテム拾い
    elseif state_ == CHARASTATE_ITENGET then

	//-------------------------------------------------------------
    // ▼ 死亡
    elseif state_ == CHARASTATE_DEAD then

	

	//-------------------------------------------------------------
    // ▼ 通常攻撃 1 段目
    elseif state_ == CHARASTATE_ATTACK_1 then
		
		if frame_count_ == 0 then
			setPuttern( chara_, 6 )
			setVelocity( chara_, 20, 1 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,200)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   8,   15,      10,    2.0,  2.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
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
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   13,   15,      10,    10.0,  3.0,    15 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
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

			// 破損してた場合
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
			
		end
	//-------------------------------------------------------------
    // ▼ 通常攻撃 2 段目
    elseif state_ == CHARASTATE_ATTACK_2 then

		if frame_count_ == 0 then
			setPuttern( chara_, 18 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 19 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			setVelocity( chara_, 4, 10 )
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    1,  0,    6 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 8 then
			setPuttern( chara_, 20 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    1,  0,    6 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 12 then
			setPuttern( chara_, 21 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    1,  0.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 16 then
			setPuttern( chara_, 22 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    1.0,  0.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 20 then
			setPuttern( chara_, 23 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   5,   15,      10,    7.0,  4.0,    20 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
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
    // ▼ 通常攻撃 3 段目
    elseif state_ == CHARASTATE_ATTACK_3 then
		
		if frame_count_ == 0 then
			setPuttern( chara_, 30 )
			setVelocity( chara_, 2, 5 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   20,   15,      10,    4.0,  4.0,    35 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
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
    // ▼ ジャンプ攻撃
	elseif state_ == CHARASTATE_ATTACK_JUMP_ATTACK then
		
		if frame_count_ == 0 then
			setPuttern( chara_, 54 )
			//setVelocity( chara_, 2, 5 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 55 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   10,   15,      10,    4.0,  4.0,    5 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
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
			// ジャンプモーションの最初をキャンセルするために
			// フレームはジャンプモーションの終了時点に指定
			//
			setFrameCount( chara_, 8 )

        end


	//-------------------------------------------------------------
    // ▼ しゃがみ攻撃
	elseif state_ == CHARASTATE_ATTACK_SQUAT_ATTACK then

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
        if frame_count_ == 0 then
			setPuttern( chara_, 42)

		elseif frame_count_ == 1 then
			setPuttern( chara_, 43)

		elseif frame_count_ == 2 then
			setPuttern( chara_, 44)
			PlaySE("./Data/Sound/SE/sword1.wav",100,180)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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
		// 硬直時間終了
		// 硬直時間を経過したらしゃがみにする
		// 硬直時間：指定フレームの1.5倍
		//
        if frame_count_ == 20 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 37 )
			end

			setCharaState( chara_, CHARASTATE_SQUAT )
			//
			// しゃがみモーションのしゃがみ始めをキャンセルするために
			// フレームはしゃがみモーションの終了時点から開始
			//
			setFrameCount( chara_, 37 )
        end

	//-------------------------------------------------------------
    // ▼ 対空攻撃
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

			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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
