#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsEnemy
	{
		class EnemySearchPlayer;
		class EnemyChase;
		class EnemyAttack;

		class Enemy : public IGameObject
		{
		public:
			~Enemy();
			bool Start();
			void Update();

			//�G�l�~�[�̏��
			enum EnEnemyStates
			{
				enState_SearchPlayer,
				enState_Chase,
				enState_Attack,
				enStatesNum
			};

			SkinModelRender* GetEnemyModel() { return m_enemyModel; }

			/// @brief �G�l�~�[�̃L�����R�����擾����B(EnemyChase�N���X�ŗ��p)
			/// @return �G�l�~�[�̃L�����R��
			CharacterController* GetCharaCon() { return &m_charaCon; };

			/// @brief �v���C���[��ݒ�
			/// @param pl �v���C���[
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; }

			/// @brief �v���C���[���擾
			/// @return �v���C���[
			nsPlayer::Player* GetPlayer() { return m_player; }

			/// @brief �G�l�~�[�̏�Ԃ�ݒ肷��B
			/// @param enState �G�l�~�[�̏��
			void SetEnemyState(EnEnemyStates enState) { m_enemyStates = enState; };

			//�G�l�~�[�֌W�̃C���X�^���X�ɃA�N�Z�X����
			EnemyChase* GetEnemyChase() { return m_enemyChase; }
			EnemyAttack* GetEnemyAttack() { return m_enemyAttack; };
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

			//�G�l�~�[�̏��
			EnEnemyStates m_enemyStates = enState_Chase;

			//�G�l�~�[�֘A
			EnemySearchPlayer* m_enemySearchPlayer = nullptr;
			EnemyChase* m_enemyChase = nullptr;
			EnemyAttack* m_enemyAttack = nullptr;
		};
	}
}