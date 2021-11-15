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
			//�h�A�̐F�̎��
			enum EnDoorColor
			{
				enDoorColor_Red,
				enDoorColor_Blue,
				enDoorColor_Green,
				enDoorColor_Yellow,
				enDoorColor_Purple,
				enDoorColor_White,
				enDoorColor_num
			};

			bool Start();
			void Update();

			void Execute();

			void PlayerTargetSetting();

			//�J��
			void Open();
			void Close();

			//�ʒu���擾
			Vector3 GetPosition() { return m_position; };

			/// @brief �v���C���[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �v���C���[�̎Q��
			void SetPlayer(nsPlayer::Player* pl) { m_player = pl; };
			/// @brief �G�l�~�[�ɃA�N�Z�X�ł���悤�ɂ���B
			/// @param pl �G�l�~�[�̎Q��
			void SetEnemy(nsEnemy::Enemy* enemy) { m_enemy = enemy; };
			/// @brief �h�A�̐F��ݒ�
			/// @param color �h�A�̐F
			void SetDoorColor(EnDoorColor color) { m_doorColor = color; }
			/// @brief �h�A�̐F���擾
			/// @return �h�A�̐F
			EnDoorColor GetDoorColor() { return m_doorColor; }

			/// @brief �����J���Ă��邩�ǂ�����ݒ�
			/// @param unlockFlag �����J���Ă��邩�ǂ����B
			void SetUnlockFlag(bool unlockFlag) { m_unlockFlag = unlockFlag; }

			/// @brief �����J���Ă��邩�ǂ������擾
			/// @return �����J���Ă��邩�ǂ���
			bool GetUnlockFlag() { return m_unlockFlag; }

			void SetPosition(Vector3 pos) { m_position = pos; };
			void SetDirection(Vector3 dir) { dir.Normalize(); m_direction = dir; };
		private:
			nsPlayer::Player* m_player = nullptr;
			nsEnemy::Enemy* m_enemy = nullptr;

			SkinModelRender* m_doorModel = nullptr;

			//�h�A�̐F
			EnDoorColor m_doorColor = enDoorColor_Red;

			//�����J���Ă��邩�ǂ���
			bool m_unlockFlag = false;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = Vector3::Zero;
			Quaternion m_qRot = Quaternion::Identity;

			//�v���C���[�ւ̌���
			Vector3 m_toPlayerDir = Vector3::Zero;

			//�h�A���J���Ă��邩�ǂ���
			bool m_openFlag = false;

			//�h�A��(�J����������肵��)�����Ă��邩�ǂ���
			bool m_moveFlag = false;

			//�h�A���O����J����ꂽ���A��납��J����ꂽ��
			bool m_isOpenFromForward = false;

			//�f�t�H���g�̃h�A�̊p�x
			float m_defaultAngle = 0.0f;
			//�J���Ƀf�t�H���g�̊p�x�ɉ�����p�x
			float m_addAngle = 0.0f;

			//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}
