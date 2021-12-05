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
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
		};
	}
}

