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
			void Move();	//移動処理
			void Turn();	//回転処理

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* pl) { m_enemy = pl; };

			/// @brief エネミーが向かう位置を設定
			/// @param pos エネミーが向かう位置
			void SetTarget(Vector3 pos) { m_targetPos = pos; }

		private:
			//位置
			Vector3 m_position = { Vector3::Zero };
			//エネミーが動く速さ
			float m_moveSpeed = 0.0f;
			//速度
			Vector3 m_velocity = { Vector3::Zero };
			//回転
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//エネミーが向かう位置
			Vector3 m_targetPos = {Vector3::Zero};
			//エネミー
			Enemy* m_enemy = nullptr;
		};
	}
}

