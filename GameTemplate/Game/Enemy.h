#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsEnemy
	{
		class EnemySearchPlayer;
		class EnemyChase;
		class EnemyAttack;
		class EnemyAnim;

		class Enemy : public IGameObject
		{
		public:
			~Enemy();
			bool Start();
			void Update();

			//エネミーの状態
			enum EnEnemyStates
			{
				enState_SearchPlayer,
				enState_Chase,
				enState_Attack,
				enStatesNum
			};

			SkinModelRender* GetEnemyModel() { return m_enemyModel; }

			/// @brief エネミーのキャラコンを取得する。(EnemyChaseクラスで利用)
			/// @return エネミーのキャラコン
			CharacterController* GetCharaCon() { return &m_charaCon; };

			/// @brief プレイヤーを設定
			/// @param pl プレイヤー
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; }

			/// @brief プレイヤーを取得
			/// @return プレイヤー
			nsPlayer::Player* GetPlayer() { return m_player; }

			EnEnemyStates GetEnemyState() { return m_enemyState; };

			/// @brief エネミーの状態を設定する。
			/// @param enState エネミーの状態
			void SetEnemyState(EnEnemyStates enState) { m_enemyState = enState; };

			//エネミー関係のインスタンスにアクセスする
			EnemyChase* GetEnemyChase() { return m_enemyChase; }
			EnemyAttack* GetEnemyAttack() { return m_enemyAttack; };
			EnemyAnim* GetEnemyAnim() { return m_enemyAnim; };
		private:
			//モデル
			SkinModelRender* m_enemyModel = nullptr;
			//キャラコン
			CharacterController m_charaCon;

			//プレイヤー
			nsPlayer::Player* m_player = nullptr;

			//エネミーの状態
			EnEnemyStates m_enemyState = enState_SearchPlayer;

			//エネミー関連
			EnemySearchPlayer* m_enemySearchPlayer = nullptr;
			EnemyChase* m_enemyChase = nullptr;
			EnemyAttack* m_enemyAttack = nullptr;
			EnemyAnim* m_enemyAnim = nullptr;
		};
	}
}