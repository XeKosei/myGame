#include "stdafx.h"
#include "EnemyInclude.h"


namespace nsHikageri
{
	namespace nsEnemy
	{
		void EnemyFlinch::ExecuteUpdate()
		{
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_enemy->SetEnemyState(Enemy::enState_Scream);
			}
		}

		void EnemyFlinch::Mineralization()
		{
			m_enemy->GetEnemyModel()->SetStoneRenderFlag(true);
		}
	}
}