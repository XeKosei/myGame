#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsAbilityMedousaEyeConstant;
		bool AbilityMedousaEye::Start()
		{
			m_medousaEyeFlashCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;

			return true;
		}
		void AbilityMedousaEye::ExecuteUpdate()
		{
			if (m_medousaEyeFlashCount <= 0)
			{
				if (g_pad[0]->IsPress(enButtonRB2) == false)
				{
					m_abilityManager->GetEnemy()->SetEnemyState(nsEnemy::Enemy::enState_Petrifaction);
				}
			}
			if (m_flashLight->GetAbilityStrobeFlash()->GetIsFinishStrobeCharge())
			{
				if (m_medousaEyeFlashCount > 0)
				{
					m_medousaEyeFlashCount--;
				}
			}
			else
			{
				m_medousaEyeFlashCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;
			}
			
		}
	}
}