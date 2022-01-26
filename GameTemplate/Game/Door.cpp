#include "stdafx.h"
#include "Door.h"
#include "GimmickConstant.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h"

namespace nsHikageri
{
	namespace nsGimmick
	{
		using namespace nsDoorConstant;

		Door::~Door()
		{
			DeleteGO(m_doorModel);
		}

		bool Door::Start()
		{
			m_doorModel = NewGO<SkinModelRender>(0);
			switch (m_doorColor)
			{
			case enDoorColor_Red:
				m_doorModel->Init("Assets/modelData/RedDoor.tkm");
				break;
			case enDoorColor_Blue:
				m_doorModel->Init("Assets/modelData/BlueDoor.tkm");
				break;
			case enDoorColor_Green:
				m_doorModel->Init("Assets/modelData/GreenDoor.tkm");
				break;
			case enDoorColor_Yellow:
				m_doorModel->Init("Assets/modelData/YellowDoor.tkm");
				break;
			case enDoorColor_Purple:
				m_doorModel->Init("Assets/modelData/PurpleDoor.tkm");
				break;
			case enDoorColor_White:
				m_doorModel->Init("Assets/modelData/WhiteDoor.tkm");
				break;
			default:
				m_doorModel->Init("Assets/modelData/Door.tkm");
				break;
			}
			//�X�e�[�W�̃��f���̐ÓI�����I�u�W�F�N�g���쐬       
			//m_physicsStaticObject.CreateFromModel(m_doorModel->GetModel(), m_doorModel->GetModel().GetWorldMatrix());
			//���ÓI�����I�u�W�F�N�g���쐬������Ń��f���̍��W���]��ݒ肵�Ȃ��ƁA���ꂪ������B
			//�ʒu��ݒ�
			m_doorModel->SetPosition(m_position);

			//��]��ݒ�
			m_direction.Normalize();
			m_defaultAngle = atan2(m_direction.x, m_direction.z);
			m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle);
			m_doorModel->SetRotation(m_qRot);

			//�ÓI�����I�u�W�F�N�g�̈ʒu�Ɖ�]��ݒ�
			//m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);

			//phisicsStaticObject���ƁA�L�����R���Əd�Ȃ������ɂ������ȋ���������̂ŁA
			//�}篃L�����R���ɕύX
			//�L�����R����ݒ�
			m_charaCon.Init(
				DOOR_CHARACON_WIDTH,	//���a
				DOOR_CHARACON_HEIGHT,	//����
				m_centerPos//�����ʒu
			);

			m_executeCannotOpenCount = INI_DOOR_CANNOTOPEN_EXECUTECOUNT;

			return true;
		}

		void Door::Update()
		{
			PlayerTargetSetting();

			if (m_unlockFlag == true)
			{
				//�h�A�̏���
				Execute();
			}
			else
			{
				CannotOpen();
			}
		}

