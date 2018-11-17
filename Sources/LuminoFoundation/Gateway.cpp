//=============================================================================
//�y Gateway �z
//=============================================================================

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
#if MIGRATION
#else
#include <Core/Threading/EventFlag.h>
#include <Core/Threading/Thread.h>
#include <Core/System/Manager.h>
#include <Core/Manager.h>
#endif
#include "GameSceneManager.h"
#include "Gateway.h"
#include "Accessor.h"



//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
namespace LNote
{
    static bool gInited = false;

    //---------------------------------------------------------------------
    // �� ������
	//---------------------------------------------------------------------
	int initialize()
    {
        if ( gInited ) { return -1; }

        // wchar_t �œ��{����g����悤�ɂ���
        //setlocale( LC_ALL, "" );

        // �G���[�������W���[��������
        //Base::Error::initialize();

        gInited = true;

        return 0;
    }

    //---------------------------------------------------------------------
    // ���I������
	//---------------------------------------------------------------------
	void finalize()
    {
		Engine::Terminate();
        // �I������
        //gFramework->finalize();
        //Base::Error::finalize();

        //LN_SAFE_RELEASE( gFramework );

        gInited = false;
    }
   
    //---------------------------------------------------------------------
    // ��
	//---------------------------------------------------------------------
	int run( MD_lnMain ln_main_, MD_lnConfig ln_config_ )
    {
        if ( !ln_main_ ) { return -1; }

        int r = -1;
        //LNRESULT lr;

        //// Framework �̏������f�[�^�����
        //Core::ConfigData* init_data = LN_NEW Core::ConfigData();
        //
        //// LConfig �� lnConfig ���g���ď������f�[�^�ݒ�
        //LConfig config( init_data );
        //if ( ln_config_ )
        //{
        //    ln_config_( config );
        //}

        /*
        if ( init_data->Failed )
        {
            SAFE_DELETE( init_data );
		    return -1;
        }
        */

		EngineSettings settings;
		ln_config_(&settings);

        initialize();

        // Framework ������������
        //Framework* fw = Framework::getInstance();
        //gFramework = LN_NEW Core::Manager();

		try
		{
			Engine::Initialize();
			//gFramework->initialize( *init_data );
			//LN_PCALL( lr );

			// �ݒ�͂����g��Ȃ��̂ŉ��
			//SAFE_DELETE( init_data );

			gGameSceneManager = LN_NEW Utility::GameSceneManager();
			//Utility::GameSceneManager::InitData sdata;
			////sdata.LogFile = NULL;
			//sdata.Framework = gFramework;
			gGameSceneManager->initialize(/* sdata */);

			//if ( LN_SUCCEEDED( lr ) && lr != LN_FALSE )
			{
				// Accessor ������
				Accessor::initializeLNGlobalAccessor();

				// main �Ăяo��
				r = ln_main_();

           
				// �I������
				//gFramework->finalize();
			}

			gGameSceneManager->finalize();
			LN_SAFE_RELEASE( gGameSceneManager );

			Accessor::finalizeLNGlobalAccessor();
		}
		catch (Exception& e)
		{
			printf(e.what());
			throw;
		}
        
        finalize();

        return r;
    }

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

} // namespace LNote

//=============================================================================
//								end of file
//=============================================================================