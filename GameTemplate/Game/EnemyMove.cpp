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

		void EnemyMove::ExecuteUpdate()
		{
			Move();
			Turn();
		}

		void EnemyMove::Move()
		{
			//�^�[�Q�b�g�ƃG�l�~�[�Ƃ̃x�N�g�����v�Z�B
			m_direction = m_targetPos - m_position;
			m_direction.Normalize();

			//�ړ�����
			if (m_slowMoveFlag == false)
				m_velocity = m_direction * m_moveSpeed;
			else
				m_velocity = m_direction * ENEMY_SLOWWALK_SPEED;

			m_velocity *= GameTime::GetInstance().GetFrameDeltaTime();

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

			//�^�[�Q�b�g�n�_�ɂقړ��B������A
			if ((m_position - m_targetPos).Length() < 5.0f)
			{
				m_position = m_targetPos;
				m_enemy->GetCharaCon()->SetPosition(m_position);
			}
			
			//���f���ʒu��ݒ肷��B
			m_enemy->GetEnemyModel()->SetPosition(m_position);	
		}

		void EnemyMove::Turn()
		{
			if (m_velocity.x != 0.0f || m_velocity.z != 0.0f)
			{
				//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
				//m_direction.x / m_direction.z�̌��ʂ�tan�ƂɂȂ�B
				//atan2���g�p���āA�p�x�����߂Ă���B
				//���ꂪ��]�p�x�ɂȂ�B
				float angle = atan2(m_direction.x, m_direction.z);
				//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
				//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
				m_qRot.SetRotation(Vector3::AxisY, angle);
				m_enemy->GetEnemyModel()->SetRotation(m_qRot);
			}
		}
	}
}