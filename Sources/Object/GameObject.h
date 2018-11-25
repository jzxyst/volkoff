//=============================================================================
/*! 
    @addtogroup 
    @file       GameObject.h
    @brief      オブジェクトベース
    
    オブジェクトベースの定義
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/12
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/12 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_GAME_OBJECT_H__
#define __INCLUDE_GAME_OBJECT_H__


/*! @par include */
#include "./../Event/EventType.h"
#include "./GameObjectManager.h"
//
class GameObjectManager;

// [山本] enum ObjectType は GameObjectManager.h に移動しました (Include の都合で)

/// 向きを表す定数
typedef enum _ENUM_CHARACTER_DIRECTION
{
	CHARADIR_UNDEF = 0, //未定義
	CHARADIR_RIGHT,     //右
	CHARADIR_LEFT,      //左
}CharaDir;

    
static const float GRAVITY_ACCEL = 0.0512f;      ///< 重力加速度
static const float FRICTION_COEFF = 0.5;//0.112f;     ///< 摩擦係数

class GameObjectManager;


/*! @class GameObject */
class GameObject// : public EventListener
{
protected:
    u32     mHandle;        ///< GameObjectManager によって割り当てられる一意のハンドル

	//ObjectType  mObjType;       //オブジェクトタイプ
	LVector3    mPosition;      //ワールド座標
	LVector3    mDefPosition;   //初期ワールド座標
	LVector3    mScrPosition;   //スクリーン座標 (使ってない？)
	LVector3    mScale;         //拡大率
    LVector3    mAccel;		    ///< 加速度 (慣性とか重力とか)
	LVector3	mVelocity;	    ///< 速度

    CharaDir    m_eDirection;       ///< 現在のキャラクターの向き (setDirection で変更すること)

	float mAngle;          //Radian

	int         mLife;      //体力
    int         mMaxLife;   ///< 最大体力
	int         mScore;     //スコア
	

	LRect mColRect;	       // 当たり判定矩形

    bool		mOnGround;      ///< 地上にいるかどうか
    bool        mIsEntity;      ///< じぶんのホスト内で作成されたオブジェクトの場合、true (継承先オブジェクトの create() 内で設定する)

private:
    bool mExit;            //削除フラグ

public:
    

	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------
    const unsigned int getHandle() const {return mHandle;}

	//virtual const ObjectType& getObjType() const {return mObjType;}
	virtual ObjectType getObjType() const = 0;

	virtual const int getScore() const {return mScore;}

	const LVector3& getPosition() const {return mPosition;}

	const LVector3& getDefPosition() const {return mDefPosition;}

	const LVector3& getScrPosition() const {return mScrPosition;}

	const LVector3& getScale() const {return mScale;}

	const float& getAngle() const {return mAngle;}

    const CharaDir& getDirection() const {return m_eDirection;}

	const int& getLife() const {return mLife;}

    /// 最大 HP
    const int& getMaxLife() const {return mMaxLife;}     
	
	virtual const char* getName() const {return NULL;}

	const bool getExit() const {return mExit;}

    /// 死亡判定
    bool isDead() const { return mLife <= 0; }

