//=============================================================================
/*! 
    @addtogroup 
    @file       RankingManager.h
    @brief      RankingManagerクラスヘッダ
    
    ランキングサーバに接続し、スコアに関する処理を行うクラス
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/11/22
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Hi-ra Mizuno. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/11/22 Hi-ra Mizuno
      -# 作成
*/
//=============================================================================


//Include Guard
#ifndef __INCLUDE_RANKING_MANAGER_H__
#define __INCLUDE_RANKING_MANAGER_H__


/*! @par include */
#include <list>


/*! @val global */
static const char scg_szScoreServerName[] = "www.aleibar.net";
static const char scg_szNameRefPoint[] = "Name=";
static const char scg_szScoreRefPoint[] = "Score=";
static const char scg_szTimeRefPoint[] = "Time=";
static const char scg_szStageRefPoint[] = "Stage=";
static const char scg_szDateRefPoint[] = "Date=";
static const char scg_szRankRefPoint[] = "Rank=";

static const char scg_szRankingFileName[] = "ranking.dat";


/*! @par struct */
typedef struct _TAG_SCORE_DATA
{
	char szName[128];
	unsigned int unScore;
	unsigned int unTime;
	int nStage;
	char szDate[32];
	int nRank;
}ScoreData;


/*! @class RankingManager
	@brief RankingManagerクラス

	ランキングサーバに接続し、スコアに関する処理を行うクラス

*/
class RankingManager
{
public:
	/*! @par publicメンバ変数 */

private:
	/*! @par privateメンバ変数 */

public:
	/*! @par 例外処理 */


private:
	/*! @par コンストラクタ・デストラクタ */
	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::RankingManager
	
		デフォルトコンストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	RankingManager();

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::~RankingManager
	
		デストラクタ
	
		@param[in]      void
		@return         none
		@exception      none
	*/
	//---------------------------------------------------------------------------
	~RankingManager();

public:
	/*! @par publicメンバ関数 */
	//---------------------------------------------------------------------------
	/*! @brief メンバゲッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! @brief メンバセッター */
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::getInstance
	
		インスタンスを取得する
	
		@param[in]      void
		@return         RankingManager* - インスタンスポインタ
		@exception      none
	*/
	//---------------------------------------------------------------------------
	static RankingManager* getInstance() {static RankingManager CInstance; return &CInstance;};

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::Initialize
	
		初期化処理
	
		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Initialize();

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::Release
	
		終了処理
	
		@param[in]      void
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool Release();

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::GetStoryRanking
	
		ストーリーモードのランキングを取得する
	
		@param[in]      int nRankingNum_     - 取得数
		@return         std::list<ScoreData> - スコアデータリスト
		@exception      none
	*/
	//---------------------------------------------------------------------------
	std::list<ScoreData> GetStoryRanking(int nRankingNum_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::GetSurvivalRanking
	
		サバイバルモードのランキングを取得する
	
		@param[in]      int nRankingNum_     - 取得数
		@return         std::list<ScoreData> - スコアデータリスト
		@exception      none
	*/
	//---------------------------------------------------------------------------
	std::list<ScoreData> GetSurvivalRanking(int nRankingNum_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::GetLocalStoryRanking
	
		ストーリーモードのローカルランキングを取得する
	
		@param[in]      int nRankingNum_     - 取得数
		@return         std::list<ScoreData> - スコアデータリスト
		@exception      none
	*/
	//---------------------------------------------------------------------------
	std::list<ScoreData> GetLocalStoryRanking(int nRankingNum_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::PostStoryScore
	
		ストーリーモードのスコアデータを送信する
	
		@param[in]      char         *pszName_ - 名前
		@param[in]      unsigned int unScore_  - スコア
		@param[in]      int          nStage_   - ステージ数
		@param[in]      unsigned int unTime_   - クリア時間
		@param[in]      int          nRank_    - 難易度
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool PostStoryScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::PostSurvivalScore
	
		サバイバルモードのスコアデータを送信する
	
		@param[in]      char         *pszName_ - 名前
		@param[in]      unsigned int unScore_  - スコア
		@param[in]      int          nStage_   - ステージ数
		@param[in]      unsigned int unTime_   - クリア時間
		@param[in]      int          nRank_    - 難易度
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool PostSurvivalScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_);

	//---------------------------------------------------------------------------
	/*! 
		@brief RankingManager::PostLocalStoryScore
	
		ストーリーモードのスコアデータをローカルに書きこむ
	
		@param[in]      char         *pszName_ - 名前
		@param[in]      unsigned int unScore_  - スコア
		@param[in]      int          nStage_   - ステージ数
		@param[in]      unsigned int unTime_   - クリア時間
		@param[in]      int          nRank_    - 難易度
		@return         bool
		- true  成功
		- false 失敗
		@exception      none
	*/
	//---------------------------------------------------------------------------
	bool PostLocalStoryScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_);
};


bool ScoreDesc(const ScoreData &a_,const ScoreData &b_);


//End of Include Guard
#endif


//=============================================================================
//								End of File
//=============================================================================