#include "stdafx.h"
#include "FlashLightInclude.h"

namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightActionConstant;

		FlashLightAction::~FlashLightAction()
		{

		}
		void FlashLightAction::Init(FlashLight* flashLight)
		{
			m_flashLight = flashLight;
		}

		//FlashLight.cppで毎フレーム呼ばれる処理
		void FlashLightAction::ExecuteUpdate()
		{
			//ボタンが押されたら
			if (g_pad[0]->IsTrigger(enButtonRB1))
			{
				//懐中電灯の電源のスイッチを切り替える。
				SwitchOnOff();
				SoundSource* ss = NewGO<SoundSource>(0);
				ss->Init(L"Assets/sound/FlashLightSwitch.wav");
				ss->Play(false);
			}

			if (GetIsFlashLightSwitchOn() == true)
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
		}

		void FlashLightAction::SwitchOnOff()
		{
			if (m_flashLight->GetFlashLightBattery()->GetBatteryLevel() > 0.0f)
			{
				//懐中電灯の電源のスイッチを切り替える
				SetIsFlashLightSwitchOn(!GetIsFlashLightSwitchOn());
				//電源がOFFだったとき
				if (GetIsFlashLightSwitchOn() == false)
				{	
					//OFFならば影響範囲を0にする。
					m_flashLight->GetSpotLight()->SetRange(0.0f);
				}
				else
				{
					//ONならば影響範囲を設定
					m_flashLight->GetSpotLight()->SetRange(nsFlashLightConstant::INI_FLASHLIGHT_RANGE);
				}
			}
			else
			{
				//電源がONだったとき
				if (GetIsFlashLightSwitchOn() == true)
				{
					//懐中電灯の電源のスイッチを切り替える
					SetIsFlashLightSwitchOn(!GetIsFlashLightSwitchOn());
					//ONならば影響範囲を設定
					m_flashLight->GetSpotLight()->SetRange(0.0f);

				}
			}
		}
	}
}