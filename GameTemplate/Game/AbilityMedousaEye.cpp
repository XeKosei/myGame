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

		AbilityMedousaEye::~AbilityMedousaEye()
		{

		}

		bool AbilityMedousaEye::Start()
		{
			m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;

			return true;
		}
		void AbilityMedousaEye::ExecuteUpdate()
		{
			if (m_abilityAcitveFlag == false)
				return;

			//メドゥーサアイのチャージが終わったら
			if (m_medousaEyeChargeCount <= 0)
			{
				//ボタンを放すと
				if (g_pad[0]->IsPress(enButtonRB2) == false)
				{
					//敵がストロボフラッシュを受けて怯んでいるならば
					if (m_abilityManager->GetEnemy()->GetEnemyState() == nsEnemy::Enemy::enState_Flinch)
					{
						//石化させる
						m_abilityManager->GetEnemy()->SetEnemyState(nsEnemy::Enemy::enState_Petrifaction);
						//鍵を落とす(仮)
						nsItem::ItemKey* itemKey = NewGO<nsItem::ItemKey>(0);
						itemKey->SetPlayer(m_flashLight->GetPlayer());
						itemKey->SetKeyColor(nsGimmick::Door::enDoorColor_White);
						itemKey->SetPosition(m_abilityManager->GetEnemy()->GetEnemyMove()->GetPosition());
						//メドゥーサアイのカウントを0に。
						m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;

						m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_MEDOUSAEYEFLASH_BATTERY_COST);
					}
				}
			}
			//ストロボフラッシュのチャージが完了していたら、
			if (m_flashLight->GetAbilityStrobeFlash()->GetIsFinishStrobeCharge())
			{
				//メドゥーサアイのチャージを行う。
				if (m_medousaEyeChargeCount > 0)
				{
					m_medousaEyeChargeCount--;
				}
			}
			else
			{
				//メドゥーサアイのカウントを0に。
				m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;
			}
		}
	}
}