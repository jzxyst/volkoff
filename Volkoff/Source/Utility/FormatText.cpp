//=============================================================================
//�y FormatText �z
//=============================================================================

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
#include "stdafx.h"
#include "FormatText.h"
#include <math.h>



namespace LNote
{
namespace Core
{
namespace Base
{

class StringUtil
{
public:
	inline static bool checkMultiByteChar(const char* code_)
	{
#ifdef LN_UNICODE
		return false;
#else
		return  ((unsigned char)*code_ >= 0x81 && (unsigned char)*code_ <= 0x9f) || ((unsigned char)*code_ >= 0xe0 && (unsigned char)*code_ <= 0xfc);
#endif
	}

	inline static void replaceString(std::string* str_, const char* from_, const char* to_)
	{
		std::string::size_type pos = 0;
		int from_length = (int)strlen(from_);
		int to_length = (int)strlen(to_);

		while (pos = str_->find(from_, pos), pos != std::string::npos)
		{
			str_->replace(pos, from_length, to_);
			pos += to_length;
		}
	}

	inline static int strlenMB(const lnChar* str_)
	{
#ifdef LNOTE_UNICODE
		return _tcslen(str_);
#else
		//int max_len = _tcslen( str_ );
		int count = 0;
		//int i = 0;
		//for ( ; i < max_len; )
		while (*str_)
		{
			if (checkMultiByteChar(str_))
			{
				str_ += 2;
				//i += 2;
			}
			else
			{
				++str_;
				//++i
			}
			++count;
		}
		return count;
#endif
	}
};

}
}
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
namespace LNote
{
namespace Utility
{
    


//=============================================================================
// �� FormatText �N���X
//=============================================================================

    //---------------------------------------------------------------------
    // �� �R���X�g���N�^
    //---------------------------------------------------------------------
    FormatText::FormatText()
        : mFont             ( NULL )
        , mDefaultFontSize  ( 20 )
        , mTypingSpeed      ( 2 )
        , mIndex            ( 0 )
        , mWaitCount        ( 0 )
        , mX                ( 0 )
        , mY                ( 0 )
        , mCurrentLine      ( 0 )
        , mLineHeight       ( 0 )
        //, mRubyChar     ( NULL )
        , mRubyLength       ( 0 )
        , mRubyX            ( 0 )
        , mRubyFont         ( NULL )
    {
    }

    //---------------------------------------------------------------------
    // �� �f�X�g���N�^
    //---------------------------------------------------------------------
    FormatText::~FormatText()
    {
    }


    //---------------------------------------------------------------------
	// �� �������ݒ肷��
    //---------------------------------------------------------------------
    void FormatText::setText( const lnChar* text_ )
    {
        mSrcText = text_;
    }

    //---------------------------------------------------------------------
	// �� �t�H���g��ݒ肷��
    //---------------------------------------------------------------------
    void FormatText::setFont(FontPtr font_ )
    {
        mFont = font_;

        if (mFont != nullptr)
        {
            mDefaultFontSize = mFont->GetSize();
            mRubyFont = mFont->Clone();
            mRubyFont->SetSize( mFont->GetSize() / 2 );
        }
    }

    //---------------------------------------------------------------------
	// �� �^�C�s���O�X�s�[�h�̐ݒ�
    //---------------------------------------------------------------------
    void FormatText::setTypingSpeed( int speed_ )
    {
        mTypingSpeed = std::max( 0, speed_ );
    }

    //---------------------------------------------------------------------
	// �� �`����`�̐ݒ�
    //---------------------------------------------------------------------
    void FormatText::setDrawRect( const Rect& rect_ )
    {
        mDrawRect = rect_;
    }

