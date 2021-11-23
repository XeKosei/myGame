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
			void ExecuteUpdate();

			//�Ή�
			void Mineralization();

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
		};

	}
}