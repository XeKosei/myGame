#include "stdafx.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsEnemy
	{
		using namespace nsEnemyStressConstant;

		EnemyStress::~EnemyStress()
		{

		}

		void EnemyStress::Init(Enemy* enemy)
		{
			m_enemy = enemy;
		}

		void EnemyStress::ExecuteUpdate()
		{
			//ストレス値が前フレームの値と同じか下回っているとき、ストレスを受けていない。
			if (m_stressNum <= m_oldStressNum)
			{
				SubStress(SUB_STRESS_SPEED);
				m_enemy->GetEnemyMove()->SetSlowMoveFlag(false);
			}

			if (m_stressNum >= MAX_STRESS_NUM)
			{
				m_stressNum = 0;
				m_enemy->SetEnemyState(Enemy::enState_Suffer);
			}

			m_oldStressNum = m_stressNum;
		}

		void EnemyStress::Suffer()
		{
			if (m_enemy->GetEnemyModel()->IsPlayingAnimation() == false)
			{
				m_enemy->SetEnemyState(Enemy::enState_SearchPlayer);
				//m_enemy->GetEnemySearchPlayer()->CalcNextSearchPos();
				m_enemy->GetEnemyMove()->RouteSearch(m_enemy->GetEnemyMove()->GetPosition(), m_enemy->GetEnemySearchPlayer()->GetTargetSearchPos());
				m_enemy->GetEnemyMove()->SetSlowMoveFlag(false);
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