    //---------------------------------------------------------------------
	// �� �ݒ肳�ꂽ�������Ƃɕ`������\�z����
    //---------------------------------------------------------------------
    void FormatText::build()
    {
        

    
        Core::Base::StringUtil::replaceString( &mSrcText, _T( "\\f" ), _T( "\\001" ) );
        Core::Base::StringUtil::replaceString( &mSrcText, _T( "\\F" ), _T( "\\001" ) );
        Core::Base::StringUtil::replaceString( &mSrcText, _T( "\\r" ), _T( "\\027" ) );
        Core::Base::StringUtil::replaceString( &mSrcText, _T( "\\R" ), _T( "\\027" ) );



        int w, h;
        _getLineSize( mSrcText.c_str(), &w, &h );

        mDrawDataEntryQueue.clear();
        mIndex = 0;
        mWaitCount = 0;
        mX = 0;
        mY = 0;
        mCurrentLine = 0;
        mLineHeight = h;


    }

    //---------------------------------------------------------------------
	// �� �t���[���X�V
    //---------------------------------------------------------------------
    void FormatText::update()
    {
        if ( mSrcText.size() <= 0 || isFinished() ) { return; }

        const lnChar* text = mSrcText.c_str();
        //Rect rc;

        while ( true )
        {
            // �ҋ@���Ԃ�����ꍇ�͌��炵�Ă���I��
            if ( mWaitCount > 0 )
            {
                --mWaitCount;
                return;
            }

            // �I��
            if ( text[ mIndex ] == _T( '\0' ) )
            {
                break;
            }

            // ���s
            if ( text[ mIndex ] == _T( '\n' ) )
            {
                ++mCurrentLine;
                ++mIndex;
                mX = 0;

                int w, h;
                _getLineSize( &text[ mIndex ], &w, &h );
                mY = mY + mLineHeight;
                mLineHeight = h;
                continue;
            }

            // ���䕶���̏���
            int adv_idx;
            int unknown_code;
            bool is_continue = _checkControlChar( &text[ mIndex ], &adv_idx, &unknown_code );
            mIndex += adv_idx;
            if ( is_continue )
            {
                continue;
            }

            // ���䕶���̏�����ɏI�[�E���s���w���Ă��邩�A���䕶���̏ꍇ�� continue
            if ( text[ mIndex ] == _T( '\0' ) || text[ mIndex ] == _T( '\n' ) || text[ mIndex ] == CONTROL_CHAR )
            {
                continue;
            }

            
            /// ���r�̕`����̍쐬
            _makeRubyData();

            



            // �}���`�o�C�g�������ǂ����Ń`�F�b�N���镶���񒷂������߂� unicode �̏ꍇ�͏�� 1
            int len = Core::Base::StringUtil::checkMultiByteChar( &text[ mIndex ] ) ? 2 : 1;

            Size size = mFont->MeasureRenderSize(StringRef(&text[ mIndex ], len));


            DrawDataEntry entry;
            entry.DrawData.Text = &text[ mIndex ];
            entry.DrawData.Length = len;
            entry.DrawData.Rect.Set( mX, mY + ( mLineHeight - size.height), size.width, size.height);
            entry.DrawData.Font = mFont;
            mDrawDataEntryQueue.push_back( entry );

            mX += size.width;

            mIndex += len;

            mWaitCount = mTypingSpeed;
        }


        //mDrawDataEntryList

        /*
        const lnChar* line_head = mSrcText.c_str();
        int line_width = 0;

        while ( true )
        {
            line_head = _buildLine( line_head, &line_width );
            if ( *line_head == _T( '\0' ) )
            {
                break;
            }
        }
        */
    }

    //---------------------------------------------------------------------
	// �� �`����̎擾
    //---------------------------------------------------------------------
    bool FormatText::getNextDrawData( LNFormatTextDrawData* data_ )
    {
        if ( mDrawDataEntryQueue.empty() ) { return false; }

		*data_ = mDrawDataEntryQueue.front().DrawData;
        data_->Rect.x += mDrawRect.x;
        data_->Rect.y += mDrawRect.y;
		mDrawDataEntryQueue.pop_front();

		return true;
    }

