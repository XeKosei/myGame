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

			//噛みつきに抵抗する。
			void RegistToBite(int registNum) { m_enemyBiteCount -= registNum; };

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			int m_attackMotionCount = 0;

			//噛みつき行動の遷移
			EnEnemyBiteStates m_biteState = enBiteState_PreBite;
			//エネミーが噛みつき続ける時間をカウント
			int m_enemyBiteCount = 0;
			//エネミーの噛みつきアニメーションの時間をカウント
			int m_enemyBiteAnimCount = 0;
		};

	}
}