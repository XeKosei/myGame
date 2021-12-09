#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;

		class PlayerMove
		{
		public:
			~PlayerMove();
			void Init(Player* pl);
			void ExecuteUpdate();
			void Move();	//�ړ�����
			void Turn();	//��]����
			void FootStepsSE();	//����

			Vector3 GetVelocity() { return m_velocity; };

			/// @brief �v���C���[�̃��f���̈ʒu���擾
			/// @return �v���C���[�̈ʒu
			Vector3 GetPosition() { return m_position; };
			
		private:
			//�ʒu
			Vector3 m_position = { Vector3::Zero };
			//�v���C���[����������
			float m_plMoveSpeed = 0.0f;
			//���x
			Vector3 m_velocity = { Vector3::Zero };
			//��]
			Quaternion m_qRot = { 0.0f,0.0f,0.0f,0.0f };
			//�v���C���[
			Player* m_player = nullptr;

			//����
			float m_footStepInterval = 0;
		};
	}
}