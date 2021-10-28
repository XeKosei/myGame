#include "stdafx.h"
#include "FlashLightInclude.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightBattery;
		bool FlashLightBattery::Start()
		{
			//電池残量を最大に設定
			m_batteryLevel = MAX_BATTERY_LEVEL;
			return true;
		}
		void FlashLightBattery::ExecuteUpdate()
		{
			//懐中電灯の電源が付いているならば
			if (m_flashLight->GetFlashLightAction()->GetFlashFlag() == true)
			{
				if (m_batteryLevel > 0.0f)
				{
					m_batteryLevel -= BATTERY_LEVEL_DECREASE_SPEED;
				}

				//バッテリー残量が無くなったら、懐中電灯を消す。
				if (m_batteryLevel <= 0.0f)
				{
					m_batteryLevel = 0.0f;
					m_flashLight->GetFlashLightAction()->SwitchOnOff();
				}
			}

			

		}




	}
}