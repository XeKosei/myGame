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

			void ChargeFlashPrepare();

			void ChargeFlash();
		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;

			int m_chargeCount = 0;

			Vector3 m_chargeFlashColor = { 50.0f, 50.0f, 50.0f };

			bool m_chargeFlashFlag = false;
		};
	}
}

