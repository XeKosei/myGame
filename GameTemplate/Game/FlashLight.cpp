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
			LightManager::GetInstance()->SetIsFlashLightSwitchOn(false, 0);
			//LightManager::GetInstance()->SetSpotLightCameraFar(INI_FLASHLIGHT_RANGE);
			//懐中電灯関係のクラスの初期化
			m_flashLightAction.Init(this);
			m_flashLightBattery.Init(this);

			//アビリティ関連
			m_abilityStrobeFlash.Init(this);
			m_abilityClairvoyance.Init(this);
			m_abilityMedousaEye.Init(this);

			//壊れる処理のカウント
			m_breakMoveCount = INI_BREAKMOVE_COUNT;

			return true;
		}

		void FlashLight::Update()
		{
			//プレイヤーが死んでいるなら、処理しない
			if (m_player->GetPlayerState() == nsPlayer::Player::enState_Dead)
				return;

			// モデル用の嘘座標を計算する
			Vector3 spotLightUp = Cross(g_camera3D->GetForward(), g_camera3D->GetRight());

			m_modelPos = g_camera3D->GetPosition();
			m_modelPos += g_camera3D->GetRight() * FLASHLIGHT_MODEL_POS_APPLY_VALUE.x;
			m_modelPos += g_camera3D->GetForward() * FLASHLIGHT_MODEL_POS_APPLY_VALUE.z;
			m_modelPos += Cross(g_camera3D->GetForward(), g_camera3D->GetRight()) * FLASHLIGHT_MODEL_POS_APPLY_VALUE.y;

			//実際の懐中電灯の座標

			//まず懐中電灯をカメラと同じ位置に設定
			m_position = g_camera3D->GetPosition();
			//懐中電灯の位置を横にずらす。
			m_position += g_camera3D->GetRight() * FLASHLIGHT_POS_APPLY_VALUE.x;
			//懐中電灯の位置を縦にずらす
			m_position += spotLightUp * FLASHLIGHT_POS_APPLY_VALUE.y;
			m_position += g_camera3D->GetForward() * FLASHLIGHT_POS_APPLY_VALUE.z;

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
			m_flashLightModel->SetPosition(m_modelPos);
			m_spotLight->SetPosition(m_position);
			nsHikageri::LightManager::GetInstance()->SetSpotLightCameraPosition(m_position, 0);

			//壊れているならば
			if (m_isBreak)
			{
				BreakMove();
				return;
			}

			//懐中電灯関係の処理
			//if (m_player->GetPlayerState() == nsPlayer::Player::enState_Normal ||
			//	m_player->GetPlayerState() == nsPlayer::Player::enState_Invincible )
			{
				m_flashLightAction.ExecuteUpdate();
				m_flashLightBattery.ExecuteUpdate();
				m_abilityStrobeFlash.ExecuteUpdate();
				m_abilityClairvoyance.ExecuteUpdate();
				m_abilityMedousaEye.ExecuteUpdate();
			}
		}

		//壊れる処理
		void FlashLight::BreakMove()
		{
			if (m_breakMoveCount > 0)
			{
				m_breakMoveCount--;

				if (m_breakMoveCount == 99)
				{
					m_abilityStrobeFlash.Reset();
					m_abilityClairvoyance.Reset();
					m_abilityMedousaEye.Reset();

					SpotLightGoOut();
					m_player->GetPlayerUI()->SetBatteryUIDeleteFlag(true);
					SoundSource* breakSS = NewGO<SoundSource>(0);
					breakSS->Init(L"Assets/sound/FlashLightBreak.wav");
					breakSS->Play(false);
				}
				else if (m_breakMoveCount == 98)
					SpotLightOn();
				else if (m_breakMoveCount == 75)
					SpotLightGoOut();
				else if (m_breakMoveCount == 74)
					SpotLightOn();
				else if (m_breakMoveCount == 70)
					SpotLightGoOut();
				else if (m_breakMoveCount == 69)
					SpotLightOn();
				else if (m_breakMoveCount == 50)
					SpotLightGoOut();
				else if (m_breakMoveCount == 45)
					SpotLightOn();
				else if (m_breakMoveCount == 35)
					SpotLightGoOut();
				else if (m_breakMoveCount == 25)
					SpotLightOn();
				else if (m_breakMoveCount == 12)
					SpotLightGoOut();
				else if (m_breakMoveCount == 1)
					SpotLightOn();
				else if (m_breakMoveCount == 0)
					SpotLightGoOut();

			}
		}

	}
}