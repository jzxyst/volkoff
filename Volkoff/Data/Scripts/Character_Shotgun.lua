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
			AttackUnLock( chara_ )

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
			AttackUnLock( chara_ )

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

			// 破損してた場合
			if getBreakWeapon( chara_ ) == 1 then
				setPuttern( chara_, 0 )
			end

			setCharaState( chara_, CHARASTATE_JUMP )
			setFrameCount( chara_, 8 )
			
		end


	//-------------------------------------------------------------
    // ▼ しゃがみ攻撃
	elseif state_ == CHARASTATE_ATTACK_SQUAT_ATTACK then

		if frame_count_ == 0 then
			AttackUnLock( chara_ )
		end

		//
		// 硬直時間終了
		// 硬直時間を経過したらしゃがみにする
		// 硬直時間：指定フレームの1.5倍
		//
        if frame_count_ == 0 then

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
