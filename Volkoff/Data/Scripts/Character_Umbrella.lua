//=============================================================================
//【 Character_BareHands 】
//-----------------------------------------------------------------------------
//  素手状態の動作の定義
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
		setFrameCount( chara_, -1 )
        
	//-------------------------------------------------------------
    // ▼ 走り状態
    elseif state_ == CHARASTATE_RUN then

		if getOnGround( chara_ ) then
			// 地上では歩行モーション
			if frame_count_ < 23 then
				setPuttern( chara_, 12 + frame_count_ / 5 )
			else
				// 経過フレーム数を 0 に戻す
				setFrameCount( chara_, -1 )
			end
		else
			// 空中ではジャンプモーション
			if frame_count_  <= 7 then
				setPuttern( chara_, 24 + frame_count_ / 2 )
			elseif frame_count_ >= 8 then
				setPuttern( chara_, 27 )
				setFrameCount( chara_, 8 )
			end
		end

	//-------------------------------------------------------------
    // ▼ ジャンプ
    elseif state_ == CHARASTATE_JUMP then

		if frame_count_  <= 7 then
			setPuttern( chara_, 24 + frame_count_ / 2 )
		elseif frame_count_ == 8 then
			setPuttern( chara_, 27 )
		end

	//-------------------------------------------------------------
    // ▼ しゃがみ
    elseif state_ == CHARASTATE_SQUAT then

		if frame_count_ < 2 then
			setPuttern( chara_, 36 )
		else
			setPuttern( chara_, 37 )
            setFrameCount( chara_, 3 )
		end

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

		setPuttern( chara_, 86 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // ▼ しゃがみガード
    elseif state_ == CHARASTATE_SQGUARD then
		setPuttern( chara_, 74 )
		setFrameCount( chara_, 3 )

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
			setPuttern( chara_, 102 + frame_count_ / 4 ) 
			//
			// 動作終了、消えるまで最後のコマを表示
			//
		elseif frame_count_ == 20 then
			setPuttern( chara_, 102 + 4 )
		end

		return
	

	//-------------------------------------------------------------
    // ▼ 通常攻撃 1 段目
    elseif state_ == CHARASTATE_ATTACK_1 then

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_== 1 then		        	
				PlaySE("./Data/Sound/SE/sword1.wav",100,150)
		end

        if frame_count_ <= 9 then
			setPuttern( chara_, 6 + frame_count_ / 4 )
			//
			// 攻撃終了、次段受け付け
			// frame_count_    : 動作フレーム*コマ数
			// 行動制限のロックを解除し、
			// 画像をフォロースルーのものに変更。
			//

		elseif frame_count_ == 16 then
			AttackUnLock( chara_ )
		end

		if frame_count_== 9 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// とりあえず敵に攻撃
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun

					attackEffect( chara_, target,	  14,   40,      5,    1.0,  1.0,    8 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end	    

				end
			end
		end

		//
		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//
		if frame_count_ == 40 then

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // ▼ 通常攻撃 2 段目
    elseif state_ == CHARASTATE_ATTACK_2 then
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_== 1 then
				PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			setPuttern( chara_, 18 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 19 )
		end

		if frame_count_ ==9 then
			setPuttern( chara_,20 )
		end

		if frame_count_ ==12 then
			setPuttern( chara_,21 )
		end

		if frame_count_ ==15 then
			setPuttern( chara_, 30 )
		end

		if frame_count_ ==24 then
			//setPuttern( chara_,31 )
		end

		if frame_count_ ==28 then
			//setPuttern( chara_,32 )
		end
		if frame_count_ ==32 then
			//setPuttern( chara_,33 )
		end
		//
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ ==16 then	
			AttackUnLock( chara_ )
		end
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// 攻撃判定フレーム
		if frame_count_ ==6 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 18,   40,      15,    2.0,  0.0,    45 )
					
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end
        
		//
		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//

		if frame_count_ == 50 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // ▼ 通常攻撃 3 段目
    elseif state_ == CHARASTATE_ATTACK_3 then
		
			//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_ >= 10 then
			setVelocity( chara_,5, 0 )
		end
		if frame_count_ == 8 then
			setVelocity( chara_,6, 4 )
		end
		if frame_count_== 1 then
				PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			setPuttern( chara_, 18 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 78 )
		end

		if frame_count_ ==7 then
			setPuttern( chara_,79 )
		end

		if frame_count_ ==13 then
			PlaySE("./Data/Sound/SE/kan1a.wav",80,60)
			setPuttern( chara_,80 )
		end

		if frame_count_ ==30 then
			setPuttern( chara_, 81)
		end

		//
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ ==42 then	
			AttackUnLock( chara_ )
		end
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// 攻撃判定フレーム
		if frame_count_ == 8 or
			frame_count_ == 18 or
			frame_count_ == 25 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 12,   40,      15,    10.0,  2.0,    40 )
					//x, y = getCharaPosition( chara_ )
					//CreateEffect(1,x,y+20)
					
					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end
				end
			end
		end
        
		//
		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//

		if frame_count_ == 50 then
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

		if frame_count_<= 30 and frame_count_>= 0 then
			setAccel( chara_,0,-0.1)

		end

		if frame_count_== 1 then
			if CheckWeaponBreak( chara_, 1 ) == 1 then
				setBreakWeapon( chara_ );
			end
			setPuttern( chara_, 78 )
			setVelocity( chara_,4, 6 )
			PlaySE("./Data/Sound/SE/kan1a.wav",80,60)
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 79 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 80 )
		end


			//
			// 攻撃終了
			// frame_count_    : 動作フレーム*コマ数
			// 行動制限のロックを解除し、
			// 画像をフォロースルーのものに変更。
			//
		if frame_count_ == 40 then
			AttackUnLock( chara_ )
			setAccel( chara_,0,-1)
			setPuttern( chara_, 27 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 8 or
		   frame_count_ == 15 or
		   frame_count_ == 20 or
		   frame_count_ == 25 or
		   frame_count_ == 30 or
		   frame_count_ == 35 or
		   frame_count_ == 40 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 14,   30,      30,    5.0,  2.0,    15 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end

		//
		// 硬直時間終了
		// 硬直時間を経過したらジャンプにする
		// 硬直時間：指定フレームの1.5倍
		//
        if frame_count_ == 60 then
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

		if frame_count_== 1 then
				PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			 setPuttern( chara_, 42 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 43 )
		end

		if frame_count_ == 12 then
				PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			setPuttern( chara_, 42 )
		end

		if frame_count_ ==18 then
			setPuttern( chara_, 43 )
		end


			//
			// 攻撃終了
			// frame_count_    : 動作フレーム*コマ数
			// 行動制限のロックを解除し、
			// 画像をフォロースルーのものに変更。
			//
		if frame_count_ == 24 then
			AttackUnLock( chara_ )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 6 or
		   frame_count_ == 18 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  13,   20,      20,    2.0,  2.0,    8 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end

		//
		// 硬直時間終了
		// 硬直時間を経過したら待機にする
		// 受け付け：指定フレームの2倍
		//
        if frame_count_ == 27 then

			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 47 )
			end

			setCharaState( chara_, CHARASTATE_SQUAT )
			setFrameCount( chara_, 5 )
        end

	//-------------------------------------------------------------
    // ▼ 対空攻撃
	elseif state_ == CHARASTATE_ATTACK_ANTIAIR_ATTACK then

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//

		if frame_count_== 1 then
			 setPuttern( chara_, 66 )
		end

       if frame_count_ == 4 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 68 )
					x, y = getCharaPosition( chara_ )
					CreateEffect(1,x,y+80)
					PlaySE("./Data/Sound/SE/Explosion01.ogg",50,130)
		end


			//
			// 攻撃終了
			// frame_count_    : 動作フレーム*コマ数
			// 行動制限のロックを解除し、
			// 画像をフォロースルーのものに変更。
			//
		if frame_count_ == 95 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
			//setPuttern( chara_, 71 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 6 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  42,   30,      50,    8.0,  18.0,   120 )
					setFrameCount( chara_, 75 )
					if CheckWeaponBreak( chara_, 3 ) == 1 then
						setBreakWeapon( chara_ );
					end
				end
			end
		end
		if frame_count_ == 10 or
		   frame_count_ == 18 or
		   frame_count_ == 24 or
		   frame_count_ == 32 or
		   frame_count_ == 50 or
		   frame_count_ == 65 or
		   frame_count_ == 80 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	5,   20,      10,    5.0,  5.0,   15 )
					setFrameCount( chara_,frame_count_+7  )
					//if CheckWeaponBreak( chara_, 1 ) == 1 then
					//	setBreakWeapon( chara_ );
					//end
				end
			end
		end
		//
		// 硬直時間終了
		// 硬直時間を経過したら待機にする
		// 受け付け：指定フレームの2倍
		//
        if frame_count_ >= 100 then

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
