#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyMoveConstant;

		bool EnemyMove::Start()
		{
			return true;
		}

		//Enemy.cpp��Update()�ŌĂяo������
		void EnemyMove::ExecuteUpdate()
		{
			Move();
			Turn();
		}

		void EnemyMove::Move()
		{
			m_targetPos = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition();
			//�X�e�B�b�N�̌X������v���C���[�̑��x���v�Z
			m_velocity = m_targetPos - m_position;
			m_velocity.Normalize();
			m_velocity *= ENEMY_WALK_SPEED;

			//��������
			m_velocity.x -= m_velocity.x * ENEMY_MOVE_FRICTION;
			m_velocity.z -= m_velocity.z * ENEMY_MOVE_FRICTION;

			//�d��
			if (m_enemy->GetCharaCon()->IsOnGround() == false)
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
			m_position = m_enemy->GetCharaCon()->Execute(m_velocity, 1.0f);
			//�ʒu��ݒ肷��B
			m_enemy->GetEnemyModel()->SetPosition(m_position);
		}

		void EnemyMove::Turn()
		{
			if (m_velocity.x != 0.0f || m_velocity.z != 0.0f)
			{
				//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
				//cameraDir.x / cameraDir.z�̌��ʂ�tan�ƂɂȂ�B
				//atan2���g�p���āA�p�x�����߂Ă���B
				//���ꂪ��]�p�x�ɂȂ�B
				float angle = atan2(m_velocity.x, m_velocity.z);
				//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
				//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
				m_qRot.SetRotation(Vector3::AxisY, angle);
				m_enemy->GetEnemyModel()->SetRotation(m_qRot);
			}
		}
	}
}