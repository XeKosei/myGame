#include "stdafx.h"
#include "FlashLightInclude.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightBatteryConstant;

		FlashLightBattery::~FlashLightBattery()
		{
			DeleteGO(m_font);
		}

		bool FlashLightBattery::Start()
		{
			//電池残量を最大に設定
			m_batteryLevel = MAX_BATTERY_LEVEL;

			//デバッグ用
			m_font = NewGO<FontRender>(3);
			m_font->SetText(L"バッテリー:" + std::to_wstring(m_batteryLevel));
			m_font->SetColor({0.5f, 0.5f, 0.0f, 1.0f});
			m_font->SetPosition({250.0f, 250.0f});

			m_flashLight->GetPlayer()->GetPlayerUI()->SetBatterySprite(m_batteryLevel);

			return true;
		}
		void FlashLightBattery::ExecuteUpdate()
		{
			//懐中電灯の電源が付いているならば
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn() == true)
			{
				//プレイヤーは安心できる。(SAN値が減らない)
				m_flashLight->GetPlayer()->GetPlayerSanity()->SetReliefFlag(true);

				if (m_batteryLevel > 0.0f)
				{
					ConsumBatteryLevel(BATTERY_LEVEL_DECREASE_SPEED);
				}

				//バッテリー残量が無くなったら、懐中電灯を消す。
				if (m_batteryLevel <= 0.0f)
				{
					m_batteryLevel = 0.0f;
					m_font->SetText(L"バッテリー:" + std::to_wstring(m_batteryLevel));
					m_flashLight->GetFlashLightAction()->SwitchOnOff();
				}
			}
		}

		void FlashLightBattery::ConsumBatteryLevel(float consumNum)
		{
			m_batteryLevel -= consumNum; 
			m_flashLight->GetPlayer()->GetPlayerUI()->SetBatterySprite(m_batteryLevel);

			m_font->SetText(L"バッテリー:" + std::to_wstring(m_batteryLevel));
		}

		void FlashLightBattery::SetBatteryLevel(float batteryLevel)
		{
			m_batteryLevel = batteryLevel; 
			m_flashLight->GetPlayer()->GetPlayerUI()->SetBatterySprite(m_batteryLevel);

			m_font->SetText(L"バッテリー:" + std::to_wstring(m_batteryLevel));
		}
	}
}