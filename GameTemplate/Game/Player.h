#pragma once
namespace nsHikageri
{
	namespace nsFlashLight { class FlashLight; }

	namespace nsPlayer
	{
		class PlayerMove;
		class PlayerCamera;		
		class PlayerAction;
		class PlayerHP;
		class PlayerBitten;

		class Player : public IGameObject
		{
		public:
			enum EnPlayerStates
			{
				enState_Normal,
				enState_Bitten,
				enState_Dead,
				enState_Stop,
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

			//�v���C���[�֌W�̃C���X�^���X�ɃA�N�Z�X����
			PlayerMove* GetPlayerMove() { return m_playerMove; };
			PlayerCamera* GetPlayerCamera() { return m_playerCamera; };
			PlayerAction* nsPlayerActionConstant() { return m_playerAction; };
			PlayerHP* GetPlayerHP() { return m_playerHP; };
			PlayerBitten* GetPlayerBitten() { return m_playerBitten; }
		private:
			//���f��
			SkinModelRender* m_playerModel = nullptr;
			//�v���C���[�̃L�����R��
			CharacterController m_charaCon;

			//���G����
			int m_invincibleTime = 0;

			//�v���C���[�֌W�̃N���X
			PlayerMove* m_playerMove = nullptr;
			PlayerCamera* m_playerCamera = nullptr;
			PlayerAction* m_playerAction = nullptr;
			PlayerHP* m_playerHP = nullptr;
			PlayerBitten* m_playerBitten = nullptr;

			EnPlayerStates m_playerState = enState_Normal;

			//�����d��
			nsFlashLight::FlashLight* m_flashLight = nullptr;
		};
	}
}