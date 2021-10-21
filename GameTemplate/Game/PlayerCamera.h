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

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

			/// @brief �v���C���[�̖ڂ̍�����ݒ�
			/// @param height �ݒ肷�鍂���B
			void SetPlEyeHeight(int height) { m_plEyeHeight = height; };

		private:
			//�J�����̎��_
			Vector3 m_cameraPos = { 0.0f, 200.0f, -1500.0f };
			//�J�����̒����_
			Vector3 m_toCameraPos = { 0.0f, 200.0f, 500.0f };
			//�J�����̌���
			Vector3 m_cameraDir = { 0.0f,0.0f,1.0f };
			//�v���C���[�̖ڂ̍���
			int m_plEyeHeight = 0.0f;
			//�v���C���[
			Player* m_player = nullptr;
		};
	}
}