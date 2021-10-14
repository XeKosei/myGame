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

			//���ށB
			void CrouchDown();

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief �v���C���[���[�u�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param plCamera �v���C���[���[�u�ɎQ��
			void SetPlayerMove(PlayerMove* plMove) { m_playerMove = plMove; };

			/// @brief �v���C���[�J�����ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param plCamera �v���C���[�J�����̎Q��
			void SetPlayerCamera(PlayerCamera* plCamera) { m_playerCamera = plCamera; };

		private:
			//�v���C���[
			Player* m_player = nullptr;
			//�v���C���[���[�u�N���X
			PlayerMove* m_playerMove = nullptr;
			//�v���C���[�J����
			PlayerCamera* m_playerCamera = nullptr;
			//���ރA�N�V�����֘A
			bool m_crouchDownFlag = false;
		};
	}
}

