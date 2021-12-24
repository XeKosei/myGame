#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;
		//透視能力(クレアボヤンス)
		class AbilityClairvoyance
		{
		public:
			~AbilityClairvoyance();
			void Init(FlashLight* flashLight);
			void ExecuteUpdate();

			void PlaySE();

			/// @brief フラッシュライトにアクセスできるようにする。
			/// @param pl フラッシュライトに参照
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

			/// @brief アビリティマネージャーを設定
			/// @param abilityManager アビリティマネージャー
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

			/// @brief アビリティが解放されているかどうかを設定する。
			/// @param flag 解放するかどうか
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }

			bool GetUseAbilityFlag() { return m_useAbility; }
		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			//アビリティを発動中かどうか
			bool m_useAbility = false;

			//SE関連
			bool m_canPlaySSFlag = true;
			int m_canPlaySSCount = 0;

			//アビリティが解放されているかどうか
			bool m_abilityAcitveFlag = true;
		};
	}
}