#include "stdafx.h"
#include "Door.h"
#include "GimmickConstant.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h"

namespace nsHikageri
{
	namespace nsGimmick
	{
		bool Door::Start()
		{
			m_position = { 0.0f, 0.0f, 150.0f };
			m_direction = {-1.0f,0.0f,0.0f };
			m_direction.Normalize();
			m_defaultAngle = atan2(m_direction.x, m_direction.z);
			Quaternion qRot;
			qRot.SetRotation(Vector3::AxisY, m_defaultAngle);

			m_doorModel = NewGO<SkinModelRender>(0);
			m_doorModel->Init("Assets/modelData/Door.tkm");
			m_doorModel->SetPosition(m_position);
			m_doorModel->SetRotation(qRot);
			//�X�e�[�W�̃��f���̐ÓI�����I�u�W�F�N�g���쐬       
			//m_physicsStaticObject.CreateFromModel(m_doorModel->GetModel(), m_doorModel->GetModel().GetWorldMatrix());

			return true;
		}

		void Door::Update()
		{
			//�h�A�������Ă��Ȃ��Ƃ�
			if (m_moveFlag == false)
			{
				//�{�^���������ꂽ��A�h�A�������n�߂�B(�J�������邩)
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					m_moveFlag = true;
					
					//�h�A���J���Ƃ�
					if (m_openFlag == false)
					{
						//�v���C���[�ւ̌���
						Vector3 m_toPlayerDir = m_player->GetPlayerMove()->GetPosition() - m_position;
						m_toPlayerDir.Normalize();
						//�v���C���[�Ƃ̈ʒu�֌W�ŁA�����O�ɊJ�������ɊJ���������߂�
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
			//�h�A�������Ă���Ƃ�
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
			//�O���炠����ꂽ�Ƃ�
			if (m_isOpenFromForward)
			{
				if (m_addAngle > -3.14f / 2)
				{
					m_addAngle -= 0.1f;
					Quaternion qRot;
					qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
					m_doorModel->SetRotation(qRot);
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = true;
				}
			}
			else
			{
				if (m_addAngle < 3.14f / 2)
				{
					m_addAngle += 0.1f;
					Quaternion qRot;
					qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
					m_doorModel->SetRotation(qRot);
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = true;
				}	
			}
		}

		void Door::Close()
		{
			if (m_isOpenFromForward)
			{
				if (m_addAngle < 0.0f)
				{
					m_addAngle += 0.1f;
					Quaternion qRot;
					qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
					m_doorModel->SetRotation(qRot);
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = false;
				}
			}
			else
			{
				if (m_addAngle > 0.0f)
				{
					m_addAngle -= 0.1f;
					Quaternion qRot;
					qRot.SetRotation(Vector3::AxisY, m_defaultAngle + m_addAngle);
					m_doorModel->SetRotation(qRot);
				}
				else
				{
					m_moveFlag = false;
					m_openFlag = false;
				}
			}
		}
	}
}