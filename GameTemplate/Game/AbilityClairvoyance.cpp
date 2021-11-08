#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		void AbilityClairvoyance::ExecuteUpdate()
		{
			//ボタンが押されたとき、エネミーを透視可能に。
			if (m_flashLight->GetFlashLightAction()->GetFlashFlag())
			{
				if (m_canSetClairvoyance == true && g_pad[0]->IsTrigger(enButtonLB2))
					{
						QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
							{
								enemy->GetEnemyModel()->SetClairvoyanceCasterFlag(true);
								return true;
							}
						);
						m_canSetClairvoyance = false;
					}
				//ボタンが離されたとき、エネミーを透視不可能に。
				else if (m_canSetClairvoyance == false && g_pad[0]->IsPress(enButtonLB2) == false)
				{
					QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
						{
							enemy->GetEnemyModel()->SetClairvoyanceCasterFlag(false);
							return true;
						}
					);
					m_canSetClairvoyance = true;
				}
			}
		}
	}
}