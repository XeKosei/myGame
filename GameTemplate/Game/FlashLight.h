#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsFlashLight
	{	
		class FlashLightAction;
		class AbilityStrobeFlash;
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

			/// @brief 懐中電灯の電源のON/OFFをセットする。
			/// @param falshFlag true 電源ON / false 電源OFF
			void SetFlashFlag(bool falshFlag) { m_falshFlag = falshFlag; };

			/// @brief 懐中電灯の電源が入っているかどうかのフラグを取得
			/// @return 懐中電灯の電源ON/OFFフラグ
			bool GetFlashFlag() { return m_falshFlag; };

			/// @brief 懐中電灯の射出角度を設定する。
			/// @param angle 射出角度
			void SetFlashLightAngle(float angle) 
			{ 
				if (angle <= 0.9 && angle >= 0.1)
				{
					m_flashLightAngle = angle;
					m_spotLight->SetAngle(m_flashLightAngle / 2);
					nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle);
				};
			}

			/// @brief 懐中電灯の射出角度を取得
			/// @return 射出角度
			float GetFlashLightAngle() { return m_flashLightAngle; }

			FlashLightAction* GetFlashLightAction() { return m_flashLightAction; }
			AbilityStrobeFlash* GetAbilityStrobeFlash() { return m_abilityStrobeFlash; }

		private:
			SkinModelRender* m_flashLightModel = nullptr;
			//スポットライト
			SpotLight* m_spotLight = nullptr;
			//向き
			Vector3 m_direction = { 0.0f, 0.0f, 0.0 };
			//位置
			Vector3 m_position = Vector3::Zero;
			//プレイヤー
			nsPlayer::Player* m_player = nullptr;

			//懐中電灯の電源が入っているか。
			bool m_falshFlag = false;

			//懐中電灯のスポットライトの射出角度
			float m_flashLightAngle = 0.0f;

			//フラッシュライト関連
			FlashLightAction* m_flashLightAction = nullptr;
			AbilityStrobeFlash* m_abilityStrobeFlash = nullptr;
		};
	}
}
