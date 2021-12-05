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

		void AbilityMedousaEye::Init(FlashLight* flashLight)
		{
			m_flashLight = flashLight;

			m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;

			//エフェクト
			m_chargingEff.Init(u"Assets/effect/StrobeFlashEff.efk");
			m_chargingEff.SetScale(INI_MEDOUSAEYEFLASH_EFF_SCALE);

		}
		void AbilityMedousaEye::ExecuteUpdate()
		{
			if (m_abilityAcitveFlag == false)
				return;

			//懐中電灯がついているとき。
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn())
			{
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

							m_flashLight->GetFlashLightBattery()->ConsumBatteryLevel(INI_MEDOUSAEYEFLASH_BATTERY_COST);

							Reset();
						}
					}
				}
				//ストロボフラッシュのチャージが完了していたら、
				if (m_flashLight->GetAbilityStrobeFlash()->GetIsFinishStrobeCharge())
				{
					//エフェクトの再生
					if (m_chargingEff.IsPlay() == false)
					{
						m_chargingEff.Play();
					}
					m_chargingEff.SetPosition(m_flashLight->GetModelPos());
					m_chargingEff.Update();

					//メドゥーサアイのチャージを行う。
					if (m_medousaEyeChargeCount > 0)
					{
						m_medousaEyeChargeCount--;
					}
				}
				else
				{
					Reset();
				}
			}
			else
			{
				Reset();
			}
		}

		void AbilityMedousaEye::Reset()
		{
			//エフェクトを停止
			m_chargingEff.Stop();
			//メドゥーサアイのカウントを0に。
			m_medousaEyeChargeCount = INI_MEDOUSAEYEFLASH_CHARGE_COUNT;
		}
	}
}