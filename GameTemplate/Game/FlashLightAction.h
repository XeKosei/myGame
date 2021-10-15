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

			void ChargeFlashPrepare();

			void ChargeFlash();
		private:
			//�t���b�V�����C�g
			FlashLight* m_flashLight = nullptr;

			int m_chargeCount = 0;

			Vector3 m_chargeFlashColor = { 50.0f, 50.0f, 50.0f };

			bool m_chargeFlashFlag = false;
		};
	}
}

