#include "stdafx.h"
#include "FlashLight.h"
#include "FlashLightAction.h"
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
			m_flashLightModel->SetSpotLightCasterFlag(false);

			//スポットライトを生成
			m_spotLight = NewGO<nsHikageri::SpotLight>(0);
			m_spotLight->SetPosition(m_player->GetPosition());
			m_spotLight->SetDirection(m_direction);
			m_spotLight->SetColor(FLASHLIGHT_INI_COLOR);
			m_spotLight->SetRange(0.0f);
			m_flashLightAngle = FLASHLIGHT_INI_ANGLE;	//スポットライトの射出角度
			m_spotLight->SetAngle(m_flashLightAngle / 2);//(スポットライトに送るアングルは半径なので、2で割る。

			//スポットライトカメラのアングルを設定
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle);

			//懐中電灯関係のインスタンスを作成
			m_flashLightAction = NewGO<FlashLightAction>(0);
			m_flashLightAction->SetFlashLight(this);

			return true;
		}

		void FlashLight::Update()
		{
			//懐中電灯関係の処理
			m_flashLightAction->ExecuteUpdate();

			//まず懐中電灯をカメラと同じ位置に設定
			m_position = g_camera3D->GetPosition();
			//懐中電灯の位置を横にずらす。
			m_position += g_camera3D->GetRight() * APPLY_FLASHLIGHT_POS_VALUE.x;
			//懐中電灯の位置を奥にずらす。
			m_position += g_camera3D->GetForward() * APPLY_FLASHLIGHT_POS_VALUE.z;

			//向きを設定
			m_direction = g_camera3D->GetForward();
			m_direction.Normalize();
			Vector3 spotLigTarget = m_position + m_direction * TO_SPOTLIGHTCAMERA_TARGET_DIS;
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(spotLigTarget);
			m_spotLight->SetDirection({ m_direction });

			//懐中電灯のモデルを回転させる。
			Quaternion qRotMat = Quaternion::Identity;
			qRotMat.SetRotation(g_camera3D->GetCameraRotation());
			m_flashLightModel->SetRotation(qRotMat);

			//懐中電灯の位置を計算。※懐中電灯の位置を縦にずらすのは、後でやらないとモデルの回転が上手く行かない。
			m_position -= Cross(g_camera3D->GetForward(), g_camera3D->GetRight()) * APPLY_FLASHLIGHT_POS_VALUE.y;
			m_flashLightModel->SetPosition(m_position);
			m_spotLight->SetPosition(m_position);
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_position);
		}
	}
}