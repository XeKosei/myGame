#include "stdafx.h"
#include "FlashLightInclude.h"
#include "EnemyInclude.h"
#include "ItemKey.h"
#include "Door.h"
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
			if (m_abilityAcitveFlag == false)
				return;

			if (m_medousaEyeFlashCount <= 0)
			{
				if (g_pad[0]->IsPress(enButtonRB2) == false)
				{
					m_abilityManager->GetEnemy()->SetEnemyState(nsEnemy::Enemy::enState_Petrifaction);
					nsItem::ItemKey* itemKey = NewGO<nsItem::ItemKey>(0);
					itemKey->SetPlayer(m_flashLight->GetPlayer());
					itemKey->SetKeyColor(nsGimmick::Door::enDoorColor_White);
					itemKey->SetPosition(m_abilityManager->GetEnemy()->GetEnemyMove()->GetPosition());
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