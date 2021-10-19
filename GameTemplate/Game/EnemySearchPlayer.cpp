#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemySearchPlayerConstant;

		void EnemySearchPlayer::ExecuteUpdate()
		{
			//�G�l�~�[�̈ʒu����v���C���[�̈ʒu�ւ̃x�N�g�������߂�
			Vector3 toTargetDir = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_position;
			toTargetDir.Normalize();

			//�G�l�~�[�̌����Ƃ̓��ς����ȏ�Ȃ�A�v���C���[��ǂ������n�߂�B
			if (Dot(toTargetDir, nsEnemyConstant::INI_ENEMY_DIRECTION) >= 0.9f)
			{
				m_enemy->SetEnemyState(Enemy::enState_Chase);
			}
		}
	}
}