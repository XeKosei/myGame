#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;

		class FlashLightAction : public IGameObject
		{
		public:
			~FlashLightAction();
			bool Start();
			void ExecuteUpdate();

			/// @brief �����d���̓d����ON/OFF����B
			void SwitchOnOff();

			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

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

