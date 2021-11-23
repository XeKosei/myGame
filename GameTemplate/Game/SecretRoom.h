#pragma once
namespace nsHikageri
{
	namespace nsBackGround
	{
		class SecretRoom : public IGameObject
		{
		public:
			~SecretRoom();
			bool Start();
			void Update();

			SkinModelRender* GetSecretRoomModel() { return m_secretRoomModel; }
			SkinModelRender* GetFakeWallModel() { return m_fakeWallModel; }
		private:
			//モデル
			SkinModelRender* m_secretRoomModel = nullptr;
			SkinModelRender* m_fakeWallModel = nullptr;
			//CharaConとの当たり判定に使用する静的物理オブジェクト
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}