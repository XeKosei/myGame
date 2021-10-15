#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsFlashLight
	{	
		class FlashLightAction;
		class AbilityStrobeFlash;
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

			/// @brief �����d���̓d����ON/OFF���Z�b�g����B
			/// @param falshFlag true �d��ON / false �d��OFF
			void SetFlashFlag(bool falshFlag) { m_falshFlag = falshFlag; };

			/// @brief �����d���̓d���������Ă��邩�ǂ����̃t���O���擾
			/// @return �����d���̓d��ON/OFF�t���O
			bool GetFlashFlag() { return m_falshFlag; };

			/// @brief �����d���̎ˏo�p�x��ݒ肷��B
			/// @param angle �ˏo�p�x
			void SetFlashLightAngle(float angle) 
			{ 
				if (angle <= 0.9 && angle >= 0.1)
				{
					m_flashLightAngle = angle;
					m_spotLight->SetAngle(m_flashLightAngle / 2);
					nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle);
				};
			}

			/// @brief �����d���̎ˏo�p�x���擾
			/// @return �ˏo�p�x
			float GetFlashLightAngle() { return m_flashLightAngle; }

			FlashLightAction* GetFlashLightAction() { return m_flashLightAction; }
			AbilityStrobeFlash* GetAbilityStrobeFlash() { return m_abilityStrobeFlash; }

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

			//�����d���̓d���������Ă��邩�B
			bool m_falshFlag = false;

			//�����d���̃X�|�b�g���C�g�̎ˏo�p�x
			float m_flashLightAngle = 0.0f;

			//�t���b�V�����C�g�֘A
			FlashLightAction* m_flashLightAction = nullptr;
			AbilityStrobeFlash* m_abilityStrobeFlash = nullptr;
		};
	}
}
