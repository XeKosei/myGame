#pragma once
namespace nsHikageri
{
	namespace nsFlashLight { class FlashLight; }

	namespace nsPlayer
	{
		class PlayerMove;
		class PlayerCamera;		
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

			Vector3 GetPosition() { return m_position; };
			/// @brief �v���C���[�̃��f���̉�]��ݒ肷��B(PlayerMove�N���X�ŗ��p)
			/// @param qRot �ݒ肷���]
			void SetRotation(Quaternion qRot) { m_playerModel->SetRotation(qRot); };

			/// @brief �v���C���[�̃L�����R�����擾����B(PlayerMove�N���X�ŗ��p)
			/// @return �v���C���[�̃L�����R��
			CharacterController* GetCharaCon() { return &m_charaCon; };
		private:
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

			//�����d��
			nsFlashLight::FlashLight* m_flashLight = nullptr;
		};
	}
}