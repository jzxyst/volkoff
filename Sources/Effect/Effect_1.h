//=============================================================================
//【 Effect_1 】
//-----------------------------------------------------------------------------
///**
//  @file       Effect_1.h
//  @brief      Effect_1
//  @author     yama
//  @par
//              エフェクトひとつにつきひとつソースファイル使うのは例によってナシ。
//              ひとつのソースに 10 個くらいまとめる方向で。
//*/
//=============================================================================

#pragma once

#include "EffectBase.h"

//=============================================================================
// ■ Effect_Test_1 クラス
//-----------------------------------------------------------------------------
///**
//  @brief		テスト用エフェクト
//*/
//=============================================================================
class Effect_Test_1 : public EffectBase
{
public:

	/// コンストラクタ
    Effect_Test_1( const LVector3& pos_ );

    /// デストラクタ
    ~Effect_Test_1();

public:

    /// フレーム更新 (false を返すと解放する)
    virtual bool update();

private:

    Ref<LBatchPanel>  mPanel;
    u32     mFrameCount;

};


//=============================================================================
// ■ Effect_Test_2 クラス
//-----------------------------------------------------------------------------
///**
//  @brief		テスト用エフェクト
//*/
//=============================================================================
class Effect_Test_2 : public EffectBase
{
public:

	/// コンストラクタ
    Effect_Test_2( const LVector3& pos_ );

    /// デストラクタ
    ~Effect_Test_2();

public:

    /// フレーム更新 (false を返すと解放する)
    virtual bool update();

private:

    Ref<LBatchPanel>  mPanel;
    u32     mFrameCount;

};



//=============================================================================
// ■ Effect_Explosion クラス
//-----------------------------------------------------------------------------
///**
//  @brief		爆発エフェクト
//*/
//=============================================================================
class Effect_Explosion : public EffectBase
{
public:

	/// コンストラクタ
    Effect_Explosion( const LVector3& pos_ );

    /// デストラクタ
    ~Effect_Explosion();

public:

    /// フレーム更新 (false を返すと解放する)
    virtual bool update();

private:
	static const int scm_nComNum = 5;

    Ref<LBatchPanel>  mPanel;
    u32     mFrameCount;

};
//=============================================================================
// ■ Effect_Explosion2 クラス
//-----------------------------------------------------------------------------
///**
//  @brief		爆発エフェクト2
//*/
//=============================================================================
class Effect_Explosion2 : public EffectBase
{
public:

	/// コンストラクタ
    Effect_Explosion2( const LVector3& pos_ );

    /// デストラクタ
    ~Effect_Explosion2();

public:

    /// フレーム更新 (false を返すと解放する)
    virtual bool update();

private:
	static const int scm_nComNum = 5;

    Ref<LBatchPanel>  mPanel;
    u32     mFrameCount;

};

//=============================================================================
// ■ Effect_Test_3 クラス
//-----------------------------------------------------------------------------
///**
//  @brief		テスト用エフェクト
//*/
//=============================================================================
class Effect_Test_3 : public EffectBase
{
public:

	/// コンストラクタ
    Effect_Test_3( const LVector3& pos_ );

    /// デストラクタ
    ~Effect_Test_3();

public:

    /// フレーム更新 (false を返すと解放する)
    virtual bool update();

private:

    LPanel  mPanel;
    u32     mFrameCount;

};

//=============================================================================
// ■ Effect_Test_3 クラス
//-----------------------------------------------------------------------------
///**
//  @brief		テスト用エフェクト
//*/
//=============================================================================
class Effect_Thunder : public EffectBase
{
public:

	/// コンストラクタ
    Effect_Thunder( const LVector3& pos_ );

    /// デストラクタ
    ~Effect_Thunder();

public:

    /// フレーム更新 (false を返すと解放する)
    virtual bool update();

private:

    LPanel  mPanel;
    u32     mFrameCount;

};
//=============================================================================
//								end of file
//=============================================================================
