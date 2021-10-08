#include "stdafx.h"
#include "FlashLight.h"
#include "FlashLightConstant.h"
#include "Player.h"

namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightConstant;

		FlashLight::~FlashLight()
		{
			//DeleteGO(m_flashLightModel);
			DeleteGO(m_spotLight);
			
		}

		bool FlashLight::Start()
		{
			//懐中電灯のモデルを生成
			m_flashLightModel = NewGO<SkinModelRender>(0);
			m_flashLightModel->Init("Assets/modelData/FlashLight.tkm");
			m_flashLightModel->SetPosition(m_position);

			//スポットライトを生成
			m_spotLight = NewGO<nsHikageri::SpotLight>(0);
			m_spotLight->SetPosition(m_player->GetPosition());
			m_spotLight->SetDirection(m_direction);
			m_spotLight->SetColor(FLASHLIGHT_INI_COLOR);
			m_spotLight->SetRange(FLASHLIGHT_INI_RANGE);
			m_spotLight->SetAngle(FLASHLIGHT_INI_ANGLE / 2);	//(スポットライトに送るアングルは半径なので、2で割る。

			//スポットライトカメラのアングルを設定
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(FLASHLIGHT_INI_ANGLE);

			return true;
		}

		void FlashLight::Update()
		{
			m_position = {m_player->GetPosition().x + 1.0f, m_player->GetPosition().y + 200.0f, m_player->GetPosition().z };
			m_position += m_direction * 5.0f;
			m_flashLightModel->SetPosition(m_position);
			m_spotLight->SetPosition(m_position);
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_position);

			//向きを設定
			if (g_pad[0]->IsPress(enButtonLB1) == false)
			{
				m_direction = g_camera3D->GetForward();
				m_direction.y = 0.0f;
				m_direction.Normalize();
			}
			else
			{
				m_direction = g_camera3D->GetForward();
			}

			Vector3 spotLigTarget = m_position + m_direction * 100.0f;
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(spotLigTarget);
			m_spotLight->SetDirection({ m_direction });
		}
	}
}