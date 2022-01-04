#pragma once
#include "FlashLightAction.h"
#include "FlashLightBattery.h"
#include "AbilityStrobeFlash.h"
#include "AbilityClairvoyance.h"
#include "AbilityMedousaEye.h"

#include "GameSceneConstant.h"
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsEnemy { class Enemy; }
	namespace nsFlashLight
	{
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
					nsHikageri::LightManager::GetInstance()->SetSpotLightCameraAngle(m_flashLightAngle, 0);
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

			Vector3 GetPosition() { return m_position; }

			Vector3 GetModelPos() { return m_modelPos; }

			/*/// @brief �G�l�~�[���擾
			/// @return �G�l�~�[
			nsEnemy::Enemy* GetEnemy() { return m_enemy; }*/

			//�����d���֌W�̃C���X�^���X�ɃA�N�Z�X����
			FlashLightAction* GetFlashLightAction() { return &m_flashLightAction; }
			FlashLightBattery* GetFlashLightBattery() { return &m_flashLightBattery; }
			AbilityStrobeFlash* GetAbilityStrobeFlash() { return &m_abilityStrobeFlash; }
			AbilityClairvoyance* GetAbilityClairvoyance() { return &m_abilityClairvoyance; }
			AbilityMedousaEye* GetAbilityMedousaEye() { return &m_abilityMedousaEye; }
		private:
			SkinModelRender* m_flashLightModel = nullptr;
			//�X�|�b�g���C�g
			SpotLight* m_spotLight = nullptr;
			//����
			Vector3 m_direction = { 0.0f, 0.0f, 0.0 };
			//�X�|�b�g���C�g�̈ʒu
			Vector3 m_position = Vector3::Zero;
			//���f���̈ʒu
			Vector3 m_modelPos = Vector3::Zero;
			//�v���C���[
			nsPlayer::Player* m_player = nullptr;

			//�����d���̃X�|�b�g���C�g�̎ˏo�p�x
			float m_flashLightAngle = 0.0f;

			//�t���b�V�����C�g�֘A
			FlashLightAction m_flashLightAction;
			FlashLightBattery m_flashLightBattery;
			AbilityStrobeFlash m_abilityStrobeFlash;
			AbilityClairvoyance m_abilityClairvoyance;
			AbilityMedousaEye m_abilityMedousaEye;

			//nsEnemy::Enemy* m_enemy[nsGameScene::nsGameSceneConstant::ENEMY_NUM] = {nullptr, nullptr, nullptr};
		};
	}
}
