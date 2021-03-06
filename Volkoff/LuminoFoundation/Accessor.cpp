//=============================================================================
//【 Accessor 】
//=============================================================================

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
#include "stdafx.h"
#include "Accessor.h"

#if MIGRATION

namespace LNote
{
	Utility::GameSceneManager*  gGameSceneManager = NULL;

	namespace Accessor
	{
		ScreenMotionBlurImageEffectPtr	BlurLayer;
		ToneImageEffectPtr				ToneLayer;

		void initializeLNGlobalAccessor()
		{
			BlurLayer = ScreenMotionBlurImageEffect::Create();
			CameraViewportLayer::GetDefault2D()->GetImageEffects()->Add(BlurLayer);

			ToneLayer = ToneImageEffect::Create();
			CameraViewportLayer::GetDefault2D()->GetImageEffects()->Add(ToneLayer);
		}

		void finalizeLNGlobalAccessor()
		{
			BlurLayer.SafeRelease();
			ToneLayer.SafeRelease();
		}
	}
}

#else
namespace LNote
{
    Core::Manager*			gFramework = NULL;
    Utility::GameSceneManager*  gGameSceneManager = NULL; 
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
namespace LNote
{
namespace Accessor
{

LFramework		Framework;
LMouse			Mouse;
LKeyboard		Keyboard;
LGameController	Input;
LGameAudio      Audio;
LGraphics       Graphics;
LCamera         Camera;
//LDebugFont      DebugFont;
//LDebugFont      ldout;

void initializeLNGlobalAccessor()
{
    // グローバル変数にちゃんとしたインスタンスを持たせていく

    Framework = LFramework::getInstance();

    LInput input = LInput::getInstance();
    if ( input != nil )
    {
        Mouse       = input.getMouse();
        Keyboard    = input.getKeyboard();
        Input       = input.getGameController( 0 );
    }

    Audio       = LGameAudio::getInstance();
    Graphics    = LGraphics::getInstance();
    Camera      = LCamera::getDefaultCamera();
    //DebugFont   = LDebugFont::getInstance();
    //ldout       = LDebugFont::getInstance();
}

void finalizeLNGlobalAccessor()
{
    Framework = LFramework();
    Mouse = LMouse();
    Keyboard = LKeyboard();
    Input = LGameController();
    Audio = LGameAudio();
    Graphics = LGraphics();
    Camera = LCamera();
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

} // namespace Accessor
} // namespace LNote
#endif

//=============================================================================
//								end of file
//=============================================================================