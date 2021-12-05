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
			void Init(Enemy* enemy);
			void ExecuteUpdate();

			//石化
			void Mineralization();

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
		};

	}
}