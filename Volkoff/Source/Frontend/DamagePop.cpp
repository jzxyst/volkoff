//=============================================================================
//�y DamagePop �z
//=============================================================================

#include "stdafx.h"
#include "../Utility/Util.h"
#include "DamagePop.h"

//=============================================================================
// �� DamagePop �N���X
//=============================================================================


    //---------------------------------------------------------------------
    // �� �R���X�g���N�^
    //---------------------------------------------------------------------
    DamagePop::DamagePop()
    {
        mNumberTexture = Assets::LoadTexture( "Data/Graphics/Frontend/Number_1.png" );
    }

    //---------------------------------------------------------------------
    // �� �f�X�g���N�^
    //---------------------------------------------------------------------
    DamagePop::~DamagePop()
    {
        PopNumberList::iterator itr = mPopNumberList.begin();
        PopNumberList::iterator end = mPopNumberList.end();
        for ( ; itr != end; ++itr )
        {
            delete (*itr);
        }
    }

    //---------------------------------------------------------------------
    // �� ������\��������
    //---------------------------------------------------------------------
    void DamagePop::popNumber( const LVector3& pos_, u32 value_, int type_ )
    {
        PopNumber* number = NEW PopNumber( pos_, value_, type_, mNumberTexture );
        mPopNumberList.push_back( number );
    }

    //---------------------------------------------------------------------
    // �� �t���[���X�V
    //---------------------------------------------------------------------
    void DamagePop::update()
    {
        PopNumberList::iterator itr = mPopNumberList.begin();
        PopNumberList::iterator end = mPopNumberList.end();
        for ( ; itr != end; )
        {
            if ( !(*itr)->update() )
            {
                delete (*itr);
                itr = mPopNumberList.erase( itr );
            }
            else
            {
                ++itr;
            }
        }
    }


//=============================================================================
// �� DamagePop::PopNumber �N���X
//=============================================================================


    //---------------------------------------------------------------------
    // �� �R���X�g���N�^
    //---------------------------------------------------------------------
    DamagePop::PopNumber::PopNumber( const LVector3& pos_, u32 value_, int type_, LTexture texture_ )
        : mFrameCount   ( 0 )
    {
        const int num_w = 8;            // 1�����̃s�N�Z����
        const int num_h = 14;           // 1�����̃s�N�Z������
        int digit = Util::getNumberDigits( value_ );    // ����


        

        mNumberTexture = Texture2D::Create( num_w * digit, num_h );
        int x = num_w * digit - num_w;
        for ( int i = 0; i < digit; ++i )
        {
            int v = value_ % 10;

            mNumberTexture->Blt( x, 0, texture_, LRect( v * num_w, num_h * type_, num_w, num_h ) );

            value_ /= 10;
            x -= num_w;
        }


        static Randomizer random;

        mPosition.x = random.GetFloatRange( pos_.x - 10.f, pos_.x + 10.f );
        mPosition.y = random.GetFloatRange( pos_.y - 10.f, pos_.y + 10.f );

        mVelocity.x = random.GetFloatRange( -3.f, 3.f );
        mVelocity.y = 4.f;//random.getFloat( 0.f, 10.f );
        mVelocity.z = 0;

        //_p(pos_.y);
        //_p(mPosition.y);


        mNumberSprite = Sprite2D::Create( mNumberTexture );
        mNumberSprite->SetCenter( mNumberTexture->GetSize().width / 2, mNumberTexture->GetSize().height / 2 );
        mNumberSprite->SetPriority(-1000);	// ��ɏ������悤�ɂ���
        mNumberSprite->SetDepthTestEnabled( false );
    }

    //---------------------------------------------------------------------
    // �� �f�X�g���N�^
    //---------------------------------------------------------------------
    DamagePop::PopNumber::~PopNumber()
    {
    }

    //---------------------------------------------------------------------
    // �� �t���[���X�V
    //---------------------------------------------------------------------
    bool DamagePop::PopNumber::update()
    {
        mPosition += mVelocity;
        mVelocity.y -= 0.25f;

        // �X�N���[�����W�ɕϊ�
        LVector3 pos_2d = Camera::GetDefault3DCamera()->WorldToViewportPoint(mPosition);
        //Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->convertWorldPosToScreenPos( &pos_2d, mPosition );
		pos_2d.z = 0;
		mNumberSprite->SetPosition( pos_2d );


        if ( mFrameCount <= 7 )
        {
            mNumberSprite->SetScale( 1.25f + 0.25f * ( 7 - mFrameCount ) );
        }

        if ( mFrameCount > 10 )
        {
            float c = static_cast< float >( 40 - mFrameCount ) / 40;
            mNumberSprite->SetOpacity( c );
        }

        if ( mFrameCount >= 40 )
        {
            return false;
        }
        ++mFrameCount;


        /*

        // �X�N���[�����W�ɕϊ�
        LVector3 pos_2d;
        Engine::Framework::getInstance()->getSceneManager()->getDefaultSceneGraph()->getDefaultCamera()->convertWorldPosToScreenPos( &pos_2d, mPosition );
        //mPosition.y -= 100;
        mNumberSprite.setPosition( pos_2d );



        ++mFrameCount;

        if ( mFrameCount <= 7 )
        {
            mNumberSprite.setScale( 1.25f + 0.25f * ( 7 - mFrameCount ) );
            return true;
        }

        //mNumberSprite.setOpacity( 0.7f );

        
        if ( mFrameCount < 60 )
        {
            return true;
        }

        //mPosition.y += 1.0f;
        //mNumberSprite.setPosition( mPosition );

        float c = 0.033f *( 90 - mFrameCount );
        mNumberSprite.setOpacity( c );//max( c, 0.7f ) );
 

        
        if ( mFrameCount > 90 )
        {
            return false;
        }
        */
        return true;
    }

 

//=============================================================================
//								end of file
//=============================================================================