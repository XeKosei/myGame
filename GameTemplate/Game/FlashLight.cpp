#include "stdafx.h"
#include "FlashLightInclude.h"
#include "PlayerInclude.h"
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsFlashLight
	{
		using namespace nsFlashLightConstant;

		FlashLight::~FlashLight()
		{
			DeleteGO(m_flashLightModel);
			DeleteGO(m_spotLight);
			DeleteGO(m_flashLightAction);
			DeleteGO(m_flashLightBattery);
			DeleteGO(m_abilityManager);
			DeleteGO(m_abilityStrobeFlash);
			DeleteGO(m_abilityClairvoyance);
			DeleteGO(m_abilityMedousaEye);
		}

		bool FlashLight::Start()
		{
			//懐中電灯のモデルを生成
			m_flashLightModel = NewGO<SkinModelRender>(0);
			m_flashLightModel->Init("Assets/modelData/FlashLight.tkm");
			m_flashLightModel->SetPosition(m_position);
			m_flashLightModel->SetScale(INI_FLASHLIGHT_MODEL_SCALE);
			m_flashLightModel->SetSpotLightCasterFlag(false);

			//スポットライトを生成
			m_spotLight = NewGO<nsHikageri::SpotLight>(0);//シャンデリアのスポットライトより先に作りたいので、優先順位は0にする。
			m_spotLight->SetPosition(m_player->GetPlayerMove()->GetPosition());
			m_spotLight->SetDirection(m_direction);
			m_spotLight->SetColor(INI_FLASHLIGHT_COLOR);
			m_spotLight->SetRange(0.0f);
			m_flashLightAngle = INI_FLASHLIGHT_ANGLE;	//スポットライトの射出角度
			m_spotLight->SetAngle(m_flashLightAngle / 2);//(スポットライトに送るアングルは半径なので、2で割る。

			//スポットライトカメラの設定
			LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle, 0);
			//LightManager::GetInstance()->SetSpotLightCameraFar(INI_FLASHLIGHT_RANGE);
			//懐中電灯関係のインスタンスを作成
			m_flashLightAction = NewGO<FlashLightAction>(0);
			m_flashLightAction->SetFlashLight(this);
			m_flashLightBattery = NewGO<FlashLightBattery>(0);
			m_flashLightBattery->SetFlashLight(this);

			//アビリティ関連
			m_abilityManager = NewGO<AbilityManager>(0);
			m_abilityManager->SetFlashLight(this);
			m_abilityStrobeFlash = NewGO<AbilityStrobeFlash>(0);
			m_abilityStrobeFlash->SetFlashLight(this);
			m_abilityStrobeFlash->SetAbilityManager(m_abilityManager);
			m_abilityClairvoyance = NewGO<AbilityClairvoyance>(0);
			m_abilityClairvoyance->SetFlashLight(this);
			m_abilityClairvoyance->SetAbilityManager(m_abilityManager);
			m_abilityMedousaEye = NewGO<AbilityMedousaEye>(0);
			m_abilityMedousaEye->SetFlashLight(this);
			m_abilityMedousaEye->SetAbilityManager(m_abilityManager);

			return true;
		}

		void FlashLight::Update()
		{
			//懐中電灯関係の処理
			//if (m_player->GetPlayerState() == nsPlayer::Player::enState_Normal ||
			//	m_player->GetPlayerState() == nsPlayer::Player::enState_Invincible )
			{
				m_flashLightAction->ExecuteUpdate();
				m_flashLightBattery->ExecuteUpdate();
				m_abilityStrobeFlash->ExecuteUpdate();
				m_abilityClairvoyance->ExecuteUpdate();
				m_abilityMedousaEye->ExecuteUpdate();
			}

			// モデル用の嘘座標を計算する
			Vector3 spotLightUp = Cross(g_camera3D->GetForward(), g_camera3D->GetRight());
			Vector3 modelPos;
			modelPos = g_camera3D->GetPosition();
			modelPos += g_camera3D->GetRight() * FLASHLIGHT_MODEL_POS_APPLY_VALUE.x;
			modelPos += g_camera3D->GetForward() * FLASHLIGHT_MODEL_POS_APPLY_VALUE.z;
			modelPos += spotLightUp * FLASHLIGHT_MODEL_POS_APPLY_VALUE.y;

			//実際の懐中電灯の座標

			//まず懐中電灯をカメラと同じ位置に設定
			m_position = g_camera3D->GetPosition();
			//懐中電灯の位置を横にずらす。
			m_position += g_camera3D->GetRight() * FLASHLIGHT_POS_APPLY_VALUE.x;
			//懐中電灯の位置を縦にずらす
			m_position += spotLightUp * FLASHLIGHT_POS_APPLY_VALUE.y;
	
			//向きを設定
			m_direction = g_camera3D->GetForward();
			m_direction.Normalize();
			Vector3 spotLigTarget = m_position + m_direction * TO_SPOTLIGHTCAMERA_TARGET_DIS;
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraTarget(spotLigTarget, 0);
			m_spotLight->SetDirection({ m_direction });

			//懐中電灯のモデルを回転させる。
			Quaternion qRotMat = Quaternion::Identity;
			qRotMat.SetRotation(g_camera3D->GetCameraRotation());
			m_flashLightModel->SetRotation(qRotMat);

			//懐中電灯の位置を計算。※懐中電灯の位置をずらすのは、後でやらないとモデルの回転が上手く行かない。
			m_flashLightModel->SetPosition(modelPos);
			m_spotLight->SetPosition(m_position);
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_position, 0);
		}
	}
}