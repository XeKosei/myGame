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
			//�d�r�c�ʂ��ő�ɐݒ�
			m_batteryLevel = MAX_BATTERY_LEVEL;

			//�f�o�b�O�p
			m_font = NewGO<FontRender>(3);
			m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
			m_font->SetColor({0.5f, 0.5f, 0.0f, 1.0f});
			m_font->SetPosition({250.0f, 250.0f});

			m_flashLight->GetPlayer()->GetPlayerUI()->SetBatterySprite(m_batteryLevel);

			return true;
		}
		void FlashLightBattery::ExecuteUpdate()
		{
			//�����d���̓d�����t���Ă���Ȃ��
			if (m_flashLight->GetFlashLightAction()->GetIsFlashLightSwitchOn() == true)
			{
				//�v���C���[�͈��S�ł���B(SAN�l������Ȃ�)
				m_flashLight->GetPlayer()->GetPlayerSanity()->SetReliefFlag(true);

				if (m_batteryLevel > 0.0f)
				{
					ConsumBatteryLevel(BATTERY_LEVEL_DECREASE_SPEED);
				}

				//�o�b�e���[�c�ʂ������Ȃ�����A�����d���������B
				if (m_batteryLevel <= 0.0f)
				{
					m_batteryLevel = 0.0f;
					m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
					m_flashLight->GetFlashLightAction()->SwitchOnOff();
				}
			}
		}

		void FlashLightBattery::ConsumBatteryLevel(float consumNum)
		{
			m_batteryLevel -= consumNum; 
			m_flashLight->GetPlayer()->GetPlayerUI()->SetBatterySprite(m_batteryLevel);

			m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
		}

		void FlashLightBattery::SetBatteryLevel(float batteryLevel)
		{
			m_batteryLevel = batteryLevel; 
			m_flashLight->GetPlayer()->GetPlayerUI()->SetBatterySprite(m_batteryLevel);

			m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
		}
	}
}