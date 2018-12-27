//=============================================================================
//【 Effect_2 】
//=============================================================================

#include "Effect_2.h"

//=============================================================================
// ■ Effect_ValfirleDead クラス
//=============================================================================

//---------------------------------------------------------------------
// ● コンストラクタ
//---------------------------------------------------------------------
Effect_ValfirleDead::Effect_ValfirleDead( const LVector3& pos_ )
{
    LTexture tex = Assets::loadTexture( "Data/Graphics/Effect/Effect_2.png" );
    for ( int i = 0; i < 4; ++i )
    {
        mLinePanels[ i ] = LBatchPanel::create( 32 + i * 12, 256, tex );
        mLinePanels[ i ]->setSourceRect( 0, 0, 128, 512 );
        mLinePanels[ i ]->setPosition( pos_ + LVector3( 0, 0, -10 ) );
        mLinePanels[ i ]->setRenderPriority( -10000 );
        mLinePanels[ i ]->setDepthTestEnabled( false );
        mLinePanels[ i ]->setDepthWriteEnabled( false );
        mLinePanels[ i ]->setOpacity( 0 );
        //mLinePanels[ i ]->SetBlendMode( LN_BLEND_SUB );
    }

	//LRefPtr<Core::Graphics::ITexture> texture2(
	//	gFramework->getGraphicsManager()->getGraphicsDevice()->createTexture( 
	//	"D:/Proj/TestMat/2206234.png" ));
	//LRefPtr<Core::Scene::Sprite3D> sprite1( LN_NEW Core::Scene::Sprite3D( gFramework->getSceneManager()->getDefaultSceneGraph() ) );
	//sprite1->initialize( texture2->getSize().x, texture2->getSize().y );
	//sprite1->setTexture( texture2 );
	//sprite1->addRef();
	////sprite1->setOpacity( 0.9);
	//sprite1->setPosition( pos_ + LVector3( 0, 0, -10 ) );
 //   sprite1->setPriority( -LN_SCENENODEPRIORITY_PROXY + 10 );
    //sprite1->setEnableDepthTest( false );
    //sprite1->setEnableDepthWrite( false );

    // これだと十字に広がる
    /*
    LNParticleCreateData data;
    data.ParticleNum = 32;
    data.VelocityRand.set   ( 150.0f, 150.0f, 0 );
    data.Size = 20;
    data.SizeRand = 15;
    data.FadeIn = 60;
    data.Life = 120;
    data.AfterImageNum = 10;
    data.CreateInterval = 10;
    data.Loop = true;

    data.SizeRandType = LN_RANDRATE_MIN;    // サイズが小さいものほど、
    data.VelRandTypeX = LN_RANDRATE_OUTER;    // 速度が大きい
    data.VelRandTypeY = LN_RANDRATE_OUTER;
    */

#if MIGRATION
#else
	const float VEL_SCALE = 0.05f;
	const float VEL_SCALE2 = 0.0001f;

    LNParticleCreateData data;
	data.TimeScale = 1;
    data.ParticleNum = 128;
    data.Size = 25;
    data.SizeRand = 10;
    data.FadeIn = 60;
    data.Life = 180;
    data.AfterImageNum = 10;
	data.GenerationInterval = 5;
    data.Loop = true;

    data.Velocity.set    ( 0, 100.0f * VEL_SCALE, 0 );
    data.VelocityRand.set( 0, 50.0f * VEL_SCALE, 0 );
    data.Axis.set    ( 0, 0, 1 );
    data.AngleRand = LMath::PI * 2;

    data.SizeRandType = Core::Math::ExRandRateType_Min;    // サイズが小さいものほど、
    data.VelRandTypeY = Core::Math::ExRandRateType_Max;    // 速度が大きい


    mParticle = LParticle::create( LTexture::create( "Data/Graphics/Effect/Particle_1.png" ), data );
    mParticle.setPosition( pos_ );
    mParticle.setPriority( LN_SCENENODEPRIORITY_PROXY + 1 );
    mParticle.setEnableDepthTest( false );
    mParticle.setEnableDepthWrite( false );
    mParticle.setBlendMode( LN_BLEND_SUB );


    /*
    LNParticleCreateData data2;
    data2.ParticleNum = 16;
    data2.Size = 10;
    data2.SizeRand = 8;
    data2.FadeIn = 1;
    data2.FadeOut = 20;
    data2.Life = 40;
    data2.AfterImageNum = 16;
    data2.CreateInterval = 0;
    data2.Loop = false;
    data2.Velocity.set( 0, 220, 0 );
    data2.VelocityRand.set( 0, 100, 0 );
    //data2.Accel.set( 0, -3000, 0 );
    data2.Axis.set    ( 0, 0, 1 );
    data2.AngleRand = LMath::PI * 2;
    */
    LNParticleCreateData data2;
	data2.TimeScale = 1;
    data2.ParticleNum = 64;
    data2.Size = 40;
    data2.SizeRand = 20;
    data2.FadeIn = 1;
    data2.FadeOut = 10;
    data2.Life = 80;
    //data2.AfterImageNum = 16;
	data2.GenerationInterval = 0;
    data2.Loop = false;
    data2.Velocity.set( 0, 500.0 / 60, 0);//600.0 * VEL_SCALE2, 0 );
    data2.VelocityRand.set( 0, 100.0 / 60, 0 );
    data2.Accel.set( 0, -13.5 / 60, 0 );
    data2.Axis.set    ( 0, 0, 1 );
    data2.AngleRand = LMath::PI * 2;


    mFirstParticle = LParticle::create( LTexture::create( "Data/Graphics/Effect/Particle_1.png" ), data2 );
    mFirstParticle.setPosition( pos_ );
    mFirstParticle.setPriority( LN_SCENENODEPRIORITY_PROXY + 1 );
    mFirstParticle.setEnableDepthTest( false );
    mFirstParticle.setEnableDepthWrite( false );
    mFirstParticle.setBlendMode( LN_BLEND_SUB );
#endif


    mFrameCount = 0;

    //LLayer::getBGLayer().setTone( LTone( 1, 1, 1 ), 5.0f );
}

