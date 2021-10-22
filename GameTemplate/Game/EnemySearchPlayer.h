#pragma once
namespace nsHikageri
{
	namespace nsEnemy
	{
		class EnemySearchPlayer : public IGameObject
		{
		public:
			bool Start();

			void ExecuteUpdate();

			void Move();

			void Turn();

			void SetMovePos(Vector3 pos1, Vector3 pos2) { m_searchPos[0] = pos1; m_searchPos[1] = pos2; };

			/// @brief エネミーにアクセスできるようにする。
			/// @param pl エネミーの参照
			void SetEnemy(Enemy* enemy) { m_enemy = enemy; };

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
			Vector3 m_dir = { -1.0f, 0.0f, 0.0f };
			//回転
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//エネミーが向かう位置
			Vector3 m_targetPos = { Vector3::Zero };

			//仮の移動処理
			Vector3 m_searchPos[2] = { { 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f} };
			bool m_searchFlag = false;
		};

	}
}