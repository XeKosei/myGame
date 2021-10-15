#include "stdafx.h"
#include "FlashLightAction.h"
#include "FlashLight.h"
#include "FlashLightConstant.h"

namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightActionConstant;

		FlashLightAction::~FlashLightAction()
		{

		}
		bool FlashLightAction::Start()
		{
			return true;
		}

		//FlashLight.cppで毎フレーム呼ばれる処理
		void FlashLightAction::ExecuteUpdate()
		{
			//ボタンが押されたら
			if (g_pad[0]->IsTrigger(enButtonRB1))
			{
				//懐中電灯の電源のスイッチを切り替える。
				SwitchOnOff();
			}

			if (m_flashLight->GetFlashFlag() == true)
			{
				//十字ボタンの上下で、懐中電灯の射出角度を調節できる。
				if (g_pad[0]->IsPress(enButtonUp))
				{
					m_flashLight->SetFlashLightAngle(m_flashLight->GetFlashLightAngle() + FLASHLIGHT_ANGLE_ADJUST_SPEED);
				}
				if (g_pad[0]->IsPress(enButtonDown))
				{
					m_flashLight->SetFlashLightAngle(m_flashLight->GetFlashLightAngle() - FLASHLIGHT_ANGLE_ADJUST_SPEED);
				}
			}
			
			ChargeFlashPrepare();
			
			if (m_chargeFlashFlag == true)
			{
				ChargeFlash();
			}
		}

		void FlashLightAction::SwitchOnOff()
		{
			//懐中電灯の電源のスイッチを切り替える
			m_flashLight->SetFlashFlag(!m_flashLight->GetFlashFlag());

			//電源がONならば
			if (m_flashLight->GetFlashFlag() == true)
			{
				//ONならば影響範囲を設定
				m_flashLight->GetSpotLight()->SetRange(nsFlashLightConstant::FLASHLIGHT_INI_RANGE);

			}
			//電源がOFFならば
			else
			{
				//OFFならば影響範囲を0にする。
				m_flashLight->GetSpotLight()->SetRange(0.0f);
			}
		}

		void FlashLightAction::ChargeFlashPrepare()
		{
			if (g_pad[0]->IsPress(enButtonRB2))
			{
				if (m_chargeCount < 50)
				{
					m_chargeCount++;
				}
			}
			else 
			{
				if (m_chargeCount >= 50)
				{
					m_chargeFlashFlag = true;
				}
				m_chargeCount = 0;
			}
		}

		void FlashLightAction::ChargeFlash()
		{
			m_flashLight->GetSpotLight()->SetColor(m_chargeFlashColor);

			m_chargeFlashColor -= {1.0f, 1.0f, 1.0f};

			if (m_chargeFlashColor.x <= 10.0f)
			{
				m_chargeFlashFlag = false;
				m_chargeFlashColor = { 100.0f, 100.0f, 100.0f };
			}
		}
	}
}