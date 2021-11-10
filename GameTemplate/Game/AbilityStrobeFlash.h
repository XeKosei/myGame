#pragma once

namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;
		//�X�g���{�̂悤�ȃt���b�V��
		class AbilityStrobeFlash : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

			/// @brief �X�g���{�t���b�V���𔭓����鏀���̏���
			void StrobeFlashPrepare();

			/// @brief �X�g���{�t���b�V���𔭓����鏈��
			void StrobeFlash();

			/// @brief �A�r���e�B�}�l�[�W���[��ݒ�
			/// @param abilityManager �A�r���e�B�}�l�[�W���[
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			//�X�g���{�t���b�V�����`���[�W����J�E���g
			int m_strobeChargeCount = 0;

			//�X�g���{�t���b�V���̃J���[(���邳)
			Vector3 m_strobeFlashColor = { 0.0f, 0.0f, 0.0f };

			//�X�g���{�t���b�V���𔭓�����t���O
			bool m_strobeFlashFlag = false;

		};
	}
}

