#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyVoice
		{
		public:
			~EnemyVoice();
			void Init(Enemy* enemy);
			void ExecuteUpdate();

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
		};
	}
}
