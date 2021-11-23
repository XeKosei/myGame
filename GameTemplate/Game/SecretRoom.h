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
			//���f��
			SkinModelRender* m_secretRoomModel = nullptr;
			SkinModelRender* m_fakeWallModel = nullptr;
			//CharaCon�Ƃ̓����蔻��Ɏg�p����ÓI�����I�u�W�F�N�g
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}