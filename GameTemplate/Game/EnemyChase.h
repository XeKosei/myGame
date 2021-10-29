#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyChase : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();
			void Chase();	//追跡処理

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
		};
	}
}

