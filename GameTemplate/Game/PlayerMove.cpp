#include "stdafx.h"
#include "PlayerMove.h"
#include "Player.h"
#include "PlayerConstant.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerMoveConstant;

		bool PlayerMove::Start()
		{
			return true;
		}

		void PlayerMove::ExecuteUpdate()
		{
			Move();
			Turn();
		}

		void PlayerMove::Move()
		{
			//�X�e�B�b�N�̌X������v���C���[�̑��x���v�Z
			Vector3 xSpeed = g_camera3D->GetRight() * g_pad[0]->GetLStickXF();
			Vector3 ySpeed = Cross(g_camera3D->GetRight(), Vector3::AxisY) * g_pad[0]->GetLStickYF();
			m_velocity = (xSpeed + ySpeed) * PLAYER_MOVE_SPEED;

			//�v���C���[���㉺�ɓ�����
			m_velocity.y = 0.0f;

			if (g_pad[0]->IsPress(enButtonRB2))
				m_velocity.y += 10.0f;
			if (g_pad[0]->IsPress(enButtonLB2))
				m_velocity.y -= 10.0f;

			//�ʒu�ɑ��x�����Z
			m_position += m_velocity;
			//�ʒu��ݒ肷��B
			m_player->SetPosition(m_position);
		}

		void PlayerMove::Turn()
		{
			if (g_pad[0]->IsPress(enButtonLB1) == false)
			{
				//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
				//cameraDir.x / cameraDir.z�̌��ʂ�tan�ƂɂȂ�B
				//atan2���g�p���āA�p�x�����߂Ă���B
				//���ꂪ��]�p�x�ɂȂ�B
				Vector3 cameraDir = g_camera3D->GetForward();
				cameraDir.y = 0.0f;
				float angle = atan2(cameraDir.x, cameraDir.z);
				//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
				//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
				m_qRot.SetRotation(Vector3::AxisY, angle);
				m_player->SetRotation(m_qRot);
			}
		}
	}
}