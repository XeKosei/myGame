#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsEnemy { class Enemy; }

	namespace nsGimmick
	{
		class Door : public IGameObject
		{
		public:
			bool Start();
			void Update();

			void Open();
			void Close();

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };
			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };
		private:
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;

			SkinModelRender* m_doorModel = nullptr;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = Vector3::Zero;

			//�h�A���J���Ă��邩�ǂ���
			bool m_openFlag = false;

			//�h�A��(�J����������肵��)�����Ă��邩�ǂ���
			bool m_moveFlag = false;

			//�h�A���O����J����ꂽ���A��납��J����ꂽ��
			bool m_isOpenFromForward = false;

			float m_defaultAngle = 0.0f;

			float m_addAngle = 0.0f;

			//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}
