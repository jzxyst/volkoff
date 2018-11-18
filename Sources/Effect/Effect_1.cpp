//=============================================================================
//【 Effect_1 】
//=============================================================================

#include "Effect_1.h"

//=============================================================================
// ■ Effect_1 クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Test_1::Effect_Test_1( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = LBatchPanel::create( 80, 80 );
    mPanel->setTexture(Assets::LoadTexture( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->setSourceRect( 0, 128, 128, 128 );
    mPanel->setEulerAngles( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Test_1::~Effect_Test_1()
{

}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Test_1::update()
{
    mPanel->setScale( mFrameCount, 0.3f, 1 );
    mPanel->SetOpacity( 1.0f - ( mFrameCount / 6.0f ) );

    ++mFrameCount;
    if ( mFrameCount > 6 )
    {
        return false;
    }
    return true;
}




//=============================================================================
// ■ Effect_2 クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Test_2::Effect_Test_2( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = LBatchPanel::create( 80, 80 );
    mPanel->setTexture(Assets::loadTexture( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->setSourceRect( 0, 128, 128, 128 );
    mPanel->setEulerAngles( 0, 0, Math::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Test_2::~Effect_Test_2()
{
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Test_2::update()
{
    mPanel->SetScale( mFrameCount / 2, 1.0f, mFrameCount / 2);
    //mPanel->SetOpacity( 1.0f - ( mFrameCount / 6.0f ) );

    ++mFrameCount;
    if ( mFrameCount > 6 )
    {
        return false;
    }
    return true;
}



//=============================================================================
// ■ Effect_Explosion クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Explosion::Effect_Explosion( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = LBatchPanel::create( 160, 160 );
    mPanel->SetTexture(Assets::loadTexture( "./Data/Graphics/Effect/Explosion01.png" ) );
    mPanel->setSourceRect( 0, 128, 128, 128 );
    mPanel->SetAngles( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );

	Vector3 scr = Vector3::TransformCoord(pos_, Accessor::Main3Camera->GetProjectionMatrix());
	Accessor::BlurLayer->SetBlurStatus(0.5, Vector2(scr.x, scr.y), 1.05, 0.6);
	//LLayer::getBGLayer()->blur(0.6, 0.5, 1.05, pos_, true );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Explosion::~Effect_Explosion()
{

}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Explosion::update()
{
    ++mFrameCount;
    if ( mFrameCount > 30 )
    {
        return false;
    }

	//アニメーション
	this->mPanel->setSourceRect(128 * (mFrameCount % 5),128 * (mFrameCount / 5),128,128);
    return true;
}

//=============================================================================
// ■ Effect_Explosion2 クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Explosion2::Effect_Explosion2( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = LBatchPanel::create( 20, 20 );
    mPanel->setTexture(Assets::loadTexture( "./Data/Graphics/Effect/Explosion01.png" ) );
    mPanel->setSourceRect( 0, 128, 128, 128 );
    mPanel->SetAngles( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );



    mFrameCount = 0;
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Explosion2::~Effect_Explosion2()
{

}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Explosion2::update()
{
    ++mFrameCount;
    if ( mFrameCount > 15 )
    {
        return false;
    }

	//アニメーション
	this->mPanel->setSourceRect(128 * (mFrameCount ),128 * (mFrameCount / 5),128,128);
    return true;
}

//=============================================================================
// ■ Effect_3 クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Test_3::Effect_Test_3( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = LBatchPanel::create( 120,130 );
    mPanel->setTexture(Assets::loadTexture( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->setSourceRect( 0, 128, 128, 128 );
  //  mPanel->SetAngle( 0, 0, LMath::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->setPosition( pos_ );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Test_3::~Effect_Test_3()
{
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Test_3::update()
{
    mPanel->SetScale( mFrameCount / 3, 1.0f, mFrameCount / 3);
    //mPanel->SetOpacity( 1.0f - ( mFrameCount / 6.0f ) );

    ++mFrameCount;
    if ( mFrameCount > 9 )
    {
        return false;
    }
    return true;
}

//=============================================================================
// ■ Effect_Thunder クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_Thunder::Effect_Thunder( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = LBatchPanel::create( 64,2000 );
    mPanel->SetTexture(Assets::LoadTexture( "Data/Graphics/Effect/Thunder_1.png" ) );
    mPanel->setSourceRect(0, 512, 64, 512 );
  //  mPanel->SetAngle( 0, 0, LMath::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );

	Vector3 scr = Vector3::TransformCoord(pos_, Accessor::Main3Camera->GetProjectionMatrix());
	Accessor::BlurLayer->SetBlurStatus(0.5, Vector2(scr.x, scr.y), 1.05, 0.6);
	//LLayer::getBGLayer()->blur(0.6, 0.5, 1.05, pos_, true );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_Thunder::~Effect_Thunder()
{
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_Thunder::update()
{
  //  mPanel->SetScale(1, 1.0f, 1);
    //mPanel->SetOpacity( 1.0f - ( mFrameCount / 6.0f ) );
    mPanel->setSourceRect(64*(mFrameCount/5), 512, 64, 512 );
    ++mFrameCount;
    if ( mFrameCount >20 )
    {
        return false;
    }
    return true;
}
//=============================================================================
//								end of file
//=============================================================================