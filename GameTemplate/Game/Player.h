#pragma once
#include "PlayerAction.h"
#include "PlayerMove.h"
#include "PlayerCamera.h"
#include "PlayerSanity.h"
#include "PlayerBitten.h"
#include "PlayerPouch.h"
#include "PlayerTarget.h"
#include "PlayerRead.h"
#include "PlayerUI.h"
#include "PlayerDispMessage.h"
namespace nsHikageri
{
	namespace nsFlashLight { class FlashLight; }

	namespace nsPlayer
	{	
		class Player : public IGameObject
		{
		public:
			enum EnPlayerStates
			{
				enState_Normal,
				enState_Bitten,
				enState_Dead,
				enState_Stop,
				enState_Read,
				enStatesNum,
				enState_Invincible,
			};

			~Player();
			bool Start();
			void Update();

			/// @brief �v���C���[�̃��f���̃C���X�^���X���擾����B
			/// @return �v���C���[�̃��f���̃C���X�^���X
			SkinModelRender* GetPlayerModel() { return m_playerModel; }

			/// @brief �v���C���[�̃L�����R�����擾����B(PlayerMove�N���X�ŗ��p)
			/// @return �v���C���[�̃L�����R��
			CharacterController* GetCharaCon() { return &m_charaCon; };

			//�v���C���[�̏�Ԃ�ݒ�
			void SetPlayerState(EnPlayerStates plState) { m_playerState = plState; }
			//�v���C���[�̏�Ԃ��擾
			EnPlayerStates GetPlayerState() { return m_playerState; }

			/// @brief ���G���Ԃ�ݒ�(��)
			/// @param time �ݒ肷�鎞��
			void SetInvincible(int time) { m_playerState = enState_Invincible; m_invincibleTime = time; }

			//���G���̏���
			void Invincible();

			/// @brief �����d����ݒ�
			/// @param flashLight �����d��
			void SetFlashLight(nsFlashLight::FlashLight* flashLight) { m_flashLight = flashLight; }

			/// @brief �����d�����擾
			/// @return �����d��
			nsFlashLight::FlashLight* GetFlashLight() { return m_flashLight; }

			//�v���C���[�֌W�̃C���X�^���X�ɃA�N�Z�X����
			PlayerMove* GetPlayerMove() { return &m_playerMove; };
			PlayerCamera* GetPlayerCamera() { return &m_playerCamera; };
			PlayerAction* GetPlayerAction() { return &m_playerAction; };
			PlayerSanity* GetPlayerSanity() { return &m_playerSanity; };
			PlayerBitten* GetPlayerBitten() { return &m_playerBitten; }
			PlayerPouch* GetPlayerPouch() { return &m_playerPouch; }
			PlayerTarget* GetPlayerTarget() { return &m_playerTarget; };
			PlayerRead* GetPlayerRead() { return &m_playerRead; }
			PlayerUI* GetPlayerUI() { return &m_playerUI; }
			PlayerDispMessage* GetPlayerDispMessage() { return &m_playerDispMessage; }
		private:
			//���f��
			SkinModelRender* m_playerModel = nullptr;
			//�v���C���[�̃L�����R��
			CharacterController m_charaCon;

			//���G����
			int m_invincibleTime = 0;

			//�v���C���[�֌W�̃N���X
			PlayerMove m_playerMove;
			PlayerCamera m_playerCamera;
			PlayerAction m_playerAction;
			PlayerSanity m_playerSanity;
			PlayerBitten m_playerBitten;
			PlayerPouch m_playerPouch;
			PlayerTarget m_playerTarget;
			PlayerRead m_playerRead;
			PlayerUI m_playerUI;
			PlayerDispMessage m_playerDispMessage;

			EnPlayerStates m_playerState = enState_Normal;

			//�����d��
			nsFlashLight::FlashLight* m_flashLight = nullptr;
		};
	}
}