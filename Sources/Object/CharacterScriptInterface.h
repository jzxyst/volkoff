//=============================================================================
//【 CharacterScriptInterface 】
//-----------------------------------------------------------------------------
///**
//  @file       CharacterScriptInterface.h
//  @brief      CharacterScriptInterface
//  @author     yama
//*/
//=============================================================================

#pragma once

#include "../Lua/lua.hpp"
#include "Character.h"

//=============================================================================
// ■ CharacterScriptInterface クラス
//-----------------------------------------------------------------------------
///**
//	@brief      Lua に登録する関数をまとめたクラス
//
//  
//*/
//=============================================================================
class CharacterScriptInterface
{
public:

    /// インスタンスの取得
    static CharacterScriptInterface* getInstance();

    //---------------------------------------------------------------------
	///**
    //  @brief      アニメーションのフレーム更新
    //
    //  @param[in]  character_  : 更新するキャラクター
    //*/    
    //---------------------------------------------------------------------
    void update( Character* character_ );

private:

    /// コンストラクタ
    CharacterScriptInterface();

    /// デストラクタ
    ~CharacterScriptInterface();


private:

    // ▼ 以下は Lua に登録する関数

    //---------------------------------------------------------------------
	///**
    //  @brief      キャラクターの属する攻撃グループの取得
    //
    //  @param[in]  p1 : キャラクターのポインタ
    //
    //  @return     AttackedGroup の値
    //*/
    //---------------------------------------------------------------------
	static int getCharaAttackedGroup( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      キャラクターのポジションの取得
    //
    //  @param[in]  p1 : キャラクターのポインタ
    //
    //  @return     X座標,Y座標
    //*/
    //---------------------------------------------------------------------
	static int getCharaPosition( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      キャラクターの状態を設定する
    //
    //  @param[in]  p1 : キャラクターのポインタ
    //  @param[in]  p2 : 設定する状態
    //*/
    //---------------------------------------------------------------------
	static int setCharaState( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      フレーム数を設定する
    //
    //  @param[in]  p1 : キャラクターのポインタ
    //  @param[in]  p2 : フレーム数
    //
    //  @par
    //              lua の update() が終わった後、自動的にフレーム数は +1 される。
    //              アニメーションループを行いたい場合、この関数を使って
    //              値を設定すること。
    //*/
    //---------------------------------------------------------------------
	static int setFrameCount( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      キャラクターのアニメパターンを設定する
    //
    //  @param[in]  p1 : キャラクターのポインタ
    //  @param[in]  p2 : 設定するパターン番号
    //*/
    //---------------------------------------------------------------------
	static int setPuttern( lua_State *l_ );


    //---------------------------------------------------------------------
	///**
    //  @brief      攻撃の当たり判定を行う
    //
    //  @param[in]  p1 : キャラクターのポインタ
    //  @param[in]  p2 : 対象のグループ (AttackedGroup の組み合わせ)
    //
    //  @par
    //              現在のアニメーション状態 (CharaState、向き、経過フレーム数)
    //              から攻撃の当たり判定を実行し、当たったオブジェクトの
    //              ハンドルの配列 (テーブル) を返す。
    //*/
    //---------------------------------------------------------------------
	static int judgeAttackCollision( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      攻撃効果の適用 (対象を攻撃する)
    //
    //  @param[in]  p1 : キャラクターのポインタ (攻撃側キャラクター)
    //  @param[in]  p2 : 攻撃対象を表すキャラクターのポインタ (被ダメージ側キャラクター)
    //  @param[in]  p3 : 基本ダメージ量
    //  @param[in]  p4 : ランダム率 (30とすると、±30% の範囲で変動する)
    //  @param[in]  p5 : クリティカル率 (%)
    //  @param[in]  p6 : ふっ飛ばしベクトル X (キャラが右を向いている時)
    //  @param[in]  p7 : ふっ飛ばしベクトル Y
    //  @param[in]  p8 : のけぞりフレーム数
    //*/
    //---------------------------------------------------------------------
	static int attackEffect( lua_State *l_ );

    //---------------------------------------------------------------------
	///**
    //  @brief      キャラクターを削除する
    //
    //  @param[in]  p1 : キャラクターのポインタ
    //
    //  @par
    //              呼ばれたフレームの update() 終了時に解放する。
    //*/
    //---------------------------------------------------------------------
	static int disposeObject( lua_State *l_ );

	//
	// Character::AttackLock
	// 攻撃時の行動制限
	//
	// @param[in] p1 : キャラクターのポインタ
	//
	// 呼ぶとロックがかかります。
	// 攻撃モーションをジャンプなどでキャンセルさせないため
	//
	static int AttackLock( lua_State *l_ );

	//
	// Character::AttackUnLock
	// 攻撃時の行動制限解除
	//
	// @param[in] p1 : キャラクターのポインタ
	//
	// 呼ぶとロックがはずれます。
	// 攻撃モーション終了時には必ず呼んでください
	//
	static int AttackUnLock( lua_State *l_ );

	//
	// CharacterScriptInterface::getOnGround
	//
	// @param[in] p1 : キャラクタのポインタ
	//
	// 現在地上にいるかどうかを返す
	// 1        = 地上
	// それ以外 = 空中
	//
	static int getOnGround( lua_State *l_ );

	//
	// CharacterScriptInterface::setVelocity
	// 攻撃時の移動量を指定
	//
	// @param[in] p1 : キャラクタのポインタ
	// @param[in] p2 : キャラクタのｘベクトル
	// @param[in] p3 : キャラクタのｙベクトル
	//
	// ｘはキャラが向いてるほうが＋です
	// 戻り値は無し
	//
	static int setVelocity( lua_State *l_ );

	//
	// CharacterScriptInterface::CheckWeaponBreak
	//
	// @param[in] p1 : キャラクタのポインタ
	// @param[in] p2 : 武器へのダメージ
	//
	// 戻り値
	// 　０　：無事
	// 　１　：武器破損
	// 武器が壊れたかどうかを判定します。
	//
	static int CheckWeaponBreak( lua_State *l_ );

	//
	// CharacterScriptInterface::setBreakWeapon
	//
	// @param[in] p1 : キャラクタのポインタ
	// @param[in] p2 : 武器が破損したかどうか
	//
	// 攻撃時に呼んでください。
	// 武器が破損していれば1を指定してください。
    //
    //  [yama] 武器破壊時の素手切り替えを Character::UpdateSelf() に移行したのに合わせて、
    //  この関数は非推奨。中身は空の実装にしました。
	//
	static int setBreakWeapon( lua_State *l_ );

	//
	// CharacterScriptInterface::getBreakWeapon
	//
	// @param[in] p1 : キャラクタのポインタ
	//
	// 攻撃時、武器が破損しているか確認する
	// 素手は呼ばないよーに！
	//
	static int getBreakWeapon( lua_State *l_ );

	static int PlaySE( lua_State *l_ );

	static int CreateEffect( lua_State *l_ );

	static int setDirection( lua_State *l_);

	static int setPosition( lua_State *l_);

	static int GrenadeGenerate( lua_State * l_);

	static int BulletGenerate( lua_State * l_);

	static int setInvincibleFrame( lua_State * l_);

	static int setAccel(lua_State * l_);

	static int getDirection( lua_State * l_);

	static int getLife(lua_State * l_);

	static int setLife(lua_State *l_);

	static int getMaxLife(lua_State * l_);

	static int getRank(lua_State * l_);

	static int getPlayerPos(lua_State *l_);
	static int Rand(lua_State *l_);

	static int getPhase(lua_State *l_);

	static int setNum(lua_State *l_);

	static int getNum(lua_State *l_);

	static int SummonEnemy(lua_State *l_);

	static int Division(lua_State *l_);

	static int SetOpacity(lua_State *l_);

	static int SetDestructfrag(lua_State *l_);

	static int GetDestructfrag(lua_State *_);

	static int ThunderGenerate(lua_State *_);

	static int SummonSoul(lua_State *_);

private:

    lua_State* mLuaStates[ WEAPON_MAX_NUM ];

};

//=============================================================================
//                              end of file
//=============================================================================
