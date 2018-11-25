//=============================================================================
/*! 
    @addtogroup 
    @file       Enemy.cpp
    @brief      
    
    キャラクタークラスの実装
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/11/07
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/07 Hi-ra Mizuo
      -# 作成
*/
//=============================================================================


/*! @par include */
#include "Enemy.h"
#include "Player.h"
#include "./Item/Cure_S.h"
#include "./Item/Cure_M.h"
#include "./Item/Cure_L.h"
#include "./../Game/GameManager.h"

static const char* gEnemyRandomNames[] =
{
    "K.Yamamoto",
    "S.Mizuno",
    "T.Matsui",
    "K.Hosoda",

    "Kouhei",
    "Takuya",
    "Hiroki",
    "Satoru",
	////////
	"vellfire",
	"Valfarle",
	"Velfirle",
	"VilFarle",
	"Valfire",
	"Varforle",
	"Walfirle",
	"Volfire",
    "WARST",
    "unsigned",
	"Tolman",
	"Oppenheimer",
	"Abdul",
	"Corleone",
	"Al Pacino",
	"James",
	"Robin",
	"Bond",
	"Regan",
	"Damien",
	"Vincent",
	"Joe",
	"Frank",
	"Albert",
	"Thomas",
	"Paul",
	"Marcello",
	"Carlos",
	"Silvio",
	"Roberto",
	"Jimmy",
	"Edison",
	"C6H2CH3(NO2)3",
	"H2SO4",
	"VEGA",
	"KCN",
	"Lucky Luciano",
	"Salvatore",
	"Giovanni",
	"Bernardo",
	"Vito",
	"Al Capone"
	"Terminator",
	"Mad Max",
	"HUMAN GAS",
	"gyro",
	"Sentinel",
	"Rotterdam",
	"Tom",
	"Frederico",
	"Jason",
	"Freddy",
	"Predator",
	"SpiderMa",
	"Hannibal",
	"Jack",
	"Claude",
	"Debussy",
	"Nordstrom",
	"Lee",
	"Andre",
	"Great Andre",
	"Reissner",
	"Kami - Kaze",
	"Geisya",
	"Ninja",
	"Harakiri",
	"Little Boy",
	"Invincible",
	"Fat Man",
	"Badguy",
    "歩兵",
    "ペカン",
    "けしごむ",
	"xxx",
    "WARST",
	"smith",
	"ken",
	"kumi",
	"emiya",
	"人間",
	"VTEC",
	"Lethal Weapon",//ギリギリ
	"TAKAHASHI",
	"New Yorker",
	"Human Rocket",
	"グンマー県民",
	"最強の尖兵",
	"又次郎",
	"磯吉",
	"春吉",
	"章六",
	"藤堂",
	"ひよりん",
	"ぽんこつ",
	"とんこつ",
	"なんこつ",
	"みやびちゃん",
	"ああああ",
	"無名",
	"モブ男",
	"モブ郎",
	"モブ美",
	"モブ子",
	"匿名希望",
	" ]-[!35_#! ",
	"K99999",
	"k,",
	"うどん",
	"ラーメン",
	"宣伝部長",
	"広報担当",
	"諜報部員",
	"倉庫番",
	"侵略者",
	"太田太郎",
	"伊勢崎だろう",
	"黄金のカカト",
	"吹き荒ぶ風",
	"荒れ狂う稲光",
	"乾いた大地",
	"炎のさだめ",
	"魅力的な昆布",
	"戦う市長",
	"月光菩薩",
	"虚栄心",
	"卑弥呼",
	"暗黒舞踏",
	"謹賀新年",
	"戦闘潮流",
	"最終防衛線",
	"最強伝説",
	"残虐超人",
	"無敵超人",
	"悪行超人",
	"守護神",
	"絶滅危惧種",
	"町内大会３位",
	"全国模試１位",
	"9代目毒味役",
	"未来世紀",
	"雑音",
	"アル中",
	"ヤク中",
	"人間凶器",
	"全身筋肉",
	"懐刀",
	"テロリスト",
	"刺客",
	"三下",
	"下っ端",
	"チンピラ",
	"鉄砲玉",
	"不良",
	"ザコキャラ",
	"万年補欠",
	"FBI",
	"UMA",
	"KGB",
	"CIA",
	"LV 5",
	"LV 100",
	"戦闘力５",
	"戦闘力1200",
	"戦闘力4000",
	"戦闘力53万",
	"IQ 106 4馬力",
	"IQ 80",
	"IQ 200",
	"IQ 13億",
	"IQ 1万3千",
	"2012年",
	"007",
	"????",
	"正体不明",
	"Algernon",
	"ash",
	"Fender",
	"Strat",
	"Swinger",
	"Telecaster",
	"Speed Freak",
	"刹那",
	"Magneto",
	"Klaus",
	"Kinkel",
	"DENON",
	"flanger",
	"Wesson",
	"Henrietta",
	"Marian",
	"日光菩薩",
	"Charles",
	"世紀末覇者",
	"199X年",
	"一郎",
	"二郎",
	"三郎",
	"四朗",
	"五郎",
	"六郎",
	"七郎",
	"八郎",
	"九郎",
	"十郎",
	"十一郎",
	"Howard",
	"Cessna",
	"Megadeth",
	"Anthrax",
	"Leazas",
	"Calvin",
	"Klein",
	"Habmann",
	"CATOREX",
	"Kesselring"
	"Svend",
	"Andersen",
	"Philippe",
	"Graham",
	"edmundo",
	"涅槃寂静",
	"不可説不可説",
	"藤四郎",
	"国光",
	"正宗",
	"AKG",
	".exe",
	".rar",
	".zip",
	".lzh",
	".png",
	".jpg",
	".wav",
	".frac",
	".tak",
	".dat",
	"Michelangelo",
	"地獄の門番",
	"19990707",
	"Kaspersky",
	"Norton",
	"Angolmois",
	"Samoen",
	"Butcher",
	"Blackwell",
	"Gibson",
	"Rickenbacker",
	"Pfeifer",
	"Zeliska",
	"Pylon",
	"Gates",
	"Jobs",
	"netero",
	"Hartmann",
	"Alfred",
	"Giaccho",
	"Abbacchio",
	"徒歩二分",
	"Fatalpulse",
	"極彩色",
	"Black Ace",
	"Magento",
	"Reno",
	"ide",
	"curse",
	"Stroheim",
	"Emmerich",
	"無冠の帝王",
	"Noah",
	"Brocken",
	"Magento",
	"Ferdinand",
	"Hans",
	"Friedrich",
	"Ernst",
	"Richthofen",
	"Gotthard",
	"ムエタイの帝王",
	"未来からの刺客",
	"Heinrich",
	"Marseille",
	"羽藤",
	"Edvard",
	"Walter",
	"Barbarossa",
	"新人の尾崎",
	"神人の尾崎",
	"真神の尾崎",
	"ヒィッツ",
	"衝撃の",
	"無敗神話",
	"†漆黒の堕天使†",
	"天上天下",
	"悪鬼羅刹",
	"末期少女病",
	"OI・OIO",
	"ジャックハンマー",
	"烈",
	"海王",
	"鎬",
	"挑発伝説",
	"塩漬け",
	"徒手空拳",
	"糖尿病",
	"低血糖",
	"第二の主役",
	"達人王",
	"隻眼の復讐鬼",
	"獣医越前",
	"傭兵越前",
	"暗黒街の支配者",
	"ダニー",
	"グレッグ",
	"メラニート",
	"暴走石黒",
	"妄想石黒",
	"拳を極めしもの",
	"SGスミニー",
	"隼のYES",
	"イクシオン",
	"AX-2",
	"両腕カンフー",
	"空飛ぶギロチン",
	"讃美歌13番",
	"李",
	"五爪竜",
	"妄人",
	"超級風水師",
	"維多利亜",
	"お好み焼き",
	"Hello world",
	"蜃気楼",
	"TAO",
	"しんのゆうしゃ",
	"死亡通知",
	"死亡遊戯",
	"ダミーだこりゃ",
	"忍びよる影",
	"迫りくる恐怖",
	"這い寄るモノ",
    /*
    ーーーーーーーー ←全角8文字
    眠りを売る山本
    */

    "合縁奇縁",  // 人と人とは、互いに気心が合う合わないことがあるが、それは不思議な縁によるものだということ。
    "愛別離苦",  // 親子・兄弟・夫婦が生別・死別する、その苦しみや悲しみ。
    "曖昧模糊",  // 実態がはっきりせず、よく分からないさま。
    "青色吐息",  // 困難や心配事でがっかりして苦しそうに吐くため息。
    "青息吐息",
    "悪衣悪食",  // 粗末な衣服と粗末な食べ物。衣食の貧しさなど、外面的なものに心を奪われてはならない。
    "悪因悪果",  // 悪い行いや原因には、かならず悪い報いや結果がある。
    "悪逆無道",  // 人道や道理に外れた、ひどい悪事を行うこと。
    "悪事千里",  // 悪いことは千里の彼方にまで知れ渡ってしまうこと。
    "悪戦苦闘",  // 困難に直面しながら、死に物狂いの苦しい努力をしたり、戦ったりすること。
    "阿鼻叫喚",  // 多くの人が、悲惨な状況の下で、苦しんだり泣き叫んだりして救いを求めるさま。
    "蛙鳴蝉噪",  // 役に立たぬ議論や、内容のない文章のたとえ。
    "阿諛追従",  // 相手に気に入られようとして、おべっかを言ってへつらうこと。
    "暗雲低迷",  // 今にも危険や破局が起こりそうな不安なさま。
    "安閑恬静",  // 何事もなく安らかで、静かなこと。無欲で落ち着いている悟りの境地。
    "安居楽業",  // 世の中が平和で、人々の生活が安定し、楽しく仕事に励んでいる状態。
    "暗中模索",  // 手がかりのない物事を、いろいろと考えて、探ってやってみること。
    "安寧秩序",  // 世の中が穏やかに治まり、安全と秩序がきちんと保たれていること。

    "ニャン外務大臣",  // タイの外務大臣
    "バカ議員",         // バカ・ディエス議員。ボリビアの上院議員
    "ヒッキー大佐",   // ジェイムズ・ヒッキー大佐。アメリカ第４歩兵師団・第１旅団司令官。
    "ストロー外相",   // ジャック・ストロー。イギリスの外相
    "サル首相",         // セネガルの首相
    "ｽﾀｯﾌﾙﾋﾞｰﾑ",        // 米軍統合参謀本部作戦副部長
    "ベロ司教",         // カルロス・フィリペ・シメネス・ベロ。東ティモールの司教
    "ﾏﾘﾝﾁｪｯｸ科技相",       // スロベニア共和国の科技相
    "クーちゃん大統領",     // スロベニア共和国の大統領
    "ドラゴニャ経済相",     // スロベニア共和国の経済相
    "シャベタ外務次官",     // ボスニア・ヘルツェゴビナの外務次官
    "カルビー外相",       // イエメンの外相
    "ﾏｯｷｰ国家経済相",  // オマーン国の国家経済相
    "アホカス大使",       // ヴィルヨ・アホカス。フィンランドの大使。
    "チョン・シネ",       // 韓国統計庁の社会統計局長
    "アダム・ニート",      // イギリスのアーティスト
    "ぽっぽ首相",      // 
    "コッコ宰相",      // 

    "重箱の隅",
    "毘沙門",
    "年配者",
    "爪楊枝",
    "精肉メン",
    "合成樹脂",
    "高精度椎茸製造機",
    "黒い学生",
    "新入り",
    "高精度新入り",
    "舞台装置",
    "爪切り後継者",
    "置物の管理者",

    "必死だよ！",
    "つよいよ！",
    "すごいよ！",
    "補食します",
    "寝ちゃうー",
    "帰りたい…",

    "ならやん",
    "ふみやん",

    "アナナス",
    "アマゾンゆり",
    "アロエ",
    "ブドウ球菌",
    "藻類",
    "菌類",

    "消えぬ灯",
    "壊れない友情",
    "正義が勝つ",
    "あの日の記憶",
    "眠れない夜",
    "置いてきた財布",
    "偉大なる俺",


    /*
    ーーーーーーーー ←全角8文字
    三角木馬の石黒
    */
    

    "-拳の方程式-",
    "-無音の円環-",
    "-現世の枷-",
    "-終焉の桜-",

	"グロ少尉",
	"グロ中尉",
	"グロ大尉",
	"エーカゲン２世",
	"クソスレータ",
	"ロリモスキー",
	"御前賀 夕菜",
	"伊路目 郁内",
	"モーネル秋田",

	"脊撃肘",
	"通天砲",
	"龍珠連砲",
	"蛇出洞",
	"蛇形穿拳",
	"燕子妙水",
	"大龍形",
	"牙掃腿",
	"円青龍",
	"鷂子入林",
	"単把",
	"岱手",
	"蛇撥草",
	"背剄",
	"秘宗歩",
	"穿拳",
	"大纏崩捶",
	"鷂子鑽天",
	"鷹雙展翅",
	"崩拳",
	"馬形短炮",
	"馬形推斬",
	"打突連拳",
	"打突凶把",
	"天扇脚",
	"刮地風",
	"跌釵井鴦脚",
	"低身後掃腿",
	"槃手脚",
	"迅脚前掃扇腿",
	"脚歩双把",
	"脚歩双把震",
	"難陀穿拳",
	"虎蹲山",
	"挑領",
	"避身衝腿",
	"猿手脚",
	"烏牛擺頭",
	"双把",
	"野馬奔槽",
	"綵鶏腿",
	"虎撲把",
	"鷂子功掌燈",
	"青嵐拳",
	"撃胆肘",
	"烈震脚",
	"烈震踏",
	"絶招通天砲",
	"絶招鷹捉把",
	"後掃落襲脚",
	"無影拳",
	"迎門四把撞",
	"右掌底打",
	"舞身撲面掌",
	"蒼空砲",
	"獅子水月把",
	"衝陽腿",
	"掃腿",
	"野馬闖槽",



    
};

