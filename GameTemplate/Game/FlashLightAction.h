#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;

		class FlashLightAction : public IGameObject
		{
		public:
			~FlashLightAction();
			bool Start();
			void ExecuteUpdate();

			/// @brief 懐中電灯の電源をON/OFFする。
			void SwitchOnOff();

			/// @brief フラッシュライトにアクセスできるようにする。
			/// @param pl フラッシュライトに参照
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;
		};
	}
}

