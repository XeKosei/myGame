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
			return true;
		}

		void PlayerCamera::ExecuteUpdate()
		{
			//R�X�e�B�b�N�̌X�����擾
			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();

			//R�X�e�B�b�N�̌X������A�J�����̌������v�Z�B
			m_cameraDir += g_camera3D->GetRight() * x * CAMERA_MOVE_SPEED;
			m_cameraDir += g_camera3D->GetUp() * y * CAMERA_MOVE_SPEED;
			m_cameraDir.Normalize();

			//�J�����̈ʒu���v�Z����B
			m_cameraPos = m_player->GetPosition();
			//�J�����̈ʒu���A�v���C���[�̖ڂ̍����ɂ���B
			m_cameraPos.y += PLAYER_EYES_HEIGHT;
			//�J�����̈ʒu����A�J�����̌����Ă�������Ɉ��ȏ���������ʒu�𒍎��_�Ƃ��Đݒ肷��B
			Vector3 cameraTarget = m_cameraPos + m_cameraDir * TO_CAMERA_TARGET_DIS;

			g_camera3D->SetPosition(m_cameraPos);
			g_camera3D->SetTarget(cameraTarget);
			
		}
	}
}