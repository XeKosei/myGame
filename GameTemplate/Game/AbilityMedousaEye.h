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

			/// @brief チャージSEの再生
			void PlayChargeSE();

			/// @brief チャージ完了後のSE
			void PlayChargedSE();

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

			//チャージSE 
			SoundSource* m_chargeSS = nullptr;
			bool m_canPlayChargeSS = true;
			SoundSource* m_chargedSS = nullptr;
			bool m_canPlayChargedSS = true;
		};
	}
}