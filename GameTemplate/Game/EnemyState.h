#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyState : public IGameObject
		{
		public:
			//�G�l�~�[�̏��
			enum EnEnemyStates
			{
				enState_SearchPlayer,
				enState_Chase,
				enState_Attack,
				enStatesNum
			};

			void ExecuteUpdate();

			void SearchPlayer();
			//�v���C���[��ǂ������鏈��
			void Chase();

			void SetEnemyState(EnEnemyStates enState) { m_enemyStates = enState; };

			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//�G�l�~�[
			Enemy* m_enemy = nullptr;
			//�G�l�~�[�̏��
			EnEnemyStates m_enemyStates = enState_Chase;

		};
	}
}