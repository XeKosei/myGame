#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		//class PlayerConstant;

		class PlayerCamera : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//カメラの視点
			Vector3 m_cameraPos = { 0.0f, 200.0f, -1500.0f };
			//カメラの注視点
			Vector3 m_toCameraPos = { 0.0f, 200.0f, 500.0f };
			//カメラの向き
			Vector3 m_cameraDir = { 0.0f,0.0f,1.0f };
			//プレイヤー
			Player* m_player = nullptr;
		};
	}
}