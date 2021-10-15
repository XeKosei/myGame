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

			/// @brief 懐中電灯の電源のON/OFFをセットする。
			/// @param falshFlag true 電源ON / false 電源OFF
			void SetFlashFlag(bool falshFlag) { m_falshFlag = falshFlag; };

			/// @brief 懐中電灯の電源が入っているかどうかのフラグを取得
			/// @return 懐中電灯の電源ON/OFFフラグ
			bool GetFlashFlag() { return m_falshFlag; };

		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;

			//懐中電灯の電源が入っているか。
			bool m_falshFlag = false;

		};
	}
}

