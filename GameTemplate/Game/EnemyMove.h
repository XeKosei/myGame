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

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetEnemy(Enemy* pl) { m_enemy = pl; };
		private:
			//位置
			Vector3 m_position = { Vector3::Zero };
			//プレイヤーが動く速さ
			float m_moveSpeed = 0.0f;
			//速度
			Vector3 m_velocity = { Vector3::Zero };
			//回転
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//プレイヤー
			Enemy* m_enemy = nullptr;
		};
	}
}

