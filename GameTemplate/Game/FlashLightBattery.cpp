#include "stdafx.h"
#include "FlashLightInclude.h"
#include "PlayerInclude.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightBatteryConstant;
		bool FlashLightBattery::Start()
		{
			//�d�r�c�ʂ��ő�ɐݒ�
			m_batteryLevel = MAX_BATTERY_LEVEL;

			//�f�o�b�O�p
			m_font = NewGO<FontRender>(3);
			m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
			m_font->SetColor({0.5f, 0.5f, 0.0f, 1.0f});
			m_font->SetPosition({250.0f, 250.0f});

			return true;
		}
		void FlashLightBattery::ExecuteUpdate()
		{
			//�����d���̓d�����t���Ă���Ȃ��
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn() == true)
			{
				if (m_batteryLevel > 0.0f)
				{
					m_batteryLevel -= BATTERY_LEVEL_DECREASE_SPEED;
					m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
				}

				//�o�b�e���[�c�ʂ������Ȃ�����A�����d���������B
				if (m_batteryLevel <= 0.0f)
				{
					m_batteryLevel = 0.0f;
					m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
					m_flashLight->GetFlashLightAction()->SwitchOnOff();
				}
			}

			else
			{
				m_flashLight->GetPlayer()->GetPlayerSanity()->Damage(0.01f);
			}
		}
	}
}