//=============================================================================
//【 CharacterScriptInterface 】
//=============================================================================

#include "GameObjectManager.h"
#include "Weapon.h"
#include "CharacterScriptInterface.h"
#include "./../Effect/Effect_1.h"
#include "./../Game/GameManager.h"
#include "Weapon.h"
#include "Player.h"
#include "Grenade.h"
#include "Bullet.h"
#include "Valfirle.h"
#include "MidBoss1.h"
#include "ValfirleToken.h"
//=============================================================================
// ■ CharacterScriptInterface クラス
//=============================================================================

//---------------------------------------------------------------------
// ● インスタンスの取得
//---------------------------------------------------------------------
CharacterScriptInterface* CharacterScriptInterface::getInstance()
{
    static CharacterScriptInterface inst;
    return &inst;
}

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
CharacterScriptInterface::CharacterScriptInterface()
{
    for ( int i = 0; i < WEAPON_MAX_NUM; ++i )
    {
        mLuaStates[ i ] = NULL;

        if ( CharaResourceNames[ i ].Script )
        {
        
            lua_State* l = luaL_newstate();
            luaopen_base( l );
            luaL_openlibs( l );
            if ( luaL_dofile( l, CharaResourceNames[ i ].Script ) )
            {
                assert( 0, "スクリプトのエラー:\n\n%s", lua_tostring( l, lua_gettop( l ) ) );
            }

            // グローバル変数 (定数) の登録

            // キャラクターの状態
	        lua_pushnumber( l, CHARASTATE_WAIT );   // 値
	        lua_setglobal( l, "CHARASTATE_WAIT" );  // 変数名
            lua_pushnumber( l, CHARASTATE_RUN );
	        lua_setglobal( l, "CHARASTATE_RUN" );
            lua_pushnumber( l, CHARASTATE_JUMP );
	        lua_setglobal( l, "CHARASTATE_JUMP" );
            lua_pushnumber( l, CHARASTATE_SQUAT );
	        lua_setglobal( l, "CHARASTATE_SQUAT" );
            lua_pushnumber( l, CHARASTATE_STUN );
	        lua_setglobal( l, "CHARASTATE_STUN" );
            lua_pushnumber( l, CHARASTATE_BLOW );
	        lua_setglobal( l, "CHARASTATE_BLOW" );
            lua_pushnumber( l, CHARASTATE_SQUAT );
	        lua_setglobal( l, "CHARASTATE_SQUAT" );
            lua_pushnumber( l, CHARASTATE_GUARD );
	        lua_setglobal( l, "CHARASTATE_GUARD" );
            lua_pushnumber( l, CHARASTATE_SQUAT );
	        lua_setglobal( l, "CHARASTATE_SQUAT" );
            lua_pushnumber( l, CHARASTATE_SQGUARD );
	        lua_setglobal( l, "CHARASTATE_SQGUARD" );
            lua_pushnumber( l, CHARASTATE_LADDER_WAIT );
	        lua_setglobal( l, "CHARASTATE_LADDER_WAIT" );
            lua_pushnumber( l, CHARASTATE_LADDER_UP );
	        lua_setglobal( l, "CHARASTATE_LADDER_UP" );
            lua_pushnumber( l, CHARASTATE_LADDER_DOWN );
	        lua_setglobal( l, "CHARASTATE_LADDER_DOWN" );
            lua_pushnumber( l, CHARASTATE_ITENGET );
	        lua_setglobal( l, "CHARASTATE_ITENGET" );
            lua_pushnumber( l, CHARASTATE_DEAD );
	        lua_setglobal( l, "CHARASTATE_DEAD" );
            lua_pushnumber( l, CHARASTATE_ATTACK_1 );
	        lua_setglobal( l, "CHARASTATE_ATTACK_1" );
            lua_pushnumber( l, CHARASTATE_ATTACK_2 );
	        lua_setglobal( l, "CHARASTATE_ATTACK_2" );
            lua_pushnumber( l, CHARASTATE_ATTACK_3 );
	        lua_setglobal( l, "CHARASTATE_ATTACK_3" );
            lua_pushnumber( l, CHARASTATE_ATTACK_SQUAT_ATTACK );
	        lua_setglobal( l, "CHARASTATE_ATTACK_SQUAT_ATTACK" );
            lua_pushnumber( l, CHARASTATE_ATTACK_JUMP_ATTACK );
	        lua_setglobal( l, "CHARASTATE_ATTACK_JUMP_ATTACK" );
            lua_pushnumber( l, CHARASTATE_ATTACK_ANTIAIR_ATTACK );
	        lua_setglobal( l, "CHARASTATE_ATTACK_ANTIAIR_ATTACK" );
            lua_pushnumber( l, CHARASTATE_ATTACK_DUSH_ATTACK );
	        lua_setglobal( l, "CHARASTATE_ATTACK_DUSH_ATTACK" );

            // 攻撃対象グループ
            lua_pushnumber( l, ATKGROUP_PLAYER );
	        lua_setglobal( l, "ATKGROUP_PLAYER" );
            lua_pushnumber( l, ATKGROUP_ENEMY );
	        lua_setglobal( l, "ATKGROUP_ENEMY" );
            lua_pushnumber( l, ATKGROUP_ALL );
	        lua_setglobal( l, "ATKGROUP_ALL" );

        // 関数の登録
        lua_register( l, "getCharaAttackedGroup",   getCharaAttackedGroup );
		lua_register( l, "getCharaPosition",        getCharaPosition );
        lua_register( l, "setCharaState",           setCharaState );
        lua_register( l, "setFrameCount",           setFrameCount );
        lua_register( l, "setPuttern",              setPuttern );
        lua_register( l, "judgeAttackCollision",    judgeAttackCollision );
        lua_register( l, "attackEffect",            attackEffect );
        lua_register( l, "disposeObject",           disposeObject );
		lua_register( l, "AttackLock",				AttackLock );
		lua_register( l, "AttackUnLock",			AttackUnLock );
		lua_register( l, "getOnGround",             getOnGround );
		lua_register( l, "PlaySE",			        PlaySE );
		lua_register( l, "CreateEffect",		    CreateEffect );
		lua_register( l, "PlaySE",			PlaySE );
		lua_register( l, "CreateEffect",			CreateEffect );
		lua_register( l, "setVelocity",				setVelocity );
		lua_register( l, "CheckWeaponBreak",		CheckWeaponBreak );
		lua_register( l, "setBreakWeapon",			setBreakWeapon );
		lua_register( l, "getBreakWeapon",			getBreakWeapon );
		lua_register( l, "setDirection",			setDirection );
		lua_register( l, "setPosition",			    setPosition );
		lua_register( l, "GrenadeGenerate",			GrenadeGenerate );
		lua_register( l, "BulletGenerate",			BulletGenerate );
		lua_register( l, "setInvincibleFrame",     setInvincibleFrame);
		lua_register( l, "getLife",                getLife);
		lua_register( l, "getMaxLife",     getMaxLife);
		lua_register( l,"setLife",            setLife);
		lua_register( l, "setAccel",               setAccel);
		lua_register( l, "getDirection",           getDirection);
		lua_register( l, "getRank",               getRank);
		lua_register( l, "getPlayerPos",               getPlayerPos);
		lua_register( l, "Rand",               Rand);
		lua_register(l,"getPhase", getPhase);
		lua_register(l,"getNum", getNum);
		lua_register(l,"setNum", setNum);
		lua_register(l ,"SummonEnemy",SummonEnemy);
		lua_register(l ,"Division",Division);
		lua_register(l ,"SetOpacity",SetOpacity);
		lua_register(l ,"SetDestructfrag",SetDestructfrag);
		lua_register(l ,"GetDestructfrag",GetDestructfrag);
		lua_register(l ,"ThunderGenerate",ThunderGenerate);
		lua_register(l ,"SummonSoul",SummonSoul);
            mLuaStates[ i ]  = l;
        }
    }
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
CharacterScriptInterface::~CharacterScriptInterface()
{
    for ( int i = 0; i < WEAPON_MAX_NUM; ++i )
    {
        if ( mLuaStates[ i ] )
        {
            lua_close( mLuaStates[ i ] );
            mLuaStates[ i ] = NULL;
        }
    }
}


//---------------------------------------------------------------------
// ● アニメーションのフレーム更新
//---------------------------------------------------------------------
void CharacterScriptInterface::update( Character* character_ )
{
    int weapon = character_->getWeaponData().WeaponType;

    // スタックに Lua ファイル内の "update" 関数を積む
    lua_getglobal( mLuaStates[ weapon ], "update" );

    // キャラクターのポインタがひとつめの引数
    lua_pushlightuserdata( mLuaStates[ weapon ], character_ );

    // 状態がふたつめの引数
    lua_pushnumber( mLuaStates[ weapon ], character_->getCharaState() );

    // フレームカウントがみっつめの引数
    lua_pushnumber( mLuaStates[ weapon ], character_->getFrameCount() );

    // 積んだデータを使って、引数3個、戻り値0個で関数を呼び出す
    lua_pcall( mLuaStates[ weapon ], 3, 0, NULL );
}



//---------------------------------------------------------------------
// ● キャラクターの属する攻撃グループの取得
//---------------------------------------------------------------------
int CharacterScriptInterface::getCharaAttackedGroup( lua_State *l_ )
{
    Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

    lua_pop( l_, lua_gettop( l_ ) );

    lua_pushnumber( l_, character->getAttackedGroup() );

    // 戻り値の数は 1
    return 1;
}

//---------------------------------------------------------------------
// ● キャラクターの属する攻撃グループの取得
//---------------------------------------------------------------------
int CharacterScriptInterface::getCharaPosition( lua_State *l_ )
{
    Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

    lua_pop( l_, lua_gettop( l_ ) );

	lua_pushnumber( l_, character->getPosition().x );
	lua_pushnumber( l_, character->getPosition().y );

    // 戻り値の数は 1
    return 2;
}

//---------------------------------------------------------------------
// ● キャラクターの状態を設定する
//---------------------------------------------------------------------
int CharacterScriptInterface::setCharaState( lua_State *l_ )
{
    Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
    character->setCharaState( static_cast< CharaState >( static_cast< int >( lua_tonumber( l_, 2 ) ) ) );

    // スタック削除
    lua_pop( l_, lua_gettop( l_ ) );

    // 戻り値の数は 0
    return 0;
}

//---------------------------------------------------------------------
// ● フレーム数を設定する
//---------------------------------------------------------------------
int CharacterScriptInterface::setFrameCount( lua_State *l_ )
{
    Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
    character->setFrameCount( static_cast< int >( lua_tonumber( l_, 2 ) ) );

    // スタック削除
    lua_pop( l_, lua_gettop( l_ ) );

    // 戻り値の数は 0
    return 0;
}

//---------------------------------------------------------------------
// ● キャラクターのアニメパターンを設定する
//---------------------------------------------------------------------
int CharacterScriptInterface::setPuttern( lua_State *l_ )
{
    Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

    character->setAnimePuttern( static_cast< int >( lua_tonumber( l_, 2 ) ) );


    // スタック削除
    lua_pop( l_, lua_gettop( l_ ) );

    // 戻り値の数は 0
    return 0;
}

//---------------------------------------------------------------------
// ● 攻撃の当たり判定を行う
//---------------------------------------------------------------------
int CharacterScriptInterface::judgeAttackCollision( lua_State *l_ )
{
    // 引数取得
    Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
    u32 target_group = static_cast< int >( lua_tonumber( l_, 2 ) );
    lua_pop( l_, lua_gettop( l_ ) );

    // 攻撃用の判定矩形があるか確認
    const LRect* rc = character->getAttackBoundingRect();
    if ( rc )
    {
        // 当たり判定実行
        HitObjectList* obj_list = GameObjectManager::getInstance()->judgeCollitionToAttackedObject( *rc, target_group );
        if ( obj_list->size() > 0 )
        {
            // 当たったオブジェクトのハンドルを lua のテーブルに格納していく
            lua_newtable( l_ );
            int idx = 1;
            HitObjectList::iterator itr = obj_list->begin();
            HitObjectList::iterator end = obj_list->end();
            for ( ; itr != end; ++itr )
            {
                lua_pushnumber( l_, idx );
                lua_pushlightuserdata( l_, (*itr) );
                lua_settable( l_, -3 );
                ++idx;
            }
            return 1;
        }
    }
    return 0;
}

//---------------------------------------------------------------------
// ● 攻撃効果の適用 (対象を攻撃する)
//---------------------------------------------------------------------
int CharacterScriptInterface::attackEffect( lua_State *l_ )
{
    Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
    AttackedObject* obj = static_cast< AttackedObject* >( lua_touserdata( l_, 2 ) );

    obj->attackEffect(
        character, 
        static_cast< int >( lua_tonumber( l_, 3 ) ),
        static_cast< u32 >( lua_tonumber( l_, 4 ) ),
        static_cast< u32 >( lua_tonumber( l_, 5 ) ),
        LVector3( static_cast< float >( lua_tonumber( l_, 6 ) ), static_cast< float >( lua_tonumber( l_, 7 ) ), 0 ),
        static_cast< float >( lua_tonumber( l_, 8 ) ) );

    lua_pop( l_, lua_gettop( l_ ) );

    return 0;
}

//---------------------------------------------------------------------
// ● キャラクターを削除する
//---------------------------------------------------------------------
int CharacterScriptInterface::disposeObject( lua_State *l_ )
{
    Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
    character->setExit( true );

    lua_pop( l_, lua_gettop( l_ ) );
    return 0;
}

//
// Character::AttackLock
// 攻撃時の行動制限
//
// @param[in] p1 : キャラクターのポインタ
//
// 呼ぶとロックがかかります。
// 攻撃モーションをジャンプなどでキャンセルさせないため
//
int CharacterScriptInterface::AttackLock( lua_State *l_ )
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
	character->AttackLock();

	lua_pop( l_, lua_gettop( l_ ) );
	return 0;
}

