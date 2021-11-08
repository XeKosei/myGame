#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsAbilityClairvoyanceConstant;
		void AbilityClairvoyance::ExecuteUpdate()
		{
			//ボタンが押されたとき、エネミーを透視可能に。
			if (m_flashLight->GetFlashLightAction()->GetFlashFlag())
			{
				if (m_isClairvoyanceActivate)
				{
					m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_CRAIRVOYANCE_BATTERY_COST);
				}

				if (m_isClairvoyanceActivate == false && g_pad[0]->IsTrigger(enButtonLB2))
					{
						QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
							{
								enemy->GetEnemyModel()->SetClairvoyanceCasterFlag(true);
								return true;
							}
						);
						m_isClairvoyanceActivate = true;
					}
				//ボタンが離されたとき、エネミーを透視不可能に。
				else if (m_isClairvoyanceActivate == true && g_pad[0]->IsPress(enButtonLB2) == false)
				{
					QueryGOs<nsEnemy::Enemy>("enemy", [this](nsEnemy::Enemy* enemy)->bool
						{
							enemy->GetEnemyModel()->SetClairvoyanceCasterFlag(false);
							return true;
						}
					);
					m_isClairvoyanceActivate = false;
				}
			}
		}
	}
}