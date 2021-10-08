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

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

		private:
			//�J�����̎��_
			Vector3 m_cameraPos = { 0.0f, 200.0f, -1500.0f };
			//�J�����̒����_
			Vector3 m_toCameraPos = { 0.0f, 200.0f, 500.0f };
			//�J�����̌���
			Vector3 m_cameraDir = { 0.0f,0.0f,1.0f };
			//�v���C���[
			Player* m_player = nullptr;
		};
	}
}