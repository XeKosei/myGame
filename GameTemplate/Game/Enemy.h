#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsEnemy
	{
		class EnemyMove;
		class EnemySearchPlayer;
		class EnemyChase;
		class EnemyAttack;
		class EnemyAnim;
		class EnemyScream;
		class EnemyFlinch;
		class EnemyStress;

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
				enState_Scream,
				enState_Flinch,
				enState_Suffer,
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

			EnEnemyStates GetEnemyState() { return m_enemyState; };

			/// @brief �G�l�~�[�̏�Ԃ�ݒ肷��B
			/// @param enState �G�l�~�[�̏��
			void SetEnemyState(EnEnemyStates enState) { m_enemyState = enState; };

			//m_searchPos�ł̉��ړ������Ŏg�p
			void SetMovePos(Vector3 pos1, Vector3 pos2) { m_searchPos[0] = pos1; m_searchPos[1] = pos2; };

			//�G�l�~�[�֌W�̃C���X�^���X�ɃA�N�Z�X����
			EnemyMove* GetEnemyMove() { return m_enemyMove; }
			EnemySearchPlayer* GetEnemySearchPlayer() { return m_enemySearchPlayer; };
			EnemyChase* GetEnemyChase() { return m_enemyChase; }
			EnemyAttack* GetEnemyAttack() { return m_enemyAttack; };
			EnemyScream* GetEnemyScream() { return m_enemyScream; }
			EnemyFlinch* GetEnemyFlinch() { return m_enemyFlinch; }
			EnemyStress* GetEnemyStress() { return m_enemyStress; }
			EnemyAnim* GetEnemyAnim() { return m_enemyAnim; };
		private:
			//���f��
			SkinModelRender* m_enemyModel = nullptr;
			//�L�����R��
			CharacterController m_charaCon;

			//�v���C���[
			nsPlayer::Player* m_player = nullptr;

			//�G�l�~�[�̏��
			EnEnemyStates m_enemyState = enState_SearchPlayer;

			Vector3 m_searchPos[2] = { { 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f} };

			//�G�l�~�[�֘A
			EnemyMove* m_enemyMove = nullptr;
			EnemySearchPlayer* m_enemySearchPlayer = nullptr;
			EnemyChase* m_enemyChase = nullptr;
			EnemyAttack* m_enemyAttack = nullptr;
			EnemyScream* m_enemyScream = nullptr;
			EnemyFlinch* m_enemyFlinch = nullptr;
			EnemyStress* m_enemyStress = nullptr;
			EnemyAnim* m_enemyAnim = nullptr;
		};
	}
}