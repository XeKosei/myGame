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
			bool Start();

			void ExecuteUpdate();
			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

			/// @brief �A�r���e�B�}�l�[�W���[��ݒ�
			/// @param abilityManager �A�r���e�B�}�l�[�W���[
			void SetAbilityManager(AbilityManager* abilityManager) { m_abilityManager = abilityManager; }

		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			int m_medousaEyeFlashCount = 0;
		};
	}
}