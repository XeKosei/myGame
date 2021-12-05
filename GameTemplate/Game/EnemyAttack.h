#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyAttack
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
			void Init(Enemy* enemy);
			void ExecuteUpdate();

			void Reset();

			void Attack();

			void PreBite();
			void Bite();
			void EndBite();

			EnEnemyBiteStates GetBiteState() { return m_biteState; };

			//���݂��ɒ�R����B
			void RegistToBite(int registNum) { m_enemyBiteCount -= registNum; };

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