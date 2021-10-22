#include "stdafx.h"
#include "EnemyInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		void EnemyScream::Executeupdate()
		{
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_enemy->SetEnemyState(Enemy::enState_Chase);
			}
		}
	}
}