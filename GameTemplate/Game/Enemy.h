#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsEnemy
	{
		class EnemyMove;
		class EnemyState;
		class EnemyAttack;

		class Enemy : public IGameObject
		{
		public:
			~Enemy();
			bool Start();
			void Update();

			/// @brief �G�l�~�[���f���̈ʒu��ݒ肷��BEnemyMove�N���X�ŗ��p)
			/// @param pos �ݒ肷��ʒu
			void SetPosition(Vector3 pos) { m_enemyModel->SetPosition(pos); };

			/// @brief �G�l�~�[�̃��f���̉�]��ݒ肷��B(EnemyMove�N���X�ŗ��p)
			/// @param qRot �ݒ肷���]
			void SetRotation(Quaternion qRot) { m_enemyModel->SetRotation(qRot); };

			/// @brief �G�l�~�[�̃L�����R�����擾����B(EnemyMove�N���X�ŗ��p)
			/// @return �G�l�~�[�̃L�����R��
			CharacterController* GetCharaCon() { return &m_charaCon; };

			/// @brief �v���C���[��ݒ�
			/// @param pl �v���C���[
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; }

			/// @brief �v���C���[���擾
			/// @return �v���C���[
			nsPlayer::Player* GetPlayer() { return m_player; }

			EnemyMove* GetEnemyMove() { return m_enemyMove; }
			EnemyAttack* GetEnemyAttack() { return m_enemyAttack; };
			EnemyState* GetEnemyState() { return m_enemyState; };
		private:
			//���f��
			SkinModelRender* m_enemyModel = nullptr;
			//�L�����R��
			CharacterController m_charaCon;
			//�A�j���[�V����
			enum {
				enAnimationClip_Run,
				enAnimationClip_num,  //�񋓓��Ŏg���v�f�̐���\���_�~�[
			};
			AnimationClip animationClips[enAnimationClip_num];

			//�v���C���[
			nsPlayer::Player* m_player = nullptr;
			//�^�[�Q�b�g�̈ʒu
			Vector3 m_targetPos = Vector3::Zero;

			//�G�l�~�[�֘A
			EnemyMove* m_enemyMove = nullptr;
			EnemyState* m_enemyState = nullptr;
			EnemyAttack* m_enemyAttack = nullptr;
		};
	}
}