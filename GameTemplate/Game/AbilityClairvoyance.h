#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class AbilityManager;
		//�����\��(�N���A�{�����X)
		class AbilityClairvoyance
		{
		public:
			~AbilityClairvoyance();
			void Init(FlashLight* flashLight);
			void ExecuteUpdate();

			void PlaySE();

			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

			/// @brief �A�r���e�B���������Ă��邩�ǂ�����ݒ肷��B
			/// @param flag ������邩�ǂ���
			void SetAbilityActiveFlag(bool flag) { m_abilityAcitveFlag = flag; }

			bool GetUseAbilityFlag() { return m_useAbility; }
		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;

			//�A�r���e�B�𔭓������ǂ���
			bool m_useAbility = false;

			//SE�֘A
			bool m_canPlaySSFlag = true;
			int m_canPlaySSCount = 0;

			//�A�r���e�B���������Ă��邩�ǂ���
			bool m_abilityAcitveFlag = false;
		};
	}
}