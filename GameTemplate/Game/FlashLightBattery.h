#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class FlashLightBattery : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			float GetBatteryLevel() { return m_batteryLevel; };

			/// @brief フラッシュライトにアクセスできるようにする。
			/// @param pl フラッシュライトに参照
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;

			//バッテリー残量
			float m_batteryLevel = 0.0f;
		};
	}
}