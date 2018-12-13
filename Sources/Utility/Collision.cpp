//
// Collision.cpp
// Datファイルからデータを復元し、
// 当たり判定をするクラス
//

#include "Collision.h"

// コンストラクタ
Collision::Collision()
{
    mReadFP = NULL;
}

// デストラクタ
Collision::~Collision()
{
}

// 初期化
void Collision::Initialize()
{
	for ( int i = 0; i < SET_H_NUM*SET_V_NUM; ++i )
		ZeroMemory( &mLoadData[ i ], sizeof( Data ) );
}

//
// LoadFile
// 引　数 const char* fileName_
// 戻り値 void
//
// 引数で指定された
// 当たり判定データの読み込み
//
void Collision::LoadFile( const char* fileName_ )
{
    if ( mReadFP )
    {
        fclose( mReadFP );
        mReadFP = NULL;
    }

	// 読み込み--------------------------
	fopen_s( &mReadFP, fileName_, "rb" );
	if ( mReadFP == NULL )
	{
		printf( "Error:datファイルオープンに失敗\n" );
		printf( "ファイルが存在しないか、パスが違う可能性があります。\n" );
		printf( "File< %s >\n", fileName_ );
		fclose( mReadFP );
		exit( 1 );
	}
	fread( &mLoadData, sizeof( Data ), SET_H_NUM*SET_V_NUM, mReadFP );
}

//
// getAtkCollision
// 引　数 const unsigned int ActionIdx, const unsigned int Frames
// 戻り値 LRect
//
// アクション番号とコマ番号を渡すと
// 　その動作の攻撃の当たり判定が返る( x, y, width, height )
//
LRect* Collision::getAtkCollision( const unsigned int ActionIdx, const unsigned int Frames )
{
	int idx   = ActionIdx;
	int frame = Frames;

	// idxが2列目
	if ( ActionIdx >= 6 )
	{
		idx   -= 6;
		frame += 6;
	}

	mAtkArea.set(
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.V );

	// すべて０(=データなし)の場合nullリターン
	if ( mAtkArea.x == 0
		&& mAtkArea.y == 0
		&& mAtkArea.width == 0
		&& mAtkArea.height == 0 )
	{
		//printf( "取得位置 Idx %d, Frame %d 該当データなし\n", ActionIdx, Frames );
		return NULL;
	}

    /*
	printf( "当たり判定取得:指定位置%d,%d/取得位置%d,%d\n  攻撃 判定:x %d, y %d, width %d, height %d\n",
		ActionIdx,
		Frames,
		idx,
		frame,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Atk_size.V );
        */

	return &mAtkArea;
}

//
// getDmgCollision
// 引　数 const unsigned int ActionIdx, const unsigned int Frames
// 戻り値 LRect
//
// アクション番号とコマ番号を渡すと
// 　その動作のダメージの当たり判定が返る( x, y, width, height )
//
LRect* Collision::getDmgCollision( const unsigned int ActionIdx, const unsigned int Frames )
{
	int idx   = ActionIdx;
	int frame = Frames;

	// idxが2列目
	if ( ActionIdx >= 6 )
	{
		idx   -= 6;
		frame += 6;
	}

	mDmgArea.set(
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_pos.H,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_pos.V,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_size.H,
		mLoadData[ idx*SET_H_NUM + frame ].Dmg_size.V );

	// すべて０(=データなし)の場合nullリターン
	if ( mDmgArea.x == 0
		&& mDmgArea.y == 0
		&& mDmgArea.width == 0
		&& mDmgArea.height == 0 )
	{
		printf( "取得位置 Idx %d, Frame %d 該当データなし\n", ActionIdx, Frames );
		return NULL;
	}

	return &mDmgArea;
}

//
// getOrigin
// 引　数 const unsigned int ActionIdx, const unsigned int Frames
// 戻り値 LVector2
//
// アクション番号とコマ番号を渡すと
// 　その動作の基準点が返る( x, y )
//
LVector2 Collision::getOrigin( const unsigned int ActionIdx, const unsigned int Frames )
{
	LVector2    Origin;
	int idx   = ActionIdx;
	int frame = Frames;

	// idxが2列目
	if ( ActionIdx >= 6 )
	{
		idx   -= 6;
		frame += 6;
	}

	Origin.x = static_cast< float >( mLoadData[ idx*SET_H_NUM + frame ].origin.H );
	Origin.y = static_cast< float >( mLoadData[ idx*SET_H_NUM + frame ].origin.V );

	return Origin;
}

// [山本] 攻撃用当たり判定をコマ番号から取得する (コマ番号は左上から右にかけて +1、下に行くにつれて +12)
LRect* Collision::getAtkCollisionByIndex( const unsigned int index_ )
{
    mAtkArea.set(
		mLoadData[ index_ ].Atk_pos.H,
		mLoadData[ index_ ].Atk_pos.V,
		mLoadData[ index_ ].Atk_size.H,
		mLoadData[ index_ ].Atk_size.V );

	if ( mAtkArea.x == 0
		&& mAtkArea.y == 0
		&& mAtkArea.width == 0
		&& mAtkArea.height == 0 )
	{
		return NULL;
	}

    return &mAtkArea;
}

// [山本] ダメージ用当たり判定をコマ番号から取得する
LRect* Collision::getDmgCollisionByIndex( const unsigned int index_ )
{
    mDmgArea.set(
		mLoadData[ index_ ].Dmg_pos.H,
		mLoadData[ index_ ].Dmg_pos.V,
		mLoadData[ index_ ].Dmg_size.H,
		mLoadData[ index_ ].Dmg_size.V );

	if ( mDmgArea.x == 0
		&& mDmgArea.y == 0
		&& mDmgArea.width == 0
		&& mDmgArea.height == 0 )
	{
		return NULL;
	}

	return &mDmgArea;
}

// [山本] 原点をコマ番号から取得する
LVector2 Collision::getOriginByIndex( const unsigned int index_ )
{
    return LVector2( 
        static_cast< float >( mLoadData[ index_ ].origin.H ),
        static_cast< float >( mLoadData[ index_ ].origin.V ) );
}

//
// checkHit
// 引　数 const LVector3 alphaPos, const LRect* alpha,
//        const LVector3 betaPos,  const LRect* beta
// 戻り値 bool
//
// 当たり判定のRectを渡すと
// 　当たっているかどうかをboolで返す
//
bool Collision::checkHit( const LVector3 alphaPos, const LRect* alpha, const LVector3 betaPos, const LRect* beta )
{
	LRect L = *alpha;
	LRect R = *beta;

	L.x      += static_cast< int >( alphaPos.x );
	L.y      += static_cast< int >( alphaPos.y );
	L.width  += static_cast< int >( alphaPos.x );
	L.height += static_cast< int >( alphaPos.y );

	R.x      += static_cast< int >( betaPos.x );
	R.y      += static_cast< int >( betaPos.y );
	R.width  += static_cast< int >( betaPos.x );
	R.height += static_cast< int >( betaPos.y );

	// ｘが小さいほうが左
	if ( L.x > R.x )
	{
		LRect temp;

		temp = L;
		L = R;
		R = temp;		
	}

	// Lの右端がRの左端以上
	if ( L.width >= R.x )
	{
		if ( L.height >= R.y )
		{
			return true;
		}
		else if ( L.y <= R.height )
		{
			return true;
		}
	}

	return false;
}

// 解放
void Collision::Release()
{
	fclose( mReadFP );
}
// EOF