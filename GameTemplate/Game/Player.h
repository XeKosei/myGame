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

		class Player : public IGameObject
		{
		public:
			~Player();
			bool Start();
			void Update();

			/// @brief �v���C���[�̃��f���̃C���X�^���X���擾����B
			/// @return �v���C���[�̃��f���̃C���X�^���X
			SkinModelRender* GetPlayerModel() { return m_playerModel; }

			/// @brief �v���C���[�̃L�����R�����擾����B(PlayerMove�N���X�ŗ��p)
			/// @return �v���C���[�̃L�����R��
			CharacterController* GetCharaCon() { return &m_charaCon; };

			//���񂾂��ǂ���(��)
			void SetDeadFlag(bool isDead) { m_deadFlag = isDead; }

			//�v���C���[�֌W�̃C���X�^���X�ɃA�N�Z�X����
			PlayerMove* GetPlayerMove() { return m_playerMove; };
			PlayerCamera* GetPlayerCamera() { return m_playerCamera; };
			PlayerAction* nsPlayerActionConstant() { return m_playerAction; };
			PlayerHP* GetPlayerHP() { return m_playerHP; };

		private:
			bool m_deadFlag = false;

			//���f��
			SkinModelRender* m_playerModel = nullptr;
			//�v���C���[�̃L�����R��
			CharacterController m_charaCon;

			//�A�j���[�V�����֘A
			enum {
				enAnimationClip_Idle,
				enAnimationClip_walk,
				enAnimationClip_num,  //�񋓓��Ŏg���v�f�̐���\���_�~�[
			};
			AnimationClip animationClips[enAnimationClip_num];

			//�v���C���[�֌W�̃N���X
			PlayerMove* m_playerMove = nullptr;
			PlayerCamera* m_playerCamera = nullptr;
			PlayerAction* m_playerAction = nullptr;
			PlayerHP* m_playerHP = nullptr;

			//�����d��
			nsFlashLight::FlashLight* m_flashLight = nullptr;
		};
	}
}