//
// Character::AttackUnLock
// 攻撃時の行動制限解除
//
// @param[in] p1 : キャラクターのポインタ
//
// 呼ぶとロックがはずれます。
// 攻撃モーション終了時には必ず呼んでください
//
int CharacterScriptInterface::AttackUnLock( lua_State *l_ )
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
	character->AttackUnLock();

	lua_pop( l_, lua_gettop( l_ ) );
	return 0;
	if(GameManager::getInstance()->getPlayer()->getWeaponData().UseCount==0)
	{
		WeaponData temp;
		temp.WeaponType=WEAPON_NON;
		temp.UseCount=-1;
		GameManager::getInstance()->getPlayer()->changeWeapon(temp);
		return 1;
	}
	else
	{
		lua_pop( l_, lua_gettop( l_ ) );
		return 0;
	}



}
//
// CharacterScriptInterface::getOnGround
//
// @param[in] p1 : キャラクタのポインタ
//
// 現在地上にいるかどうかを返す
// 1        = 地上
// それ以外 = 空中
//
int CharacterScriptInterface::getOnGround( lua_State *l_ )
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
	bool ground = character->getOnGround();

	int result = 0;

	if ( ground ) result = 1;

	lua_pop( l_, lua_gettop( l_ ) );
	return result;
}

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
int CharacterScriptInterface::setVelocity( lua_State *l_ )
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

	LVector3 vec_;

	vec_.x = static_cast< float >( lua_tonumber( l_, 2) );
	vec_.y = static_cast< float >( lua_tonumber( l_, 3) );
	vec_.z = 0.0f;

	if ( character->getDirection() != 1 )
	{
		vec_.x *= -1;
	}

	character->setVelocity( vec_ );

	lua_pop( l_, lua_gettop( l_ ) );
	return 0;
}

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
int CharacterScriptInterface::CheckWeaponBreak( lua_State *l_ )
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
	int result = 0;

	// プレイヤーのみ
	if ( character->getObjType() == OBJ_CHARACTER )
	{
		int damage = lua_tonumber( l_,2 );

		if( 0 < GameManager::getInstance()->getPlayer()->getWeaponData().UseCount )
		{
			GameManager::getInstance()->getPlayer()->setWeponUseCount(GameManager::getInstance()->getPlayer()->getWeaponData().UseCount - damage );
		}
		
		if( GameManager::getInstance()->getPlayer()->getWeaponData().UseCount <= 0 )
		{
			//スコア加算
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(300*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*(GameManager::getInstance()->getRank()+1)));          
 
			GameManager::getInstance()->getPlayer()->setWeponUseCount( 0 );
			result = 1;
		}
	}

	lua_pop( l_, lua_gettop( l_ ) );
	return result;
}

