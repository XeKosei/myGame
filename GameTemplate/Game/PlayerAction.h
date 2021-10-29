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

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

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

