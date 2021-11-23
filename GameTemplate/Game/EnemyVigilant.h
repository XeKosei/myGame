#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyVigilant : public IGameObject
		{
		public:
			~EnemyVigilant();
			void ExecuteUpdate();

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;

			//レイを飛ばす間隔
			int m_calcLineHitModelConstant = 0;
		};
	}
}
