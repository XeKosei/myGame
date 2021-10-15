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

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

			/// @brief エネミーの状態を設定する。
			/// @param enState エネミーの状態
			void SetEnemyState(EnEnemyStates enState) { m_enemyStates = enState; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//エネミーの状態
			EnEnemyStates m_enemyStates = enState_Chase;

		};
	}
}