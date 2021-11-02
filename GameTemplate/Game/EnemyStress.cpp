#include "stdafx.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyStressConstant;
		void EnemyStress::ExecuteUpdate()
		{
			if (m_stressNum >= MAX_STRESS_NUM)
			{
				m_stressNum = 0;
				m_enemy->SetEnemyState(Enemy::enState_Suffer);
			}
		}

		void EnemyStress::Suffer()
		{
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_enemy->SetEnemyState(Enemy::enState_SearchPlayer);
			}
		}

		void EnemyStress::AddStress(int num)
		{
			m_stressNum += num;
			if (m_stressNum >= MAX_STRESS_NUM)
			{
				m_stressNum = MAX_STRESS_NUM;
			}
		}
		void EnemyStress::SubStress(int num)
		{
			m_stressNum -= num;
			if (m_stressNum <= 0)
			{
				m_stressNum = 0;
			}
		}
	}
}