#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsEnemy
	{
		class EnemySearchPlayer;
		class EnemyChase;
		class EnemyAttack;

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

			/// @brief エネミーの状態を設定する。
			/// @param enState エネミーの状態
			void SetEnemyState(EnEnemyStates enState) { m_enemyStates = enState; };

			//エネミー関係のインスタンスにアクセスする
			EnemyChase* GetEnemyChase() { return m_enemyChase; }
			EnemyAttack* GetEnemyAttack() { return m_enemyAttack; };
		private:
			//モデル
			SkinModelRender* m_enemyModel = nullptr;
			//キャラコン
			CharacterController m_charaCon;
			//アニメーション
			enum {
				enAnimationClip_Run,
				enAnimationClip_num,  //列挙内で使う要素の数を表すダミー
			};
			AnimationClip animationClips[enAnimationClip_num];

			//プレイヤー
			nsPlayer::Player* m_player = nullptr;

			//エネミーの状態
			EnEnemyStates m_enemyStates = enState_Chase;

			//エネミー関連
			EnemySearchPlayer* m_enemySearchPlayer = nullptr;
			EnemyChase* m_enemyChase = nullptr;
			EnemyAttack* m_enemyAttack = nullptr;
		};
	}
}