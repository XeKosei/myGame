#pragma once
namespace nsHikageri
{
	namespace nsGameScene
	{
		class GameScene;
		class GameClear : public IGameObject
		{
		public:
			~GameClear();
			bool Start();
			void Update();

			void SetGameScene(GameScene* gameScene) { m_gameScene = gameScene; }
		private:
			GameScene* m_gameScene = nullptr;

			SpriteRender* m_whiteSprite = nullptr;
			Vector4 m_whiteSpriteColor = {0.0f,0.0f,0.0f,0.0f};

			SpriteRender* m_titleNameSprite = nullptr;
			Vector4 m_titleNameColor = { 1.0f,1.0f,1.0f,1.0f };

			FontRender* m_clearFont = nullptr;
			Vector4 m_clearFontColor = { 0.0f,0.0f,0.0f,0.0f };

			int m_gameClearExecuteCount = 0;

		};
	}
}