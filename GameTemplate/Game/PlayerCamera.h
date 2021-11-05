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

			//目の高さの設定で使用する変数
			void EyeHeightMove();

			void SetCameraDir(Vector3 dir) { m_cameraDir = dir; };

			Vector3 GetCameraPos() { return m_cameraPos; };
			/// @brief カメラの向きを取得
			/// @return カメラの向き
			Vector3 GetDirection() { return g_camera3D->GetForward(); }

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
			float m_plEyeHeight = 0.0f;
			//プレイヤー
			Player* m_player = nullptr;

			//目の高さの設定で使用する変数
			float m_addEyeHeight = 0.0f;
			bool m_addEyeHeightFlag = true;
			float speed = 0.0f;
			bool m_resetEyeHeightFlag = true;
		};
	}
}