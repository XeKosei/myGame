#pragma once
namespace nsHikageri
{
	namespace nsGimmick
	{
		class EyeWall : public IGameObject
		{
		public:
			~EyeWall();

			bool Start();

			void Update();

			void Disapper();

			Vector3 GetPosition() { return m_position; }
			void SetPosition(Vector3 pos) { m_position = pos; }

			Vector3 GetDirection() { return m_direction; }
			void SetDirection(Vector3 dir) { m_direction = dir; }

			/// @brief �����邩�ǂ����̃t���O��ݒ�B
			/// @param disapperFlag �����邩�ǂ���
			void SetDisapperFlag(bool disapperFlag) { m_disapperFlag = disapperFlag; }

			/// @brief �����邩�ǂ����̃t���O��ݒ�B
			/// @return �����邩�ǂ���
			bool GetDisapperFlag() { return m_disapperFlag; }
		private:
			SkinModelRender* m_eyeWallModel = nullptr;
			//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_physicsStaticObject;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = Vector3::Zero;
			Vector3 m_scale = { 1.0f,1.0f,1.0f };

			//Disapper()�֘A
			float m_disapperSpeed = 0.0f;
			int m_disapperMoveCount = 0;

			//�����邩�ǂ����̃t���O
			bool m_disapperFlag = false;
		};
	}
}

