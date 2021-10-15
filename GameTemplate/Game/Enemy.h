#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }

	namespace nsEnemy
	{
		class EnemyMove;
		class EnemyState;
		class EnemyAttack;

		class Enemy : public IGameObject
		{
		public:
			~Enemy();
			bool Start();
			void Update();

			/// @brief エネミーモデルの位置を設定する。EnemyMoveクラスで利用)
			/// @param pos 設定する位置
			void SetPosition(Vector3 pos) { m_enemyModel->SetPosition(pos); };

			/// @brief エネミーのモデルの回転を設定する。(EnemyMoveクラスで利用)
			/// @param qRot 設定する回転
			void SetRotation(Quaternion qRot) { m_enemyModel->SetRotation(qRot); };

			/// @brief エネミーのキャラコンを取得する。(EnemyMoveクラスで利用)
			/// @return エネミーのキャラコン
			CharacterController* GetCharaCon() { return &m_charaCon; };

			/// @brief プレイヤーを設定
			/// @param pl プレイヤー
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; }

			/// @brief プレイヤーを取得
			/// @return プレイヤー
			nsPlayer::Player* GetPlayer() { return m_player; }

			EnemyMove* GetEnemyMove() { return m_enemyMove; }
			EnemyAttack* GetEnemyAttack() { return m_enemyAttack; };
			EnemyState* GetEnemyState() { return m_enemyState; };
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
			//ターゲットの位置
			Vector3 m_targetPos = Vector3::Zero;

			//エネミー関連
			EnemyMove* m_enemyMove = nullptr;
			EnemyState* m_enemyState = nullptr;
			EnemyAttack* m_enemyAttack = nullptr;
		};
	}
}