//=============================================================================
//【 DamagePop 】
//-----------------------------------------------------------------------------
///**
//  @file       DamagePop.h
//  @brief      DamagePop
//  @author     yama
//*/
//=============================================================================

#pragma once

#include <list>

//=============================================================================
// ■ DamagePop クラス
//-----------------------------------------------------------------------------
///**
//  @brief     被ダメージ時などにポップする数字を管理するクラス
//*/
//=============================================================================
class DamagePop
{
public:

    DamagePop();

    ~DamagePop();

    //---------------------------------------------------------------------
    ///**
    //  @brief      数字を表示させる
    //
    //  @param[in]  pos_   : 出現させる座標 (3D空間)
    //  @param[in]  value_ : 値 (正の整数)
    //  @param[in]  type_  : 数値の種類(色 0=白 1=ダメージ 2=回復 3=クリティカル)
    //
    //*/
    //---------------------------------------------------------------------
    void popNumber( const LVector3& pos_, u32 value_, int type_ );

    //---------------------------------------------------------------------
    ///**
    //  @brief      フレーム更新
    //*/
    //---------------------------------------------------------------------
    void update();



    
private:

    // ポップしている数字ひとつ分を表すクラス
    class PopNumber
    {
    public:
        PopNumber( const LVector3& pos_, u32 value_, int type_, LTexture texture_ );
        ~PopNumber();

        bool update();

    private:

        LVector3    mPosition;
        LVector3    mVelocity;
        ln::Ref<ln::UISprite>     mNumberSprite;
        LTexture    mNumberTexture;
        u32         mFrameCount;

    };

private:

    typedef std::list< PopNumber* >     PopNumberList;

private:

    PopNumberList   mPopNumberList;
    LTexture        mNumberTexture;
    
    
};

//=============================================================================
//								end of file
//=============================================================================