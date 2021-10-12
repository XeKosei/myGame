#pragma once
namespace nsHikageri
{
	namespace nsPlayer
	{
		class Player;
		//class PlayerConstant;

		class PlayerMove : public IGameObject
		{
		public:
			bool Start();
			void ExecuteUpdate();
			void Move();	//�ړ�����
			void Turn();	//��]����

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(Player* pl) { m_player = pl; };

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
		};
	}
}