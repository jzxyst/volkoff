//=============================================================================
//【 Character_KATANA 】
//-----------------------------------------------------------------------------
//  刀装備状態の動作の定義
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
    
        setPuttern( chara_, 0)
        
	//-------------------------------------------------------------
    // ▼ 走り状態
    elseif state_ == CHARASTATE_RUN then

		if getOnGround( chara_ ) then
			// 地上では歩行モーション
			if frame_count_ < 29 then
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

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//

		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 66 )
		end

       if frame_count_ == 2 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 68 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 69 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 70 )
		end

			//
			// 攻撃終了
			// frame_count_    : 動作フレーム*コマ数
			// 行動制限のロックを解除し、
			// 画像をフォロースルーのものに変更。
			//
		if frame_count_ == 6 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 3 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  10,   20,      15,    5.0,  5.0,    10 )
				end
			end
		end
		if frame_count_ < 8 then
			//setPuttern( chara_, 36 )
		else
			setPuttern( chara_, 37 )

			// 経過フレーム数を 3 で固定
			// オーバーフロー怖いんで。
           	 setFrameCount( chara_, 8 )
		end


	//-------------------------------------------------------------
    // ▼ のけぞり
    elseif state_ == CHARASTATE_STUN then

		setPuttern( chara_, 103 )
		setFrameCount( chara_, -1 )
        
	//-------------------------------------------------------------
    // ▼ 吹っ飛び
    elseif state_ == CHARASTATE_BLOW then

		setPuttern( chara_, 60 )
		setFrameCount( chara_, -1 )

	//-------------------------------------------------------------
    // ▼ ガード
    elseif state_ == CHARASTATE_GUARD then

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_== 1 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 10 )
		end

		//
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 8 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)			
			AttackUnLock( chara_ )
			//setPuttern( chara_, 11 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// 攻撃判定フレーム
		if frame_count_ == 5 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 6,   20,      15,    2.0,  2.0,    10 )
				end
			end
		end
        
		if frame_count_ > 8 then
			setPuttern( chara_, 72 )
			//setFrameCount( chara_, -1 )
        	 setFrameCount( chara_, 8 )
		end
	//-------------------------------------------------------------
    // ▼ しゃがみガード
    elseif state_ == CHARASTATE_SQGUARD then

		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setVelocity( chara_, 0, 0 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 19 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 21 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 22 )
		end

		//
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 7 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
			setPuttern( chara_, 23 )

		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 4 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 6,   20,      2,   10.0,  1.0,    5 )
				end
			end
		end
		if frame_count_ > 8 then
			//setPuttern( chara_, 72 )
			//setFrameCount( chara_, -1 )
        	 setFrameCount( chara_, 1 )
		end
	//-------------------------------------------------------------
    // ▼ はしご待機
    elseif state_ == CHARASTATE_LADDER_WAIT then
		// なにもしない。昇降モーション止めればいい

		setFrameCount( chara_, frame_count_ - 1  )

	//-------------------------------------------------------------
    // ▼ はしご上り/降り 同じモーションなので統合
    elseif state_ == CHARASTATE_LADDER_UP or
		state_ == CHARASTATE_LADDER_DOWN then

		if frame_count_ == 0 then
			setPuttern( chara_, 96 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 97 )
		end

		if frame_count_ == 14 then
			setPuttern( chara_, 98 )
		end

		if frame_count_ == 21 then
			setPuttern( chara_, 97 )
		end

		if frame_count_ == 28 then
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // ▼ アイテム拾い
    elseif state_ == CHARASTATE_ITENGET then

	//-------------------------------------------------------------
    // ▼ 死亡
    elseif state_ == CHARASTATE_DEAD then
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
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 2 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 10 )
		end
		if frame_count_== 6 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 9 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 10 then
			setPuttern( chara_, 10 )
		end
		if frame_count_== 11 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 13 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 14 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 15 then
			setPuttern( chara_, 10 )
		end
		//
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 16 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)			
			AttackUnLock( chara_ )
			setPuttern( chara_, 11 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		// 攻撃判定フレーム
		if frame_count_ == 3 or
		   frame_count_ == 8 or
		   frame_count_ ==13 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 4,   20,      15,    1.0,  1.0,    10 )
				end
			end
		end
        
		//
		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//
		if frame_count_ == 20 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // ▼ 通常攻撃 2 段目
    elseif state_ == CHARASTATE_ATTACK_2 then


		if frame_count_== 1 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 10 )
		end
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_== 8 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setVelocity( chara_, 15, 0 )
			 setPuttern( chara_, 18 )
		end

		if frame_count_ == 11 then
			setPuttern( chara_, 19 )
			setVelocity( chara_, 15, 0 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ == 13 then
			setPuttern( chara_, 21 )
		end

		if frame_count_ == 14 then
			setPuttern( chara_, 22 )
		end
////////////////
		if frame_count_== 15 then
			PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,110)
			PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			setPuttern( chara_, 6 )
		end

		if frame_count_ == 17 then
			setPuttern( chara_, 7 )
		end

		if frame_count_ == 18 then
			setPuttern( chara_, 8 )
		end

		if frame_count_ == 19 then
			setPuttern( chara_, 9 )
		end

		if frame_count_ == 20 then
			setPuttern( chara_, 10 )
		end
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_== 21 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setVelocity( chara_, 15, 0 )
			 setPuttern( chara_, 18 )
		end

		if frame_count_ == 23 then
			setPuttern( chara_, 19 )
			setVelocity( chara_, 15, 0 )
		end

		if frame_count_ == 24 then
			setPuttern( chara_, 20 )
		end

		if frame_count_ == 25 then
			setPuttern( chara_, 21 )
		end

		if frame_count_ == 26 then
			setPuttern( chara_, 22 )
		end
		//
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 28 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			AttackUnLock( chara_ )
			setPuttern( chara_, 23 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 5 or
		   frame_count_ == 18 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 4,   20,      15,    2.0,  2.0,    10 )
				end
			end
		end

		if frame_count_ == 12 or
		   frame_count_ == 24 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	 6,   20,      15,   3.0,  2.0,    15 )
				end
			end
		end

		//
		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//
		if frame_count_ == 34 then
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

		if frame_count_== 1 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 66 )
			 setVelocity( chara_, -5, 0 )
		end

      		 if frame_count_ == 3 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 68 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 69 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 70 )
		end
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//

		if frame_count_== 10 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 17,0 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 55 )
			 setVelocity( chara_, 17,0 )
		end

		if frame_count_ == 14 then
			setPuttern( chara_, 56 )
			 setVelocity( chara_, 17,0 )
		end

		if frame_count_ == 16 then
			setPuttern( chara_, 57 )
			setVelocity( chara_, 17,0 )
		end

		if frame_count_ == 18 then
			setPuttern( chara_, 58 )
		end
		
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//

		if frame_count_== 19 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,120)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 30 )
		end

		if frame_count_ ==23 then
			setPuttern( chara_, 31 )
		end

		if frame_count_ ==26 then
			setPuttern( chara_, 32 )
		end

		if frame_count_ ==28 then
			setPuttern( chara_, 33 )
		end

		if frame_count_ ==30 then
			setPuttern( chara_, 34 )
		end
		if frame_count_ ==32 then
			setPuttern( chara_,102 )
		end
		if frame_count_ ==43 then
			setPuttern( chara_,103 )
		end
		//
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 85 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 35 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
//
		if frame_count_ == 5 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  9,   20,      15,    8.0,  4.0,    10 )
				end
			end
		end

		if frame_count_ == 12 or
			frame_count_ == 14 or
			frame_count_ == 16 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  7,   30,      15,    5.0,  .0,    10 )
				end
			end
		end