    //---------------------------------------------------------------------
	// �� �S�Ă̏������������Ă��邩�𔻒肷��
    //---------------------------------------------------------------------
    bool FormatText::isFinished() const
    {
        return ( mSrcText.size() == 0 || mSrcText.c_str()[ mIndex ] == _T( '\0' ) );
    }

    //---------------------------------------------------------------------
	// �� 1�s�̕��ƍ��������߂�
    //---------------------------------------------------------------------
    void FormatText::_getLineSize( const lnChar* str_, int* width_, int* height_ )
    {
        *width_  = 0;
        *height_ = 0;

        int org_fontsize = mFont->GetSize();
        int i = 0;
        int w = 0;
        int h = org_fontsize;
        int ruby_size = 0;

        int start_normal_char_idx = 0;
        int last_normal_char_idx = 0;

        bool font_changed = false;
        int new_font_size = 0;
        bool new_bold = false;

        while ( true )
        {
            // ���s���I�[�܂�
            if ( str_[ i ] == _T( '\n' ) || str_[ i ] == _T( '\0' ) )
            {
				Size size = mFont->MeasureRenderSize(
                    StringRef(&str_[ start_normal_char_idx ],
                    ( last_normal_char_idx - start_normal_char_idx )));
                //printf("1:%d w:%d\n",last_normal_char_idx - start_normal_char_idx, rc.width);
                *width_ += size.width;
                break;
            }

            // ���䕶����̏���
            if ( str_[ i ] == CONTROL_CHAR )
            {
                ++i;
                int code = _checkCtrlCharNumber( &str_[ i ] );
                if ( code )
                {
                    i += 3;
                }

                switch ( code )
                {
                    /////////// �t�H���g�T�C�Y�ύX
                    case 1:
                    {
                        if ( _parsControlArgs( &str_[ i ], &mCtrlArgs ) )
                        {
                            i += mCtrlArgs.CommandLength;       // ] �̎����w��

                            // �t�H���g�T�C�Y���ȗ�����Ă���ꍇ�̓f�t�H���g�̃T�C�Y�ɂ���
                            int size;
                            if ( mCtrlArgs.Args[ 0 ].IsOptional )
                            {
                                size = mDefaultFontSize;
                            }
                            else
                            {
                                size = _getIntArg( mCtrlArgs.Args[ 0 ] );
                            }

                            new_font_size = size;
                            h = std::max( h, size );
                            font_changed = true;
                        }
                        break;
                    }
                    /////////// ���r
                    case 27:
                    {
                        if ( _parsControlArgs( &str_[ i ], &mCtrlArgs ) )
                        {
                            i += mCtrlArgs.CommandLength;       // ] �̎����w��

                            // �ЂƂł�����΍s�̍����𑝂₷
                            ruby_size = mFont->GetSize() / 2;
                        }
                        break;
                    }
                }
                continue;
            }

            // �t�H���g�T�C�Y�ύX�ȂǂŁAlast_normal_char_idx �܂ł̕����񕝂��v�Z����K�v������ꍇ
            if ( font_changed )
            {
				Size size = mFont->MeasureRenderSize(
                    StringRef(&str_[ start_normal_char_idx ],
                    ( last_normal_char_idx - start_normal_char_idx )));
                //printf("2:%d w:%d\n",last_normal_char_idx - start_normal_char_idx, rc.width);
                *width_ += size.width;
                start_normal_char_idx = i;
                

                mFont->SetSize( new_font_size );
                font_changed = false;
            }

            // �����܂ŗ����畁�ʂ̕���
            
            if ( Core::Base::StringUtil::checkMultiByteChar( &str_[ i ] ) )
            {
                i += 2;
            }
            else
            {
                ++i;
            }

            last_normal_char_idx = i;
        }

        mFont->SetSize( org_fontsize );
        *height_ = h + ruby_size;
        return;
    }

    

