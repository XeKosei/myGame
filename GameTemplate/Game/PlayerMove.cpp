#include "stdafx.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsPlayer
	{
		using namespace nsPlayerMoveConstant;

		PlayerMove::~PlayerMove()
		{

		}

		void PlayerMove::Init(Player* pl)
		{
			m_player = pl;
		}

		//Player.cpp��Update()�ŌĂяo������
		void PlayerMove::ExecuteUpdate()
		{
			Move();
			Turn();
		}

		void PlayerMove::Move()
		{
			if (m_player->GetPlayerAction()->GetCrouchDownFlag() == true)
			{
				m_plMoveSpeed = PLAYER_CROUCHDOWN_WALK_SPEED;
			}
			//B�{�^����������Ă�����A�O���ɂ̂݃_�b�V���ł���B
			else if (g_pad[0]->IsPress(enButtonB) && g_pad[0]->GetLStickYF() >= 0.77f)
			{
				m_plMoveSpeed = PLAYER_DASH_SPEED;
			}
			else
			{
				m_plMoveSpeed = PLAYER_WALK_SPEED;
			}

			//�X�e�B�b�N�̌X������v���C���[�̑��x���v�Z
			Vector3 xSpeed = g_camera3D->GetRight() * g_pad[0]->GetLStickXF();
			Vector3 ySpeed = Cross(g_camera3D->GetRight(), Vector3::AxisY) * g_pad[0]->GetLStickYF();
			m_velocity += (xSpeed + ySpeed) * m_plMoveSpeed * GameTime::GetInstance().GetFrameDeltaTime();

			//��������
			m_velocity.x -= m_velocity.x * PLAYER_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * PLAYER_MOVE_FRICTION;

			//�d��
			if (m_player->GetCharaCon()->IsOnGround() == false) 
			{	//�n�ʂɂ��Ă��Ȃ�������
				m_velocity.y -= pow(GRAVITY_SPEED, GRAVITY_INDEX);	//�d�͂�^����
			}

			//���x���ق�0�Ȃ�΁A0�ɂ���B
			if (fabsf(m_velocity.x + m_velocity.z) < 0.001f)
			{
				m_velocity.x = 0.0f;
				m_velocity.z = 0.0f;
			}

			//�ʒu�ɑ��x�����Z
			m_position = m_player->GetCharaCon()->Execute(m_velocity, 1.0f);
			//m_position += m_velocity;
			//�ʒu��ݒ肷��B
			m_player->GetPlayerModel()->SetPosition(m_position);
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
				m_player->GetPlayerModel()->SetRotation(m_qRot);
			}
		}
	}
}