//---------------------------------------------------------------------
// ● デストラクタ
//---------------------------------------------------------------------
Effect_ValfirleDead::~Effect_ValfirleDead()
{
}

//---------------------------------------------------------------------
// ● フレーム更新 (false を返すと解放する)
//---------------------------------------------------------------------
bool Effect_ValfirleDead::update()
{
    float op = ( 0.008f * mFrameCount < 1.0f ) ? 0.008f * mFrameCount : 1.0f;
	
    mLinePanels[ 0 ]->setScale( 0.01 * mFrameCount + 1.0f,  0.01 * mFrameCount + 1.0f, 1 );
    mLinePanels[ 0 ]->setEulerAngles( 0, 0, -0.002f * mFrameCount );
    mLinePanels[ 0 ]->setOpacity( op );

    mLinePanels[ 1 ]->setScale( 0.01 * mFrameCount + 0.5f,  0.01 * mFrameCount + 2.0f, 1 );
    mLinePanels[ 1 ]->setEulerAngles( 0, 0, 0.001f * mFrameCount + 1.0f );
    mLinePanels[ 1 ]->setOpacity( op );

    mLinePanels[ 2 ]->setScale( 0.01 * mFrameCount + 0.25f, 0.01 * mFrameCount + 0.8f, 1 );
    mLinePanels[ 2 ]->setEulerAngles( 0, 0, -0.001f * mFrameCount + 2.5f );
    mLinePanels[ 2 ]->setOpacity( op );

    mLinePanels[ 3 ]->setScale( 0.01 * mFrameCount + 0.10f, 0.01 * mFrameCount + 1.5f, 1 );
    mLinePanels[ 3 ]->setEulerAngles( 0, 0, 0.005f * mFrameCount + 3.0f );
    mLinePanels[ 3 ]->setOpacity( op );
	
    ++mFrameCount;

	//mLinePanels[ 0 ].getScale().dump();
	//mLinePanels[ 0 ].getAngle().dump();
	//_p(mLinePanels[ 0 ].getOpacity());
    if ( mFrameCount == 300 )
    {
        //LLayer::getBGLayer().setTone( LTone( 0, 0, 0 ), 0 );
        return false;
    }
    return true;
}




//=============================================================================
//								end of file
//=============================================================================
