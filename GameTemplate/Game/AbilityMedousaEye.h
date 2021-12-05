#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;

		class AbilityMedousaEye : public IGameObject
		{
		public:
			~AbilityMedousaEye();
			void Init(FlashLight* flashLight);
			void ExecuteUpdate();

			void Reset();

			/// @brief アビリティマネージャーを設定
			/// @param abilityManager アビリティマネージャー
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

			/// @brief アビリティが解放されているかどうかを設定する。
			/// @param flag 解放するかどうか
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }
		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			int m_medousaEyeChargeCount = 0;

			//アビリティが解放されているかどうか
			bool m_abilityAcitveFlag = false;

			//エフェクト
			Effect m_chargingEff;
		};
	}
}