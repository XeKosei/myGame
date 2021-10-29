#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerMove;
		class PlayerCamera;
		class PlayerAction;
		class PlayerAction : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();

			/// @brief プレイヤーにアクセスできるようにする。
			/// @param pl プレイヤーの参照
			void SetPlayer(Player* pl) { m_player = pl; };

			//屈んでいるかどうか
			bool GetCrouchDownFlag() { return m_crouchDownFlag; }

			//屈む。
			void CrouchDown();

		private:
			//プレイヤー
			Player* m_player = nullptr;
			//屈むアクション関連
			bool m_crouchDownFlag = false;
		};
	}
}