//
// CharacterScriptInterface::setBreakWeapon
//
// @param[in] p1 : キャラクタのポインタ
// @param[in] p2 : 武器が破損したかどうか
//
// 攻撃時に呼んでください。
// 武器が破損していればtrueを指定してください。
//
int CharacterScriptInterface::setBreakWeapon( lua_State *l_ )
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
	//character->setBreakWeapon( lua_tonumber( l_, 2 ) );

	lua_pop( l_, lua_gettop( l_ ) );
	return 0;
}

//
// CharacterScriptInterface::getBreakWeapon
//
// @param[in] p1 : キャラクタのポインタ
//
// 攻撃時、武器が破損しているか確認する
// 素手は呼ばないよーに！
//
int CharacterScriptInterface::getBreakWeapon( lua_State *l_ )
{
	int result = 0;

	if( GameManager::getInstance()->getPlayer()->getWeaponData().UseCount <= 0 )
	{
		Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

        // ↓Character::UpdateSelf に移動

		//character->setBreakWeapon( false );

        /*
		WeaponData temp;
		temp.WeaponType=WEAPON_NON;
		temp.UseCount=-1;
		GameManager::getInstance()->getPlayer()->changeWeapon(temp);
        */

        // 追加
        character->setBreakWeapon( true );

		result = 1;

		lua_pop( l_, lua_gettop( l_ ) );
	}

	//lua_pop( l_, lua_gettop( l_ ) );
	return result;
}

