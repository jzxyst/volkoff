//=============================================================================
// ■ Arrange_Ring
// 2011/1/21 Keisuke Hosoda
//
// 動作：
//  2次元における中心点からの円周上の座標を返す
//=============================================================================
#include "stdafx.h"
#include "Arrange_Ring.h"
#include <d3dx9math.h>
#include <windows.h>

// コンストラクタ
Ring::Ring()
{
	ZeroMemory( &mStdCir, sizeof( StandardCircle ) );
	ZeroMemory( &mSData, sizeof( StarData ) );
	ZeroMemory( &mTData, sizeof( TurnData ) );
}

// デストラクタ
Ring::~Ring()
{
}

//---------------------------------------------------------------------
// < 2011/1/21 Keisuke_Hosoda >
//
// 関数名： Initialize
//
//  引数 ： < void >
// 戻り値： < void >
//  処理 ： 初期化。使用前に一度だけ呼ぶこと
//---------------------------------------------------------------------
void Ring::Initialize()
{
	mTData.InputLock = false;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： Process
//
//  引数 ： < void >
// 戻り値： < void >
//  処理 ： ループの中で呼ぶこと
//---------------------------------------------------------------------
void Ring::Process()
{
	mTData.OldTurnVec = mTData.TurnVec;

	// 回転しているかどうか
	if ( mTData.TurnVec != 0 )
	{
		float ditect = 1;

		// 回転中は入力を受け付けない
		mTData.InputLock = true;

		// 回転方向
		if ( mTData.TurnVec > 0 ) ditect = -1;

		mTData.Deg += mTData.TurnSpeed * ditect;
		mTData.TurnLimit += mTData.TurnSpeed;
	}

	// 回転角度を範囲内に収める
	if ( mTData.Deg < 0 )
		mTData.Deg += 360;
	
	if ( mTData.Deg >= 360 )
		mTData.Deg -= 360;

	// 回転後の基準座標にあるStarの添え字
	if ( mSData.Angle <= mTData.TurnLimit )
	{
		mTData.TurnVec   = 0;
		mTData.TurnLimit = 0;
		mTData.InputLock = false;

		if ( mTData.OldTurnVec > 0 )
		{
			if ( mSData.Target < ( mSData.setNum-1 ) )
				++mSData.Target;
			else
				mSData.Target = 0;
		}
		else
		{
			if ( mSData.Target > 0 )
				--mSData.Target;
			else
				mSData.Target = ( mSData.setNum-1 );
		}

		ResetDeg( &mSData.Target );
	}

	// 角度から円周上の座標を取得
	for ( unsigned int i = 0; i < mSData.setNum; ++i )
	{
		mTData.Rad = D3DXToRadian( mTData.Deg + ( mSData.Angle * i ) + mSData.OriginDeg );
		mSData.Pos[ i ].x = mStdCir.Origin.x + mStdCir.Radius.x * cos( mTData.Rad );
		mSData.Pos[ i ].y = mStdCir.Origin.y - mStdCir.Radius.y * sin( mTData.Rad );
	}
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： Release
//
//  引数 ： < void >
// 戻り値： < void >
//  処理 ： 解放処理。必ず明示的に呼ぶこと
//---------------------------------------------------------------------
void Ring::Release()
{
}

// 以下セッタ＆ゲッタ

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： setCircleOrigin
//
//  引数 ： < const int x, const int y >
// 戻り値： < void >
//  処理 ： 引数指定の場所を円の原点とする
//---------------------------------------------------------------------
void Ring::setCircleOrigin( const int x, const int y )
{
	mStdCir.Origin.x = static_cast< float >( x );
	mStdCir.Origin.y = static_cast< float >( y );
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： setCircleSize
//
//  引数 ： < const float width, const float height >
// 戻り値： < void >
//  処理 ： 円の大きさを引数で指定する
//---------------------------------------------------------------------
void Ring::setCircleSize( const float width, const float height )
{
	mStdCir.Radius.x = width;
	mStdCir.Radius.y = height;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： setCircle
//
//  引数 ： < const int x, const int y, 
//            const float width, const float height >
// 戻り値： < void >
//  処理 ： 円のデータを引数で指定する
//---------------------------------------------------------------------
void Ring::setCircle( const int x, const int y, const float width, const float height )
{
	mStdCir.Origin.x = static_cast< float >( x );
	mStdCir.Origin.y = static_cast< float >( y );
	mStdCir.Radius.x = width;
	mStdCir.Radius.y = height;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： setStarNum
//
//  引数 ： < const unsigned int number >
// 戻り値： < void >
//  処理 ： 円周上に並ぶ座標( Star )の数を設定
//---------------------------------------------------------------------
void Ring::setStarNum( const unsigned int number )
{
	mSData.setNum = number;

	for ( unsigned int i = 0; i < number; ++i )
	{
		HVector2 star;
		ZeroMemory( &star, sizeof( HVector2 ) );
		mSData.Pos.push_back( star );
	}
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： setOriginDeg
//
//  引数 ： < const float degree >
// 戻り値： < void >
//  処理 ： Starの基準角度を引数指定
//---------------------------------------------------------------------
void Ring::setOriginDeg( const float degree )
{
	mSData.OriginDeg = degree;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： setTarget
//
//  引数 ： < const unsigned int idx >
// 戻り値： < void >
//  処理 ： 基準位置に引数指定のStarを配置
//---------------------------------------------------------------------
void Ring::setTarget( const unsigned int idx )
{
	mSData.Target = idx;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： setTurnDirection
//
//  引数 ： < const int direct >
// 戻り値： < void >
//  処理 ： 回転方向、-1, 0, 1で指定
//---------------------------------------------------------------------
void Ring::setTurnDirection( const int direct )
{
	mTData.TurnVec = direct;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： setTurnSpeed
//
//  引数 ： < const float speed >
// 戻り値： < void >
//  処理 ： 基準位置に引数指定のStarを配置
//---------------------------------------------------------------------
void Ring::setTurnSpeed( const float speed )
{
	mTData.TurnSpeed = speed;
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： ResetDeg
//
//  引数 ： < const int target >
// 戻り値： < void >
//  処理 ： 基準座標に引数指定のStarをセットする
//---------------------------------------------------------------------
void Ring::ResetDeg( const unsigned int *target )
{
	calcAngle();
	mTData.Deg = 360 - ( mSData.Angle * static_cast< float >( *target ) );
}

//---------------------------------------------------------------------
// < 2011/10/21 Keisuke_Hosoda >
//
// 関数名： calcAngle
//
//  引数 ： < void >
// 戻り値： < void >
//  処理 ： 円周上の点を等間隔に並べるための角度を計算。
//    基準点から見て最適な角度に調整する。
//    増減させるたびに一度だけ呼ぶ。
//---------------------------------------------------------------------
void Ring::calcAngle()
{
	if ( mSData.setNum != 0 )
		mSData.Angle = 360 / static_cast< float >( mSData.setNum );
	else
		mSData.Angle = 0;
}

//=============================================================================
//								End of File
//=============================================================================