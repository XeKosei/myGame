#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;

		class FlashLightAction
		{
		public:
			~FlashLightAction();
			void Init(FlashLight* flashLight);
			void ExecuteUpdate();

			/// @brief �����d���̓d����ON/OFF����B
			void SwitchOnOff();

			/// @brief �����d���̓d����ON/OFF���Z�b�g����B
			/// @param falshFlag true �d��ON / false �d��OFF
			void SetIsFlashLightSwitchOn(bool falshFlag) { 
				m_isFalshLightSwitchOn = falshFlag; 
				LightManager::GetInstance()->SetIsFlashLightSwitchOn(falshFlag, 0);
			};

			/// @brief �����d���̓d���������Ă��邩�ǂ����̃t���O���擾
			/// @return �����d���̓d��ON/OFF�t���O
			bool GetIsFlashLightSwitchOn() { return m_isFalshLightSwitchOn;	};

		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;

			//�����d���̓d���������Ă��邩�B
			bool m_isFalshLightSwitchOn = false;

		};
	}
}

