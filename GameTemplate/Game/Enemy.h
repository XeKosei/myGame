#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class EnemyMove;

		class Enemy : public IGameObject
		{
		public:
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

			//エネミー関連
			EnemyMove* m_enemyMove = nullptr;
		};
	}
}