int CharacterScriptInterface::PlaySE( lua_State *l_ )
{
	std::string temp=lua_tostring(l_,1);
	int a = lua_tonumber(l_, 2);
	int b = lua_tonumber(l_, 3);


	lua_pop( l_, lua_gettop( l_ ) );

    GameAudio::playSE(temp.c_str(),0.01f * a, 0.01f * b);

	return 0;
}

int CharacterScriptInterface::CreateEffect( lua_State *l_ )
{
	int nEffectNo = lua_tonumber(l_,1);
	int x = lua_tonumber(l_, 2);
	int y = lua_tonumber(l_, 3);

	LVector3 v;
	v.x = x;
	v.y = y;
	v.z = 0.f;

	switch(nEffectNo)
	{
	case 0:
		NEW Effect_Test_1(v);

		//NEW Effect_Thunder(v);
		break;

	case 1:
		NEW Effect_Explosion(v);
		break;

	case 2:
		NEW Effect_Test_2(v);
		break;
	case 3:
		NEW Effect_Explosion2(v);
		break;
	case 4: 
		NEW Effect_Test_3(v);
		break;
	case 5:
		NEW Effect_Thunder(v);
	default:
		break;

	}

	return 0;
}
int CharacterScriptInterface::setDirection( lua_State *l_)
{
		Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
		int dir = lua_tonumber(l_, 2);
		if(dir==1)
			character->setDirection(CHARADIR_RIGHT);
		else
			character->setDirection(CHARADIR_LEFT);
		return 0;
}
int CharacterScriptInterface::setPosition( lua_State *l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
	LVector3 v;
	v.x=lua_tonumber(l_, 2);
	v.y=lua_tonumber(l_, 3);
	v.z=lua_tonumber(l_, 4);
	
	character->setPosition(v);

	return 0;
}
//グレネード生成
int CharacterScriptInterface::GrenadeGenerate( lua_State * l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

	//printf("aaaa\n");
	float spx = lua_tonumber(l_, 2);
	float spy = lua_tonumber(l_, 3);

	float svx= lua_tonumber(l_, 4);
	float svy= lua_tonumber(l_, 5);
	float fs = lua_tonumber(l_, 6);

	int da = lua_tonumber(l_, 7);
	u32 ra = lua_tonumber(l_, 8);
	u32 cr = lua_tonumber(l_, 9);
	float bvx = lua_tonumber(l_, 10);
	float bvy = lua_tonumber(l_, 11);
 	u32 sf = lua_tonumber(l_, 12);
	int rbx = lua_tonumber(l_, 13);
	int rby = lua_tonumber(l_, 14);
	u32 rs = lua_tonumber(l_, 15);


	Grenade *gre;
	gre = new Grenade();
	gre->Initialize();
	gre->setGeneObjType(character->getObjType());

	gre->setPosition(LVector3(spx,spy,0));
	gre->setVelocity(LVector3(svx,svy,0));
	gre->setFallSpeed(fs);
	gre->setDirection(character->getDirection());
	gre->setAttackParam(da,ra,cr,LVector3(bvx,bvy,0),sf);
	gre->setRandBrow(rbx,rby);
	gre->setRandStun(rs);

	return 0;
}
//弾生成
int CharacterScriptInterface::BulletGenerate( lua_State * l_)
{
	//printf("aaaa\n");
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );


	float spx = lua_tonumber(l_, 2);
	float spy = lua_tonumber(l_, 3);

	float svx= lua_tonumber(l_, 4);
	float svy= lua_tonumber(l_, 5);

	int da = lua_tonumber(l_, 6);
	u32 ra = lua_tonumber(l_, 7);
	u32 cr = lua_tonumber(l_, 8);

	float bvx = lua_tonumber(l_, 9);
	float bvy = lua_tonumber(l_, 10);
 	u32 sf = lua_tonumber(l_, 11);
 	u32 lf = lua_tonumber(l_, 12);
	int vol = lua_tonumber(l_, 13);

	Bullet *bul;
	bul = new Bullet();
	bul->Initialize();
	bul->setGeneObjType(character->getObjType());
	bul->setPosition(LVector3(spx,spy,0));
	bul->setVelocity(LVector3(svx,svy,0));
	bul->setDirection(character->getDirection());
	bul->setAttackParam(da,ra,cr,LVector3(bvx,bvy,0),sf);
	bul->setLifeFrame(lf);
	bul->setSeVol(vol);

	return 0;
}
int CharacterScriptInterface::setInvincibleFrame( lua_State *l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

	u32 InvincibleFrame  = lua_tonumber(l_, 2);

	character->setInvincibleFrame(InvincibleFrame);

	return 0;
}
int CharacterScriptInterface::setAccel(lua_State *l_)
{
		Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

	float x= lua_tonumber(l_,2);
	float y= lua_tonumber(l_, 3);

	character->setAccel(LVector3(x,y,0));

	return 0;
}
int CharacterScriptInterface::getLife(lua_State *l_)
{
		Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

		lua_pushnumber( l_, character->getLife() );

		return 1;
}
int CharacterScriptInterface::setLife(lua_State *l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

	int temp= lua_tonumber(l_,2);

	character->setLife(temp);

	return 0;
}
int CharacterScriptInterface::getDirection(lua_State *l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

	lua_pushnumber( l_, character->getDirection() );

	return 1;
}

