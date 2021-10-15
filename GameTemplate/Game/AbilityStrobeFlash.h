#pragma once

namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		//ストロボのようなフラッシュ
		class AbilityStrobeFlash : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			/// @brief ストロボフラッシュを発動する準備の処理
			void StrobeFlashPrepare();

			/// @brief ストロボフラッシュを発動する処理
			void StrobeFlash();

			/// @brief フラッシュライトにアクセスできるようにする。
			/// @param pl フラッシュライトに参照
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;
			
			//ストロボフラッシュをチャージするカウント
			int m_strobeChargeCount = 0;

			//ストロボフラッシュのカラー(明るさ)
			Vector3 m_strobeFlashColor = { 0.0f, 0.0f, 0.0f };
			
			//ストロボフラッシュを発動するフラグ
			bool m_strobeFlashFlag = false;

		};
	}
}