    //---------------------------------------------------------------------
	// �� str_ �ȍ~�ɑ��� 3 �̕��������������`�F�b�N���āA���l�������l��Ԃ� (�����ȏꍇ�� 0)
    //---------------------------------------------------------------------
    int FormatText::_checkCtrlCharNumber( const lnChar* str_ )
    {
        if ( isdigit( *str_ ) && isdigit( *(str_ + 1) ) && isdigit( *(str_ + 2) ) )
        {
            return
                (*str_       - _T( '0' )) * 100 +
                (*(str_ + 1) - _T( '0' )) * 10  +
                (*(str_ + 2) - _T( '0' ));
        }
        return 0;
    }

    //---------------------------------------------------------------------
	// �� ���䕶�����ǂ������`�F�b�N���ď���������
	//---------------------------------------------------------------------
	bool FormatText::_checkControlChar( const lnChar* str_, int* adv_index_, int* unknown_code_ )
    {
        *unknown_code_ = 0;
        *adv_index_ = 0;
        int i = 0;

        // ���䕶����̏���
        if ( str_[ i ] == CONTROL_CHAR )
        {
            ++i;
            int code = _checkCtrlCharNumber( &str_[ i ] );
            if ( code )
            {
                i += 3;

                _parsControlArgs( &str_[ i ], &mCtrlArgs );
                i += mCtrlArgs.CommandLength;

                switch ( code )
                {
                    /////////// �t�H���g�T�C�Y�ύX
                    case 1:
                    {
                        // �t�H���g�T�C�Y���ȗ�����Ă���ꍇ�̓f�t�H���g�̃T�C�Y�ɂ���
                        int size;
                        if ( mCtrlArgs.Args[ 0 ].IsOptional )
                        {
                            mFont->SetSize( mDefaultFontSize );
                        }
                        else
                        {
                            mFont->SetSize( _getIntArg( mCtrlArgs.Args[ 0 ] ) );
                        }
                    
                        break;
                    }
                    /////////// ���r
                    case 27:
                    {
                        //Base::StringUtil::trimHFSpace( &mRubyText, ln_std_tstring( mCtrlArgs.Args[ 1 ].BeginChar, mCtrlArgs.Args[ 1 ].Length ) );
                        mRubyText   = ln_std_tstring( mCtrlArgs.Args[ 1 ].BeginChar, mCtrlArgs.Args[ 1 ].Length );

                        mRubyLength = mRubyText.size();
                        //mRubySize   = mFont->getSize() / 2;

						ln_std_tstring tmp( mCtrlArgs.Args[ 0 ].BeginChar, mCtrlArgs.Args[ 0 ].Length );
                         
                        // mIndex �� '\\' ���w���Ă���B
                        //  + 4 �� \ �� 3���̐���
                        mSrcText.replace( mIndex, mCtrlArgs.CommandLength + 4, tmp.c_str() );

                        mRubyMainStr    = &mSrcText.c_str()[ mIndex ];
                        mRubyMainStrLen = Core::Base::StringUtil::strlenMB( tmp.c_str() );//mCtrlArgs.Args[ 0 ].Length;


                        // ���r�ƃ��C��������̕����擾
                        int ruby_w, main_w;
						Size size = mFont->MeasureRenderSize( tmp.c_str() );
                        main_w = size.width;
						size = mRubyFont->MeasureRenderSize( mRubyText.c_str() );
                        ruby_w = size.width;

                        // �}���`�o�C�g�̏ꍇ�͂����1�����Ƃ������������v�Z
                        int true_len = Core::Base::StringUtil::strlenMB( mRubyText.c_str() );

                        mRubySize = mRubyFont->GetSize();
                        //_p(mRubySize);
                        
                        // ���r�̕`����n�߂� X ���W�Ɖ��Z�ʂ̌v�Z
                        if ( main_w >= ruby_w || true_len == 1 )
                        {
                            if ( true_len == 1 )
                            {
                                mRubyX = static_cast< float >( main_w ) / ( true_len * 2 ) - mRubySize / 2;
                            }
                            else
                            {
                                mRubyX = static_cast< float >( main_w ) / ( true_len * 2 ) - mRubySize / 3;
                            }
                            
                            
                            mRubyOffsetX = static_cast< float >( main_w ) / true_len;
                            //int ox = mX + ( main_w - ruby_w ) / 2;
                        }
                        else
                        {
                            //mRubyX       = static_cast< float >( ruby_w - main_w - mRubySize ) / 2;
                            //mRubyX       = ( main_w / 2 ) - ( ruby_w / 2 );//static_cast< float >( ruby_w - main_w ) / 2;
                            mRubyX       = static_cast< float >( main_w - ruby_w ) / 2;
                            mRubyOffsetX = static_cast< float >( ruby_w ) / true_len;
                        }
                        
                        mRubyX = mX + mRubyX;

                        i = 0;
                        break;
                    }
                    /////////// �o�^����Ă��Ȃ��R�[�h
                    default:
                    {
                        *unknown_code_ = code;
                        break;
                    }
                }
            }
        }
        *adv_index_ = i;
        return false;
    }

