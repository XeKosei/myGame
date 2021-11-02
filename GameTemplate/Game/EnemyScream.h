#pragma once
namespace nsHikageri
{
	namespace nsEnemy 
	{
		class Enemy;
		class EnemyScream : public IGameObject
		{
		public:

			void ExecuteUpdate();

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
		};
	}
}

