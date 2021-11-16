#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "SecretRoom.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsAbilityClairvoyanceConstant;

		bool AbilityClairvoyance::Start()
		{
			return true;
		}

		void AbilityClairvoyance::ExecuteUpdate()
		{
			if (m_abilityAcitveFlag == false)
				return;

			//懐中電灯をつけているとき
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn())
			{
				//バッテリー消費
				if (m_useAbility)
				{
					m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_CRAIRVOYANCE_BATTERY_COST);
				}

				//ボタンが押されたとき、透視可能に。
				if (m_useAbility == false && g_pad[0]->IsTrigger(enButtonLB2))
				{
					m_abilityManager->GetEnemy()->GetEnemyModel()->SetClairvoyanceCasterFlag(true);
					m_abilityManager->GetSecretRoom()->GetSecretRoomModel()->SetClairvoyanceCasterFlag(true);

					m_useAbility = true;
				}
				//ボタンが離されたとき、透視不可能に。
				else if (m_useAbility == true && g_pad[0]->IsPress(enButtonLB2) == false)
				{
					m_abilityManager->GetEnemy()->GetEnemyModel()->SetClairvoyanceCasterFlag(false);
					m_abilityManager->GetSecretRoom()->GetSecretRoomModel()->SetClairvoyanceCasterFlag(false);
					m_useAbility = false;
				}
			}
			//懐中電灯が付いていないとき、リセット
			else
			{
				m_abilityManager->GetEnemy()->GetEnemyModel()->SetClairvoyanceCasterFlag(false);
				m_abilityManager->GetSecretRoom()->GetSecretRoomModel()->SetClairvoyanceCasterFlag(false);
				m_useAbility = false;
			}
		}
	}
}