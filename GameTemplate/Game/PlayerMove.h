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
			bool Start();
			void ExecuteUpdate();
			void Move();
			void Turn();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//位置
			Vector3 m_position = { Vector3::Zero };
			//速度
			Vector3 m_velocity = { Vector3::Zero };
			//回転
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//プレイヤー
			Player* m_player = nullptr;
		};
	}
}