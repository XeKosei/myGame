#pragma once

namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyFlinch : public IGameObject
		{
		public:
			~EnemyFlinch();
			void ExecuteUpdate();

			//石化
			void Mineralization();

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
		};

	}
}