// gEnemyRandomNames の数
static const int ENEMY_RAND_NAME_MAX = sizeof( gEnemyRandomNames ) / sizeof( gEnemyRandomNames[ 0 ] );


//---------------------------------------------------------------------------
// ● オブジェクトを作成する
//---------------------------------------------------------------------------
Enemy* Enemy::create( void* args_, bool is_entity_ )
{
    Enemy* o = NEW Enemy();
    o->Initialize( *static_cast< CreateData* >( args_ ) );
    o->mIsEntity = is_entity_;

    // 自分がこのホストで作成されたものであれば、自分以外のホストに生成したことを送信する
    if ( is_entity_ )
    {
        GameManager::getInstance()->getGameSession()->sendCreatedObjectEvent( OBJ_ENEMY, args_, sizeof( CreateData ) );
    }

    return o;
}


//---------------------------------------------------------------------------
// ● オブジェクトをランダムで作成する
//---------------------------------------------------------------------------
Enemy* Enemy::createRandom()
{
    Enemy::CreateData data;
    data.Position = LVector3(0,0,0);
    data.WeaponLevel = 1;
    data.WeaponType  = Weapon::getRandWeaponID();
    /*
	data.WeaponType = WEAPON_NON;
	for(int i = 0;i < WEAPON_MAX_NUM;++i)
	{
		if(!(::rand() % gWeaponBaseData[i].Rate))
		{
			data.WeaponType = static_cast<WeaponType>(i);
			break;
		}
	}

	data.WeaponType = static_cast<WeaponType>(::rand() % WEAPON_NORMAL_MAX_NUM);
	//data.WeaponType = WEAPON_KATANA;
    */

	Enemy* pEnemy = Enemy::create( &data );

    return pEnemy;
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::Enemy

	デフォルトコンストラクタ

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Enemy::Enemy()
    : mWeaponLevel  ( 1 )
{
	
	this->m_eCharaState = CHARASTATE_WAIT;

	this->m_AnimePuttern = 0;

	this->m_eAction = ENEMY_ACT_WAIT;

	this->m_bCreateWeapon = false;

	this->m_nAttackDelay = 0;
	this->m_nWalkIntvCnt = 0;
	this->m_nWalkRangeCnt = 0;
	this->m_bWalkDir = false;
	this->m_nEscapeRangeCnt = 0;
	this->m_nStandbyCnt = 0;
	this->m_nGuardCnt = 0;
	this->m_nSquatCnt = 0;
	this->mStandOnObject = false;

    // 攻撃対象グループは敵側
    setAttackedGroup( ATKGROUP_ENEMY );
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::~Enemy

	デストラクタ

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
Enemy::~Enemy()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::Initialize

	初期化処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::Initialize( const CreateData& data_ )
{
    this->m_pszName = gEnemyRandomNames[ rand() % ENEMY_RAND_NAME_MAX ]; // ランダム名
	this->mScore = 100;
	this->mExp = 10;
    this->mPosition = data_.Position;
    this->mVelocity = data_.Velocity;
    mWeaponLevel    = data_.WeaponLevel;
    
	bool r = Character::Initialize();
	this->mCharaPanel->setColorScale(0.5f,0.5f,0.5f);

    
	this->mLife = this->mMaxLife = scg_nLife[GameManager::getInstance()->getRank()];

	this->m_nRandAttackRange = ::rand() % 40 - 20;
	this->m_nRandAttackDelay = ::rand() % 40 - 10;
	this->m_nRandSearchRange = this->scm_nSearchX;
	this->m_nAttackRangeRand = ::rand() % this->scm_nAttackRangeRand;

	WeaponData data;
	data.UseCount = -1;
	data.WeaponType =  static_cast<WeaponType>(data_.WeaponType);
	this->changeWeapon(data);

	this->mStandOnObject = false;


	return r;
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::Release

	終了処理

	@param[in]      void
	@return         bool
	- true  成功
	- false 失敗
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::Release()
{
	//SAFE_DELETE(this->m_pCWeapon); //deleteはManagerに任せる

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::Update

	フレーム更新処理

	@param[in]      void
	@return         bool
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::Update()
{
	//_p(mOnGround);
	//_p(mClimbLadder);
	//_p(this->mStandOnObject);

    return Character::Update();
}

//---------------------------------------------------------------------------
// ● フレーム更新処理 (オブジェクトに影響を与える処理)
//---------------------------------------------------------------------------
bool Enemy::UpdateSelf()
{
	//死んだ際に持っている武器を落とす
	if(this->mLife <= 0 && !this->m_bCreateWeapon)
	{
		if(this->mWeaponData.WeaponType)
		{
			Weapon::CreateData wdata;

			wdata.Data.WeaponType  = this->mWeaponData.WeaponType;
			wdata.Data.UseCount    = gWeaponBaseData[this->mWeaponData.WeaponType].UseCount;

			LVector3 v = this->mPosition;
			v.x -= 25;
			v.y += 80;
			wdata.Position = v;
			Weapon::create( &wdata );

			this->m_bCreateWeapon = true;
		}
		else
		{
			//素手の場合、低確率で回復アイテムを落とす
			if(!(::rand() % 10))
			{
				Cure_S *pCure = new Cure_S();
				pCure->Initialize();

				LVector3 v = this->mPosition;
				v.x -= 30;
				v.y += 100;

				pCure->setPosition(v);
			}
			this->m_bCreateWeapon = true;
		}
	}

	bool right = false;
	bool left  = false;
	bool button_A  = false;
	bool button_B  = false;
	bool Up = false;
	bool UpTrigger = false;
	bool Down = false;
	bool DownTrigger = false;
	bool Guard = false;
	bool GuardTrigger = false;

	Player *pPlayer = GameManager::getInstance()->getPlayer();

	//AI
	switch(this->m_eAction)
	{
	//未定義
	case ENEMY_ACT_UNDEF:
		this->m_eAction = ENEMY_ACT_WAIT;
		break;

	//待機
	case ENEMY_ACT_WAIT:
		//範囲内探索を行う
		if(this->SearchPlayer())
		{
			//範囲内であれば追跡を開始する
			this->m_eAction = ENEMY_ACT_CHASE;
			break;
		}

		//散歩を開始する
		if(this->m_nWalkIntvCnt > this->scm_nWalkIntv)
		{
			this->m_nWalkRangeCnt = ::rand() % this->scm_nWalkRange; //散歩距離の設定
			this->m_nWalkIntvCnt = 0;
			this->m_bWalkDir = static_cast<bool>(::rand() % 2);
			this->m_eAction = ENEMY_ACT_WALK;
		}
		else
		{
			++this->m_nWalkIntvCnt;
		}
		break;

	//散歩
	case ENEMY_ACT_WALK:
		//散歩を行っている
		if(this->m_nWalkRangeCnt)
		{
			if(this->m_bWalkDir)
				right = true;
			else
				left = true;

			--this->m_nWalkRangeCnt;
		}
		//散歩終わり
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//追跡
	case ENEMY_ACT_CHASE:
		//プレイヤーが探索範囲内である
		if(this->SearchPlayer())
		{
			//Playerは右にいる
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				right = true;
			}
			//Playerは左にいる
			else
			{
				left = true;
			}

			//まれにジャンプする
			if(!(::rand() % scg_nJumpRatio[GameManager::getInstance()->getRank()]))
			{
				button_B = true;
			}

			//プレイヤーが観察範囲内である
			if(::abs(this->mPosition.x + ::rand() % this->scm_nSearchRand - pPlayer->getPosition().x) <= this->scm_nStandbyRange)
			{
				//ランダムで観察を開始する
				if(!(::rand() % scg_nStandbyRatio[GameManager::getInstance()->getRank()]))
				{
					this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
					this->m_eAction = ENEMY_ACT_STANDBY;
					break;
				}
			}

			//プレイヤーが攻撃範囲内である
			if(this->SearchAttack1Range())
			{
				this->m_eAction = ENEMY_ACT_ATTACK_RANGE;
				break;
			}
		}
		else
		{
			//探索範囲外であれば待機に戻す
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//観察
	case ENEMY_ACT_STANDBY:
		//プレイヤーがジャンプした瞬間対空攻撃を行う
		if(pPlayer->getCharaState() == CHARASTATE_JUMP)
		{
			//this->m_nStandbyCnt = 0;
			break;
		}

		//観察を行う
		if(this->m_nStandbyCnt)
		{
			--this->m_nStandbyCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//逃走
	case ENEMY_ACT_ESCAPE:
		if(this->m_nEscapeRangeCnt)
		{
			//Playerは右にいる
			if(this->mPosition.x - pPlayer->getPosition().x < 0)
			{
				left = true;
			}
			//Playerは左にいる
			else
			{
				right = true;
			}

			--this->m_nEscapeRangeCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//攻撃範囲内
	case ENEMY_ACT_ATTACK_RANGE:
		if(this->SearchAttack1Range())
		{
			//ランダムで攻撃を開始する
			if(!(::rand() % scg_nAttackRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_eAction = ENEMY_ACT_ATTACK;
				break;
			}
			//ランダムで防御を開始する
			if(!(::rand() % scg_nGuardRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_GUARD;
				break;
			}
			//ランダムで観察を開始する
			if(!(::rand() % scg_nStandbyRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nStandbyCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_STANDBY;
				break;
			}
			//ランダムでしゃがみガードを開始する
			if(!(::rand() % scg_nSquatGuardRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nGuardCnt = ::rand() % this->scm_nGuardIntv;
				this->m_eAction = ENEMY_ACT_SQUAT_GUARD;
				break;
			}
			//ランダムでしゃがみを開始する
			if(!(::rand() % scg_nSquatRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nSquatCnt = ::rand() % this->scm_nStandbyIntv;
				this->m_eAction = ENEMY_ACT_SQUAT;
				break;
			}
			//ランダムで逃走を開始する
			if(!(::rand() % scg_nEscapeRatio[GameManager::getInstance()->getRank()]))
			{
				this->m_nEscapeRangeCnt = ::rand() % this->scm_nEscapeRange;
				this->m_eAction = ENEMY_ACT_ESCAPE;
				break;
			}
		}
		//攻撃範囲外
		else
		{
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//攻撃中
	case ENEMY_ACT_ATTACK:
		if(this->SearchAttack1Range())
		{
			switch(this->m_eCharaState)
			{
			case CHARASTATE_ATTACK_SQUAT_ATTACK:
			case CHARASTATE_ATTACK_JUMP_ATTACK:
			case CHARASTATE_ATTACK_ANTIAIR_ATTACK:
			case CHARASTATE_ATTACK_DUSH_ATTACK:
				//特殊攻撃後は待機に戻す
				this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_1:
				//通常攻撃2段目
				if(scg_bAttack2Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nAttack2Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			case CHARASTATE_ATTACK_2:
				//通常攻撃3段目
				if(scg_bAttack3Permission[GameManager::getInstance()->getRank()] && (::rand() % scg_nAttack3Ratio[GameManager::getInstance()->getRank()]))
					button_A = true;
				else
					this->m_eAction = ENEMY_ACT_WAIT;
				break;

			default:
				//ジャンプ攻撃は事前にジャンプする
				if(!(::rand() % scg_nJumpAttackRatio[GameManager::getInstance()->getRank()]))
				{
					button_B = true;
					break;
				}
				//しゃがみ攻撃
				if(!(::rand() % scg_nSquatAttackRatio[GameManager::getInstance()->getRank()]))
				{
					Down = true;
				}

				//通常攻撃1段目
				button_A = true;

				break;
			}

			//Player座標が上であれば、対空攻撃をする
			if(this->mPosition.y < pPlayer->getPosition().y)
			{
				Up = true;
			}
		}
		else
		{
			this->m_eAction = ENEMY_ACT_CHASE;
		}
		break;

	//防御
	case ENEMY_ACT_GUARD:
		if(this->m_nGuardCnt)
		{
			Guard = true;
			--this->m_nGuardCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//しゃがみガード
	case ENEMY_ACT_SQUAT_GUARD:
		if(this->m_nGuardCnt)
		{
			GuardTrigger = true;
			Guard = true;
			Down = true;
			--this->m_nGuardCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	//しゃがみ
	case ENEMY_ACT_SQUAT:
		if(this->m_nSquatCnt)
		{
			Down = true;
			--this->m_nSquatCnt;
		}
		else
		{
			this->m_eAction = ENEMY_ACT_WAIT;
		}
		break;

	default:
		this->m_eAction = ENEMY_ACT_WAIT;
		break;
	}
	//AI end

    // 死亡 (死亡モーション中) は入力を受け付けない
    if ( isDead() )
    {
        return true;
    }

    // 移動できる場合 (のけぞり中等ではない)
    if ( mStunFrame == 0 )
    {
        //------------------------------------------------------
        // 攻撃動作中の場合
        if ( isAttacking() )
        {
			// 行動制限解除（=出し終わり）してないと操作不可
			if ( !mAttackLocked )
			{
				// 連続攻撃
				if ( button_A )
				{
					// 行動制限
					this->AttackLock();

					switch( m_eCharaState )
					{
					case CHARASTATE_ATTACK_1:
						if(scg_bAttack2Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_2, NULL, 0 );
						break;

					case CHARASTATE_ATTACK_2:
						if(scg_bAttack3Permission[GameManager::getInstance()->getRank()])
							getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_3, NULL, 0 );
						break;

					default:
						// 万が一おかしい値になったらロック解除
						this->AttackUnLock();
						break;
					}
				}
			}
        }
        //------------------------------------------------------
        // 攻撃動作中ではない場合
        else
        {
			
			// 攻撃開始
            if ( button_A && m_eCharaState != EV_ACTION_ATTACK_1 )  // 後ろのは仮
            {
                // ジャンプ中の場合
                if ( mJump )
                {
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_JUMP_ATTACK, NULL, 0 );
                }
                // しゃがみ中の場合
                else if ( Down )
                {
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_SQUAT_ATTACK, NULL, 0 );
                }
				// 上を押しながらの場合
				else if ( !mTouchLadder && Up )
				{
					this->AttackLock();
					getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_ANTIAIR_ATTACK, NULL, 0 );
					this->m_nAttackDelay = 0;
				}
                // 以上以外は通常攻撃
                else
                {
					// 攻撃のため行動制限
					if(scg_bAttack1Permission[GameManager::getInstance()->getRank()])
					{
						this->AttackLock();
						getManager()->postEvent( getHandle(), EV_ACTION_ATTACK_1, NULL, 0 );
					}
                }

                return true;
            }

			// ガード
			if ( !Down && Guard && mOnGround && !mClimbLadder && m_eCharaState != CHARASTATE_GUARD )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_GUARD, NULL, 0 );
				return true;
			}

			// 向きを変えるための処理
			if ( right )
			{
				setDirection( CHARADIR_RIGHT );
			}
			else if ( left )
			{
				setDirection( CHARADIR_LEFT );
			}

			// 右移動
			//if ( !mClimbLadder && right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
			//{
			//	// 方向をつけて EV_ACTION_RUN イベントを送る。
			//	// このあと、HandleEvent() で実際に移動を開始する。
			//	// このイベントはキューイングせず、即座に HandleEvent() に送られる。
			//	//u32 dir = CHARADIR_RIGHT;

			//	if ( !Down )
			//		getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			//		// getManager()->postEvent( getHandle(), EV_ACTION_RUN, &dir, sizeof( u32 ) );
			//}
			//// 左移動
			//else if( !mClimbLadder && left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) )
			//{
			//	//u32 dir = CHARADIR_LEFT;

			// 移動
			if ( ( !Guard && !this->mClimbLadder && right && !left && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_RIGHT ) )
				|| ( !Guard && !this->mClimbLadder && left && !right && ( m_eCharaState != CHARASTATE_RUN || m_eDirection != CHARADIR_LEFT ) ) )
			{
				if ( !Down )
					getManager()->postEvent( getHandle(), EV_ACTION_RUN, NULL, 0 );
			}
			// 左右のいずれも押されていない場合は待機にする
			// 梯子離したときも待機で。
			// (後ろの mState != CHARASTATE_WAIT は、待機中に連続でイベントが送られないようにするために必要)
			else if ( ( !Guard && this->mOnGround && ( ( !right && !left ) || ( right && left ) ) && !Down && !this->mClimbLadder && m_eCharaState != CHARASTATE_WAIT )
				|| this->mNewTouchObj != OBJ_LADDER && this->mOldTouchObj == OBJ_LADDER && m_eCharaState != CHARASTATE_WAIT && m_eCharaState != CHARASTATE_JUMP && m_eCharaState != CHARASTATE_RUN )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_WAIT, NULL, 0 );
			}

			// ジャンプ開始
			if ( button_B && m_eCharaState != CHARASTATE_JUMP && ( this->mOnGround || this->mClimbLadder ) )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_JUMP, NULL, 0 );
				return true;
			}

			// しゃがみ開始
			if ( Down && this->mOnGround && !this->mTouchLadder )
			{
				// しゃがみながらガードした場合
				// ガードしながらしゃがんだ場合
				if ( ( ( GuardTrigger ) || ( DownTrigger && Guard ) ) && m_eCharaState != CHARASTATE_SQGUARD )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT_GUARD, NULL, 0 );
				}
				else if ( !Guard && m_eCharaState != CHARASTATE_SQUAT )
				{
					getManager()->postEvent( getHandle(), EV_ACTION_SQUAT, NULL, 0 );
				}
			}

			// はしごつかみ
			if ( mTouchLadder
				&& m_eCharaState != CHARASTATE_LADDER_UP
				&& m_eCharaState != CHARASTATE_LADDER_DOWN
				&& m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				bool Catch = false;

				if ( UpTrigger && mDistance.y > 0 )
					Catch = true;

				if ( DownTrigger && mDistance.y < 0 )
					Catch = true;

				if ( Catch )
				{
					this->mPosition.set(
						mPosition.x + mDistance.x,
						mPosition.y,
						mPosition.z
						);
					mClimbLadder = true;
				}
			}

			// はしご上昇
			if ( Up && m_eCharaState != CHARASTATE_LADDER_UP && mClimbLadder )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_UP, NULL, 0 );

				return true;
			}
			// はしご下降
			else if ( Down && m_eCharaState != CHARASTATE_LADDER_DOWN && mClimbLadder )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_DOWN, NULL, 0 );

				return true;
			}
			// はしご待機
			else if ( !Up && !Down && mClimbLadder && m_eCharaState != CHARASTATE_LADDER_WAIT )
			{
				getManager()->postEvent( getHandle(), EV_ACTION_LADDER_WAIT, NULL, 0 );

				return true;
			}
        }
    }

    return true;
}




