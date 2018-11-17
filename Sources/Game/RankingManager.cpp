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


/*! @par include */
#include "./RankingManager.h"
#include "./../Network/NetworkHelper.h"
#include "./../Utility/File.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <time.h>


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::RankingManager
	
	デフォルトコンストラクタ
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
RankingManager::RankingManager()
{
}


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::~RankingManager
	
	デストラクタ
	
	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
RankingManager::~RankingManager()
{
	this->Release();
}


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
bool RankingManager::Initialize()
{
	this->Release();

	//SocketManager::getInstance()->Initialize();

	return true;
}


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
bool RankingManager::Release()
{
	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::GetStoryRanking
	
	ストーリーモードのランキングを取得する
	
	@param[in]      int nRankingNum_     - 取得数
	@return         std::list<ScoreData> - スコアデータリスト
	@exception      none
*/
//---------------------------------------------------------------------------
std::list<ScoreData> RankingManager::GetStoryRanking(int nRankingNum_)
{
	//初期化
	SOCKET hSock = INVALID_SOCKET;
	sockaddr_in stServerAddr;
	std::list<ScoreData> liRes;

	::memset(&stServerAddr,NULL,sizeof(stServerAddr));

	//ソケット作成
	if((hSock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
		return liRes;

	//接続先設定
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = ::htons(80);

	hostent* stHost = ::gethostbyname(scg_szScoreServerName);
	if(!stHost)
		return liRes;

	if(::memcpy_s(&stServerAddr.sin_addr,sizeof(stServerAddr.sin_addr),stHost->h_addr_list[0],stHost->h_length))
		return liRes;

	//サーバに接続
	if(!NetworkHelper::getInstance()->ConnectEx(hSock,stServerAddr,5000))
	{
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);

		return liRes;
	}

	//サーバにHTTPリクエストを送信し、ランキングを取得する
	static const char sc_szRequest[] = "GET /ota-gamepg/lastvalfirle/storyscore.php HTTP/1.1\r\nHost: www.aleibar.net\r\nConnection: close\r\n\r\n";

	if(::send(hSock,sc_szRequest,sizeof(sc_szRequest),0) < 0)
	{
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);

		return liRes;
	}

	//サーバからの応答を受信
	int nRecvSize = 0,nDone = 0,cnt = 0;
	std::vector<char> vcRecvBuffer;
	const int c_nRecvBufferSize = ETHERNET_MTU;

	do
	{
		++cnt;
		vcRecvBuffer.resize(vcRecvBuffer.size() + c_nRecvBufferSize);

		nRecvSize = ::recv(hSock,&vcRecvBuffer[nDone],vcRecvBuffer.capacity(),0);

		if(nRecvSize <= 0)
			break;

		nDone += nRecvSize;
	}while(nRecvSize >= c_nRecvBufferSize);

	//ソケットの解放
	::shutdown(hSock,SD_BOTH);
	::closesocket(hSock);
		
	//レスポンスの解析
	std::string strRes = &vcRecvBuffer[0];
	ScoreData stBuf;
	char szBuf[128];
	std::stringstream ss;
	unsigned int nIndex = 0,nEndIndex = 0,nStrDone = 0;

	::memset(&stBuf,'\0',sizeof(stBuf));
	::memset(&szBuf,'\0',sizeof(szBuf));

	for(int i = 0;i < nRankingNum_;++i)
	{
		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&stBuf,'\0',sizeof(stBuf));
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Name="を検索する
		if((nIndex = strRes.find(scg_szNameRefPoint)) == std::string::npos)
			return liRes;

		//検索された値に"Name="分を加算
		nIndex += sizeof(scg_szNameRefPoint) - 1;

		//区切りである' 'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//見つけた名前を構造体にコピー
		if(::memcpy_s(&stBuf.szName,sizeof(stBuf.szName),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Score="を検索する
		if((nIndex = strRes.find(scg_szScoreRefPoint)) == std::string::npos)
			return liRes;

		//検索された値に"Score="分を加算
		nIndex += sizeof(scg_szScoreRefPoint) - 1;

		//区切りである' 'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//見つけた名前をバッファにコピー
		if(::memcpy_s(&szBuf,sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		//文字列から数値に変換
		ss << szBuf;
		ss >> stBuf.unScore;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Time="を検索する
		if((nIndex = strRes.find(scg_szTimeRefPoint)) == std::string::npos)
			return liRes;

		//検索された値に"Time="分を加算
		nIndex += sizeof(scg_szTimeRefPoint) - 1;

		//区切りである' 'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//見つけた名前をバッファにコピー
		if(::memcpy_s(&szBuf,sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		//文字列から数値に変換
		ss << szBuf;
		ss >> stBuf.unTime;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Stage="を検索する
		if((nIndex = strRes.find(scg_szStageRefPoint)) == std::string::npos)
			return liRes;

		//検索された値に"Stage="分を加算
		nIndex += sizeof(scg_szStageRefPoint) - 1;

		//区切りである' 'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//見つけた名前をバッファにコピー
		if(::memcpy_s(&szBuf,sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		//文字列から数値に変換
		ss << szBuf;
		ss >> stBuf.nStage;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Date="を検索する
		if((nIndex = strRes.find(scg_szDateRefPoint)) == std::string::npos)
			return liRes;

		//検索された値に"Date="分を加算
		nIndex += sizeof(scg_szDateRefPoint) - 1;

		//区切りである' 'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//見つけた名前を構造体にコピー
		if(::memcpy_s(&stBuf.szDate,sizeof(stBuf.szDate),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		/*------------------------------------------------------------------------------------*/

		nIndex = 0;
		nEndIndex = 0;
		ss.clear();
		ss.str("");
		::memset(&szBuf,'\0',sizeof(szBuf));

		//"Rank="を検索する
		if((nIndex = strRes.find(scg_szRankRefPoint)) == std::string::npos)
			return liRes;

		//検索された値に"Rank="分を加算
		nIndex += sizeof(scg_szRankRefPoint) - 1;

		//区切りである' 'が見つかるまで続ける
		for(nEndIndex = nIndex;nEndIndex < strRes.length();++nEndIndex)
		{
			if(strRes[nEndIndex] == ' ')
				break;
		}

		//見つけた名前をバッファにコピー
		if(::memcpy_s(&szBuf,sizeof(szBuf),&strRes.c_str()[nIndex],nEndIndex - nIndex))
			return liRes;

		//文字列から数値に変換
		ss << szBuf;
		ss >> stBuf.nRank;

		/*-----------------------------------------------------------------*/

		//次のスコアに移る
		//"<br />"を検索する
		if((nIndex = strRes.find("<br />")) == std::string::npos)
			return liRes;

		//検索された値に"Name="分を加算
		nIndex += sizeof("<br />") - 1;
		nStrDone += nIndex;

		strRes = &vcRecvBuffer[nStrDone];

		liRes.push_back(stBuf);
	}

	return liRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::GetSurvivalRanking
	
	サバイバルモードのランキングを取得する
	
	@param[in]      int nRankingNum_     - 取得数
	@return         std::list<ScoreData> - スコアデータリスト
	@exception      none
*/
//---------------------------------------------------------------------------
std::list<ScoreData> RankingManager::GetSurvivalRanking(int nRankingNum_)
{
	std::list<ScoreData> liRes;

	return liRes;
}


//---------------------------------------------------------------------------
/*! 
	@brief RankingManager::GetLocalStoryRanking
	
	ストーリーモードのローカルランキングを取得する
	
	@param[in]      int nRankingNum_     - 取得数
	@return         std::list<ScoreData> - スコアデータリスト
	@exception      none
*/
//---------------------------------------------------------------------------
std::list<ScoreData> RankingManager::GetLocalStoryRanking(int nRankingNum_)
{
	std::list<ScoreData> liRes;

	JZX::File *pFile = new JZX::File(scg_szRankingFileName,"rb");

	if(!pFile)
	{
		SAFE_DELETE(pFile);
		return liRes;
	}

	if(pFile->getFileParam() != JZX::FILE_OPEN_SUCCEED)
	{
		SAFE_DELETE(pFile);
		return liRes;
	}

	char szBuf[256],szTemp[256];
	std::string str = szBuf;
	unsigned int unIndex = 0;
	ScoreData stData;

	::memset(szBuf,'\0',256);
	::memset(szTemp,'\0',256);

	while(::fgets(szBuf,256,pFile->getFile()))
	{
		//1行終わるまで処理する
		for(int i = 0;i < 6;++i)
		{
			std::string str = szBuf;

			if((unIndex = str.find(',')) == std::string::npos)
				break;
		
			switch(i)
			{
			case 0:
				::memcpy_s(&stData.szName[0],128,str.c_str(),unIndex);
				stData.szName[unIndex] = '\0';
				break;

			case 1:
				::memcpy_s(szTemp,256,str.c_str(),unIndex);
				stData.unScore = static_cast<unsigned int>(atoi(szTemp));
				break;

			case 2:
				::memcpy_s(szTemp,256,str.c_str(),unIndex);
				stData.nStage = atoi(szTemp);
				break;

			case 3:
				::memcpy_s(szTemp,256,str.c_str(),unIndex);
				stData.unTime = static_cast<unsigned int>(atoi(szTemp));
				break;

			case 4:
				::memcpy_s(szTemp,256,str.c_str(),unIndex);
				stData.nRank = atoi(szTemp);
				break;

			case 5:
				::memcpy_s(&stData.szDate[0],32,str.c_str(),unIndex);
				stData.szDate[unIndex] = '\0';
				break;

			default:
				break;
			}

			::memcpy_s(szBuf,256,&szBuf[unIndex + 1],256 - (unIndex + 1));
			::memset(szTemp,'\0',256);
		}

		liRes.push_back(stData);

		::memset(szBuf,'\0',256);
		::memset(szTemp,'\0',256);
		::memset(&stData,sizeof(stData),NULL);
	}

	liRes.sort(ScoreDesc);

	if(liRes.size() > nRankingNum_)
	{
		std::list<ScoreData>::iterator itr = liRes.begin();
		for(int i = 0;i < nRankingNum_;++i)
		{
			++itr;
		}

		liRes.erase(itr,liRes.end());
	}

	pFile->Close();
	SAFE_DELETE(pFile);

	return liRes;
}


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
bool RankingManager::PostStoryScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_)
{
	//初期化
	SOCKET hSock = INVALID_SOCKET;
	sockaddr_in stServerAddr;
	std::list<ScoreData> liRes;

	::memset(&stServerAddr,NULL,sizeof(stServerAddr));

	//ソケット作成
	if((hSock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
		return false;

	//接続先設定
	stServerAddr.sin_family = AF_INET;
	stServerAddr.sin_port = ::htons(80);

	hostent* stHost = ::gethostbyname(scg_szScoreServerName);
	if(!stHost)
		return false;

	if(::memcpy_s(&stServerAddr.sin_addr,sizeof(stServerAddr.sin_addr),stHost->h_addr_list[0],stHost->h_length))
		return false;

	//サーバに接続
	if(!NetworkHelper::getInstance()->ConnectEx(hSock,stServerAddr,5000))
	{
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);

		return false;
	}

	//サーバにHTTPリクエストを送信し、スコアを登録する
	std::string strBuf,strBody;
	char szBuf[256];
	::memset(&szBuf[0],'\0',sizeof(szBuf));

	strBody += "Name=";
	strBody += pszName_;
	strBody += '&';

	::sprintf_s(&szBuf[0],sizeof(szBuf),"%u",unScore_);
	strBody += "Score=";
	strBody += szBuf;
	strBody += '&';

	::sprintf_s(&szBuf[0],sizeof(szBuf),"%d",nStage_);
	strBody += "Stage=";
	strBody += szBuf;
	strBody += '&';

	::sprintf_s(&szBuf[0],sizeof(szBuf),"%u",unTime_);
	strBody += "Time=";
	strBody += szBuf;
	strBody += '&';

	::sprintf_s(&szBuf[0],sizeof(szBuf),"%d",nRank_);
	strBody += "Rank=";
	strBody += szBuf;
	strBody += "\r\n";

	::sprintf_s(&szBuf[0],sizeof(szBuf),"POST /ota-gamepg/lastvalfirle/storyscore.php HTTP/1.1\r\nHost: www.aleibar.net\r\nContent-type: application/x-www-form-urlencoded\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",strBody.length());
	strBuf = szBuf;
	strBuf += strBody;

	if(::send(hSock,strBuf.c_str(),strBuf.size(),0) < 0)
	{
		::shutdown(hSock,SD_BOTH);
		::closesocket(hSock);

		return false;
	}

	//サーバからの応答を受信
	int nRecvSize = 0,nDone = 0,cnt = 0;
	std::vector<char> vcRecvBuffer;
	const int c_nRecvBufferSize = ETHERNET_MTU;

	do
	{
		++cnt;
		vcRecvBuffer.resize(vcRecvBuffer.size() + c_nRecvBufferSize);

		nRecvSize = ::recv(hSock,&vcRecvBuffer[nDone],vcRecvBuffer.capacity(),0);

		if(nRecvSize <= 0)
			break;

		nDone += nRecvSize;
	}while(nRecvSize >= c_nRecvBufferSize);

	//ソケットの解放
	::shutdown(hSock,SD_BOTH);
	::closesocket(hSock);
		
	//レスポンスの解析
	for(int i = 0;i < nDone;++i)
	{
		std::cout << vcRecvBuffer[i];
	}

	return true;
}


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
bool RankingManager::PostSurvivalScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_)
{
	return true;
}


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
bool RankingManager::PostLocalStoryScore(char *pszName_,unsigned int unScore_,int nStage_,unsigned int unTime_,int nRank_)
{
	JZX::File *pFile = new JZX::File(scg_szRankingFileName,"ab+");

	if(!pFile)
	{
		SAFE_DELETE(pFile);
		return false;
	}

	if(pFile->getFileParam() != JZX::FILE_OPEN_SUCCEED)
	{
		SAFE_DELETE(pFile);
		return false;
	}

	//日付を取得
    time_t unTimer = 0;
    tm *stDate = NULL;
    char szBuf[256];

	::memset(szBuf,'\0',256);

    unTimer = ::time(NULL);
    stDate = ::localtime(&unTimer);
    strftime(szBuf,255,"%Y-%b-%d %I:%M:%S",stDate);

	//ファイル出力
	::fprintf_s(pFile->getFile(),"%s,%u,%d,%u,%d,%s,\r\n",pszName_,unScore_,nStage_,unTime_,nRank_,szBuf);

	pFile->Close();
	SAFE_DELETE(pFile);

	return true;
}


bool ScoreDesc(const ScoreData &a_,const ScoreData &b_)
{
	return a_.unScore > b_.unScore;
}



//=============================================================================
//								End of File
//=============================================================================