		void Door::PlayerTargetSetting()
		{
			//�h�A�̃Z���^�[�ʒu�����߂�
			if (m_openFlag == false)
				m_centerPos = m_position + Cross(m_direction, Vector3::AxisY) * DOOR_CENTER_POS_X;
			else
			{
				if (m_isOpenFromForward)
					m_centerPos = m_position + m_direction * DOOR_CENTER_POS_X;
				else 
					m_centerPos = m_position - m_direction * DOOR_CENTER_POS_X;
			}

			m_centerPos.y += DOOR_CENTER_POS_Y;

			Vector3 dis = m_centerPos - m_player->GetPlayerCamera()->GetCameraPos();
			m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//�v���C���[�Ƃ̋������߂��A�h�A�̕��������Ă�����
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= DOOR_CATCH_EYE_DOT)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Door);
				m_player->GetPlayerTarget()->SetTargetDoor(this);
			}

			m_charaCon.SetPosition(m_centerPos);
		}

		//�h�A�̏���
		void Door::Execute()
		{
			//�h�A���J���Ă��Ȃ��Ƃ�
			if (m_moveFlag == false)
			{
				//�h�A���J���Ƃ�
				if (m_openFlag == false)
				{
					//�G�l�~�[���߂��ɗ���ƁA�����J���B
					QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
						{
							float dis = (m_position - enemy->GetEnemyMove()->GetPosition()).Length();
							if (dis <= 200.0f)
							{
								m_moveFlag = true;

								//�G�l�~�[�Ƃ̈ʒu�֌W�ŁA�����O�ɊJ�������ɊJ���������߂�
								Vector3 toEnemyDir = m_centerPos - enemy->GetEnemyMove()->GetPosition();
								toEnemyDir.Normalize();
								float dot = Dot(m_direction, toEnemyDir);
								if (dot >= 0)
								{
									m_isOpenFromForward = true;
								}
								else
								{
									m_isOpenFromForward = false;
								}
							}
							return true;
						}
					);
				}
			}
			//�h�A���J���Ă���Ƃ�
			else
			{
				//�h�A���J���Ă���Ȃ�A����
				if (m_openFlag)
				{
					Close();
				}
				//�h�A�����Ă���Ȃ�A�J���B
				else
				{
					Open();
				}
			}
		}

		void Door::Open()
		{
			//�O����J����ꂽ�Ƃ�
			if (m_isOpenFromForward)
			{
				if (m_addAngle < MAX_DOOR_OPNE_ANGLE)
				{
					m_addAngle += DOOR_OPEN_SPEED;

				}
				else
				{
					//m_addAngle = MAX_DOOR_OPNE_ANGLE;
					m_moveFlag = false;
					m_openFlag = true;
				}
			}
			//��납��J����ꂽ�Ƃ�
			else
			{
				if (m_addAngle > -MAX_DOOR_OPNE_ANGLE)
				{
					m_addAngle -= DOOR_OPEN_SPEED;
				}
				else
				{
					//m_addAngle = -MAX_DOOR_OPNE_ANGLE;
					m_moveFlag = false;
					m_openFlag = true;
				}	
			}
			//��]��ݒ�
			m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
			m_doorModel->SetRotation(m_qRot);
			//m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);

			//SE
			SEManage(enDoorSound_Open);
		}

		void Door::Close()
		{
			//�O����J�����Ă���Ƃ�
			if (m_isOpenFromForward)
			{
				if (m_addAngle > 0.0f)
				{
					m_addAngle -= DOOR_OPEN_SPEED;
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = false;
				}
			}
			//��납��J�����Ă���Ƃ�
			else
			{
				if (m_addAngle < 0.0f)
				{
					m_addAngle += DOOR_OPEN_SPEED;
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = false;
				}
			}
			//��]��ݒ�
			m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
			m_doorModel->SetRotation(m_qRot);
			//m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);

			//SE
			SEManage(enDoorSound_Close);
		}

		void Door::CannotOpen()
		{
			//�t���O��true�Ȃ�A�K�`���K�`������B
			if (m_executeCannotOpenFlag)
			{
				//�K�`���K�`���������鎞�Ԃ��J�E���g
				m_executeCannotOpenCount--;

				//�O�ɓ���
				if (m_cannotOpenMoveForward)
				{
					m_addAngle += DOOR_CANNOTOPNE_MOVESPEED;
					if (m_addAngle >= MAX_CANNOTOPEN_ADDANGLE)
					{
						m_cannotOpenMoveForward = false;
					}
				}
				//���ɓ���
				else
				{
					m_addAngle -= DOOR_CANNOTOPNE_MOVESPEED;
					if (m_addAngle <= -MAX_CANNOTOPEN_ADDANGLE)
					{
						m_cannotOpenMoveForward = true;
					}
				}

				//�J�E���g���I������烊�Z�b�g
				if (m_executeCannotOpenCount <= 0)
				{
					m_executeCannotOpenCount = INI_DOOR_CANNOTOPEN_EXECUTECOUNT;
					m_executeCannotOpenFlag = false;
					m_cannotOpenMoveForward = false;
					m_addAngle = 0.0f;
				}

				//��]��ݒ�
				m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
				m_doorModel->SetRotation(m_qRot);

				//SE
				SEManage(enDoorSound_Locked);
			}
		}

		void Door::SEManage(EnDoorSounds soundKind)
		{
			if (m_canPlaySS == true)
			{
				if (m_ss != nullptr)
				{
					DeleteGO(m_ss);
					m_ss = nullptr;
				}
				switch (soundKind)
				{
				case enDoorSound_Locked:
					m_ss = NewGO<SoundSource>(0);
					m_ss->Init(L"Assets/sound/DoorLocked.wav");
					m_ss->Play(false);
					m_canPlaySS = false;
					break;
				case enDoorSound_Open:
					m_ss = NewGO<SoundSource>(0);
					m_ss->Init(L"Assets/sound/DoorOpen.wav");
					m_ss->Play(false);
					m_canPlaySS = false;
					break;
				case enDoorSound_Close:
					m_ss = NewGO<SoundSource>(0);
					m_ss->Init(L"Assets/sound/DoorClose.wav");
					m_ss->Play(false);
					m_canPlaySS = false;				
					break;
				default:
					break;
				}
			}
			else
			{
				switch (soundKind)
				{
				case enDoorSound_Locked:
					if (m_executeCannotOpenFlag == false)
						m_canPlaySS = true;
					break;
				case enDoorSound_Open:
					if (m_openFlag == true)
						m_canPlaySS = true;
					break;
				case enDoorSound_Close:
					if (m_openFlag == false)
						m_canPlaySS = true;
					break;
				default:
					break;
				}
			}
		}

		void Door::PlayerTouchDoor()
		{
			//�����������Ă���Ȃ�΁A�K�`���K�`�����鏈�����s���B
			if (m_unlockFlag == false)
			{
				m_executeCannotOpenFlag = true;
			}
			else if (m_moveFlag == false)
			{
				m_moveFlag = true;

				//�h�A���J���Ƃ�
				if (m_openFlag == false)
				{
					//�v���C���[�Ƃ̈ʒu�֌W�ŁA�����O�ɊJ�������ɊJ���������߂�
					float dot = Dot(m_direction, m_toPlayerDir);
					if (dot >= 0)
					{
						m_isOpenFromForward = true;
					}
					else
					{
						m_isOpenFromForward = false;
					}
				}
			}
		}
	}
}