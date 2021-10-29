#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class Enemy;
		class EnemyMove : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			void Move();

			void Turn();

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

			void SetPosition(Vector3 pos) { 
				m_position = pos;
				m_enemy->GetCharaCon()->SetPosition(m_position);
				m_enemy->GetEnemyModel()->SetPosition(m_position);
			}

			/// @brief Enemyのm_positionを取得
			/// @return エネミーの位置
			Vector3 GetPosition() { return m_position; };

			/// @brief Enemyの向きを取得。
			/// @return エネミーの向き
			Vector3 GetDirection() { return m_direction; }

			/// @brief Enemyの移動速度を取得
			/// @return エネミーの移動速度
			Vector3 GetVelocity() { return m_velocity; }

			/// @brief エネミーが向かう位置を設定
			/// @param pos エネミーが向かう位置
			void SetTarget(Vector3 pos) { m_targetPos = pos; }

			/// @brief エネミーのターゲット位置を取得する。
			/// @return エネミーのターゲット位置
			Vector3 GetTarget() { return m_targetPos; }

			/// @brief エネミーの移動の速さを取得
			/// @param speed エネミーの移動の速さ
			void SetMoveSpeed(float speed) { m_moveSpeed = speed; };

		private:
			//エネミー
			Enemy* m_enemy = nullptr;
			//位置
			Vector3 m_position = { Vector3::Zero };
			//エネミーが動く速さ
			float m_moveSpeed = 0.0f;
			//速度
			Vector3 m_velocity = { Vector3::Zero };
			//向き
			Vector3 m_direction = { 0.0f, 0.0f, 0.0f };
			//回転
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//エネミーが向かう位置
			Vector3 m_targetPos = { Vector3::Zero };
		};

	}
}