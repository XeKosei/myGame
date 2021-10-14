#include "stdafx.h"
#include "PlayerCamera.h"
#include "Player.h"
#include "PlayerConstant.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerCameraConstant;

		bool PlayerCamera::Start()
		{
			m_plEyeHeight = INI_PLAYER_EYE_HEIGHT;
			return true;
		}

		//Player.cpp��Update()�ŌĂяo������
		void PlayerCamera::ExecuteUpdate()
		{
			//�O�t���[���̃J�����̈ʒu���擾
			Vector3 oldCameraDir = m_cameraDir;

			//R�X�e�B�b�N�̌X�����擾
			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();

			//R�X�e�B�b�N�̌X������A�J�����̌������v�Z�B
			m_cameraDir += g_camera3D->GetRight() * x * CAMERA_MOVE_SPEED;
			m_cameraDir += g_camera3D->GetUp() * y * CAMERA_MOVE_SPEED;
			m_cameraDir.Normalize();

			//�J�������ォ���Ɍ����������ꍇ�A����ȏ�͏㉺�Ɍ����Ȃ��悤�ɂ���B
			if (m_cameraDir.y >= 0.9f || m_cameraDir.y <= -0.9f)
			{
				m_cameraDir.y = oldCameraDir.y;
			}

			//�ȈՃN�C�b�N�^�[��(����)
			if (g_pad[0]->IsTrigger(enButtonB) && g_pad[0]->GetLStickYF() < -0.8f)
			{
				m_cameraDir.x *= -1.0f;
				m_cameraDir.z *= -1.0f;
				m_cameraDir.y = 0.0f;
			}

			//�J�����̈ʒu���v�Z����B
			m_cameraPos = m_player->GetPosition();
			//�J�����̈ʒu���A�v���C���[�̖ڂ̍����ɂ���B
			m_cameraPos.y += m_plEyeHeight;
			//�J�����̈ʒu����A�J�����̌����Ă�������Ɉ��ȏ���������ʒu�𒍎��_�Ƃ��Đݒ肷��B
			Vector3 cameraTarget = m_cameraPos + m_cameraDir * TO_CAMERA_TARGET_DIS;

			g_camera3D->SetPosition(m_cameraPos);
			g_camera3D->SetTarget(cameraTarget);
				
			g_camera3D->Update();
		}
	}
}