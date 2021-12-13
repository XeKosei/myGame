#pragma once
namespace nsHikageri
{
	namespace nsGameScene
	{
		class GameScene;
		class GameOver : public IGameObject
		{
		public:
			~GameOver();
			bool Start();
			void Update();

			void SetGameScene(GameScene* gameScene) { m_gameScene = gameScene; }
		private:
			//FontRender* m_gameOverFont = nullptr;
			SpriteRender* m_gameOverSprite = nullptr;
			GameScene* m_gameScene = nullptr;
			Vector4 m_gameOverSpriteColor = { 1.0f,1.0f,1.0f,1.0f };

			int m_gameOverExecuteCount = 0;
		};
	}
}