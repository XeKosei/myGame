#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;
		//�����\��(�N���A�{�����X)
		class AbilityClairvoyance : public IGameObject
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

			/// @brief �A�r���e�B���������Ă��邩�ǂ�����ݒ肷��B
			/// @param flag ������邩�ǂ���
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }
		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;
			AbilityManager* m_abilityManager = nullptr;

			//�N���A�{�����X�����������ǂ���
			bool m_isClairvoyanceActivate = false;

			//�A�r���e�B���������Ă��邩�ǂ���
			bool m_abilityAcitveFlag = true;
		};
	}
}