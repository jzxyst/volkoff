//=============================================================================
//�y PlayerStateWindow �z
//=============================================================================

#include "stdafx.h"
#include "../Utility/Util.h"
#include "../Object/Player.h"
#include "../Object/Weapon.h"
#include "../Game/GameManager.h"
#include "PlayerStateWindow.h"



//=============================================================================
// �� PlayerStateWindow �N���X
//=============================================================================


    //---------------------------------------------------------------------
    // �� �R���X�g���N�^
    //---------------------------------------------------------------------
    PlayerStateWindow::PlayerStateWindow( Player* player_ )
        : mPlayer               ( player_ )
        , mStep                 ( PSW_PTEP_SETUP )
        , mLastWeaponCount      ( 0 )
        , mWarningFrameCount    ( 0 )
        , mWarningShowedFlag    ( 0 )
        , mHPDieWidth           ( 0 )
        , mDieWaitFrameCount    ( 0 )
        , mEXPBarFrameCount     ( 0 )
        , mHasKey               ( 0 )
        , mKeyEffectFrameCount  ( 0 )
    {
        mHPNumber.setSpeed( 8 );

        mFrontendTexture = Assets::LoadTexture( "Data/Graphics/Frontend/Frontend_1.png" );
        mNumberTextureS  = Assets::LoadTexture( "Data/Graphics/Frontend/Number_2.png" );
        mNumberTextureL  = Assets::LoadTexture( "Data/Graphics/Frontend/Number_3.png" );

        mFrameWindow = Sprite2D::Create( mFrontendTexture );
        mFrameWindow->SetSrcRect( LRect( 128, 0, 128, 112 ) );

		mFrameWindow->SetName("mFrameWindow");

        // �t���A���ƃX�R�A�̐���
        mFloorNumSprite[0] = Sprite2D::Create(mNumberTextureS);
		mFloorNumSprite[1] = Sprite2D::Create(mNumberTextureS);
		mFloorNumSprite[0]->SetVisible(false);
        for ( int i = 0; i < 10; ++i )
        {
			mScoreNumSprite[i] = Sprite2D::Create(mNumberTextureS);
			mScoreNumSprite[i]->SetName("mScoreNumSprite");
        }


        // HP �֌W
        mHPBarSprite    = Sprite2D::Create( mFrontendTexture );
        mHPDieBarSprite = Sprite2D::Create( mFrontendTexture );
        mHPBarSprite->SetSrcRect( LRect( 256, 0, 120, 18 ) );
        mHPDieBarSprite->SetSrcRect( LRect( 376, 0, 0, 18 ) );
        mHPDieBarSprite->SetVisible( false );

        // ����A�C�R��
        mWeaponIconSprite = Sprite2D::Create( mFrontendTexture );

        // ���탌�x��
        mWeaponLevelSprite = Sprite2D::Create( mNumberTextureS );
        mWeaponEXPBar = Sprite2D::Create( mFrontendTexture );
        mWeaponEXPBar->SetSrcRect( 256, 57, 40, 7 );

        // �g�p��
        for ( int i = 0; i < 3; ++i )
        {
            mWeaponCountSprite[ i ] = Sprite2D::Create( mNumberTextureL );
            mWeaponCountWarningSprite[ i ] = Sprite2D::Create( mNumberTextureL );
            mWeaponCountWarningSprite[ i ]->SetVisible( false );
            mWeaponCountWarningSprite[ i ]->SetScale( 3.0f );
        }

        // ��
        mKeySprite = Sprite2D::Create( mFrontendTexture );
        mKeySprite->SetSrcRect( 104, 0, 24, 32 );
        mKeySprite->SetCenter( 12, 16 );
        mKeySprite->SetPosition( 118, 74 );
        mKeySprite->SetVisible( false );
        mKeyEffectSprite[ 0 ] = Sprite2D::Create( mFrontendTexture );
        mKeyEffectSprite[ 0 ]->SetSrcRect( 104, 32, 24, 24 );
        mKeyEffectSprite[ 0 ]->SetCenter( 12, 12 );
        mKeyEffectSprite[ 0 ]->SetPosition( 118, 68 );
        mKeyEffectSprite[ 0 ]->SetVisible( false );
        mKeyEffectSprite[ 1 ] = Sprite2D::Create( mFrontendTexture );
        mKeyEffectSprite[ 1 ]->SetSrcRect( 104, 0, 24, 32 );
        mKeyEffectSprite[ 1 ]->SetCenter( 12, 16 );
        mKeyEffectSprite[ 1 ]->SetPosition( 118 + 10, 68 + 10 );
        mKeyEffectSprite[ 1 ]->SetVisible( false );

        // �v���C���[�� HP ���o���Ă���
        mPlayerHP = mPlayer->getLife();
        mHPNumber.set( mPlayer->getLife() );

        setPosition( 12, 12 );
        
        refresh();
    }

    //---------------------------------------------------------------------
    // �� �f�X�g���N�^
    //---------------------------------------------------------------------
    PlayerStateWindow::~PlayerStateWindow()
    {
    }

    //---------------------------------------------------------------------
    // �� �ʒu�̐ݒ�
    //---------------------------------------------------------------------
    void PlayerStateWindow::setPosition( float x_, float y_ )
    {
        mFrameWindow->SetPosition( x_, y_ );
        mWeaponIconSprite->SetPosition( x_ + 8, y_ + 69 ); //56

        for ( int i = 0; i < 2; ++i )
        {
            //mFloorNumSprite[ i ]->setPosition( x_ + 12 + 8 * i, y_ + 3 );
            mFloorNumSprite[ i ]->SetPosition( x_ + 12 + 8 * i - 4, y_ + 3 );
        }

        for ( int i = 0; i < 10; ++i )
        {
            mScoreNumSprite[ i ]->SetPosition( x_ + 38 + 8 * i, y_ + 3 );
        }

        mHPBarSprite->SetPosition( x_ + 4, y_ + 18 );

        mWeaponEXPBar->SetPosition( x_ + 49, y_ + 38, 0.1f );

        for ( int i = 0; i < 3; ++i )
        {
            mWeaponCountSprite[ i ]->SetPosition( x_ + 54 + 9 * i, y_ + 81 );
        }

        mPosition.Set( x_, y_, 0.0f );
    }

    //---------------------------------------------------------------------
    // �� �s�����x�̐ݒ�
    //---------------------------------------------------------------------
    void PlayerStateWindow::setOpacity( float op_ )
    {
        mFrameWindow->SetOpacity( op_ );
        mWeaponIconSprite->SetOpacity( op_ );

        for ( int i = 0; i < 2; ++i )
        {
            mFloorNumSprite[ i ]->SetOpacity( op_ );
        }

        for ( int i = 0; i < 10; ++i )
        {
            mScoreNumSprite[ i ]->SetOpacity( op_ );
        }

        mHPBarSprite->SetOpacity( op_ );
        mHPDieBarSprite->SetOpacity( op_ );
        mWeaponLevelSprite->SetOpacity( op_ ); 
        mHPDieBarSprite->SetOpacity( op_ );
		mWeaponEXPBar->SetOpacity( op_ );

        for ( int i = 0; i < 3; ++i )
        {
            mWeaponCountSprite[ i ]->SetOpacity( op_ );
        }
    }

    

    //---------------------------------------------------------------------
    // �� ���t���b�V��
    //---------------------------------------------------------------------
    void PlayerStateWindow::refresh()
    {
        
    }

    //---------------------------------------------------------------------
    // �� �t���[���X�V
    //---------------------------------------------------------------------
    void PlayerStateWindow::update()
    {
        u32 nums[ 12 ];

        // �t���A��
        Util::numberToArray( GameManager::getInstance()->getFloorNum() + 1, 2, nums );
        //mFloorNumSprite[ 0 ]->setSrcRect( LRect( 7 * nums[ 0 ], 0, 7, 11 ) );
        mFloorNumSprite[ 1 ]->SetSrcRect( LRect( 7 * nums[ 1 ], 0, 7, 11 ) );

        // �X�R�A
        Util::numberToArray(  GameManager::getInstance()->getScore(), 10, nums );
        for ( int i = 0; i < 10; ++i )
        {
            mScoreNumSprite[ i ]->SetSrcRect( LRect( 7 * nums[ i ], 0, 7, 11 ) );
        }


        // ����A�C�R��
        mWeaponIconSprite->SetSrcRect( LRect( 128 + 32 * mPlayer->getWeaponData().WeaponType, 128, 32, 32 ) );

        //-----------------------------------------------------
        // ���x��
        int level = mPlayer->getLevel();
        if ( level >= MAX_PLAYER_LEVELS )   // MAX
        {
            
            mWeaponLevelSprite->SetTexture( mFrontendTexture );
            mWeaponLevelSprite->SetSrcRect( 256, 64, 32, 16 );
            mWeaponLevelSprite->SetPosition( mPosition.x + 24, mPosition.y + 40 );
            

            mWeaponEXPBar->SetSrcRect( 256 + mEXPBarFrameCount, 57, 48, 7 );

            



            
            ++mEXPBarFrameCount;
            if ( mEXPBarFrameCount >= 80 )
            {
                mEXPBarFrameCount = 0;
            }
        }
        else
        {
            mWeaponLevelSprite->SetTexture( mNumberTextureS );
            mWeaponLevelSprite->SetSrcRect( 7 * level, 0, 7, 11 );
            mWeaponLevelSprite->SetPosition( mPosition.x + 24, mPosition.y + 39 );


            float rate;// = static_cast< float >( mPlayer->getExp() ) / scg_nNextLevelExpTotal[ level - 1 ];
            if ( level == 1 )
            {
                rate = static_cast< float >( mPlayer->getExp() ) / scg_nNextLevelExpTotal[ level - 1 ];
            }
            else
            {
                int exp  = mPlayer->getExp() - scg_nNextLevelExpTotal[ level - 2 ];
                int next = scg_nNextLevelExpTotal[ level - 1 ] - scg_nNextLevelExpTotal[ level - 2 ];
                rate = static_cast< float >( exp ) / next;
            }

            rate = std::min( rate, 1.0f );

            mWeaponEXPBar->SetSrcRect( 256 + mEXPBarFrameCount, 57, (int)(rate * 48), 7 );

        }

        //-----------------------------------------------------
        // ����g�p��
        const WeaponData& weapon_data = mPlayer->getWeaponData();
        if ( weapon_data.WeaponType != WEAPON_NON )
        {
            int cnt = weapon_data.UseCount;
            int c1 = cnt / 100;
            int c2 = ( cnt - c1 * 100 ) / 10;
            int c3 = cnt % 10;

            // 3���ȉ��͐Ԃ��\��
            int wy = 0;
            float rate = static_cast< float >( cnt ) / gWeaponBaseData[ weapon_data.WeaponType ].UseCount;
            if ( rate <= 0.5f )
            {
                wy = 1;
            }

            mWeaponCountSprite[ 0 ]->SetSrcRect( LRect( 8 * c1, wy * 16, 8, 14 ) );
            mWeaponCountSprite[ 1 ]->SetSrcRect( LRect( 8 * c2, wy * 16, 8, 14 ) );
            mWeaponCountSprite[ 2 ]->SetSrcRect( LRect( 8 * c3, wy * 16, 8, 14 ) );
            mWeaponCountSprite[ 0 ]->SetVisible( true );
            mWeaponCountSprite[ 1 ]->SetVisible( true );
            mWeaponCountSprite[ 2 ]->SetVisible( true );


            // �x����\��
            if ( wy == 1 && cnt != mLastWeaponCount )
            {
                
                bool show = false;

                if ( rate <= 0.5f && mWarningShowedFlag < 1 )
                {
                    show = true;
                    mWarningShowedFlag = 1;
                }
                else if ( rate <= 0.33f && mWarningShowedFlag < 2 )
                {
                    show = true;
                    mWarningShowedFlag = 2;
                }
                
                if ( show )
                {
                    mWarningFrameCount = 60;
                    for ( int i = 0; i < 3; ++i )
                    {
                        mWeaponCountWarningSprite[ i ]->SetSrcRect( mWeaponCountSprite[ i ]->GetSrcRect() );
                        mWeaponCountWarningSprite[ i ]->SetVisible( true );
                    }
                }
            }

            mLastWeaponCount = cnt;

            // 50% �ȏ�ɉ񕜂��Ă�����x���t���O�����Z�b�g
            if ( rate > 0.5f )
            {
                mWarningShowedFlag = 0;
            }

        }
        // �f��̏ꍇ�͉����\�����Ȃ�
        else
        {
            mWeaponCountSprite[ 0 ]->SetVisible( false );
            mWeaponCountSprite[ 1 ]->SetVisible( false );
            mWeaponCountSprite[ 2 ]->SetVisible( false );
        }

        // �x���\�����̏ꍇ
        if ( mWarningFrameCount > 0 )
        {
            --mWarningFrameCount;

            float x = mPosition.x + 54 + ( 60 - mWarningFrameCount );
            float y = mPosition.y + 68 + ( 60 - mWarningFrameCount ) / 2;

            for ( int i = 0; i < 3; ++i )
            {
                mWeaponCountWarningSprite[ i ]->SetPosition( x + 24 * i, y );
                mWeaponCountWarningSprite[ i ]->SetOpacity( mWarningFrameCount * 0.016f );
            }


            // �x���̕\���I��
            if ( mWarningFrameCount == 0 )
            {
                for ( int i = 0; i < 3; ++i )
                {
                    mWeaponCountWarningSprite[ i ]->SetVisible( false );
                }
            }
        }


        switch ( mStep )
        {
            ///////////////////////////////////////// �J�n���
            case PSW_PTEP_SETUP:
            {
                // �v���C���[�� HP �ɂ킸���ł��ω�����������Z�b�g�A�b�v���f
                if ( mPlayerHP != mPlayer->getLife() || mHPNumber.isFinished() )
                {
                    mPlayerHP = mPlayer->getLife();
                    mStep = PSW_PTEP_IDLE;
                }
                // HP �o�[
                float rate = static_cast< float >( mHPNumber.getValue() ) / mPlayer->getMaxLife();
                mHPBarSprite->SetSrcRect( LRect( 256, 0, rate * 120, 18 ) );
                mHPNumber.update();
            }

            ///////////////////////////////////////// �Ď����
            case PSW_PTEP_IDLE:
            {
                if ( mPlayerHP != mPlayer->getLife() )
                {
                    int prev_hp = mPlayerHP;

                    // �񕜂������ǂ���
                    bool heal = ( mPlayerHP < mPlayer->getLife() );

                    // HP �L��
                    mPlayerHP = mPlayer->getLife();

                    // HP �o�[�̓v���C���[�̎� HP �ɍ��킹��
                    float rate = static_cast< float >( mPlayer->getLife() ) / mPlayer->getMaxLife();
                    float width = rate * 120;
                    float y = 0;

                    // �c�� HP �ɂ���ăo�[�̐F��ς���
                    if ( rate <= 0.15f )
                    {
                        y = 36;
                    }
                    else if ( rate <= 0.50f )
                    {
                        y = 18;
                    }

                    mHPBarSprite->SetSrcRect( LRect( 256, y, width, 18 ) );


                    // �񕜂����ꍇ
                    if ( heal )
                    {
                        mHPDieBarSprite->SetVisible( false );
                        mDieWaitFrameCount = 0;
                        mHPDieWidth = 0;
                    }
                    // �_���[�W���󂯂��ꍇ
                    else
                    {
                        rate = static_cast< float >( prev_hp - mPlayerHP ) / mPlayer->getMaxLife();
                        mHPDieWidth += rate * 120;

                        mHPDieBarSprite->SetVisible( true );
                        mHPDieBarSprite->SetPosition( mHPBarSprite->GetPosition().x + width - 1, mHPBarSprite->GetPosition().y );
                        mHPDieBarSprite->SetSrcRect( 376 + width - 1, 0, mHPDieWidth + 1, 18 );
                        mDieWaitFrameCount = 30;
                    }
                }

                // HP �̖����Ȃ��������̌�������
                if ( mDieWaitFrameCount > 0 )
                {
                    --mDieWaitFrameCount;
                }
                else if ( mHPDieWidth > 0 )
                {
                    --mHPDieWidth;
                    mHPDieBarSprite->SetSrcRect( mHPDieBarSprite->GetSrcRect().x, 0, mHPDieWidth + 1, 18 );
                    if ( mHPDieWidth == 0 )
                    {
                        mHPDieBarSprite->SetVisible( false );
                    }
                }
            }
        }

        //-----------------------------
        // ��

        u8 keyflag = GameManager::getInstance()->getKeyflag();
        if ( mHasKey != keyflag )
        {
            // �V�������肵���ꍇ
            if ( keyflag != 0 )
            {
                mKeySprite->SetVisible( true );
                mKeyEffectSprite[ 0 ]->SetVisible( true );
                mKeyEffectSprite[ 1 ]->SetVisible( true );
                mKeyEffectFrameCount = 7;

                GameAudio::PlaySE( "Data/Sound/SE/coin04.wav", 0.80, 1.20 );
 
            }
            // ���̃X�e�[�W�ɐi�ނƂ��ŁA���Z�b�g���ꂽ�ꍇ
            else
            {
                mKeySprite->SetVisible( false );
                mKeyEffectSprite[ 0 ]->SetVisible( false );
                mKeyEffectSprite[ 1 ]->SetVisible( false );
            }

            mHasKey = keyflag;
        }

        if ( mKeyEffectFrameCount > 0 )
        {
            --mKeyEffectFrameCount;

            mKeyEffectSprite[ 0 ]->SetOpacity( static_cast< float >( mKeyEffectFrameCount ) / 7 + 0.1f );
            mKeyEffectSprite[ 1 ]->SetOpacity( static_cast< float >( mKeyEffectFrameCount ) / 7 + 0.1f );

            mKeyEffectSprite[ 0 ]->SetScale(
                7.0f * ( 7.0f - mKeyEffectFrameCount ) + 1.0f,
                0.3f * mKeyEffectFrameCount );
            
            mKeyEffectSprite[ 1 ]->SetScale( 0.9 * ( 7.0f - mKeyEffectFrameCount ) + 1.0f );

            if ( mKeyEffectFrameCount == 0 )
            {
                mKeyEffectSprite[ 0 ]->SetVisible( false );
                mKeyEffectSprite[ 1 ]->SetVisible( false );
            }
            
        }

    }



//=============================================================================
//								end of file
//=============================================================================
