#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsFlashLight
	{
		class FlashLightAction;
		class FlashLightBattery;
		class AbilityManager;
		class AbilityStrobeFlash;
		class AbilityClairvoyance;

		//�����d��
		class FlashLight : public IGameObject
		{
		public:
			~FlashLight();
			bool Start();
			void Update();

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };

			/// @brief �����d���̃X�|�b�g���C�g���擾
			/// @return �����d���̃X�|�b�g���C�g
			SpotLight* GetSpotLight() { return m_spotLight; };

			/// @brief �����d���̎ˏo�p�x��ݒ肷��B
			/// @param angle �ˏo�p�x
			void SetFlashLightAngle(float angle)
			{
				if (angle <= 1.0f && angle >= 0.1)
				{
					m_flashLightAngle = angle;
					m_spotLight->SetAngle(m_flashLightAngle / 2);
					nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle);
				};
			}

			/// @brief �����d���̎ˏo�p�x���擾
			/// @return �ˏo�p�x(���a�ł͂Ȃ����Ƃɒ���)
			float GetFlashLightAngle() { return m_flashLightAngle; }

			/// @brief �����d���̌������擾����B
			/// @return �����d���̌���
			Vector3 GetFlashLightDir() { return m_direction; };

			/// @brief �����d���̈ʒu���擾����
			/// @return �����d���̈ʒu
			Vector3 GetFlashLightPos() { return m_position; };

			nsPlayer::Player* GetPlayer() { return m_player; };

			//�����d���֌W�̃C���X�^���X�ɃA�N�Z�X����
			FlashLightAction* GetFlashLightAction() { return m_flashLightAction; }
			FlashLightBattery* GetFlashLightBattery() { return m_flashLightBattery; }
			AbilityManager* GetAbilityManager() { return m_abilityManager; }
			AbilityStrobeFlash* GetAbilityStrobeFlash() { return m_abilityStrobeFlash; }
			AbilityClairvoyance* GetAbilityClairvoyance() { return m_abilityClairvoyance; }
		private:
			SkinModelRender* m_flashLightModel = nullptr;
			//�X�|�b�g���C�g
			SpotLight* m_spotLight = nullptr;
			//����
			Vector3 m_direction = { 0.0f, 0.0f, 0.0 };
			//�ʒu
			Vector3 m_position = Vector3::Zero;
			//�v���C���[
			nsPlayer::Player* m_player = nullptr;

			//�����d���̃X�|�b�g���C�g�̎ˏo�p�x
			float m_flashLightAngle = 0.0f;

			//�t���b�V�����C�g�֘A
			FlashLightAction* m_flashLightAction = nullptr;
			FlashLightBattery* m_flashLightBattery = nullptr;
			AbilityManager* m_abilityManager = nullptr;
			AbilityStrobeFlash* m_abilityStrobeFlash = nullptr;
			AbilityClairvoyance* m_abilityClairvoyance = nullptr;

		};
	}
}
