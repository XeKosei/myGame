#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;

		class FlashLightAction
		{
		public:
			~FlashLightAction();
			void Init(FlashLight* flashLight);
			void ExecuteUpdate();

			/// @brief 懐中電灯の電源をON/OFFする。
			void SwitchOnOff();

			/// @brief 懐中電灯の電源のON/OFFをセットする。
			/// @param falshFlag true 電源ON / false 電源OFF
			void SetIsFlashLightSwitchOn(bool falshFlag) { 
				m_isFalshLightSwitchOn = falshFlag; 
				LightManager::GetInstance()->SetIsFlashLightSwitchOn(falshFlag, 0);
			};

			/// @brief 懐中電灯の電源が入っているかどうかのフラグを取得
			/// @return 懐中電灯の電源ON/OFFフラグ
			bool GetIsFlashLightSwitchOn() { return m_isFalshLightSwitchOn;	};

		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;

			//懐中電灯の電源が入っているか。
			bool m_isFalshLightSwitchOn = false;

		};
	}
}

