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
			x, y = getCharaPosition( chara_ )
			GrenadeGenerate(chara_,x,y+40,1.5,7,0.3,55,30,1,15,10,60,-30,10,30)
			setPuttern( chara_, 65)
		end
		//setFrameCount( chara_, -1 )
    // ▼ ガード
    elseif state_ == CHARASTATE_GUARD then
		if frame_count_ == 0 then
			setPuttern( chara_, 30 )
			setVelocity( chara_,40, 2 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/Swordhit3.wav",100,120)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   14,   15,      20,    -14.0,  5.0,    65 )
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
		end
		if frame_count_ >=11 then
			setPuttern( chara_, 84 )
			//setFrameCount( chara_, -1 )
		end

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
					attackEffect( chara_, target,	   6,   15,      10,    2.0,  2.0,    5 )
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

		elseif frame_count_ == 8 then
			setPuttern( chara_, 9 )
			setVelocity( chara_, 10, 2 )
			PlaySE("./Data/Sound/SE/sword1.wav",100,170)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   8,   15,      10,    6.0,  3.0,    15 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
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
		// 攻撃判定フレーム
		if frame_count_ == 4 or
		   frame_count_ == 7 or
		   frame_count_ == 10 or
		   frame_count_ == 16 or
		   frame_count_ == 20 then

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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
		// 攻撃終了
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 21 then
			AttackUnLock( chara_ )
		end
		//
		// 硬直時間終了
		// 硬直時間を経過したら待機にする
		// 受け付け：指定フレームの2倍
		//
       		 if frame_count_ >= 35 then
	
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
	        end
	//-------------------------------------------------------------
    // ▼ 通常攻撃 3 段目
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
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   17,   15,      20,     10.0,  10.0,    65 )
					x, y = getCharaPosition( chara_ )
					setPosition(target,x,y,0)
					x, y = getCharaPosition( target )

					CreateEffect(0,x,y)

					// 武器破損チェック
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

		// 攻撃判定フレーム
		if frame_count_ == 4 or
		   frame_count_ == 7 or
		   frame_count_ == 10 or
		   frame_count_ == 13 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 3,   20,      15,    3.0,  1.0,    3 )	
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end

		//
		// 攻撃終了
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 32 then
			AttackUnLock( chara_ )
		end
		//
		// 硬直時間終了
		// 硬直時間を経過したら待機にする
		// 受け付け：指定フレームの2倍
		//
       		 if frame_count_ >= 43 then
	
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

		if frame_count_ == 0 then
			setPuttern( chara_, 30 )
			setVelocity( chara_,39, 0 )

		elseif frame_count_ == 4 then
			setPuttern( chara_, 31 )
			PlaySE("./Data/Sound/SE/Swordhit3.wav",100,120)
			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   17,   15,      20,    -14.0,  5.0,    65 )
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
    // ▼ 対空攻撃
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


		// 攻撃判定フレーム
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
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 3,   20,      10,    0.0,  9.0,    2 )	
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end

		// 攻撃判定フレーム
		if frame_count_ == 27 then

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	13,   20,      10,   10.0,  -25.0,    60 )	
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end
		//
		// 攻撃終了
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 32 then
			AttackUnLock( chara_ )
		end
		//
		// 硬直時間終了
		// 硬直時間を経過したら待機にする
		// 受け付け：指定フレームの2倍
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
