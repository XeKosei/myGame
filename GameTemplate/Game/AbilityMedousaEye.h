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

			/// @brief �`���[�WSE�̍Đ�
			void PlayChargeSE();

			/// @brief �`���[�W�������SE
			void PlayChargedSE();

			/// @brief �A�r���e�B�}�l�[�W���[��ݒ�
			/// @param abilityManager �A�r���e�B�}�l�[�W���[
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

			/// @brief �A�r���e�B���������Ă��邩�ǂ�����ݒ肷��B
			/// @param flag ������邩�ǂ���
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }
		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			int m_medousaEyeChargeCount = 0;

			//�A�r���e�B���������Ă��邩�ǂ���
			bool m_abilityAcitveFlag = false;

			//�G�t�F�N�g
			Effect m_chargingEff;

			//�`���[�WSE 
			SoundSource* m_chargeSS = nullptr;
			bool m_canPlayChargeSS = true;
			SoundSource* m_chargedSS = nullptr;
			bool m_canPlayChargedSS = true;
		};
	}
}