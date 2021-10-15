#pragma once

namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		//�X�g���{�̂悤�ȃt���b�V��
		class AbilityStrobeFlash : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			/// @brief �X�g���{�t���b�V���𔭓����鏀���̏���
			void StrobeFlashPrepare();

			/// @brief �X�g���{�t���b�V���𔭓����鏈��
			void StrobeFlash();

			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;
			
			//�X�g���{�t���b�V�����`���[�W����J�E���g
			int m_strobeChargeCount = 0;

			//�X�g���{�t���b�V���̃J���[(���邳)
			Vector3 m_strobeFlashColor = { 0.0f, 0.0f, 0.0f };
			
			//�X�g���{�t���b�V���𔭓�����t���O
			bool m_strobeFlashFlag = false;

		};
	}
}

