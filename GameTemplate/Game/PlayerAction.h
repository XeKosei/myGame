#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		class PlayerMove;
		class PlayerCamera;
		class PlayerAction;

		class PlayerAction
		{
		public:
			~PlayerAction();
			void Init(Player* pl);
			void ExecuteUpdate();

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

