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
			m_physicsStaticObject.CreateFromModel(m_doorModel->GetModel(), m_doorModel->GetModel().GetWorldMatrix());
			//���ÓI�����I�u�W�F�N�g���쐬������Ń��f���̍��W���]��ݒ肵�Ȃ��ƁA���ꂪ������B
			//�ʒu��ݒ�
			m_doorModel->SetPosition(m_position);

			//��]��ݒ�
			m_direction.Normalize();
			m_defaultAngle = atan2(m_direction.x, m_direction.z);
			m_qRot.SetRotation(Vector3::AxisY, m_defaultAngle);
			m_doorModel->SetRotation(m_qRot);

			//�ÓI�����I�u�W�F�N�g�̈ʒu�Ɖ�]��ݒ�
			m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);

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
			Vector3 centerPos;
			if (m_openFlag == false)
				centerPos = m_position + Cross(m_direction, Vector3::AxisY) * 100.0f;
			else
			{
				if (m_isOpenFromForward)
					centerPos = m_position + m_direction * 100.0f;
				else 
					centerPos = m_position - m_direction * 100.0f;
			}

			centerPos.y += 200.0f;

			Vector3 dis = centerPos - m_player->GetPlayerCamera()->GetCameraPos();
			m_toPlayerDir = dis;
			m_toPlayerDir.Normalize();

			//�v���C���[�Ƃ̋������߂��A�h�A�̕��������Ă�����
			if (dis.Length() <= nsPlayer::nsPlayerTargetConstant::CATCH_EYES_DIS
				&& Dot(m_player->GetPlayerCamera()->GetDirection(), m_toPlayerDir) >= 0.707f)
			{
				m_player->GetPlayerTarget()->SetTarget(nsPlayer::PlayerTarget::enTarget_Door);
				m_player->GetPlayerTarget()->SetTargetDoor(this);
			}
		}

		//�h�A�̏���
		void Door::Execute()
		{
			//�h�A���J���Ă��Ȃ��Ƃ�
			if (m_moveFlag == false)
			{
				//�v���C���[�̃^�[�Q�b�g�����̃h�A�ŁAA�{�^���������ꂽ��A�h�A���J��
				if (g_pad[0]->IsTrigger(enButtonA)
					&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Door
					&& m_player->GetPlayerTarget()->GetTargetDoor() == this )
				{
					m_moveFlag = true;

					//�h�A���J���Ƃ�
					if (m_openFlag == false)
					{
						//�v���C���[�Ƃ̈ʒu�֌W�ŁA�����O�ɊJ�������ɊJ���������߂�
						float dot = Dot(m_direction, m_toPlayerDir);
						if (Dot(m_direction, m_toPlayerDir) >= 0)
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
			m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);
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
			m_physicsStaticObject.SetPositionAndRotation(m_position, m_qRot);
		}

		void Door::CannotOpen()
		{
			//�v���C���[�̃^�[�Q�b�g�����̃h�A�ŁAA�{�^���������ꂽ��A�t���O��true�ɁB
			if (g_pad[0]->IsTrigger(enButtonA)
				&& m_player->GetPlayerTarget()->GetTarget() == nsPlayer::PlayerTarget::enTarget_Door
				&& m_player->GetPlayerTarget()->GetTargetDoor() == this)
			{
				m_executeCannotOpenFlag = true;
			}

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
			}
		}
	}
}