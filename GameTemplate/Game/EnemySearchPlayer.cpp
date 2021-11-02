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
			//�����ʒu���w��
			m_enemy->GetEnemyMove()->SetPosition(m_searchPos[0]);
			return true;
		}

		void EnemySearchPlayer::ExecuteUpdate()
		{
			//�ړ�����(��)
			Search();

			//�G�l�~�[�̈ʒu����v���C���[�̈ʒu�ւ̃x�N�g�������߂�
			Vector3 toPlayerDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();
			toPlayerDir.Normalize();

			//�G�l�~�[�̌����Ƃ̓��ς����ȏ�Ȃ�A�v���C���[��ǂ������n�߂�B
			if (Dot(toPlayerDir, m_enemy->GetEnemyMove()->GetDirection()) >= 0.9f)
			{
				m_enemy->SetEnemyState(Enemy::enState_Scream);
			}
		}

		void EnemySearchPlayer::Search()
		{
			//�w�肵���񂩏��̈ʒu���������鏈��

			//�G�l�~�[�̈ړ��̑�����ݒ�
			m_enemy->GetEnemyMove()->SetMoveSpeed(nsEnemyMoveConstant::ENEMY_WALK_SPEED);

			//�G�l�~�[���������ʒu��ݒ肷��B
			if (m_searchFlag == false)
			{
				m_enemy->GetEnemyMove()->SetTarget(m_searchPos[1]);		
			}
			else
			{
				m_enemy->GetEnemyMove()->SetTarget(m_searchPos[0]);
			}

			//�G�l�~�[�̈ʒu���قڃ^�[�Q�b�g�ƈꏏ�ɂȂ�����A
			if ((m_enemy->GetEnemyMove()->GetTarget() - m_enemy->GetEnemyMove()->GetPosition()).Length() <= 5.0f)
			{
				m_searchFlag = !m_searchFlag;
			}

		}
	}
}