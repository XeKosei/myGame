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

			if (GetFlashFlag() == true)
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
			//懐中電灯の電源のスイッチを切り替える
			SetFlashFlag(!GetFlashFlag());

			//電源がONならば
			if (GetFlashFlag() == true)
			{
				//ONならば影響範囲を設定
				m_flashLight->GetSpotLight()->SetRange(nsFlashLightConstant::INI_FLASHLIGHT_RANGE);

			}
			//電源がOFFならば
			else
			{
				//OFFならば影響範囲を0にする。
				m_flashLight->GetSpotLight()->SetRange(0.0f);
			}
		}
	}
}