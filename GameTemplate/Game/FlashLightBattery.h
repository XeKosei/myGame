#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class FlashLightBattery : public IGameObject
		{
		public:
			~FlashLightBattery();
			bool Start();
			void ExecuteUpdate();

			/// @brief バッテリー残量を取得
			/// @return バッテリー残量
			float GetBatteryLevel() { return m_batteryLevel; };

			/// @brief バッテリー残量を設定
			/// @param batteryLevel 設定する値
			void SetBatteryLevel(float batteryLevel);

			/// @brief 指定した値分、バッテリー残量を消費する
			/// @param consumNum 消費する値
			void ConsumBatteryLevel(float consumNum); 

			/// @brief フラッシュライトにアクセスできるようにする。
			/// @param pl フラッシュライトに参照
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;

			//バッテリー残量
			float m_batteryLevel = 50.0f;

			//バッテリー量仮表示
			FontRender* m_font = nullptr;
		};
	}
}