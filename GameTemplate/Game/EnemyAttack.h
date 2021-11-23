#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyAttack : public IGameObject
		{
		public:
			enum EnEnemyBiteStates
			{
				enBiteState_PreBite,
				enBiteState_Bite,
				enBiteState_EndBite,
				enBiteStatesNum
			};

			~EnemyAttack();
			bool Start();
			void ExecuteUpdate();

			void Attack();

			void PreBite();
			void Bite();
			void EndBite();

			EnEnemyBiteStates GetBiteState() { return m_biteState; };

			//���݂��ɒ�R����B
			void RegistToBite(int registNum) { m_enemyBiteCount -= registNum; };

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
			int m_attackMotionCount = 0;

			//���݂��s���̑J��
			EnEnemyBiteStates m_biteState = enBiteState_PreBite;
			//�G�l�~�[�����݂������鎞�Ԃ��J�E���g
			int m_enemyBiteCount = 0;
			//�G�l�~�[�̊��݂��A�j���[�V�����̎��Ԃ��J�E���g
			int m_enemyBiteAnimCount = 0;
		};

	}
}