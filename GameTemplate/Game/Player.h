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
		//class PlayerConstant;

		class Player : public IGameObject
		{
		public:
			~Player();
			bool Start();
			void Update();

			/// @brief �v���C���[�̃��f���̈ʒu��ݒ肷��B(PlayerMove�N���X�ŗ��p)
			/// @param pos �ݒ肷��ʒu
			void SetPosition(Vector3 pos) { m_position = pos; m_playerModel->SetPosition(m_position); };
	
			/// @brief �v���C���[�̃��f���̈ʒu���擾
			/// @return �v���C���[�̈ʒu
			Vector3 GetPosition() { return m_position; };

			/// @brief �v���C���[�̃��f���̉�]��ݒ肷��B(PlayerMove�N���X�ŗ��p)
			/// @param qRot �ݒ肷���]
			void SetRotation(Quaternion qRot) { m_playerModel->SetRotation(qRot); };

			void SetScale(Vector3  scale) { m_playerModel->SetScale(scale); };

			/// @brief �v���C���[�̃L�����R�����擾����B(PlayerMove�N���X�ŗ��p)
			/// @return �v���C���[�̃L�����R��
			CharacterController* GetCharaCon() { return &m_charaCon; };

			//���񂾂��ǂ���(��)
			void SetDeadFlag(bool isDead) { m_deadFlag = isDead; }

			PlayerMove* GetPlayerMove() { return m_playerMove; };
			PlayerCamera* GetPlayerCamera() { return m_playerCamera; };
			PlayerAction* nsPlayerActionConstant() { return m_playerAction; };
			PlayerHP* GetPlayerHP() { return m_playerHP; };

		private:
			bool m_deadFlag = false;
			//�v���C���[�̈ʒu
			Vector3 m_position = { Vector3::Zero };

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