int CharacterScriptInterface::getMaxLife(lua_State *l_)
{
		Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

		lua_pushnumber(l_,character->getMaxLife());
		return 1;
}
int CharacterScriptInterface::getRank(lua_State *l_)
{
   lua_pop( l_, lua_gettop( l_ ) );
   //printf("%d\n",GameManager::getInstance()->getInstance()->getRank());
	lua_pushnumber( l_, 	GameManager::getInstance()->getInstance()->getRank() );

	return 1;
}
int CharacterScriptInterface::getPlayerPos(lua_State *l_)
{
   lua_pop( l_, lua_gettop( l_ ) );

	lua_pushnumber( l_, GameManager::getInstance()->getPlayer()->getPosition().x );
	lua_pushnumber( l_, GameManager::getInstance()->getPlayer()->getPosition().y );

	return 2;
}
int CharacterScriptInterface::Rand(lua_State *l_)
{
	int a = rand();
	lua_pushnumber( l_, a);
	return 1;
}
int CharacterScriptInterface:: getPhase(lua_State *l_)
{
		Valfirle* character = static_cast< Valfirle* >( lua_touserdata( l_, 1 ) );	

		lua_pushnumber( l_,character->getPhase());
	return 1;
		
}
int CharacterScriptInterface:: getNum(lua_State *l_)
{
		Valfirle* character = static_cast< Valfirle* >( lua_touserdata( l_, 1 ) );	

		lua_pushnumber( l_,character->getNum(0));
	return 1;
		
}
int CharacterScriptInterface:: setNum(lua_State *l_)
{
		Valfirle* character = static_cast< Valfirle* >( lua_touserdata( l_, 1 ) );	
		int a= lua_tonumber(l_,2);
		character->setNum(0,a);
	return 0;
		
}
int CharacterScriptInterface:: SummonEnemy(lua_State *l_)
{
	Weapon::CreateData wdata;

	wdata.Data.WeaponType  = static_cast<WeaponType>(::rand() % (WEAPON_NORMAL_MAX_NUM - 1) + 1);
	wdata.Data.UseCount   = gWeaponBaseData[wdata.Data.WeaponType].UseCount;

	LVector3 v ;
	v.set(900,1000,0);
	v.x += ::rand() % 300 - 150;
	v.y += 180;
	wdata.Position = v;
	Weapon::create( &wdata );

	Enemy* mEnemy1 = Enemy::createRandom();
	mEnemy1->setPosition(LVector3(700,1000,1));
	mEnemy1->setDefPosition(LVector3(700,1000,1));
	mEnemy1->setScore(1);
	Enemy* mEnemy = Enemy::createRandom();
	mEnemy->setPosition(LVector3(1200,1000,1));
	mEnemy->setDefPosition(LVector3(1200,1000,1));
	mEnemy->setScore(1);
	return 0;
}
int CharacterScriptInterface:: Division(lua_State * l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
	float x= lua_tonumber(l_,2);
	float y= lua_tonumber(l_, 3);

	ValfirleToken::CreateData data;
	data.Position = LVector3(x,y,1.f);
	data.WeaponLevel = 1;
	data.WeaponType = WEAPON_VALFIRLE_TOKEN;
	ValfirleToken *pBoss = ValfirleToken::create(&data);
	pBoss->setDirection(character->getDirection());
	//pBoss->setVelocity(LVector3(5,4,1.f));
	pBoss->setInvincibleFrame(50);
	pBoss->setScore(1);
	pBoss->setLife(100);
	pBoss->setDefPosition(LVector3(x,y,1.f));
	
//	printf("分裂\n");
	return 0;
}
int CharacterScriptInterface::SetOpacity(lua_State *l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );

	float temp= lua_tonumber(l_,2);

	character->setOpacity(temp);

	return 0;
}
int CharacterScriptInterface::SetDestructfrag(lua_State *l_)
{
	ValfirleToken* character = static_cast< ValfirleToken* >( lua_touserdata( l_, 1 ) );

	bool temp= lua_tonumber(l_,2);
//	printf("ふらぐがたった！\n");
//	printf("temp%d\n",temp);
	character->setDestructfrag(temp);
	return 0;
}
int CharacterScriptInterface::GetDestructfrag(lua_State *l_)
{
	ValfirleToken* character = static_cast< ValfirleToken* >( lua_touserdata( l_, 1 ) );

	bool temp= character->getDestructfrag();

//	\\printf("%d\n",temp);
	lua_pushnumber( l_, temp);
	return 1;
}
int CharacterScriptInterface::SummonSoul(lua_State *l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );
	float x= lua_tonumber(l_,2);
	float y= lua_tonumber(l_, 3);

	ValfirleToken::CreateData data;
	data.Position = LVector3(x,y,1.f);
	data.WeaponLevel = 1;
	int temp =rand()%3;
	switch(temp)
	{
	case 0:
		data.WeaponType =WEAPON_BOSS_TAEKWONDO;
		break;
	case 1:
		data.WeaponType = WEAPON_BOSS_KNIFE;
		break;
	case 2:
		data.WeaponType = WEAPON_BOSS_KATANA;
		break;
	}
	//data.WeaponType = WEAPON_VALFIRLE_TOKEN;
	ValfirleToken *pBoss = ValfirleToken::create(&data);
	pBoss->setDirection(character->getDirection());
	//pBoss->setVelocity(LVector3(5,4,1.f));
	pBoss->setInvincibleFrame(180);
	pBoss->setDefPosition(character->getPosition());
	pBoss->setScore(1);
	pBoss->setLife(1);
	pBoss->setOpacity(0.6);
	pBoss->setDefPosition(LVector3(x-80,y,1.f));

	return 0;
}
int CharacterScriptInterface::ThunderGenerate(lua_State *l_)
{
	Character* character = static_cast< Character* >( lua_touserdata( l_, 1 ) );


	float spx = lua_tonumber(l_, 2);
	float spy = lua_tonumber(l_, 3);


	int da = lua_tonumber(l_, 4);
	u32 ra = lua_tonumber(l_, 5);
	u32 cr = lua_tonumber(l_, 6);
	float bvx = lua_tonumber(l_, 7);
	float bvy = lua_tonumber(l_, 8);
 	u32 sf = lua_tonumber(l_, 9);
	int rbx = lua_tonumber(l_, 10);
	int rby = lua_tonumber(l_, 11);


	LVector3 v(spx+10,0,0);
	v.z = 0.f;
	new Effect_Thunder(v);

	LRect AttackLect;

	AttackLect.x=spx+10;
	AttackLect.y=spy;
	AttackLect.height =2000;
	AttackLect.width =40;

	//AttackLect.x=spx+10;
	//AttackLect.y=1500;
	//AttackLect.height =2000;
	//AttackLect.width =25;
	GameAudio::playSE("./Data/Sound/SE/Thunder01.wav",0.60,1.00);

	HitObjectList*  obj_list;
	if(character->getObjType() == OBJ_CHARACTER)
	{
		obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(AttackLect,OBJ_ENEMY);
	}
	else
	{
		obj_list=GameObjectManager::getInstance()->judgeCollitionToAttackedObject(AttackLect,OBJ_CHARACTER);	
	}
	if ( obj_list->size() > 0 )
	{

		HitObjectList::iterator itr = obj_list->begin();
		HitObjectList::iterator end = obj_list->end();
		for ( ; itr != end; ++itr )
		{
			if(character->getObjType() == OBJ_CHARACTER)
			{
				//なぜかプレイヤーにあたるので
			//	if((*itr)->getObjType() != OBJ_CHARACTER)
			//	{			
					(*itr)->attackEffect(character,da,ra,cr,LVector3(bvx+rand()%rbx,bvy+rand()%rby,0),sf);
;

			//	}
			}
			else
			{
				GameManager::getInstance()->getPlayer()->attackEffect((*itr),da,ra,cr,LVector3(bvx+rand()%rbx,bvy+rand()%rby,0),sf);
			}
		}
	}

	return 0;
}
//=============================================================================
//                              end of file
//=============================================================================