//
		if frame_count_ == 26 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  15,   20,      15,   18.0,  2.0,    60 )
				end
			end
		end

		//
		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//
        if frame_count_ == 88 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
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
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 3 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 58 )
		end
		if frame_count_== 7 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 9 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 10 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 11 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 12 then
			setPuttern( chara_, 58 )
		end
		if frame_count_== 13 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 15 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 16 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 17 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 18 then
			setPuttern( chara_, 58 )
		end

		if frame_count_== 19 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 21 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 22 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 23 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 24 then
			setPuttern( chara_, 58 )
		end
		if frame_count_== 25 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 27 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 28 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 29 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 30 then
			setPuttern( chara_, 58 )
		end
		if frame_count_== 31 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 0,-8 )
		end

		if frame_count_ == 33 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 34 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 35 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 36 then
			setPuttern( chara_, 58 )
		end

		//3だんめ
		if frame_count_== 37 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,120)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)
			 PlaySE("./Data/Sound/SE/don01.wav",100,120)		
			 setPuttern( chara_, 30 )
		end

		if frame_count_ == 38 then
			setPuttern( chara_, 31 )
		end

		if frame_count_ == 39 then
			setPuttern( chara_, 32 )
		end

		if frame_count_ == 40 then
			setPuttern( chara_, 33 )
		end

		if frame_count_ == 41 then
			setPuttern( chara_, 34 )
		end

		if frame_count_ == 50 then
			setPuttern( chara_, 48 )
		end
		if frame_count_ == 60 then
			setPuttern( chara_, 102 )
		end
		if frame_count_ == 70 then
			setPuttern( chara_, 103 )
		end

			//
			// 攻撃終了
			// frame_count_    : 動作フレーム*コマ数
			// 行動制限のロックを解除し、
			// 画像をフォロースルーのものに変更。
			//
		if frame_count_ == 95 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)

			//setPuttern( chara_, 0 )
			setPuttern( chara_, 27 )
			AttackUnLock( chara_ )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 4 or
			frame_count_ == 10 or
			frame_count_ == 16 or
			frame_count_ == 22 or
			frame_count  == 28 or
			frame_count_ == 34 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  6,   30,      20,    0,  0,    17 )
				end
			end
		end
		if frame_count_ == 39 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  15,   20,      15,   14.0,  2.0,    60 )
				end
			end
		end

		//
		// 硬直時間終了
		// 硬直時間を経過したら待機にする
		// 受け付け：指定フレームの2倍
		//
        if frame_count_ == 100 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
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
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,120)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 30 )
		end

		if frame_count_ == 4 then
			setPuttern( chara_, 31 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 32 )
		end

		if frame_count_ == 7 then
			setPuttern( chara_, 33 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 34 )
		end
		if frame_count_ == 10 then
			setPuttern( chara_, 35 )
		end
		if frame_count_ == 35 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
			setPuttern( chara_, 0 )
		end
		//
		// 攻撃終了、次段受け付け
		// frame_count_    : 動作フレーム*コマ数
		// 行動制限のロックを解除し、
		// 画像をフォロースルーのものに変更。
		//
		if frame_count_ == 50 then
			AttackUnLock( chara_ )
			setPuttern( chara_, 0 )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;

		if frame_count_ == 6 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  20,   20,      15,   15.0,  2.0,    60 )
				end
			end
		end

		//
		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//
        if frame_count_ == 45 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)
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
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 66 )
			 setVelocity( chara_, -5, 0 )
		end

      		 if frame_count_ == 3 then
			setPuttern( chara_, 67 )
		end

		if frame_count_ == 5 then
			setPuttern( chara_, 68 )
		end

		if frame_count_ == 6 then
			setPuttern( chara_, 69 )
		end

		if frame_count_ == 8 then
			setPuttern( chara_, 70 )
		end
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//

		if frame_count_== 10 then
			 PlaySE("./Data/Sound/SE/KATANA_attack.wav",20,100)
			 PlaySE("./Data/Sound/SE/sword1.wav",30,350)

			 setPuttern( chara_, 54 )

			 setVelocity( chara_, 13,13 )
		end

		if frame_count_ == 13 then
			setPuttern( chara_, 55 )
		end

		if frame_count_ == 16 then
			setPuttern( chara_, 56 )
		end

		if frame_count_ == 17 then
			setPuttern( chara_, 57 )
		end

		if frame_count_ == 20 then
			setPuttern( chara_, 58 )
		end
		if frame_count_ == 25 then
			setPuttern( chara_, 102)
			 setVelocity( chara_, 0, 0 )
		end

			//
			// 攻撃終了
			// frame_count_    : 動作フレーム*コマ数
			// 行動制限のロックを解除し、
			// 画像をフォロースルーのものに変更。
			//
		if frame_count_ == 45 then
			PlaySE("./Data/Sound/SE/KATANA_attack_end.wav",50,120)

			//setPuttern( chara_, 0 )
			setPuttern( chara_, 27 )
			AttackUnLock( chara_ )
		end

		target_group = ( getCharaAttackedGroup( chara_ ) == ATKGROUP_PLAYER ) and ATKGROUP_ENEMY or ATKGROUP_PLAYER;
		if frame_count_ == 5 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					DecrementUseCount(1)
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  10,   20,      15,    8.0,  8.0,    20 )
				end
			end
		end

		if frame_count_ == 13 or
			frame_count_ == 16 or
			frame_count_ == 17 then
			// 敵に攻撃
			list = judgeAttackCollision( chara_, target_group )
			if not ( list == nil ) then
				for i, target in ipairs( list ) do
					// target を攻撃する		  damage  rand  critical  brow_x  brow_y  stun
					attackEffect( chara_, target,	  7,   30,      30,    3.0,  -5.0,    30 )
				end
			end
		end

		//
		// 硬直時間終了
		// 硬直時間を経過したら待機にする
		// 受け付け：指定フレームの2倍
		//
        if frame_count_ == 48 then
			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
        end
	end
end

//=============================================================================
//                              end of file
//=============================================================================
