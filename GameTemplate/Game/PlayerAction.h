#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerMove;
		class PlayerCamera;
		class PlayerAction;
		//class PlayerConstant;
		class PlayerAction : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			//屈む。
			void CrouchDown();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief プレイヤームーブにアクセスできるようにする。
			/// @param plCamera プレイヤームーブに参照
			void SetPlayerMove(PlayerMove* plMove) { m_playerMove = plMove; };

			/// @brief プレイヤーカメラにアクセスできるようにする。
			/// @param plCamera プレイヤーカメラの参照
			void SetPlayerCamera(PlayerCamera* plCamera) { m_playerCamera = plCamera; };

		private:
			//プレイヤー
			Player* m_player = nullptr;
			//プレイヤームーブクラス
			PlayerMove* m_playerMove = nullptr;
			//プレイヤーカメラ
			PlayerCamera* m_playerCamera = nullptr;
			//屈むアクション関連
			bool m_crouchDownFlag = false;
		};
	}
}

