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
			DeleteGO(m_pointLight);
		}

		bool Chandelier::Start()
		{
			//モデル
			m_chandelierModel = NewGO<SkinModelRender>(0);
			m_chandelierModel->Init("Assets/modelData/chandelier.tkm");
			m_chandelierModel->SetPosition(m_position);
			m_chandelierModel->SetSpotLightCasterFlag(false);

			m_pointLight = NewGO<PointLight>(0);
			m_pointLight->SetRange(250.0f);
			m_pointLight->SetPosition(m_position);
			m_pointLight->SetColor({50.0f,50.0f,50.0f});

			return true;
		}

		void Chandelier::Update()
		{
			//計算をするならば
			if (m_executeFlag)
			{
				//プレイヤーとエネミーの位置
				Vector3 playerPos = m_player->GetPlayerMove()->GetPosition();

				//プレイヤーが近くにいるならば、
				if ((playerPos - m_position).Length() <= CHANDELIER_FORCE_RANGE)
				{
					//プレイヤーは安心できる。
					m_player->GetPlayerSanity()->SetReliefFlag(true);
				}

				QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
					{
						Vector3 enemyPos = enemy->GetEnemyMove()->GetPosition();

						//エネミーが近くにいるならば、
						if ((enemyPos - m_position).Length() <= CHANDELIER_FORCE_RANGE
							&& enemy->GetStopExecuteFlag() == false)
						{
							enemy->GetEnemyMove()->SetSlowMoveFlag(true);					
							if (enemy->GetEnemyState() == nsEnemy::Enemy::enState_Chase)
							{
								enemy->GetEnemyStress()->AddStress(CHANDELIER_ADD_STRESS_SPEED);
							}
						}
						return true;
					}
				);

				//計算をするかどうかのフラグをリセット
				SetExecuteFlag(false);
			}
		}
	}
}