    //---------------------------------------------------------------------
	// �� [] �t���̐��䕶�������͂���
    //---------------------------------------------------------------------
    bool FormatText::_parsControlArgs( const lnChar* str_, CtrlArgsConteiner* out_ )
    {
        if ( *str_ != _T( '[' ) )
        {
            out_->CommandLength = 0;
            return false;
        }

        int state = 0;
        int i = 1;
        int arg_idx = 0;
        int begin = 1;

        for ( int i = 0; i < MAX_CTRL_ARGMENTS; ++i )
        {
            out_->Args[ i ].BeginChar = NULL;
            out_->Args[ i ].Length = 0;
            out_->Args[ i ].IsOptional = true;
        }


        while ( true )
        {
            // ���s�A�I�[�����������ꍇ�̓G���[
            if ( str_[ i ] == _T( '\n' ) || str_[ i ] == _T( '\0' ) )
            {
                out_->CommandLength = 0;
                return false;
            }
            // ��؂蕶��
            else if ( str_[ i ] == _T( ',' ) )
            {
                // �ő吔�ɒB���Ă��Ȃ���Βǉ�����
                if ( arg_idx < MAX_CTRL_ARGMENTS )
                {
                    out_->Args[ arg_idx ].BeginChar  = &str_[ begin ];
                    out_->Args[ arg_idx ].Length     = i - begin;

                    // �O��̃X�y�[�X���J�b�g
                    _trimArgStrSpace( &out_->Args[ arg_idx ] );

                    // ���`��A�������� 0 �ȉ��̏ꍇ�A�����͏ȗ�����Ă���
                    out_->Args[ arg_idx ].IsOptional = ( out_->Args[ arg_idx ].Length <= 0 );
                    
                    ++arg_idx;
                    ++i;
                    begin = i;
                    out_->ArgsNum = arg_idx;
                }
            }
            // �I��
            if ( str_[ i ] == _T( ']' ) )
            {
                if ( arg_idx < MAX_CTRL_ARGMENTS )
                {
                    out_->Args[ arg_idx ].BeginChar = &str_[ begin ];
                    out_->Args[ arg_idx ].Length    = i - begin;

                    // �O��̃X�y�[�X���J�b�g
                    _trimArgStrSpace( &out_->Args[ arg_idx ] );

                    // ���`��A�������� 0 �ȉ��̏ꍇ�A�����͏ȗ�����Ă���
                    out_->Args[ arg_idx ].IsOptional = ( out_->Args[ arg_idx ].Length <= 0 );
                }
                out_->CommandLength = i + 1;
                return true;
            }

            ++i;
        }

       
        return true;
    }

    //---------------------------------------------------------------------
	// �� 12 ���܂ł̕����񁨐��l�ϊ�
    //---------------------------------------------------------------------
    int FormatText::_toInt( const lnChar* str_, int len_ )
    {
        lnChar buf[ 13 ] = { 0 };
        _tcsncpy( buf, str_, std::max( len_, 12 ) );
        return _tstoi( buf );
    }

