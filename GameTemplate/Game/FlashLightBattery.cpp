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
			//�d�r�c�ʂ��ő�ɐݒ�
			m_batteryLevel = MAX_BATTERY_LEVEL;
			return true;
		}
		void FlashLightBattery::ExecuteUpdate()
		{
			//�����d���̓d�����t���Ă���Ȃ��
			if (m_flashLight->GetFlashLightAction()->GetFlashFlag() == true)
			{
				if (m_batteryLevel > 0.0f)
				{
					m_batteryLevel -= BATTERY_LEVEL_DECREASE_SPEED;
				}

				//�o�b�e���[�c�ʂ������Ȃ�����A�����d���������B
				if (m_batteryLevel <= 0.0f)
				{
					m_batteryLevel = 0.0f;
					m_flashLight->GetFlashLightAction()->SwitchOnOff();
				}
			}

			

		}




	}
}