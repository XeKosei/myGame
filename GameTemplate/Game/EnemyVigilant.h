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
			//�G�l�~�[
			Enemy* m_enemy = nullptr;

			//���C���΂��Ԋu
			int m_calcLineHitModelConstant = 0;
		};
	}
}
