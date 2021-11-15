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

			/// @brief 消えるかどうかのフラグを設定。
			/// @param disapperFlag 消えるかどうか
			void SetDisapperFlag(bool disapperFlag) { m_disapperFlag = disapperFlag; }

			/// @brief 消えるかどうかのフラグを設定。
			/// @return 消えるかどうか
			bool GetDisapperFlag() { return m_disapperFlag; }
		private:
			SkinModelRender* m_eyeWallModel = nullptr;
			//CharaConとの当たり判定に使用する静的物理オブジェクト
			PhysicsStaticObject m_physicsStaticObject;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_direction = Vector3::Zero;
			Vector3 m_scale = { 1.0f,1.0f,1.0f };

			//Disapper()関連
			float m_disapperSpeed = 0.0f;
			int m_disapperMoveCount = 0;

			//消えるかどうかのフラグ
			bool m_disapperFlag = false;
		};
	}
}