//---------------------------------------------------------------------------
/*! 
	@brief Enemy::HandleEvent

	イベント処理

	@param[in]      EventType event_ イベントタイプ
	@param[in]      void      *args_ データ(適当にキャストする)
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
int Enemy::HandleEvent(u32 event_,void *args_)
{

	switch ( event_ )
	{
	///////////////////////////////////////// 戦闘不能開始
        case EV_ACTION_START_DEAD:
			//経験値の処理
			GameManager::getInstance()->getPlayer()->setExp(GameManager::getInstance()->getPlayer()->getExp()+this->mExp);
			//printf("exp%d\n",GameManager::getInstance()->getPlayer()->getExp());
			//スコアの処理
			GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(this->getScore()*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*((GameManager::getInstance()->getRank()+1)*2)));          
            break;
	}

	return Character::HandleEvent( event_, args_ );

}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::SearchPlayer

	プレイヤーの探索を行う

	@return         bool
	- true  範囲内
	- false 範囲外
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::SearchPlayer()
{
	bool bRes = false;
	Player *pPlayer = GameManager::getInstance()->getPlayer();

	if(::abs(this->mPosition.y - pPlayer->getPosition().y) < this->scm_nSearchY)
	{
		//探索範囲内である
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) < this->m_nRandSearchRange)
		{
			bRes = true;
		}
	}

	return bRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief Enemy::SearchAttack1Range

	攻撃範囲探索を行う

	@return         bool
	- true  範囲内
	- false 範囲外
	@exception      none
*/
//---------------------------------------------------------------------------
bool Enemy::SearchAttack1Range()
{
	bool bRes = false;
	LRect *r = NULL;
	Player *pPlayer = GameManager::getInstance()->getPlayer();

	switch(this->mWeaponData.WeaponType)
	{
	case WEAPON_NON:
	case WEAPON_STICK:
	case WEAPON_KATANA:
	case WEAPON_UMBRELLA:
	case WEAPON_TAEKWONDO:
	case WEAPON_KNIFE:
	case WEAPON_GRENADE:
	case WEAPON_HAMMER:
	case WEAPON_BOSS_KATANA:
	case WEAPON_BOSS_TAEKWONDO:
	case WEAPON_BOSS_KNIFE:
		for(int i = 6;i < 23;++i)
		{
			r = this->mCollision->getAtkCollisionByIndex(i);

			if(r)
			{
				break;
			}
		}
		break;

	case WEAPON_SHOTGUN:
	{
		LRect rect = LRect(0,0,210,60);
		r = &rect;
		break;
	}

	default:
		for(int i = 6;i < 23;++i)
		{
			r = this->mCollision->getAtkCollisionByIndex(i);

			if(r)
			{
				break;
			}
		}
		break;
	}

	if(r)
	{
		//攻撃範囲内
		if(::abs(this->mPosition.x - pPlayer->getPosition().x) <= r->x + r->width - 40 + this->m_nAttackRangeRand) //40は一時的
		{
			bRes = true;
		}
	}

	return bRes;
}


/*

    ◆ エネミーAI

        ・索敵状態

            その辺をうろうろしている初期状態。
            以下の条件で攻撃状態になる。

                ・プレイヤーキャラクターが索敵範囲内に入る (視界内とかなら結構いい感じだけど、とりあえずは円で)
                ・プレイヤーキャラクターからの攻撃を受ける
                ・警報装置からの警告 (メッセージで受け取る)

            攻撃状態になるとき (m_eCharaState に値を入れるとき) に、
            ターゲットとなるプレイヤーのハンドルを保持しておく


        ・攻撃状態

            自分の持っている武器の有効範囲内にターゲットがいない場合、
            経路探索とかそんな感じのモノを使ってターゲットに近づいていく。

            ターゲットが有効範囲内にいる場合は取れる行動を選択して攻撃を行う。


            


*/


//=============================================================================
//								End of File
//=============================================================================
