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

			//�����d�������Ă���Ƃ�
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn())
			{
				//�o�b�e���[����
				if (m_useAbility)
				{
					m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_CRAIRVOYANCE_BATTERY_COST);
				}

				//�{�^���������ꂽ�Ƃ��A�����\�ɁB
				if (m_useAbility == false && g_pad[0]->IsTrigger(enButtonLB2))
				{
					m_abilityManager->GetEnemy()->GetEnemyModel()->SetClairvoyanceCasterFlag(true);
					m_abilityManager->GetSecretRoom()->GetSecretRoomModel()->SetClairvoyanceCasterFlag(true);

					m_useAbility = true;
				}
				//�{�^���������ꂽ�Ƃ��A�����s�\�ɁB
				else if (m_useAbility == true && g_pad[0]->IsPress(enButtonLB2) == false)
				{
					m_abilityManager->GetEnemy()->GetEnemyModel()->SetClairvoyanceCasterFlag(false);
					m_abilityManager->GetSecretRoom()->GetSecretRoomModel()->SetClairvoyanceCasterFlag(false);
					m_useAbility = false;
				}
			}
			//�����d�����t���Ă��Ȃ��Ƃ��A���Z�b�g
			else
			{
				m_abilityManager->GetEnemy()->GetEnemyModel()->SetClairvoyanceCasterFlag(false);
				m_abilityManager->GetSecretRoom()->GetSecretRoomModel()->SetClairvoyanceCasterFlag(false);
				m_useAbility = false;
			}
		}
	}
}