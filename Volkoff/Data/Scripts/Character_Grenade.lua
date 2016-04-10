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
				setPuttern( chara_, 12 + frame_count_ / 4 )
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
			setPuttern( chara_, 6)
			x, y = getCharaPosition( chara_ )
			GrenadeGenerate(chara_,x,y+40,4,6,0.3,110,50,1,-20,5,100,30,10,10)
			if CheckWeaponBreak( chara_, 1 ) == 1 then
				setBreakWeapon( chara_ );
			end
		end
		if frame_count_== 3 then		        	
			setPuttern( chara_, 7)
		end
		if frame_count_== 5 then		        	
			setPuttern( chara_, 8)
		end
		if frame_count_== 7 then		        	
			setPuttern( chara_, 9)
		end
		if frame_count_== 9 then		        	
			setPuttern( chara_, 10)
		end
		if frame_count_==11 then		        	
			setPuttern( chara_, 11)
			AttackUnLock( chara_ )
		end


		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//
		if frame_count_ == 11 then

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end

	//-------------------------------------------------------------
    // ▼ 通常攻撃 2 段目
    elseif state_ == CHARASTATE_ATTACK_2 then
				setCharaState( chara_, CHARASTATE_WAIT )
			AttackUnLock( chara_ )
	//-------------------------------------------------------------
    // ▼ 通常攻撃 3 段目
    elseif state_ == CHARASTATE_ATTACK_3 then
				setCharaState( chara_, CHARASTATE_WAIT )
				AttackUnLock( chara_ )	

	//-------------------------------------------------------------
    // ▼ ジャンプ攻撃
	elseif state_ == CHARASTATE_ATTACK_JUMP_ATTACK then
		//
		// 画像表示
		// 総動作フレーム      : ( 動作フレーム*コマ数 ) -1
		// setPuttern 第二引数 : 動作フレーム
		//
		if frame_count_== 1 then		        	
			PlaySE("./Data/Sound/SE/sword1.wav",100,150)
			x, y = getCharaPosition( chara_ )
			GrenadeGenerate(chara_,x,y+40,4,7.5,0.3,110,50,1,-20,5,100,30,10,10)
			if CheckWeaponBreak( chara_, 1 ) == 1 then
				setBreakWeapon( chara_ );
			end
			setPuttern( chara_, 6)
		end
		if frame_count_== 3 then		        	
			setPuttern( chara_, 7)
		end
		if frame_count_== 5 then		        	
			setPuttern( chara_, 8)
		end
		if frame_count_== 7 then		        	
			setPuttern( chara_, 9)
		end
		if frame_count_== 9 then		        	
			setPuttern( chara_, 10)
		end
		if frame_count_==11 then		        	
			setPuttern( chara_, 11)
			AttackUnLock( chara_ )
		end


		// 受け付け時間終了
		// 次の段への受け付け時間を超えたら待機にする
		// 受け付け：指定フレームの2倍
		//
		if frame_count_ == 11 then

			setCharaState( chara_, CHARASTATE_WAIT )
			setFrameCount( chara_, -1 )
		end
	//-------------------------------------------------------------
    // ▼ しゃがみ攻撃
	elseif state_ == CHARASTATE_ATTACK_SQUAT_ATTACK then
				setCharaState( chara_, CHARASTATE_WAIT )
			AttackUnLock( chara_ )

	//-------------------------------------------------------------
    // ▼ 対空攻撃
	elseif state_ == CHARASTATE_ATTACK_ANTIAIR_ATTACK then
				setCharaState( chara_, CHARASTATE_WAIT )
			AttackUnLock( chara_ )
	end
end

//=============================================================================
//                              end of file
//=============================================================================
