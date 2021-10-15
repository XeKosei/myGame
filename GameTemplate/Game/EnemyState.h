#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyState : public IGameObject
		{
		public:
			//エネミーの状態
			enum EnEnemyStates
			{
				enState_SearchPlayer,
				enState_Chase,
				enState_Attack,
				enStatesNum
			};

			void ExecuteUpdate();

			void SearchPlayer();
			//プレイヤーを追いかける処理
			void Chase();

			void SetEnemyState(EnEnemyStates enState) { m_enemyStates = enState; };

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//エネミーの状態
			EnEnemyStates m_enemyStates = enState_Chase;

		};
	}
}