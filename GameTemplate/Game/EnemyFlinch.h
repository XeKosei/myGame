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

			//�Ή�
			void Mineralization();

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
		};

	}
}