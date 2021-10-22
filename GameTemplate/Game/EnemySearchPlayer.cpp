#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemySearchPlayerConstant;

		bool EnemySearchPlayer::Start()
		{
			m_position = m_searchPos[0];
			return true;
		}

		void EnemySearchPlayer::ExecuteUpdate()
		{
			//�ړ�����(��)
			Move();
			Turn();

			//�G�l�~�[�̈ʒu����v���C���[�̈ʒu�ւ̃x�N�g�������߂�
			Vector3 toTargetDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_position;
			toTargetDir.Normalize();

			//�G�l�~�[�̌����Ƃ̓��ς����ȏ�Ȃ�A�v���C���[��ǂ������n�߂�B
			if (Dot(toTargetDir, m_dir) >= 0.9f)
			{
				m_enemy->SetEnemyState(Enemy::enState_Chase);
			}
		}

		void EnemySearchPlayer::Move()
		{
			if (m_searchFlag == false)
			{
				m_targetPos = m_searchPos[1];		
			}
			else
			{
				m_targetPos = m_searchPos[0];
			}

			m_dir = m_targetPos - m_position;
			m_dir.Normalize();

			m_velocity = m_dir * ENEMY_WALK_SPEED;
			m_position = m_enemy->GetCharaCon()->Execute(m_velocity, 1.0f);
			m_enemy->GetEnemyModel()->SetPosition(m_position);

			if ((m_targetPos - m_position).Length() <= 5.0f)
			{
				m_searchFlag = !m_searchFlag;
			}

		}
		void EnemySearchPlayer::Turn()
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