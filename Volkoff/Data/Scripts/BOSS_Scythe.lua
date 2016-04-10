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
		wx, wy = getCharaPosition( chara_ )
		if Rand()%100 == 1 then
			SetOpacity( chara_, 1 )
			setInvincibleFrame(chara_,0)
		end
        
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
    // ▼ 吹っ飛び
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

    // ▼ ガード
    elseif state_ == CHARASTATE_GUARD then

		setPuttern( chara_, 72 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // ▼ しゃがみガード
    elseif state_ == CHARASTATE_SQGUARD then
		setPuttern( chara_, 84 )
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
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//

		if frame_count_ ==50 then	
			AttackUnLock( chara_ )
		end

		// 攻撃判定フレーム
		if frame_count_== 22 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// とりあえず敵に攻撃
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 35,   20,      10,    8.0,  7.0,    60 )

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
    // ▼ 通常攻撃 2 段目
    elseif state_ == CHARASTATE_ATTACK_2 then


	//-------------------------------------------------------------
    // ▼ 通常攻撃 3 段目
    elseif state_ == CHARASTATE_ATTACK_3 then


	//-------------------------------------------------------------
    // ▼ ジャンプ攻撃
	elseif state_ == CHARASTATE_ATTACK_JUMP_ATTACK then
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
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
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
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

		// 攻撃判定フレーム
		if frame_count_ >=6 and frame_count_ <=51 and frame_count_%4 == 1 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// とりあえず敵に攻撃
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 16,   20,      20,   -7.0,  9.0,    50 )

					if CheckWeaponBreak( chara_, 1 ) == 1 then
						setBreakWeapon( chara_, 1 );
					end	    

				end
			end
		end  

		//
		// 硬直時間終了
		// 硬直時間を経過したらジャンプにする
		// 硬直時間：指定フレームの1.5倍
		//
        if frame_count_ == 52 then
			if Rand()%3 == 1 then
				setCharaState( chara_, CHARASTATE_ATTACK_ANTIAIR_ATTACK )
				setFrameCount( chara_, -1 )
			else
				setCharaState( chara_, CHARASTATE_JUMP )
				//
				// ジャンプモーションの最初をキャンセルするために
				// フレームはジャンプモーションの終了時点に指定
				//
				setFrameCount( chara_, 8 )
			end
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
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ ==55 then	
			AttackUnLock( chara_ )
		end

		// 攻撃判定フレーム
		if frame_count_== 11 then
		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// とりあえず敵に攻撃
        list = judgeAttackCollision( chara_, target_group )	
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 15,   20,      20,    2.0,  7.0,    25 )

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

		if frame_count_ == 60 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
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
