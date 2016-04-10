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
				setPuttern( chara_, 24 )
				setFrameCount( chara_, 1 )
			end
		end

	//-------------------------------------------------------------
    // ▼ ジャンプ
    elseif state_ == CHARASTATE_JUMP then
		if frame_count_  <= 1 then
			setPuttern( chara_, 24 )
		end
	//-------------------------------------------------------------
    // ▼ しゃがみ
    elseif state_ == CHARASTATE_SQUAT then
			setPuttern( chara_, 36 )

	//-------------------------------------------------------------
    // ▼ のけぞり
    elseif state_ == CHARASTATE_STUN then

		setPuttern( chara_, 48 )
        
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

		setPuttern( chara_, 72 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // ▼ しゃがみガード
    elseif state_ == CHARASTATE_SQGUARD then
		setPuttern( chara_, 84 )
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

		if frame_count_== 1 then		        	
				setVelocity( chara_, 20, 0 )
		end

		if frame_count_ == 0 then
			setPuttern( chara_, 6 )

		elseif frame_count_ == 7 then
			setPuttern( chara_, 7 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   13,   15,      10,    4.0,  2.0,    10 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 10 then
			setPuttern( chara_, 8 )

		elseif frame_count_ == 12 then
			setPuttern( chara_, 9 )
			

		elseif frame_count_ == 20 then
			setPuttern( chara_, 10 )
			setVelocity( chara_, 20, 0 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   18,   15,      10,    4.0,  2.0,    12 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end


		elseif frame_count_ == 22 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 25 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 35 then

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
			PlaySE("./Data/Sound/SE/sword1.wav",100,75)
			setVelocity( chara_, 20, 0 )
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   9,   15,      5,    4.0,  2.0,    12 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 11 then
			setPuttern( chara_, 20 )

		elseif frame_count_ == 18 then
			setPuttern( chara_, 21 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
			setVelocity( chara_, 20, 0 )
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   18,   15,      10,    4.0,  2.0,    15 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 20 then
			setPuttern( chara_, 22 )
			AttackUnLock( chara_ )

		elseif frame_count_ == 25 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 35 then

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

		elseif frame_count_ == 4 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,40)

		elseif frame_count_ == 8 then
			setPuttern( chara_, 32 )

		elseif frame_count_ == 12 then
			setPuttern( chara_, 33 )
			

		elseif frame_count_ == 14 then
			setPuttern( chara_, 34 )
			setVelocity( chara_, -30, 0 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)

			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   22,   15,      10,    10.0,  5.0,   20 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 16 then
			setPuttern( chara_, 35 )

		elseif frame_count_ == 22 then
			setPuttern( chara_, 9 )

		elseif frame_count_ == 25 then
			PlaySE("./Data/Sound/SE/sword1.wav",100,70)
			setPuttern( chara_, 10 )
			setVelocity( chara_, 35, 2 ) //35
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   22,   15,      10,    10.0,  5.0,   13 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 28 then
			setPuttern( chara_, 11 )

		elseif frame_count_ == 32 then
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   22,   15,     10,    10.0,  5.0,   13 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 40 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 45 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end

	//-------------------------------------------------------------
    // ▼ ジャンプ攻撃
	elseif state_ == CHARASTATE_ATTACK_JUMP_ATTACK then

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//

		if frame_count_== 1 then
				PlaySE("./Data/Sound/SE/don01.wav",100,120) 
				PlaySE("./Data/Sound/SE/sword1.wav",100,80) 	
				setVelocity( chara_, 0, -20 ) 
				setPuttern( chara_, 54 )
				x, y = getCharaPosition( chara_ )
				CreateEffect(0,x,y)

			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   20,   10,      10,    2.0,  18.0,    80 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end

		//
		// 攻撃終了
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		if frame_count_ == 50 then
			AttackUnLock( chara_ )
		end
		

		//
		// 硬直時間終了
		// 硬直時間を経過したらジャンプにする
		// 硬直時間：指定フレームの1.5倍
		//
        if frame_count_ == 55 then

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
        if frame_count_ == 1 then
			setPuttern( chara_, 42)
			PlaySE("./Data/Sound/SE/sword1.wav",100,80)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   10,   15,      10,    2.0,  10.0,    30 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 15 then
			AttackUnLock( chara_ )
		end

		//
		// 硬直時間終了
		// 硬直時間を経過したらしゃがみにする
		// 硬直時間：指定フレームの1.5倍
		//
        if frame_count_ == 18 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 42 )
			end

			setCharaState( chara_, CHARASTATE_SQUAT )
			//
			// しゃがみモーションのしゃがみ始めをキャンセルするために
			// フレームはしゃがみモーションの終了時点から開始
			//
			setFrameCount( chara_, 3 )
        end

	//-------------------------------------------------------------
    // ▼ 対空攻撃
	elseif state_ == CHARASTATE_ATTACK_ANTIAIR_ATTACK then

		if frame_count_ == 0 then
			setPuttern( chara_, 30 )
			setVelocity( chara_, -2, 2)

		elseif frame_count_ == 2 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,40)

		elseif frame_count_ == 4 then
			setPuttern( chara_, 32 )

		elseif frame_count_ == 6 then
			setPuttern( chara_, 33 )
			

		elseif frame_count_ == 8 then
			setPuttern( chara_, 34 )
			x, y = getCharaPosition( chara_ )
			CreateEffect(0,x,y)

			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   10,   15,      10,    0.0,  -5.0,   20 )
					x, y = getCharaPosition( target )
					CreateEffect(2,x + 10,y + 10)

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end

		elseif frame_count_ == 10 then
			setPuttern( chara_, 35 )

		elseif frame_count_ == 30 then
			AttackUnLock( chara_ )

		elseif frame_count_ == 35 then

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
