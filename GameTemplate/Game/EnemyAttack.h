#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyAttack : public IGameObject
		{
		public:
			void ExecuteUpdate();

			void Attack();

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
		};

	}
}