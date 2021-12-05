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
			void Init(Enemy* enemy);
			void ExecuteUpdate();

		private:
			//エネミー
			Enemy* m_enemy = nullptr;

			//レイを飛ばす間隔
			int m_calcLineHitModelConstant = 0;
		};
	}
}
