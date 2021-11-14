#pragma once

namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsBackGround { class BackGround; }

	namespace nsEnemy
	{
		class EnemyMove;
		class EnemySearchPlayer;
		class EnemyChase;
		class EnemyAttack;
		class EnemyAnim;
		class EnemyScream;
		class EnemyFlinch;
		class EnemyStress;

		class Enemy : public IGameObject
		{
		public:
			enum EnSearchArea
			{
				enSearchArea_1,
				enSearchArea_2,
				enSearchArea_3,
				enSearchArea_num
			};

			~Enemy();
			bool Start();
			void Update();

			//エネミーの状態
			enum EnEnemyStates
			{
				enState_SearchPlayer,
				enState_Chase,
				enState_Attack,
				enState_Scream,
				enState_Flinch,
				enState_Petrifaction,
				enState_Suffer,
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

			/// @brief ステージを取得
			/// @return ステージ
			nsBackGround::BackGround* GetBackGround() { return m_backGround; }

			EnEnemyStates GetEnemyState() { return m_enemyState; };

			/// @brief エネミーの状態を設定する。
			/// @param enState エネミーの状態
			void SetEnemyState(EnEnemyStates enState) { if (m_enemyState != enState_Petrifaction) { m_enemyState = enState; } };

			//エネミー関係のインスタンスにアクセスする
			EnemyMove* GetEnemyMove() { return m_enemyMove; }
			EnemySearchPlayer* GetEnemySearchPlayer() { return m_enemySearchPlayer; };
			EnemyChase* GetEnemyChase() { return m_enemyChase; }
			EnemyAttack* GetEnemyAttack() { return m_enemyAttack; };
			EnemyScream* GetEnemyScream() { return m_enemyScream; }
			EnemyFlinch* GetEnemyFlinch() { return m_enemyFlinch; }
			EnemyStress* GetEnemyStress() { return m_enemyStress; }
			EnemyAnim* GetEnemyAnim() { return m_enemyAnim; };
		private:
			//モデル
			SkinModelRender* m_enemyModel = nullptr;
			SkinModelRenderEX* m_enemyModelEX = nullptr;
			//キャラコン
			CharacterController m_charaCon;

			//プレイヤー
			nsPlayer::Player* m_player = nullptr;

			//ステージ
			nsBackGround::BackGround* m_backGround = nullptr;

			//エネミーの状態
			EnEnemyStates m_enemyState = enState_SearchPlayer;
			EnSearchArea m_searchArea = enSearchArea_1;

			//エネミー関連
			EnemyMove* m_enemyMove = nullptr;
			EnemySearchPlayer* m_enemySearchPlayer = nullptr;
			EnemyChase* m_enemyChase = nullptr;
			EnemyAttack* m_enemyAttack = nullptr;
			EnemyScream* m_enemyScream = nullptr;
			EnemyFlinch* m_enemyFlinch = nullptr;
			EnemyStress* m_enemyStress = nullptr;
			EnemyAnim* m_enemyAnim = nullptr;
		};
	}
}