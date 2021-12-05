#pragma once
namespace nsHikageri
{
	namespace nsFlashLight
	{
		class FlashLight;
		class FlashLightBattery : public IGameObject
		{
		public:
			~FlashLightBattery();
			void Init(FlashLight* flashLight);
			void ExecuteUpdate();

			/// @brief �o�b�e���[�c�ʂ��擾
			/// @return �o�b�e���[�c��
			float GetBatteryLevel() { return m_batteryLevel; };

			/// @brief �o�b�e���[�c�ʂ�ݒ�
			/// @param batteryLevel �ݒ肷��l
			void SetBatteryLevel(float batteryLevel);

			/// @brief �w�肵���l���A�o�b�e���[�c�ʂ������
			/// @param consumNum �����l
			void ConsumBatteryLevel(float consumNum); 

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