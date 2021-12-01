#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsFlashLight
	{
		class FlashLightAction;
		class FlashLightBattery;
		class AbilityManager;
		class AbilityStrobeFlash;
		class AbilityClairvoyance;
		class AbilityMedousaEye;

		//懐中電灯
		class FlashLight : public IGameObject
		{
		public:
			~FlashLight();
			bool Start();
			void Update();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief 懐中電灯のスポットライトを取得
			/// @return 懐中電灯のスポットライト
			SpotLight* GetSpotLight() { return m_spotLight; };

			/// @brief 懐中電灯の射出角度を設定する。
			/// @param angle 射出角度
			void SetFlashLightAngle(float angle)
			{
				if (angle <= 1.0f && angle >= 0.1)
				{
					m_flashLightAngle = angle;
					m_spotLight->SetAngle(m_flashLightAngle / 2);
					nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle, 0);
				};
			}

			/// @brief 懐中電灯の射出角度を取得
			/// @return 射出角度(半径ではないことに注意)
			float GetFlashLightAngle() { return m_flashLightAngle; }

			/// @brief 懐中電灯の向きを取得する。
			/// @return 懐中電灯の向き
			Vector3 GetFlashLightDir() { return m_direction; };

			/// @brief 懐中電灯の位置を取得する
			/// @return 懐中電灯の位置
			Vector3 GetFlashLightPos() { return m_position; };

			nsPlayer::Player* GetPlayer() { return m_player; };

			Vector3 GetPosition() { return m_position; }

			Vector3 GetModelPos() { return m_modelPos; }

			//懐中電灯関係のインスタンスにアクセスする
			FlashLightAction* GetFlashLightAction() { return m_flashLightAction; }
			FlashLightBattery* GetFlashLightBattery() { return m_flashLightBattery; }
			AbilityManager* GetAbilityManager() { return m_abilityManager; }
			AbilityStrobeFlash* GetAbilityStrobeFlash() { return m_abilityStrobeFlash; }
			AbilityClairvoyance* GetAbilityClairvoyance() { return m_abilityClairvoyance; }
			AbilityMedousaEye* GetAbilityMedousaEye() { return m_abilityMedousaEye; }
		private:
			SkinModelRender* m_flashLightModel = nullptr;
			//スポットライト
			SpotLight* m_spotLight = nullptr;
			//向き
			Vector3 m_direction = { 0.0f, 0.0f, 0.0 };
			//スポットライトの位置
			Vector3 m_position = Vector3::Zero;
			//モデルの位置
			Vector3 m_modelPos = Vector3::Zero;
			//プレイヤー
			nsPlayer::Player* m_player = nullptr;

			//懐中電灯のスポットライトの射出角度
			float m_flashLightAngle = 0.0f;

			//フラッシュライト関連
			FlashLightAction* m_flashLightAction = nullptr;
			FlashLightBattery* m_flashLightBattery = nullptr;
			AbilityManager* m_abilityManager = nullptr;
			AbilityStrobeFlash* m_abilityStrobeFlash = nullptr;
			AbilityClairvoyance* m_abilityClairvoyance = nullptr;
			AbilityMedousaEye* m_abilityMedousaEye = nullptr;
		};
	}
}
