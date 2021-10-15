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
			

		}

		void EnemyAttack::Attack()
		{
			m_enemy->GetPlayer()->GetPlayerHP()->Damage(100);
			m_enemy->GetEnemyState()->SetEnemyState(EnemyState::enState_Chase);
		}
	}
}