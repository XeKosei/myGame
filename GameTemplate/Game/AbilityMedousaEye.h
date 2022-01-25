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

			/// @brief �A�r���e�B���������Ă��邩�ǂ�����ݒ肷��B
			/// @param flag ������邩�ǂ���
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }

			/// @brief �A�r���e�B���������Ă��邩�ǂ������擾
			/// @return �A�r���e�B����̃t���O
			bool GetAbilityActiveFlag() { return m_abilityAcitveFlag; }
		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;

			int m_medousaEyeChargeCount = 0;

			//�G�t�F�N�g
			Effect m_chargingEff;

			//�`���[�WSE 
			SoundSource* m_chargeSS = nullptr;
			bool m_canPlayChargeSS = true;
			SoundSource* m_chargedSS = nullptr;
			bool m_canPlayChargedSS = true;

			//�A�r���e�B���������Ă��邩�ǂ���
			bool m_abilityAcitveFlag = true;
		};
	}
}