#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class FlashLightBattery : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			/// @brief �o�b�e���[�c�ʂ��擾
			/// @return �o�b�e���[�c��
			float GetBatteryLevel() { return m_batteryLevel; };

			/// @brief �o�b�e���[�c�ʂ�ݒ�
			/// @param batteryLevel �ݒ肷��l
			void SetBatteryLevel(float batteryLevel) { m_batteryLevel = batteryLevel; m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
			}

			/// @brief �w�肵���l���A�o�b�e���[�c�ʂ������
			/// @param consumNum �����l
			void ConsumBatteryLevel(float consumNum) { m_batteryLevel -= consumNum; m_font->SetText(L"�o�b�e���[:" + std::to_wstring(m_batteryLevel));
			}


			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;

			//�o�b�e���[�c��
			float m_batteryLevel = 50.0f;

			//�o�b�e���[�ʉ��\��
			FontRender* m_font = nullptr;
		};
	}
}