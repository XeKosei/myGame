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

			//�ڂ̍����̐ݒ�Ŏg�p����ϐ�
			void EyeHeightMove();

			void SetCameraDir(Vector3 dir) { m_cameraDir = dir; };

			Vector3 GetCameraPos() { return m_cameraPos; };
			/// @brief �J�����̌������擾
			/// @return �J�����̌���
			Vector3 GetDirection() { return g_camera3D->GetForward(); }

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
			float m_plEyeHeight = 0.0f;
			//�v���C���[
			Player* m_player = nullptr;

			//�ڂ̍����̐ݒ�Ŏg�p����ϐ�
			float m_addEyeHeight = 0.0f;
			bool m_addEyeHeightFlag = true;
			float speed = 0.0f;
			bool m_resetEyeHeightFlag = true;
		};
	}
}