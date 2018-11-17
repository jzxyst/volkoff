//
// Collision.h
// Datファイルからデータを復元し、
// 当たり判定をするクラス
//

#ifndef COLLISION_H
#define COLLISION_H

#include <stdio.h>

class Collision
{
private:

	static const int SET_H_NUM = 12; // 短形を取得する範囲が水平にいくつ並ぶか
	static const int SET_V_NUM = 12; // 短形を取得する範囲が垂直にいくつ並ぶか

	struct Position
	{
		int H;
		int V;
	};

	struct Data
	{
		Position Atk_pos; // 攻撃判定
		Position Atk_size;

		Position Dmg_pos; // ダメージ判定
		Position Dmg_size;

		Position origin; // 基準点

		bool started;
	};

	FILE *mReadFP; // 読み込みファイルポインタ
	Data mLoadData[ SET_H_NUM*SET_V_NUM ];

	LRect mAtkArea; // 攻撃判定短形
	LRect mDmgArea; // 被ダメージ判定短形

public:

	// コンストラクタ
	Collision();

	// デストラクタ
	~Collision();

	// 初期化
	void Initialize();

	//
	// LoadFile
	// 引　数 const char* fileName_
	// 戻り値 void
	//
	// 引数で指定された
	// 当たり判定データの読み込み
	//
	void LoadFile( const char* fileName_ );

	//
	// getAtkCollision
	// 引　数 const unsigned int ActionIdx, const unsigned int Frames
	// 戻り値 LRect
	//
	// アクション番号とコマ番号を渡すと
	// 　その動作の攻撃の当たり判定が返る( x, y, width, height )
	//
	LRect* getAtkCollision( const unsigned int ActionIdx, const unsigned int Frames );

	//
	// getDmgCollision
	// 引　数 const unsigned int ActionIdx, const unsigned int Frames
	// 戻り値 LRect
	//
	// アクション番号とコマ番号を渡すと
	// 　その動作のダメージの当たり判定が返る( x, y, width, height )
	//
	LRect* getDmgCollision( const unsigned int ActionIdx, const unsigned int Frames );

	//
	// getOrigin
	// 引　数 const unsigned int ActionIdx, const unsigned int Frames
	// 戻り値 LVector2
	//
	// アクション番号とコマ番号を渡すと
	// 　その動作の基準点が返る( x, y )
	//
	LVector2 getOrigin( const unsigned int ActionIdx, const unsigned int Frames );


    /// [山本] 攻撃用当たり判定をコマ番号から取得する (コマ番号は左上から右にかけて +1、下に行くにつれて +12)
    LRect* getAtkCollisionByIndex( const unsigned int index_ );

    /// [山本] ダメージ用当たり判定をコマ番号から取得する
    LRect* getDmgCollisionByIndex( const unsigned int index_ );

    /// [山本] 原点をコマ番号から取得する
    LVector2 getOriginByIndex( const unsigned int index_ );

	//
	// checkHit
	// 引　数 const LVector3 alphaPos, const LRect* alpha,
	//        const LVector3 betaPos,  const LRect* beta
	// 戻り値 bool
	//
	// 当たり判定のRectを渡すと
	// 　当たっているかどうかをboolで返す
	//
	bool checkHit( const LVector3 alphaPos, const LRect* alpha, const LVector3 betaPos, const LRect* beta );

	// 解放
	void Release();
};

#endif
// EOF