    /// 自分のホスト内から作成したオブジェクトかを判定する
    bool isEntity() const { return mIsEntity; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      ワールド座標空間上での当たり判定矩形を返す
    //
    //  @author     細田・yama
    //  @par
    //              判定を行わない場合は NULL を返す。
    //              矩形の高さ、幅はこれまで通り。
    //              この関数はオーバーライドして実装する。
    //*/
    //---------------------------------------------------------------------
	virtual const LRect* getBoundingRect(){ return NULL; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      ローカル座標空間上での当たり判定矩形を返す
    //
    //  @author     yama
    //  @par
    //              getBoundingRect() の、現在座標を考慮しないもの
    //*/
    //---------------------------------------------------------------------
	virtual const LRect* getLocalBoundingRect(){ return NULL; }



	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------
    void setHandle(unsigned int unHandle_) {mHandle = unHandle_;}   // 普通はいじっちゃダメ

	virtual void setScore(int Score_) {mScore = Score_;}

    void setPosition(const LVector3 &pos_) {mPosition = pos_;}

	void setDefPosition(const LVector3 &pos_) {mDefPosition = pos_;}

	void setScrPosition(const LVector3 &pos_) {mScrPosition = pos_;}

	void setAccel(const     LVector3 &pos_) {mAccel = pos_;}

    ///// 速度の設定 (攻撃によるふっ飛ばし等で使う)
    void setVelocity( const LVector3& vel_ );//{ mVelocity = vel_; }

    /// キャラクターの向きを設定する (Character クラスではオーバーライドして、Panel の向きを変えてる)
    virtual void setDirection( CharaDir dir_ ) { m_eDirection = dir_; }

    /// true を渡すと、次回の update() 終了後に削除する
    virtual void setExit( bool f_ ) { mExit = f_; }

	virtual void setLife( int life_ ) { mLife = life_; }

	//---------------------------------------------------------------------------
	/*! @brief Hoge */
	//---------------------------------------------------------------------------
	GameObject();

	virtual ~GameObject();

	//virtual bool Initialize() = 0;    // 引数付きの Initialize() が作れなくなる！

	virtual int HandleEvent(u32 event_,void *args_) { return 0; }

	


    /// 長い名前書くのが面倒なのでこちらに実装
    GameObjectManager* getManager();

    //---------------------------------------------------------------------
    ///**
    //  @brief      フレーム更新
    //
    //  @author     yama
    //  @par
    //              この Update() は自由落下するオブジェクトの更新処理が
    //              書かれている。
    //              Player はちょっと複雑なのでこの関数は呼ばず、独自で
    //              定義している。
    //*/
    //---------------------------------------------------------------------
    virtual bool Update();

    //---------------------------------------------------------------------
    ///**
    //  @brief      フレーム更新 (オブジェクトに影響を与える処理)
    //
    //  @author     yama
    //  @par
    //              当たり判定やダメージを与える処理等、
    //              フレーム更新中にするべき処理のうち、
    //              「オブジェクトに影響を与える処理」をこの関数で定義する。
    //              
    //              これは、ネットワーク実装時に自分のホストで作成した
    //              オブジェクト (自身が操作するプレイヤーや、発射した弾)
    //              が行う当たり判定は自分のところで行う必要があるため、
    //              その処理を分離するために必要になる。
    //
    //              この関数は、Update() の後に、自分のホストで作成した 
    //              GameObject のみに対して、GameObjectManager から呼び出される。
    //
    //
    //              要するに…
    //
    //                  ・入力
    //                  ・アニメーション中の攻撃の当たり判定
    //
    //              等はここに書いてください。
    //*/
    //---------------------------------------------------------------------
    virtual bool UpdateSelf() { return true; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      地形との当たり判定を行う
    //
    //  @param[out] dx_  : 修正 X オフセット (呼び出し側で mPosition に加算すること)
    //  @param[out] dy_  : 修正 Y オフセット (呼び出し側で mPosition に加算すること)
    //
    //  @return     enum MapCollFlag の組み合わせ
    //
    //  @par
    //              関数が呼ばれた時点での速度によって移動したあとの
    //              位置を使って判定を行う。
    //              ステージ上に落ちている武器やアイテム用に用意したもの。
    //              Character は Update() 内で独自に定義している。
    //*/
    //---------------------------------------------------------------------
    virtual u32 judgeCollisionToMap( float* dx_, float* dy_ );

 
    friend class GameObjectManager;
};

/// オブジェクトが属する攻撃判定グループ
enum AttackedGroup
{
    ATKGROUP_NONE       = 0,        ///< どこにも属さない
    ATKGROUP_PLAYER     = 0x01,     ///< プレイヤー側に属する
    ATKGROUP_ENEMY      = 0x02,     ///< 敵側に属する
    ATKGROUP_ALL        = ATKGROUP_PLAYER | ATKGROUP_ENEMY ///< 両方 (敵の攻撃でも壊れるオブジェクトとか、敵味方吹っ飛ばす地雷とか)
};

//=============================================================================
// ■ AttackedObject クラス
//-----------------------------------------------------------------------------
///**
//  @brief		攻撃をする・攻撃を受けるオブジェクトの基底      
//
//  @note
//              なんか include がゴチャゴチャになってコンパイル通らなくなってたので、
//              とりあえず通すためにこっちに移動。
//*/
//=============================================================================
class AttackedObject
    : public GameObject
    , public LNote::Core::Base::NodeList< AttackedObject >::Node
{
public:
    
    /// コンストラクタ
    AttackedObject();

    /// デストラクタ
    virtual ~AttackedObject();

public:

    //---------------------------------------------------------------------
    ///**
    //  @brief      オブジェクトが属するグループを設定する
    //
    //  @return     AttackedGroup のフラグの組み合わせ
    //*/
    //---------------------------------------------------------------------
    void setAttackedGroup( u32 flags_ ) { mAttackedGroup = flags_; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      オブジェクトが属するグループを返す
    //
    //  @return     AttackedGroup のフラグの組み合わせ
    //*/
    //---------------------------------------------------------------------
    u32 getAttackedGroup() { return mAttackedGroup; }

    //---------------------------------------------------------------------
    ///**
    //  @brief      オブジェクトの、攻撃を受けるときの当たり判定矩形を返す
    //
    //  @par
    //              オーバーライドしない場合、getBoundingRect() と同じ動作。
    //              必要な場合、この関数はオーバーライドして実装すること。
    //              NULL を返す場合、当たり判定を行わない。
    //*/
    //---------------------------------------------------------------------
    virtual const LRect* getAttackedCollisionRect() { return getBoundingRect(); }

    //---------------------------------------------------------------------
    ///**
    //  @brief      このオブジェクトに攻撃を与える
    //
    //  @param[in]  attacker_       : 攻撃側 (後で何か使うかもしれないので一応)
    //  @param[in]  damage_         : 与えるダメージ
    //  @param[in]  range_rate_     : damage_ に対するばらつきの範囲。±range_rate_％ の範囲で変化する
    //  @param[in]  critical_rate_  : クリティカル率 (0～100)
    //  @param[in]  brow_vec_       : ふっ飛ばしベクトル
    //  @param[in]  stun_frame_     : のけぞりフレーム数
    //
    //  @author     yama
    //  @note
    //              ネットワークでプレイしている場合、普通にダメージを与えると
    //              実態ではないオブジェクトに対してダメージを与えることになってしまう。
    //              そのため、この関数内では実際にダメージを与えることはせず、
    //                  ・ダメージ量
    //                  ・クリティカル有無
    //              をメッセージとしてすべてのホストに送信する。
    //
    //              (ガードブレイクの強さも必要？)
    //*/
    //---------------------------------------------------------------------
    virtual void attackEffect( GameObject* attacker_, int damage_, u32 range_rate_, u32 critical_rate_, const LVector3& brow_vec_, u32 stun_frame_ );

    /// イベント処理
    virtual int HandleEvent( u32 event_,void *args_ );

private:

    u32     mAttackedGroup;     ///< AttackedGroup の組み合わせ。通常はどれか一つ

};

//End of Include Guard
#endif



//=============================================================================
//								End of File
//=============================================================================
