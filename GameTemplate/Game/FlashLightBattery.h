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

			float GetBatteryLevel() { return m_batteryLevel; };

			/// @brief �t���b�V�����C�g�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �t���b�V�����C�g�ɎQ��
			void SetFlashLight(FlashLight* flashLight) { m_flashLight = flashLight; };

		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;

			//�o�b�e���[�c��
			float m_batteryLevel = 0.0f;
		};
	}
}