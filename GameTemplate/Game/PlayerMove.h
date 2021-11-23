#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		//class PlayerConstant;

		class PlayerMove : public IGameObject
		{
		public:
			~PlayerMove();
			bool Start();
			void ExecuteUpdate();
			void Move();	//移動処理
			void Turn();	//回転処理

			Vector3 GetVelocity() { return m_velocity; };

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief プレイヤーのモデルの位置を取得
			/// @return プレイヤーの位置
			Vector3 GetPosition() { return m_position; };
			
		private:
			//位置
			Vector3 m_position = { Vector3::Zero };
			//プレイヤーが動く速さ
			float m_plMoveSpeed = 0.0f;
			//速度
			Vector3 m_velocity = { Vector3::Zero };
			//回転
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//プレイヤー
			Player* m_player = nullptr;
		};
	}
}