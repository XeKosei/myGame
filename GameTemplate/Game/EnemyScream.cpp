#include "stdafx.h"
#include "EnemyInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		EnemyScream::~EnemyScream()
		{

		}

		void EnemyScream::ExecuteUpdate()
		{
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_enemy->SetEnemyState(Enemy::enState_Chase);
			}
		}
	}
}