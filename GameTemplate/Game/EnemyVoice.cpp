#include "stdafx.h"
#include "EnemyInclude.h"

namespace nsHikageri
{
	namespace nsEnemy
	{
		EnemyVoice::~EnemyVoice()
		{

		}

		void EnemyVoice::Init(Enemy* enemy)
		{
			m_enemy = enemy;
		}

		void EnemyVoice::ExecuteUpdate()
		{
			switch (m_enemy->GetEnemyState())
			{
			case Enemy::enState_SearchPlayer:

				break;
			case Enemy::enState_Chase:

				break;
			case Enemy::enState_Attack:

				break;
			case Enemy::enState_Scream:

				break;
			case Enemy::enState_Flinch:

				break;
			case Enemy::enState_Petrifaction:

				break;
			case Enemy::enState_Suffer:

				break;
			case Enemy::enState_Vigilant:

				break;
			default:
				break;
			}
		}
	}
}