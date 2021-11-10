#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;
		//透視能力(クレアボヤンス)
		class AbilityClairvoyance : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();
			/// @brief フラッシュライトにアクセスできるようにする。
			/// @param pl フラッシュライトに参照
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

			/// @brief アビリティマネージャーを設定
			/// @param abilityManager アビリティマネージャー
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			//クレアボヤンスが発動中かどうか
			bool m_isClairvoyanceActivate = false;
		};
	}
}