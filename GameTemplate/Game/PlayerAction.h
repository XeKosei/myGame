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

			//����ł��邩�ǂ���
			bool GetCrouchDownFlag() { return m_crouchDownFlag; }

			//���ށB
			void CrouchDown();

		private:
			//�v���C���[
			Player* m_player = nullptr;
			//���ރA�N�V�����֘A
			bool m_crouchDownFlag = false;
		};
	}
}

