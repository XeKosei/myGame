#pragma once
#include "BackGround.h"
namespace nsHikageri
{
	namespace nsBackGround { class BachGround; }
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;
		//�X�g���{�̂悤�ȃt���b�V��
		class AbilityStrobeFlash
		{
		public:
			~AbilityStrobeFlash();
			void Init(FlashLight* flashLight);
			void ExecuteUpdate();

			void Reset();

			/// @brief �X�g���{�t���b�V���𔭓����鏀���̏���
			void StrobeFlashPrepare();

			/// @brief �X�g���{�t���b�V���𔭓����鏈��
			void StrobeFlash();

			/// @brief �����d���̃t���b�V�����������Ă��邩�ǂ����𒲂ׂ�B
			/// @param chackPos �������Ă��邩���ׂ����ʒu
			/// @return �������Ă������ǂ���
			bool CheckHitFlash(Vector3 chackPos);

			/// @brief �`���[�WSE�̍Đ�
			void PlayChargeSE();

			/// @brief �`���[�W�������SE
			void PlayChargedSE();

			/// @brief �A�r���e�B�}�l�[�W���[��ݒ�
			/// @param abilityManager �A�r���e�B�}�l�[�W���[
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

			/// @brief �X�g���{�t���b�V���̃`���[�W���������Ă��邩�ǂ������擾
			/// @return �`���[�W����:true ������:false
			bool GetIsFinishStrobeCharge() { if (m_strobeChargeCount <= 0) { return true; } else { return false; } }
		
			/// @brief �A�r���e�B���������Ă��邩�ǂ�����ݒ肷��B
			/// @param flag ������邩�ǂ���
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }
		private:
			nsBackGround::BackGround* m_backGround = nullptr;
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			//�X�g���{�t���b�V�����`���[�W����J�E���g
			int m_strobeChargeCount = 0;

			//�X�g���{�t���b�V���̃J���[(���邳)
			Vector3 m_strobeFlashColor = { 0.0f, 0.0f, 0.0f };

			//�X�g���{�t���b�V���𔭓�����t���O
			bool m_useAbility = false;
			
			//�G�t�F�N�g
			Effect m_chargingEff;

			//�`���[�WSE 
			SoundSource* m_chargeSS = nullptr;
			bool m_canPlayChargeSS = true;
			SoundSource* m_chargedSS = nullptr;
			bool m_canPlayChargedSS = true;

			//�A�r���e�B���������Ă��邩�ǂ���
			bool m_abilityAcitveFlag = false;
		};
	}
}

