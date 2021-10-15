#include "stdafx.h"
#include "EnemyInclude.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyStateConstant;
		
		void EnemyState::ExecuteUpdate()
		{
			switch (m_enemyStates)
			{
			case enState_SearchPlayer:
				SearchPlayer();
				break;
			case enState_Chase:
				Chase();
				break;
			case enState_Attack:
				m_enemy->GetEnemyAttack()->Attack();
				break;
			default:
				break;
			}
		}

		void EnemyState::SearchPlayer()
		{
			


		}

		void EnemyState::Chase()
		{
			//プレイヤーとの距離を計算
			Vector3 dis = m_enemy->GetPlayer()->GetPlayerMove()->GetPosition() - m_enemy->GetEnemyMove()->GetPosition();
			if (dis.Length() <= ENEMY_CAN_ATTACK_DIS)
			{
				m_enemyStates = enState_Attack;
			}
		}


	}
}