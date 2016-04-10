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
			// 地上
			setPuttern( chara_, 12 + frame_count_ / 5 )
			if frame_count_ >= 29 then
			    // 経過フレーム数を 0 に戻す
			    setFrameCount( chara_, -1 )
			end
		else
			// 空中
			if frame_count_  <= 1 then
				setPuttern( chara_, 24 )
			elseif frame_count_ >= 2 then
				setPuttern( chara_, 25 )
				setFrameCount( chara_, 2 )
			end
		end

	//-------------------------------------------------------------
    // ▼ ジャンプ
    elseif state_ == CHARASTATE_JUMP then
		if frame_count_  <= 1 then
			setPuttern( chara_, 24 )
		elseif frame_count_ == 2 then
			setPuttern( chara_, 25 )
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
		setPuttern( chara_, 48 )
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
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_ <= 19 then
			setPuttern( chara_, 60 + frame_count_ / 4 ) 
			//
			// 動作終了、消えるまで最後のコマを表示
			//
		elseif frame_count_ == 20 then
			setPuttern( chara_, 60 + 4 )
		end

		return	

	//-------------------------------------------------------------
    // ▼ 通常攻撃 1 段目
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

			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   12,   15,      10,    3.0,  4.0,    7 )
					x, y = getCharaPosition( target )
					CreateEffect(0,x,y)

					// 武器破損チェック
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
				PlaySE("./Data/Sound/SE/sword1.wav",100,150)
		end

		if frame_count_== 15 then		        	
				PlaySE("./Data/Sound/SE/metal01.wav",150,140)
		end

		if frame_count_ == 0 then
			setPuttern( chara_, 18 )

			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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

			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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
    // ▼ 通常攻撃 3 段目
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

			// 攻撃
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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
    // ▼ ジャンプ攻撃
	elseif state_ == CHARASTATE_ATTACK_JUMP_ATTACK then

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
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
		// 攻撃終了
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		if frame_count_ == 20 then
			AttackUnLock( chara_ )
		end
		

		//
		// 硬直時間終了
		// 硬直時間を経過したらジャンプにする
		// 硬直時間：指定フレームの1.5倍
		//
        if frame_count_ == 20 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 25 )
			end

			setCharaState( chara_, CHARASTATE_JUMP )
			//
			// ジャンプモーションの最初をキャンセルするために
			// フレームはジャンプモーションの終了時点に指定
			//
			setFrameCount( chara_, 25 )

        end


	//-------------------------------------------------------------
    // ▼ しゃがみ攻撃
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
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
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
		// 攻撃終了
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		if frame_count_ == 17 then
			AttackUnLock( chara_ )
		end
		
		if frame_count_ == 22 then

			// 破損してた場合
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
				PlaySE("./Data/Sound/SE/sword1.wav",100,60)
		end

		setVelocity( chara_, 0, 0 )

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
        if frame_count_ <= 25 then
			setPuttern( chara_, 66 + frame_count_ / 4 )
			//
			// 攻撃終了
			// frame_count_    : 動作フレーム*コマ数
			// 行動制限のロックを解除し、
			// 画像をフォロースルーのものに変更。
			//
		elseif frame_count_ == 24 then
			setPuttern( chara_, 66 + 3 )
			AttackUnLock( chara_ )
		end

		if frame_count_ == 10 then
			target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

			// とりあえず敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	   32,   15,      10,    0.0,  -7.0,    20 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
							setBreakWeapon( chara_, 1 );
					end
				end
			end
		end

		//
		// 硬直時間終了
		// 硬直時間を経過したら待機にする
		// 硬直時間：指定フレームの1.5倍
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
