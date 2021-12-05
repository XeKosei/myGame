#pragma once
namespace nsHikageri
{
	namespace nsEnemy 
	{
		class Enemy;
		class EnemyScream : public IGameObject
		{
		public:
			~EnemyScream();
			void Init(Enemy* enemy);
			void ExecuteUpdate();

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
		};
	}
}

