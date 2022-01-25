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

			/// @brief アビリティが解放されているかどうかを設定する。
			/// @param flag 解放するかどうか
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }

			/// @brief アビリティが解放されているかどうかを取得
			/// @return アビリティ解放のフラグ
			bool GetAbilityActiveFlag() { return m_abilityAcitveFlag; }
		private:
			//フラッシュライト
			FlashLight* m_flashLight = nullptr;

			int m_medousaEyeChargeCount = 0;

			//エフェクト
			Effect m_chargingEff;

			//チャージSE 
			SoundSource* m_chargeSS = nullptr;
			bool m_canPlayChargeSS = true;
			SoundSource* m_chargedSS = nullptr;
			bool m_canPlayChargedSS = true;

			//アビリティが解放されているかどうか
			bool m_abilityAcitveFlag = true;
		};
	}
}