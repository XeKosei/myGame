#include "stdafx.h"
#include "Chandelier.h"
#include "PlayerInclude.h"
#include "EnemyInclude.h"
#include "GimmickConstant.h"

namespace nsHikageri
{
	namespace nsGimmick
	{
		using namespace nsChandelierConstant;

		Chandelier::~Chandelier()
		{
			DeleteGO(m_chandelierModel);
		}

		bool Chandelier::Start()
		{
			//モデル
			m_chandelierModel = NewGO<SkinModelRender>(0);
			m_chandelierModel->Init("Assets/modelData/chandelier.tkm");
			m_chandelierModel->SetPosition(m_position);
			m_chandelierModel->SetSpotLightCasterFlag(false);

			return true;
		}

		void Chandelier::Update()
		{
			//プレイヤーとエネミーの位置
			Vector3 playerPos = m_player->GetPlayerMove()->GetPosition();
			Vector3 enemyPos = m_enemy->GetEnemyMove()->GetPosition();

			//プレイヤーが近くにいるならば、
			if ((playerPos - m_position).Length() <= CHANDELIER_FORCE_RANGE
				&& m_enemy->GetEnemyState() != nsEnemy::Enemy::enState_Chase)
			{
				//プレイヤーは安心できる。
				m_player->GetPlayerSanity()->SetReliefFlag(true);
			}

			//エネミーが近くにいるならば、
			if ((enemyPos - m_position).Length() <= CHANDELIER_FORCE_RANGE)
			{
				m_enemy->GetEnemyMove()->SetSlowMoveFlag(true);
				if (m_enemy->GetEnemyState() == nsEnemy::Enemy::enState_Chase)
				{
					m_enemy->GetEnemyStress()->AddStress(CHANDELIER_ADD_STRESS_SPEED);
				}
			}
		}
	}
}