#pragma once
namespace nsHikageri
{
	namespace nsPlayer { class Player; }
	namespace nsBackGround
	{
		class SecretRoom : public IGameObject
		{
		public:
			~SecretRoom();
			bool Start();
			void Init(nsPlayer::Player* player) { m_player = player; };
			void Update();

			SkinModelRender* GetSecretRoomModel() { return m_secretRoomModel; }
			SkinModelRender* GetFakeWallModel() { return m_fakeWallModel; }
		private:
			nsPlayer::Player* m_player = nullptr;

			//モデル
			SkinModelRender* m_secretRoomModel = nullptr;
			SkinModelRender* m_fakeWallModel = nullptr;
			//CharaConとの当たり判定に使用する静的物理オブジェクト
			PhysicsStaticObject m_physicsStaticObject;
		};
	}
}