    //---------------------------------------------------------------------
	// �� ArgsData ���琔�l���擾
    //---------------------------------------------------------------------
    int FormatText::_getIntArg( const ArgData& arg_ )
    {
        if ( arg_.BeginChar )
        {
            return _toInt( arg_.BeginChar, arg_.Length );
        }
        return 0;
    }


    //---------------------------------------------------------------------
	// �� ���r�̕`����̍쐬 (update() ����Ă΂��)
    //---------------------------------------------------------------------
    void FormatText::_makeRubyData()
    {
        if ( mRubyLength > 0 )
        {
            // �t�H���g�T�C�Y�̃o�b�N�A�b�v������āA���r�p�̃T�C�Y���Z�b�g
            //int org_fontsize = mFont->getSize();
            //mRubyFont->setSize( mRubySize );

            int ruby_text_true_len = Core::Base::StringUtil::strlenMB( mRubyText.c_str() );

            // ���r�̕����� / ���C��������̕�����
            float num =
                static_cast< float >( ruby_text_true_len ) / mRubyMainStrLen;
            
            // ���̕`��łǂꂾ�����r��U�邩�v�Z
            float c = ceil( num );
            int cnt = c - floor( (c - num) + 0.5f );


            // �񐔕��������r��`��
            for ( int i = 0; i < cnt; ++i )
            {
                //if ( mRubyLength > 0 )  // <= �� i ���񂵂Ă�̂ŁA1�񑽂��Ȃ邱�Ƃ����邽�߁A���̕ی�
                {

                    int idx = mRubyText.size() - mRubyLength;
                    const lnChar* str = mRubyText.c_str();
                    int len = Core::Base::StringUtil::checkMultiByteChar( &str[ idx ] ) ? 2 : 1;
                    mRubyLength -= len;


                    Size size = mRubyFont->MeasureRenderSize(StringRef(&str[ idx ], len));

                    DrawDataEntry entry;
                    entry.DrawData.Text = &str[ idx ];
                    entry.DrawData.Length = len;
                    entry.DrawData.Rect.Set( mRubyX, mY + ( mLineHeight - mFont->GetSize() - mRubySize ), size.width, size.height);
                    entry.DrawData.Font = mRubyFont;
                    mDrawDataEntryQueue.push_back( entry );

                    mRubyX += mRubyOffsetX;
                }

            }
        }
    }

    //---------------------------------------------------------------------
	// �� ����������̑O��̋󔒂���菜�� (_parsControlArgs() ����Ă΂��)
    //---------------------------------------------------------------------
    void FormatText::_trimArgStrSpace( ArgData* arg_data_ )
    {
        int b = 0;
        int e = arg_data_->Length;
        const lnChar* c = arg_data_->BeginChar;
        for ( ; c[ b ] != _T( '\0' ) && c[ b ] == _T( ' ' ); ++b ) {}

        // e �� ']' ',' ���w���Ă��邱�Ƃ�����̂ŁA����̑Ή�
        /*
        for ( ;
            e >= b &&
            ( c[ e ] == _T( ',' ) || 
              c[ e ] == _T( ']' ) || 
              c[ e ] == _T( ' ' ) ) ; --e ) {}
              */
        // �}���`�o�C�g������̑Ή�
        while ( true )
        {
            if ( e > b )
            {
                // �u���v�Ȃ񂩂�2�o�C�g�ڂ� ' ' �Ɠ����Ȃ̂ŁA�����ƃ`�F�b�N���Ă����K�v������
                if ( Core::Base::StringUtil::checkMultiByteChar( &c[ e - 2 ] ) )
                {
                    break;
                }
            }
            if ( e >= b && ( c[ e ] == _T( ',' ) || c[ e ] == _T( ']' ) || c[ e ] == _T( ' ' ) ) )
            {
                --e;
            }
            else
            {
                break;
            }
        }

        arg_data_->BeginChar = &c[ b ];
        arg_data_->Length    = e - b;
    }









//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

} // namespace Utility
} // namespace LNote

//=============================================================================
//								end of file
//=============================================================================