//=============================================================================
//�y Effect_1 �z
//=============================================================================

#include "stdafx.h"
#include "Effect_1.h"

//=============================================================================
// �� Effect_1 �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
Effect_Test_1::Effect_Test_1( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = Sprite3D::Create( 80, 80 );
    mPanel->SetTexture(Assets::LoadTexture( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->SetSrcRect( 0, 128, 128, 128 );
    mPanel->SetAngles( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
Effect_Test_1::~Effect_Test_1()
{

}

//---------------------------------------------------------------------
// �� �t���[���X�V (false ��Ԃ��Ɖ������)
//---------------------------------------------------------------------
bool Effect_Test_1::update()
{
    mPanel->SetScale( mFrameCount, 0.3f, 1 );
    mPanel->SetOpacity( 1.0f - ( mFrameCount / 6.0f ) );

    ++mFrameCount;
    if ( mFrameCount > 6 )
    {
        return false;
    }
    return true;
}




//=============================================================================
// �� Effect_2 �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
Effect_Test_2::Effect_Test_2( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = Sprite3D::Create( 80, 80 );
    mPanel->SetTexture(Assets::LoadTexture( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->SetSrcRect( 0, 128, 128, 128 );
    mPanel->SetAngles( 0, 0, Math::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
Effect_Test_2::~Effect_Test_2()
{
}

//---------------------------------------------------------------------
// �� �t���[���X�V (false ��Ԃ��Ɖ������)
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
// �� Effect_Explosion �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
Effect_Explosion::Effect_Explosion( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = Sprite3D::Create( 160, 160 );
    mPanel->SetTexture(Assets::LoadTexture( "./Data/Graphics/Effect/Explosion01.png" ) );
    mPanel->SetSrcRect( 0, 128, 128, 128 );
    mPanel->SetAngles( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );

	Vector3 scr = Vector3::TransformCoord(pos_, Camera::GetMain3DCamera()->GetProjectionMatrix());
	Accessor::BlurLayer->SetBlurStatus(0.5, Vector2(scr.x, scr.y), 1.05, 0.6);
	//LLayer::getBGLayer()->blur(0.6, 0.5, 1.05, pos_, true );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
Effect_Explosion::~Effect_Explosion()
{

}

//---------------------------------------------------------------------
// �� �t���[���X�V (false ��Ԃ��Ɖ������)
//---------------------------------------------------------------------
bool Effect_Explosion::update()
{
    ++mFrameCount;
    if ( mFrameCount > 30 )
    {
        return false;
    }

	//�A�j���[�V����
	this->mPanel->SetSrcRect(128 * (mFrameCount % 5),128 * (mFrameCount / 5),128,128);
    return true;
}

//=============================================================================
// �� Effect_Explosion2 �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
Effect_Explosion2::Effect_Explosion2( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = Sprite3D::Create( 20, 20 );
    mPanel->SetTexture(Assets::LoadTexture( "./Data/Graphics/Effect/Explosion01.png" ) );
    mPanel->SetSrcRect( 0, 128, 128, 128 );
    mPanel->SetAngles( 0, 0, 0 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );



    mFrameCount = 0;
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
Effect_Explosion2::~Effect_Explosion2()
{

}

//---------------------------------------------------------------------
// �� �t���[���X�V (false ��Ԃ��Ɖ������)
//---------------------------------------------------------------------
bool Effect_Explosion2::update()
{
    ++mFrameCount;
    if ( mFrameCount > 15 )
    {
        return false;
    }

	//�A�j���[�V����
	this->mPanel->SetSrcRect(128 * (mFrameCount ),128 * (mFrameCount / 5),128,128);
    return true;
}

//=============================================================================
// �� Effect_3 �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
Effect_Test_3::Effect_Test_3( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = Sprite3D::Create( 120,130 );
    mPanel->SetTexture(Assets::LoadTexture( "Data/Graphics/Effect/Effect_1.png" ) );
    mPanel->SetSrcRect( 0, 128, 128, 128 );
  //  mPanel->SetAngle( 0, 0, LMath::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
Effect_Test_3::~Effect_Test_3()
{
}

//---------------------------------------------------------------------
// �� �t���[���X�V (false ��Ԃ��Ɖ������)
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
// �� Effect_Thunder �N���X
//=============================================================================

//---------------------------------------------------------------------
// �� �R���X�g���N�^
//---------------------------------------------------------------------
Effect_Thunder::Effect_Thunder( const LVector3& pos_ )
{
    //static Math::Random random;

    mPanel = Sprite3D::Create( 64,2000 );
    mPanel->SetTexture(Assets::LoadTexture( "Data/Graphics/Effect/Thunder_1.png" ) );
    mPanel->SetSrcRect(0, 512, 64, 512 );
  //  mPanel->SetAngle( 0, 0, LMath::PI / 2 );//random.getFloat( 3.0f ) );
    mPanel->SetPosition( pos_ );

	Vector3 scr = Vector3::TransformCoord(pos_, Camera::GetMain3DCamera()->GetProjectionMatrix());
	Accessor::BlurLayer->SetBlurStatus(0.5, Vector2(scr.x, scr.y), 1.05, 0.6);
	//LLayer::getBGLayer()->blur(0.6, 0.5, 1.05, pos_, true );

    mFrameCount = 0;
}

//---------------------------------------------------------------------
// �� �f�X�g���N�^
//---------------------------------------------------------------------
Effect_Thunder::~Effect_Thunder()
{
}

//---------------------------------------------------------------------
// �� �t���[���X�V (false ��Ԃ��Ɖ������)
//---------------------------------------------------------------------
bool Effect_Thunder::update()
{
  //  mPanel->SetScale(1, 1.0f, 1);
    //mPanel->SetOpacity( 1.0f - ( mFrameCount / 6.0f ) );
    mPanel->SetSrcRect(64*(mFrameCount/5), 512, 64, 512 );
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