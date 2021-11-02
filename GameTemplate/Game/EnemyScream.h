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

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
		};
	}
}

