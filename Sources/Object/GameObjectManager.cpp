//=============================================================================
/*! 
    @addtogroup 
    @file       GameObjectManager.cpp
    @brief      
    
    GameObjectManager�N���X�̎���
    
    @attention  -
    @note       -
    @author     Hi-ra Mizuno
    @date       2011/10/19
    @version    1.0.0
    @par        Copyright
    Copyright (c) 2011 Valfirle Developer. All Rights Reserved.
===============================================================================
    @par        History
    - 2011/10/19 Hi-ra Mizuo
      -# �쐬
*/
//=============================================================================


/*! @par include */
#include "./GameObjectManager.h"
#include "./GameObject.h"
#include "./../Game/GameManager.h"
#include "./Player.h"
#include "./../Object/Weapon.h"

#include "../Utility/Util.h"

//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::GameObjectManager

	�f�t�H���g�R���X�g���N�^

	@param[in]      void
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
GameObjectManager::GameObjectManager()
    : m_unNextHandle        ( 1 )
    , mUsingEventQueueIndex ( 0 )
{
    for ( int i = 0; i < MAX_MSG_QUEUES; ++i )
    {
        mEventQueueArray[ i ].setCapacity( MSGQUEUE_SIZE );
    }
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::~GameObjectManager

	�f�X�g���N�^

	@param[in]      none
	@return         none
	@exception      none
*/
//---------------------------------------------------------------------------
GameObjectManager::~GameObjectManager()
{
	this->Release();
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::Initialize

	����������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool GameObjectManager::Initialize()
{
	this->Release();

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::Release

	�I������

	@param[in]      void
	@return         bool
	- true  ����
	- false ���s
	@exception      none
*/
//---------------------------------------------------------------------------
bool GameObjectManager::Release()
{
    

	while(!this->m_dqObjectList.empty())
	{
		SAFE_DELETE(this->m_dqObjectList.front());
		this->m_dqObjectList.pop_front();
	}

	if (!m_dqTempList.empty())
	{
		for (GameObject* obj : m_dqTempList)
		{
			SAFE_DELETE(obj);
		}
		m_dqTempList.clear();
	}

	return true;
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::Update

	�t���[���X�V����

	@param[in]      void
	@return         void
	@exception      none
*/
//---------------------------------------------------------------------------
void GameObjectManager::Update()
{
    //_p(m_dqObjectList.size() );

    GameObjectList::iterator itr = this->m_dqObjectList.begin();
    GameObjectList::iterator end = this->m_dqObjectList.end();
	for(;itr != end; )
	{
		//�}�b�v�O�ɏo�Ă��܂����I�u�W�F�N�g�������I�ɏ������W�Ɉړ�����
		if(((*itr)->getPosition().x < 0) || ((*itr)->getPosition().x >= 2000) || ((*itr)->getPosition().y < 0) || ((*itr)->getPosition().y >= 2000))
		{
			(*itr)->setPosition((*itr)->getDefPosition());
		}

        //�폜�t���O
        if((*itr)->getExit())
		{
            //printf( "Delete %d\n", (*itr)->getHandle() );
            // map �������菜��
            m_mObjectMap.erase( (*itr)->getHandle() );

            // [yama] �擪���폜���Ă����̂��s���Ȃ̂ŏ�������
			//SAFE_DELETE(this->m_dqObjectList.front());

            SAFE_DELETE((*itr));

			itr = this->m_dqObjectList.erase(itr);
        }
        else
        {
		    (*itr)->Update();

            (*itr)->UpdateSelf();

            ++itr;
        }
	}


 

    // �L���[�ɂ���C�x���g����������
    int   size;
    char* data;

    for ( int i = 0; i <= mUsingEventQueueIndex; ++i )
    {
        LNote::Utility::MessageQueue& msg_queue = mEventQueueArray[ i ];

        while ( !msg_queue.empty() )
        {
           

            msg_queue.top( (void**)&data, &size );
            msg_queue.pop();

            EventHeader* header = reinterpret_cast< EventHeader* >( data );
			// printf("����:%d\n",header->ObjectHandle);

            // �P��̃I�u�W�F�N�g�ɑ��M����ꍇ
            if ( header->ObjectHandle != 0xffffffff )
            {
                sendEvent( header->ObjectHandle, header->Type, &data[ sizeof( EventHeader ) ], header->ArgSize );
            }

            itr = this->m_dqObjectList.begin();

        }

        msg_queue.clear();
    }


    GameObjectList::iterator titr = this->m_dqTempList.begin();
    GameObjectList::iterator tend = this->m_dqTempList.end();
	for(;titr != tend; )
	{
		m_dqObjectList.push_back(*titr);
		m_mObjectMap.insert( GameObjectPair((*titr)->getHandle(), *titr) );
		++titr;
	}
	m_dqTempList.clear();

	return;
}


//---------------------------------------------------------------------------
/*! 
	@brief GameObjectManager::AddObject

	���X�i�[�����X�g�ɒǉ�����

	@param[in]      GameObject *pCObj �ǉ�����I�u�W�F�N�g�|�C���^
	@return         �ǉ����ꂽ�I�u�W�F�N�g�Ɋ��蓖�Ă�ꂽ�n���h�� (gatHandle() �œ�������̂Ɠ���)
	@exception      none
*/
//---------------------------------------------------------------------------
u32 GameObjectManager::AddObject(GameObject *pCObj)
{
    pCObj->setHandle(m_unNextHandle);

	//TempList�Ɉړ�
	m_dqTempList.push_back(pCObj);
    //m_dqObjectList.push_back(pCObj);
    //m_mObjectMap.insert( GameObjectPair(m_unNextHandle, pCObj) );

    ++m_unNextHandle;

	return m_unNextHandle;
}


//---------------------------------------------------------------------
// �� �I�u�W�F�N�g���폜����
//---------------------------------------------------------------------
void GameObjectManager::deleteObject( GameObject* obj_ )
{
    obj_->setExit( true );
    //obj_->mExit = true;

    //printf( "deleteObject %p\n", obj_ );

    // Update ���ȂǂŃC�e���[�g���� RemoveObject() ���Ă΂��Ƃ�낵���Ȃ��B

    //SAFE_DELETE( obj_ );
}

//---------------------------------------------------------------------
// �� �U���̊֌W����I�u�W�F�N�g��ǉ����� (AttackedObject �̃R���X�g���N�^����Ă΂��)
//---------------------------------------------------------------------
void GameObjectManager::addAttackedObject( AttackedObject* obj_ )
{
    mAttackedObjectList.push_back( obj_ );
}

//---------------------------------------------------------------------
// �� �U���̊֌W����I�u�W�F�N�g���O�� (AttackedObject �̃f�X�g���N�^����Ă΂��)
//---------------------------------------------------------------------
void GameObjectManager::removeAttackedObject( AttackedObject* obj_ )
{
    mAttackedObjectList.remove( obj_ );
}

//---------------------------------------------------------------------
// �� �I�u�W�F�N�g����������
//---------------------------------------------------------------------
GameObject* GameObjectManager::findObject( u32 handle_ )
{
    GameObjectMap::iterator it = m_mObjectMap.find( handle_ );
    if ( it != m_mObjectMap.end() )
    {
        // �폜����悤�Ƃ��Ă���ꍇ�͌����Ɉ���������Ȃ�
        if ( it->second->getExit() )
        {
            return NULL;
        }

        return it->second;
    }
    return NULL;
}

//---------------------------------------------------------------------
// �� �w�肵���n���h�������I�u�W�F�N�g�ɃC�x���g�𑗐M���� (�L���[�C���O����)
//---------------------------------------------------------------------
void GameObjectManager::sendEvent( u32 handle_, u32 event_, void* data_, u32 size_ )
{
    GameObjectMap::iterator it = m_mObjectMap.find( handle_ );
    if ( it != m_mObjectMap.end() )
    {
        it->second->HandleEvent( event_, data_ );
    }
}

//---------------------------------------------------------------------
// �� �w�肵���n���h�������I�u�W�F�N�g�ɃC�x���g�𑗐M���� (�L���[�C���O����)
//---------------------------------------------------------------------
void GameObjectManager::postEvent( u32 handle_, u32 event_, void* data_, u32 size_ )
{
	// Debug
	// static int a = 0;
	// a++;
	// ::printf("�񐔁F%d �C�x���g�ԍ�:%d �����ԍ�:%d\n",a,event_,handle_);

	// �w�b�_�����
    EventHeader header;
    header.Type         = event_;
    header.ObjectHandle = handle_;
    header.ArgSize      = size_;

    // ��x mTempBuffer �ɑS�Ċi�[
    memcpy( mTempBuffer, &header, sizeof( EventHeader ) );
    memcpy( &mTempBuffer[ sizeof( EventHeader ) ], data_, size_ );

    // �L���[�ɃR�s�[
    mEventQueueArray[ mUsingEventQueueIndex ].push( mTempBuffer, sizeof( EventHeader ) + size_ );
}

//---------------------------------------------------------------------
// �� AttackedObject �ƂƂ̓����蔻����s��
//---------------------------------------------------------------------
HitObjectList* GameObjectManager::judgeCollitionToAttackedObject( const LRect& rect_, u32 target_group_ )
{
    mHitObjectList.clear();

    /*
    const LRect* rc;
    int l0, t0, r0, b0;
    int l1, t1, r1, b1;

    l0 = rect_.X;
    t0 = rect_.Y - rect_.height;
    b0 = rect_.Y;
    r0 = rect_.X + rect_.width;
    */
	const LRect* rect2;

    AttackedObjectList::iterator itr = mAttackedObjectList.begin();
    AttackedObjectList::iterator end = mAttackedObjectList.end();
    for ( ; itr != end; ++itr )
    {
        if ( target_group_ & (*itr)->getAttackedGroup() && !(*itr)->isDead() )
        {
            //rect_.dump();
            //(*itr)->getAttackedCollisionRect()->dump();
		    //printf("%d\n",(*itr)->getAttackedCollisionRect()->x);
		    //printf("%d\n",(*itr)->getAttackedCollisionRect()->y);
		    //printf("%d\n",(*itr)->getAttackedCollisionRect()->width);
		    //printf("%d\n",(*itr)->getAttackedCollisionRect()->height);

            /*
            rc = (*itr)->getAttackedCollisionRect();
            l1 = rc->x;
            t1 = rc->y - rc->height;
            b1 = rc->y;
            r1 = rc->x + rc->width;
            */

            

		    //if((rect_.X<=(*itr)->getAttackedCollisionRect()->x+(*itr)->getAttackedCollisionRect()->width)&&((*itr)->getAttackedCollisionRect()->x<=rect_.X+rect_.width)&&(rect_.Y<=(*itr)->getAttackedCollisionRect()->y+(*itr)->getAttackedCollisionRect()->height)&&((*itr)->getAttackedCollisionRect()->y<=rect_.Y+rect_.height))
            
            //printf( "%d <= %d && %d >= %d && %d >= %d && %d <= %d\n", l0, r1, r0, l1, t0, b1, b0, t1 );
            
            /*
            if ( l0 <= r1 && r0 >= l1 && t0 <= b1 && b0 >= t1 )
            {
                mHitObjectList.push_back( (*itr) );
            }
            */
			rect2 = (*itr)->getAttackedCollisionRect();
			if ( rect2 ) 
			{
				if ( Util::judgeCollitionRect( rect_, *rect2 ) )
				{
					mHitObjectList.push_back( (*itr) );
				}
			}
        }
    }  
    
    return &mHitObjectList;
}

//---------------------------------------------------------------------
// �� �w�肵����ނ̃I�u�W�F�N�g�Ɠ����蔻����s��
//---------------------------------------------------------------------
u32 GameObjectManager::judgeCollitionTypeSpecified( const LRect& rect_, ObjectType target_type_, ObjectType target_type_end_ )
{
    GameObjectList::iterator itr = m_dqObjectList.begin();
    GameObjectList::iterator end = m_dqObjectList.end();

    // �ЂƂ̎�ނƂ̔���
    if ( target_type_end_ == OBJ_UNDEF )
    {
        for ( ; itr != end; ++itr )
        {
            if ( (*itr)->getObjType() == target_type_ )
            {
                if ( Util::judgeCollitionRect( rect_, *(*itr)->getBoundingRect() ) )
                {
                    return (*itr)->getHandle();
                }
            }
        }
    }
    // �����̎�ނƂ̔���
    else
    {
        for ( ; itr != end; ++itr )
        {
            if ( target_type_ <= (*itr)->getObjType() && (*itr)->getObjType() <= target_type_end_ )
            {
                if ( Util::judgeCollitionRect( rect_, *(*itr)->getBoundingRect() ) )
                {
                    return (*itr)->getHandle();
                }
            }
        }
    }
    return 0;
}

//---------------------------------------------------------------------
///**
//  @brief      �w�肵����ނ̃I�u�W�F�N�g�Ɠ����蔻����s�����̂��ɏ�������
//
//  @param[in]  rect_             : ���[���h���W��̋�`
//  @param[in]  target_type_      : �Ώۂ̎��
//  @param[in]  target_type_end_  : �Ώۂ̎��
//
//  @return     ���������I�u�W�F�N�g�̃n���h��
//
//  @par
//              target_type_end_ �͔͈͎w�肷��ꍇ�ɒl��n���B
//              �w�肵���ꍇ�Atarget_type_ �ȏ�Atarget_type_end_ �ȉ���
//              ��ނ̃I�u�W�F�N�g�Ɣ�����s���B
//*/
//---------------------------------------------------------------------
u32 GameObjectManager::judgeCollitionTypeSpecifiedAndDelete( const LRect& rect_, ObjectType target_type_, ObjectType target_type_end_ )
{
	GameObjectList::iterator itr = m_dqObjectList.begin();
    GameObjectList::iterator end = m_dqObjectList.end();

	u32 result = OBJ_UNDEF;

    // �ЂƂ̎�ނƂ̔���
    if ( target_type_end_ == OBJ_UNDEF )
    {
        for ( ; itr != end; ++itr )
        {
            if ( (*itr)->getObjType() == target_type_ )
            {
                if ( Util::judgeCollitionRect( rect_, *(*itr)->getBoundingRect() ) )
                {
                    result = (*itr)->getHandle();

                    printf( "�� delete h:%d p:%p\n", result, this->findObject( result ) );

					this->deleteObject( *itr );
					break;
                }
            }
        }
    }
    // �����̎�ނƂ̔���
    else
    {
        for ( ; itr != end; ++itr )
        {
            if ( target_type_ <= (*itr)->getObjType() && (*itr)->getObjType() <= target_type_end_ )
            {
                if ( Util::judgeCollitionRect( rect_, *(*itr)->getBoundingRect() ) )
                {
                    result = (*itr)->getHandle();

                    printf( "�� delete h:%d p:%p\n", result, this->findObject( result ) );

					this->deleteObject( *itr );
					break;
                }
            }
        }
    }
    return result;
}

//
// GameObjectManager::CollisionToObject
//
// @param[u32] obj_type_ : �Ώۂ̃I�u�W�F�N�g�^�C�v
// @param[LRect]   rect_ : �Ώۂ̋�`
// @param[LVector2]dist_ : �I�u�W�F�N�g�ƑΏۋ�`�̒��S���W�̋���
// @param[LVector2] over_: �I�u�W�F�N�g�Ƃ̂߂荞�ݗ� (�߂��ׂ�����)
// @return[u32]          : ���X�g�̒��̓������Ă����I�u�W�F�N�g�̎��
//
//    �n���ꂽ��`�ƃ��X�g���̋�`���r
//    �������Ă����ꍇObjectType��Ԃ�
//
u32 GameObjectManager::CollisionToObject( const u32 obj_type_, LRect rect_, LVector2* dist_, LVector2* over_ )
{
    const LRect* rc;

	// [�דc]
	GameObjectList::iterator itr = this->m_dqObjectList.begin();
    GameObjectList::iterator end = this->m_dqObjectList.end();

    /*
	LRect player_rect;
	player_rect.set( rect_.X, rect_.Y, rect_.width, rect_.height );

   	LRect target_rect;
	

	int distance_x = 0;
	int distance_y = 0;

	int player_worldwidth = player_rect.X + player_rect.width;
	int player_worldheight = player_rect.Y - player_rect.height;
    */

    dist_->set( 0, 0 );
    over_->set( 0, 0 );

    // �����̃��[���h��̍��A��A�E�A���A�����̒��S�B
    // �� > �� �ȓ_�ɒ��ӁB���̕��� 0 �ɋ߂��B
    int pl = rect_.x;
    int pt = rect_.y;
    int pr = rect_.x + rect_.width;
    int pb = rect_.y - rect_.height;
    LVector2 pc( pl + ( pr - pl ) / 2, pb + ( pt - pb ) / 2 );
    LVector2 start_pc( pc );

	// ���s������0, 0��Ԃ�
	u32 result = OBJ_UNDEF;



	for ( ; itr != end; ++itr )
	{
		u32 target_type = ( *itr )->getObjType();

		// �I�u�W�F�N�g�Ǝw��OBJ�ȊO�̃I�u�W�F�N�g�Ƃ̓����蔻��
		if ( target_type != OBJ_UNDEF
			&& target_type != OBJ_CHARACTER
			&& target_type != OBJ_ENEMY
			&& target_type != OBJ_WEAPON )
        {
            // [�R�{] NULL �Q�Ɖ���̂��߁A������ƏC��
            rc = ( *itr )->getBoundingRect();
			if ( rc )
			{
                // �^�[�Q�b�g�̃��[���h��̍��A��A�E�A���A�����̒��S�B
                int tl = rc->x;
                int tt = rc->y;
                int tr = rc->x + rc->width;
                int tb = rc->y - rc->height;
                LVector2 tc( tl + ( tr - tl ) / 2, tb + ( tt - tb ) / 2 );

                //printf( "p %d %d %d %d\n", pl, pt, pr, pb );
                //printf( "t %d %d %d %d\n", tl, tt, tr, tb );

                bool is_col_width  = ( pl <= tr && pr >= tl );  // ���E���������Ă��邩�`�F�b�N
                bool is_col_height = ( pt >= tb && pb <= tt );  // �㉺���������Ă��邩�`�F�b�N

                // �������Ă���ꍇ
                if ( is_col_width && is_col_height )
                {
                    result = target_type;

                    

                    // ������Ԃ������ꍇ�ȂǁA�c�������̍��̕����傫���ꍇ
                    if ( abs( pc.x - tc.x ) > abs( pc.y - tc.y ) )
                    {
                        // �������Ώۂ̍��ɂ���ꍇ
                        if ( pc.x < tc.x )
                        {
                            over_->x = tl - pr - 1;     // ���̒l�̓}�C�i�X�ɂȂ�
                        }
                        // �������Ώۂ̉E�ɂ���ꍇ
                        else
                        {
                            over_->x = tr - pl + 1;     // ���̒l�̓v���X�ɂȂ�
                        }
                    }
                    // �ォ�������ꍇ�ȂǁA�������c�̍��̕����傫���ꍇ
                    else
                    {
                        // �������Ώۂ̉��ɂ���ꍇ
                        if ( pc.y < tc.y )
                        {
                            over_->y = tb - pt;     // ���̒l�̓}�C�i�X�ɂȂ�
                        }
                        // �������Ώۂ̏�ɂ���ꍇ
                        else
                        {
                            over_->y = tt - pb;     // ���̒l�̓v���X�ɂȂ�
                        }
                    }

                    
                    // ��̒��S���W�̋���
                    dist_->set( tc.x - pc.x, tc.y - pc.y );

                    break;

                    /*
                    //dist_->x += tc.X - pc.X;
                    //dist_->y += tc.Y - pc.Y;


                    if ( target_type == OBJ_BOX )
                    {
                        //rect_.X += dist_->x;
                        //rect_.Y += dist_->y;

                        


                        pl = pl + over_->x;
                        pt = pt + over_->y;
                        pr = pl + rect_.width;
                        pb = pt - rect_.height;
                        pc.set( pl + ( pr - pl ) / 2, pb + ( pt - pb ) / 2 );

                        over_->set( pc.X - start_pc.X, pc.Y - start_pc.Y );

                        over_->dump();

                        
                    }
                    else
                    {
                        break;
                    }
                    */
                }
                

                

                /*

                target_rect = *rc;

				// ������
				int target_worldwidth  = target_rect.X + target_rect.width;
				int target_worldheight = target_rect.Y - target_rect.height;

				bool hit_side = false;
				bool hit_height = false;

				// �v���C�����E obj		->	player
				if ( target_rect.X <= player_rect.X
					&& player_rect.X <= target_worldwidth )
				{
					over_->x = static_cast< float >( player_rect.X - target_worldwidth );
					dist_->x = static_cast< float >(
						( target_rect.X + target_rect.width*0.5f )
						- ( player_rect.X + player_rect.width*0.5f ) );
					hit_side = true;
				}
				// �v���C������ player	<-	obj
				else if ( player_rect.X < target_rect.X
					&& target_rect.X < player_worldwidth )
				{
					over_->x = static_cast< float >( player_worldwidth - target_rect.X );
					dist_->x = static_cast< float >(
						( target_rect.X + target_rect.width*0.5f )
						- ( player_rect.X + player_rect.width*0.5f ) );
					hit_side = true;
				}

				if ( hit_side )
				{
					// �v���C������
					if ( target_rect.Y <= player_rect.Y
						&& player_worldheight <= target_rect.Y )
					{
						over_->y = static_cast< float >( player_worldheight - target_rect.Y );
						dist_->y = static_cast< float >(
							( player_rect.Y - player_rect.height*0.5f )
							- ( target_rect.Y - target_rect.height*0.5f ) );
						hit_height = true;
					}
					// �v���C������
					else if ( player_rect.Y <= target_rect.Y
						&& target_worldheight <= player_rect.Y )
					{
						over_->y = static_cast< float >( target_worldheight - player_rect.Y );
						dist_->y = static_cast< float >(
							( target_rect.Y - target_rect.height*0.5f )
							- ( player_rect.Y - player_rect.height*0.5f ) );
						hit_height = true;
					}

					if ( hit_height )
					{
						break;
					}
				}
                */
			}
		}
		/*else
		{
			result = OBJ_UNDEF;
		}*/
	}

	if ( itr != end )
	{
		// �v���C���[��p�A�C�e���ɐG��Ă����ꍇ
		if ( OBJ_ITEM_BEGIN < result && result < OBJ_ITEM_END )
		{
			// �v���C���[��
			if ( obj_type_ == OBJ_CHARACTER )
			{
				//�X�R�A�̏���
				switch(result)
				{
				case OBJ_CURE_S:
					//GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(500*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*(GameManager::getInstance()->getRank()+1)));          
					break;
				case OBJ_CURE_M:
					GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(1000*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*(GameManager::getInstance()->getRank()+1))); 
					break;
				case OBJ_CURE_L:
					GameManager::getInstance()->setScore(GameManager::getInstance()->getScore()+(2000*(GameManager::getInstance()->getFloorNum()+1)*GameManager::getInstance()->getPlayer()->getLife()*(GameManager::getInstance()->getRank()+1))); 
					break;
				}
				//this->deleteObject( *itr );  // �I�u�W�F�N�g������
			}
			else // �v���C���[�ȊO��
			{
				result = OBJ_UNDEF;      // ���ɂ��G��Ă��Ȃ��Ƃ���
			}
		}
	}

	if ( result == OBJ_UNDEF )
	{
		dist_->set( 0, 0 );
		over_->set( 0, 0 );
	}

	return result;
}


//---------------------------------------------------------------------
///**
//  @brief      �w�肵����ނ̃I�u�W�F�N�g���폜����
//
//  @param[in]  target_type_  : �Ώۂ̎��
//
//  @return     ���������I�u�W�F�N�g�̃n���h��
//*/
//---------------------------------------------------------------------
u32 GameObjectManager::removeObject( ObjectType target_type_ )
{
	u32 cnt = 0;
    GameObjectList::iterator itr = m_dqObjectList.begin();
    GameObjectList::iterator end = m_dqObjectList.end();
    for ( ; itr != end; ++itr )
    {
        if ( (*itr)->getObjType() == target_type_ )
        {
			++cnt;
			(*itr)->setExit(true);
        }
    }
    return cnt;
}


//---------------------------------------------------------------------
///**
//  @brief      �v���C���[�ȊO�̃I�u�W�F�N�g���폜����
//
//  @return     
//*/
//---------------------------------------------------------------------
void GameObjectManager::deleteStageObject()
{
    GameObjectList::iterator itr = m_dqObjectList.begin();
    GameObjectList::iterator end = m_dqObjectList.end();
    for ( ; itr != end; ++itr )
    {
        if ( (*itr)->getObjType() != OBJ_CHARACTER )
        {
			(*itr)->setExit(true);
        }
    }
    return;
}

//=============================================================================
//								End of File
//=============================================================================
