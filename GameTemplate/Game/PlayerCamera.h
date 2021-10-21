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

			void SetCameraDir(Vector3 dir) { m_cameraDir = dir; };

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief プレイヤーの目の高さを設定
			/// @param height 設定する高さ。
			void SetPlEyeHeight(int height) { m_plEyeHeight = height; };

		private:
			//カメラの視点
			Vector3 m_cameraPos = { 0.0f, 200.0f, -1500.0f };
			//カメラの注視点
			Vector3 m_toCameraPos = { 0.0f, 200.0f, 500.0f };
			//カメラの向き
			Vector3 m_cameraDir = { 0.0f,0.0f,1.0f };
			//プレイヤーの目の高さ
			int m_plEyeHeight = 0.0f;
			//プレイヤー
			Player* m_player = nullptr;
		};
	}
}