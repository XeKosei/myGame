#include "stdafx.h"
#include "EnemyInclude.h"
#include "Player.h"
#include "PlayerHP.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyAttackConstant;
		void EnemyAttack::ExecuteUpdate()
		{
			m_enemy->GetPlayer()->GetPlayerHP()->Damage(34);
			m_enemy->SetEnemyState(Enemy::enState_Chase);
		}

		void EnemyAttack::Attack()
		{
			
		}
	}
}